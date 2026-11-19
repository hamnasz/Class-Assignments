// Small, targeted OOXML fixes applied to a .docx *before* docx-preview reads it.
//
// docx-preview is a good renderer but has three gaps that visibly change a document. Each is
// fixed here by editing the relevant XML part, so nothing depends on the library's internals:
//
//   1. Page-number fields. Footers/headers with PAGE / NUMPAGES come out empty (or, when Word
//      cached a result, frozen at the same number on every page). They are replaced with
//      placeholder tokens that docx-fidelity.js fills in per page after layout.
//   2. Bullets stored as Symbol / Wingdings private-use characters. Those glyphs only exist where
//      the Symbol font is installed, so bullets turn blank on phones and Linux. They are mapped
//      to ordinary Unicode bullets.
//   3. "Page break before" set directly on a paragraph is ignored (only the style-level
//      setting is read). It is turned into an explicit page break.
//
//   4. "Don't add space between paragraphs of the same style" (contextualSpacing), which is how
//      Word keeps list items tight, is ignored. The affected style ids are collected here and
//      docx-fidelity.js turns them into CSS.
//
//   5. Conditional table-style formatting (header row, banded rows, first column) is only applied
//      to rows/cells carrying a w:cnfStyle marker. Word often writes those; python-docx, pandoc
//      and others rely on the table's tblLook flags alone, so the formatting vanished. The
//      markers are derived from tblLook here, following Word's banding rules.
//   6. Even-page headers/footers are used on every second page whether or not the document turns
//      "different odd & even pages" on. LibreOffice always writes (empty) even-page parts, so its
//      files lost their header/footer on pages 2, 4, 6 ... Without the setting they are dropped.
//
// Everything is best effort: if anything goes wrong the original file is returned untouched.

const W = 'http://schemas.openxmlformats.org/wordprocessingml/2006/main';
const XML_NS = 'http://www.w3.org/XML/1998/namespace';

/** Placeholders (private-use characters) swapped for real numbers once pages exist. */
export const TOKEN = { PAGE: '\uE000PAGE\uE001', NUMPAGES: '\uE000NUMPAGES\uE001' };

const parse = (text) => {
  const doc = new DOMParser().parseFromString(text, 'application/xml');
  return doc.getElementsByTagName('parsererror').length ? null : doc;
};
const serialize = (doc) => {
  const xml = new XMLSerializer().serializeToString(doc);
  return xml.startsWith('<?xml') ? xml : `<?xml version="1.0" encoding="UTF-8" standalone="yes"?>\n${xml}`;
};
const child = (el, name) => [...el.children].find((c) => c.namespaceURI === W && c.localName === name) || null;
const all = (root, name) => [...root.getElementsByTagNameNS(W, name)];

function textRun(doc, text, rPr) {
  const r = doc.createElementNS(W, 'w:r');
  if (rPr) r.append(rPr.cloneNode(true));
  const t = doc.createElementNS(W, 'w:t');
  t.setAttributeNS(XML_NS, 'xml:space', 'preserve');
  t.textContent = text;
  r.append(t);
  return r;
}

// ---- 1. page-number fields -----------------------------------------------------------------

function fieldToken(instr) {
  const m = /^\s*(PAGE|NUMPAGES)\b([\s\S]*)$/i.exec(instr || '');
  if (!m) return null;
  // "\* roman", "\* alphabetic" ...: a number format we don't reproduce, so keep Word's cached text.
  if (/\\\*\s*(?!mergeformat|charformat)/i.test(m[2])) return null;
  return TOKEN[m[1].toUpperCase()];
}

function rewriteFields(doc) {
  let changed = false;
  for (const p of all(doc, 'p')) {
    // <w:fldSimple w:instr="PAGE">…cached result runs…</w:fldSimple>
    for (const f of all(p, 'fldSimple')) {
      const token = fieldToken(f.getAttributeNS(W, 'instr'));
      if (!token) continue;
      const firstRun = all(f, 'r')[0];
      f.replaceWith(textRun(doc, token, firstRun && child(firstRun, 'rPr')));
      changed = true;
    }
    // begin / instrText / separate / result / end, possibly nested and possibly all in one run.
    const stack = [];
    let touched = false;
    for (const node of [...p.getElementsByTagNameNS(W, '*')]) {
      const name = node.localName;
      if (name === 'fldChar') {
        const type = node.getAttributeNS(W, 'fldCharType');
        if (type === 'begin') stack.push({ instr: '', inResult: false, begin: node, doomed: [] });
        else if (type === 'separate' && stack.length) { const f = stack.at(-1); f.inResult = true; f.doomed.push(node); }
        else if (type === 'end' && stack.length) {
          const f = stack.pop();
          f.doomed.push(node);
          const token = fieldToken(f.instr);
          if (!token) continue;
          const t = doc.createElementNS(W, 'w:t');
          t.setAttributeNS(XML_NS, 'xml:space', 'preserve');
          t.textContent = token;
          f.begin.replaceWith(t);
          f.doomed.forEach((n) => n.remove());
          touched = changed = true;
        }
      } else if (stack.length) {
        const f = stack.at(-1);
        if (name === 'instrText') { f.instr += node.textContent; f.doomed.push(node); }
        else if (f.inResult && ['t', 'tab', 'br', 'noBreakHyphen', 'sym'].includes(name)) f.doomed.push(node);
      }
    }
    if (touched) for (const r of all(p, 'r')) if (![...r.children].some((c) => c.localName !== 'rPr')) r.remove();
  }
  return changed;
}

// ---- 2. Symbol / Wingdings bullets ---------------------------------------------------------

const GLYPHS = {
  symbol: { 0xF0B7: '\u2022' },
  wingdings: {
    0xF0A7: '\u25AA', 0xF0D8: '\u27A2', 0xF0FC: '\u2713', 0xF076: '\u2756', 0xF0A8: '\u25FB',
    0xF06C: '\u25CF', 0xF06E: '\u25A0', 0xF06F: '\u25A1', 0xF071: '\u2751', 0xF075: '\u25C6',
  },
};

function rewriteBullets(doc) {
  let changed = false;
  for (const lvl of all(doc, 'lvl')) {
    const text = child(lvl, 'lvlText');
    const val = text?.getAttributeNS(W, 'val');
    if (!val || [...val].length !== 1) continue;
    const rPr = child(lvl, 'rPr');
    const fonts = rPr && child(rPr, 'rFonts');
    if (!fonts) continue;
    const font = (fonts.getAttributeNS(W, 'ascii') || fonts.getAttributeNS(W, 'hAnsi') || '').toLowerCase();
    const table = font === 'symbol' ? GLYPHS.symbol : font.startsWith('wingdings') && !/[23]$/.test(font) ? GLYPHS.wingdings : null;
    if (!table) continue;
    const cp = val.codePointAt(0);
    const to = table[cp >= 0xF000 ? cp : 0xF000 | cp];   // some files store U+00B7 instead of U+F0B7
    if (!to) continue;
    text.setAttributeNS(W, 'w:val', to);
    fonts.remove();
    changed = true;
  }
  return changed;
}

// ---- 3. direct "page break before" ---------------------------------------------------------

function endsWithPageBreak(block) {
  if (block.localName !== 'p') return false;
  if (child(block, 'pPr') && child(child(block, 'pPr'), 'sectPr')) return true;   // section already ends the page
  const runs = all(block, 'r');
  const last = runs.at(-1);
  const br = last && [...last.children].filter((c) => c.localName !== 'rPr').at(-1);
  return !!br && br.localName === 'br' && br.getAttributeNS(W, 'type') === 'page';
}

function rewritePageBreakBefore(doc) {
  const body = all(doc, 'body')[0];
  if (!body) return false;
  let changed = false;
  for (const flag of all(doc, 'pageBreakBefore')) {
    if (/^(0|false|off)$/i.test(flag.getAttributeNS(W, 'val') || '')) continue;
    const pPr = flag.parentNode;
    const p = pPr?.parentNode;
    if (pPr?.localName !== 'pPr' || p?.localName !== 'p' || p.parentNode !== body) continue;   // Word ignores it inside tables
    const prev = p.previousElementSibling;
    if (!prev || endsWithPageBreak(prev)) continue;                    // already at the top of a page
    const run = doc.createElementNS(W, 'w:r');
    const br = doc.createElementNS(W, 'w:br');
    br.setAttributeNS(W, 'w:type', 'page');
    run.append(br);
    pPr.after(run);
    all(p, 'lastRenderedPageBreak').forEach((n) => n.remove());          // would double the break
    changed = true;
  }
  return changed;
}

// ---- 4. contextual spacing ---------------------------------------------------------------------

/** Ids of paragraph styles (including inherited) that switch contextual spacing on. */
function contextualSpacingStyles(doc) {
  const styles = new Map();
  for (const st of all(doc, 'style')) {
    if (st.getAttributeNS(W, 'type') !== 'paragraph') continue;
    const pPr = child(st, 'pPr');
    const flag = pPr && child(pPr, 'contextualSpacing');
    styles.set(st.getAttributeNS(W, 'styleId'), {
      base: child(st, 'basedOn')?.getAttributeNS(W, 'val') || null,
      own: flag ? !/^(0|false|off)$/i.test(flag.getAttributeNS(W, 'val') || '') : null,
    });
  }
  const resolve = (id, depth = 0) => {
    const st = styles.get(id);
    if (!st || depth > 20) return false;
    return st.own ?? (st.base ? resolve(st.base, depth + 1) : false);
  };
  return [...styles.keys()].filter((id) => resolve(id));
}

// ---- 5. conditional table styles ---------------------------------------------------------------

/** Ids of table styles (including inherited) that define conditional formatting (tblStylePr). */
function conditionalTableStyles(doc) {
  const styles = new Map();
  for (const st of all(doc, 'style')) {
    if (st.getAttributeNS(W, 'type') !== 'table') continue;
    styles.set(st.getAttributeNS(W, 'styleId'), {
      base: child(st, 'basedOn')?.getAttributeNS(W, 'val') || null,
      own: all(st, 'tblStylePr').length > 0,
    });
  }
  const resolve = (id, depth = 0) => {
    const st = styles.get(id);
    return !!st && depth < 20 && (st.own || (st.base ? resolve(st.base, depth + 1) : false));
  };
  return new Set([...styles.keys()].filter((id) => resolve(id)));
}

function setCnf(owner, propsName, attrs, insertAt) {
  if (!Object.keys(attrs).length) return false;
  let props = child(owner, propsName);
  if (!props) {
    props = owner.ownerDocument.createElementNS(W, `w:${propsName}`);
    owner.insertBefore(props, insertAt);
  }
  const cnf = owner.ownerDocument.createElementNS(W, 'w:cnfStyle');
  for (const [k, v] of Object.entries(attrs)) cnf.setAttributeNS(W, `w:${k}`, v);
  props.insertBefore(cnf, props.firstChild);
  return true;
}

function rewriteTableLook(doc, conditional) {
  let changed = false;
  for (const tbl of all(doc, 'tbl')) {
    const pr = child(tbl, 'tblPr');
    const styleId = pr && child(pr, 'tblStyle')?.getAttributeNS(W, 'val');
    const look = pr && child(pr, 'tblLook');
    if (!styleId || !look || !conditional.has(styleId) || all(tbl, 'cnfStyle').length) continue;   // Word already marked it
    const hex = parseInt(look.getAttributeNS(W, 'val') || '0', 16) || 0;
    const flag = (name, bit) => {
      const v = look.getAttributeNS(W, name);
      return v ? /^(1|true|on)$/i.test(v) : !!(hex & bit);
    };
    const first = flag('firstRow', 0x20), last = flag('lastRow', 0x40);
    const firstCol = flag('firstColumn', 0x80), lastCol = flag('lastColumn', 0x100);
    const bandRows = !flag('noHBand', 0x200), bandCols = !flag('noVBand', 0x400);

    const rows = [...tbl.children].filter((c) => c.localName === 'tr');
    rows.forEach((tr, ri) => {
      const isFirst = first && ri === 0;
      const isLast = last && ri === rows.length - 1 && rows.length > 1;
      const attrs = {};
      if (isFirst) attrs.firstRow = '1';
      if (isLast) attrs.lastRow = '1';
      if (bandRows && !isFirst && !isLast) attrs[(ri - (first ? 1 : 0)) % 2 === 0 ? 'oddHBand' : 'evenHBand'] = '1';
      const afterEx = [...tr.children].find((c) => c.localName !== 'tblPrEx') || null;
      changed = setCnf(tr, 'trPr', attrs, afterEx) || changed;

      const cells = [...tr.children].filter((c) => c.localName === 'tc');
      cells.forEach((tc, ci) => {
        const isFirstCol = firstCol && ci === 0;
        const isLastCol = lastCol && ci === cells.length - 1 && cells.length > 1;
        const cell = {};
        if (isFirstCol) cell.firstColumn = '1';
        if (isLastCol) cell.lastColumn = '1';
        if (bandCols && !isFirstCol && !isLastCol) cell[(ci - (firstCol ? 1 : 0)) % 2 === 0 ? 'oddVBand' : 'evenVBand'] = '1';
        changed = setCnf(tc, 'tcPr', cell, tc.firstChild) || changed;
      });
    });
  }
  return changed;
}

// ---- 6. even-page headers/footers ------------------------------------------------------------

function dropEvenReferences(doc) {
  let changed = false;
  for (const name of ['headerReference', 'footerReference']) {
    for (const ref of all(doc, name)) {
      if (ref.getAttributeNS(W, 'type') === 'even') { ref.remove(); changed = true; }
    }
  }
  return changed;
}

// ---- entry point -----------------------------------------------------------------------------

/**
 * Returns { buffer, contextualStyles }: an ArrayBuffer ready for docx-preview (the original, or a
 * patched copy) and the ids of paragraph styles that use contextual spacing.
 */
export async function prepareDocx(buffer, JSZip) {
  try {
    const zip = await JSZip.loadAsync(buffer);
    let dirty = false;
    let contextualStyles = [];

    const edit = async (name, fix, guard) => {
      const file = zip.file(name);
      if (!file) return;
      const text = await file.async('string');
      if (guard && !guard.test(text)) return;
      const doc = parse(text);
      if (doc && fix(doc)) { zip.file(name, serialize(doc)); dirty = true; }
    };

    for (const name of Object.keys(zip.files)) {
      if (/^word\/(header|footer)\d*\.xml$/i.test(name)) await edit(name, rewriteFields, /PAGE|fldSimple/i);
    }
    await edit('word/numbering.xml', rewriteBullets, /w:lvlText/);

    let conditional = new Set();
    const styles = zip.file('word/styles.xml');
    if (styles) {
      const text = await styles.async('string');
      const doc = /contextualSpacing|tblStylePr/.test(text) && parse(text);
      if (doc) {
        contextualStyles = contextualSpacingStyles(doc);
        conditional = conditionalTableStyles(doc);
      }
    }
    const settings = zip.file('word/settings.xml');
    const evenOdd = settings ? /<w:evenAndOddHeaders\b(?![^>]*w:val="(?:0|false|off)")/.test(await settings.async('string')) : false;
    await edit('word/document.xml',
      (doc) => [
        rewritePageBreakBefore(doc),
        conditional.size ? rewriteTableLook(doc, conditional) : false,
        evenOdd ? false : dropEvenReferences(doc),
      ].some(Boolean),
      new RegExp(`pageBreakBefore|${conditional.size ? 'w:tblLook|' : ''}${evenOdd ? '(?!)' : 'w:type="even"'}`));

    return { buffer: dirty ? await zip.generateAsync({ type: 'arraybuffer', compression: 'STORE' }) : buffer, contextualStyles };
  } catch (err) {
    console.warn('DOCX pre-processing skipped:', err);
    return { buffer, contextualStyles: [] };
  }
}
