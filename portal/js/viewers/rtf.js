import { el } from '../core/dom.js';

// A small RTF reader: enough to show a document the way its author formatted it. Text, character
// formatting (bold, italic, underline, strike, size, colour, highlight, font), paragraphs (alignment,
// indents, spacing), tabs, list numbering text, hyperlinks, tables and Unicode / code-page text.
// Images and other embedded objects are skipped (the viewer says so).

const SKIP = new Set([
  'fonttbl', 'colortbl', 'stylesheet', 'info', 'header', 'headerl', 'headerr', 'headerf', 'footer', 'footerl', 'footerr', 'footerf',
  'footnote', 'themedata', 'colorschememapping', 'latentstyles', 'datastore', 'xmlnstbl', 'listtable', 'listoverridetable',
  'rsidtbl', 'generator', 'pgdsctbl', 'revtbl', 'template', 'shpinst', 'shprslt', 'pict', 'object', 'bkmkstart', 'bkmkend',
]);
const MEDIA = new Set(['pict', 'object', 'shpinst']);
const SYMBOLS = { bullet: '\u2022', endash: '\u2013', emdash: '\u2014', lquote: '\u2018', rquote: '\u2019', ldblquote: '\u201c', rdblquote: '\u201d', emspace: '\u2003', enspace: '\u2002', qmspace: '\u2005', tab: '\u2003', '~': '\u00a0', _: '\u2011', '-': '' };
const CODEPAGES = { 932: 'shift_jis', 936: 'gbk', 949: 'euc-kr', 950: 'big5', 65001: 'utf-8', 10000: 'macintosh' };
const esc = (s) => s.replace(/[&<>"]/g, (c) => ({ '&': '&amp;', '<': '&lt;', '>': '&gt;', '"': '&quot;' }[c]));
const SAFE_LINK = /^(https?:|mailto:)/i;

function genericFor(name) {
  if (/courier|consolas|mono/i.test(name)) return 'monospace';
  if (/times|cambria|georgia|garamond|palatino|serif$/i.test(name) && !/sans/i.test(name)) return 'serif';
  return 'sans-serif';
}

export function rtfToHtml(src) {
  const out = [];
  let tableRows = [];
  let hadMedia = false;

  const fonts = {};
  const colors = [];                // index 0 is the "auto" entry before the first ';'
  let codepage = 'windows-1252';
  let st = { skip: false, dest: '', b: false, i: false, u: false, strike: false, caps: false, vert: '', fs: 0, color: null, hl: null, font: null, uc: 1, link: null };
  const stack = [];

  let runs = [];               // html of the paragraph being built
  let pp = {};                 // paragraph properties
  let row = null;              // { cells: [] } while inside a table row
  let cellParas = [];
  let fontBuf = '', fontNo = null, colorCur = {};
  let fieldInst = '';
  let bytes = [];
  let pendingSkip = 0;

  const pushBlock = (html) => {
    if (row) { cellParas.push(html); return; }
    if (tableRows.length) { out.push(`<table>${tableRows.join('')}</table>`); tableRows = []; }
    out.push(html);
  };
  const paraStyle = () => {
    const s = [];
    if (pp.align) s.push(`text-align:${pp.align}`);
    if (pp.li) s.push(`margin-left:${pp.li / 20}pt`);
    if (pp.ri) s.push(`margin-right:${pp.ri / 20}pt`);
    if (pp.fi) s.push(`text-indent:${pp.fi / 20}pt`);
    if (pp.sb) s.push(`margin-top:${pp.sb / 20}pt`);
    if (pp.sa != null) s.push(`margin-bottom:${pp.sa / 20}pt`);
    return s.length ? ` style="${s.join(';')}"` : '';
  };
  const endParagraph = () => { pushBlock(`<p${paraStyle()}>${runs.join('')}</p>`); runs = []; };

  const runStyle = () => {
    const s = [];
    if (st.b) s.push('font-weight:700');
    if (st.i) s.push('font-style:italic');
    const deco = [st.u && 'underline', st.strike && 'line-through'].filter(Boolean).join(' ');
    if (deco) s.push(`text-decoration:${deco}`);
    if (st.caps) s.push('text-transform:uppercase');
    if (st.vert) s.push(`vertical-align:${st.vert}`);
    if (st.fs) s.push(`font-size:${st.vert ? (st.fs / 2) * 0.7 : st.fs / 2}pt`);
    if (st.color != null && colors[st.color]) s.push(`color:${colors[st.color]}`);
    if (st.hl != null && colors[st.hl]) s.push(`background:${colors[st.hl]}`);
    if (st.font != null && fonts[st.font]) s.push(`font-family:'${esc(fonts[st.font])}',${genericFor(fonts[st.font])}`);
    return s.join(';');
  };
  const emit = (text) => {
    if (!text) return;
    if (st.skip) return;
    if (st.dest === 'fonttbl') {
      for (const ch of text) { if (ch === ';') { if (fontNo != null && fontBuf.trim()) fonts[fontNo] = fontBuf.trim(); fontBuf = ''; } else fontBuf += ch; }
      return;
    }
    if (st.dest === 'colortbl') return;
    if (st.dest === 'fldinst') { fieldInst += text; return; }
    const style = runStyle();
    let html = esc(text);
    if (style) html = `<span style="${style}">${html}</span>`;
    if (st.link && SAFE_LINK.test(st.link)) html = `<a href="${esc(st.link)}" target="_blank" rel="noopener noreferrer">${html}</a>`;
    runs.push(html);
  };
  const flushBytes = () => {
    if (!bytes.length) return;
    let text;
    try { text = new TextDecoder(codepage).decode(new Uint8Array(bytes)); } catch { text = new TextDecoder('windows-1252').decode(new Uint8Array(bytes)); }
    bytes = [];
    emit(text);
  };
  /** Index of the "}" that closes the group we are in (skips escaped braces). */
  const groupEnd = (from) => {
    let depth = 1;
    for (let k = from; k < src.length; k++) {
      const c = src.charCodeAt(k);
      if (c === 92) k++;                      // backslash: skip the escaped character
      else if (c === 123) depth++;
      else if (c === 125 && --depth === 0) return k;
    }
    return src.length;
  };

  const n = src.length;
  let i = 0;
  while (i < n) {
    const ch = src[i];
    if (ch === '{') { flushBytes(); stack.push({ ...st }); i++; continue; }
    if (ch === '}') {
      flushBytes();
      if (st.dest === 'colortbl') { /* palette complete */ }
      st = stack.pop() || st;
      i++; continue;
    }
    if (ch === '\r' || ch === '\n') { i++; continue; }
    if (ch !== '\\') {
      let j = i;
      while (j < n && src[j] !== '\\' && src[j] !== '{' && src[j] !== '}' && src[j] !== '\n' && src[j] !== '\r') j++;
      flushBytes();
      let chunk = src.slice(i, j);
      if (pendingSkip > 0) { const cut = Math.min(pendingSkip, chunk.length); chunk = chunk.slice(cut); pendingSkip -= cut; }
      if (st.dest === 'colortbl') { if (chunk.includes(';')) { colors.push(colorCur.r != null ? `rgb(${colorCur.r},${colorCur.g ?? 0},${colorCur.b ?? 0})` : null); colorCur = {}; } }
      else emit(chunk);
      i = j; continue;
    }

    // control word or symbol
    const next = src[i + 1];
    if (next === "'") {                                    // \'hh : one byte in the document's code page
      const byte = parseInt(src.slice(i + 2, i + 4), 16);
      i += 4;
      if (pendingSkip > 0) { pendingSkip--; continue; }
      if (!Number.isNaN(byte) && !st.skip) bytes.push(byte);
      continue;
    }
    flushBytes();
    if (!/[a-zA-Z]/.test(next || '')) {                    // control symbol
      i += 2;
      if (next === '\\' || next === '{' || next === '}') emit(next);
      else if (next === '*') st.starred = true;
      else if (next === '\n' || next === '\r') { if (!st.skip) endParagraph(); }
      else if (SYMBOLS[next] != null) emit(SYMBOLS[next]);
      continue;
    }
    const m = /\\([a-zA-Z]+)(-?\d+)? ?/y;
    m.lastIndex = i;
    const [whole, word, param] = m.exec(src);
    i += whole.length;
    const num = param == null ? null : parseInt(param, 10);

    if (st.starred) {                                      // {\* ...}: an optional destination, skipped unless we know it
      st.starred = false;
      if (word === 'fldinst') st.dest = 'fldinst';
      else { st.skip = true; i = groupEnd(i); continue; }
    }
    if (SKIP.has(word)) {
      if (word === 'fonttbl' || word === 'colortbl') { st.dest = word; if (word === 'colortbl') colorCur = {}; }
      else { if (MEDIA.has(word)) hadMedia = true; st.skip = true; i = groupEnd(i); continue; }
    }
    if (st.skip) continue;

    switch (word) {
      case 'ansicpg': codepage = CODEPAGES[num] || (num >= 1250 && num <= 1258 ? `windows-${num}` : 'windows-1252'); break;
      case 'mac': codepage = 'macintosh'; break;
      case 'par': case 'sect': endParagraph(); break;
      case 'line': runs.push('<br>'); break;
      case 'page': break;
      case 'pard': pp = {}; break;
      case 'qc': pp.align = 'center'; break;
      case 'qr': pp.align = 'right'; break;
      case 'qj': pp.align = 'justify'; break;
      case 'ql': pp.align = 'left'; break;
      case 'li': case 'ri': case 'fi': case 'sb': case 'sa': pp[word] = num || 0; break;
      case 'plain': Object.assign(st, { b: false, i: false, u: false, strike: false, caps: false, vert: '', fs: 0, color: null, hl: null, font: null }); break;
      case 'b': st.b = num !== 0; break;
      case 'i': st.i = num !== 0; break;
      case 'ul': case 'uld': case 'uldb': case 'ulw': st.u = num !== 0; break;
      case 'ulnone': st.u = false; break;
      case 'strike': case 'striked': st.strike = num !== 0; break;
      case 'caps': st.caps = num !== 0; break;
      case 'super': st.vert = 'super'; break;
      case 'sub': st.vert = 'sub'; break;
      case 'nosupersub': st.vert = ''; break;
      case 'fs': st.fs = num || 0; break;
      case 'cf': st.color = num; break;
      case 'highlight': case 'cb': st.hl = num; break;
      case 'f':
        if (st.dest === 'fonttbl') { fontNo = num; fontBuf = ''; } else st.font = num;
        break;
      case 'red': case 'green': case 'blue': if (st.dest === 'colortbl') colorCur[word[0]] = num; break;
      case 'uc': st.uc = num ?? 1; break;
      case 'u': {
        const code = num < 0 ? num + 65536 : num;
        emit(String.fromCharCode(code));
        pendingSkip = st.uc;
        break;
      }
      case 'tab': emit(SYMBOLS.tab); break;
      case 'field': fieldInst = ''; break;
      case 'fldrslt': {
        const link = /HYPERLINK\s+"([^"]+)"/i.exec(fieldInst);
        if (link) st.link = link[1];
        break;
      }
      case 'trowd': row = { cells: [] }; cellParas = []; runs = []; break;
      case 'cell': {
        if (!row) { endParagraph(); break; }
        if (runs.length) endParagraph();
        row.cells.push(cellParas.join('')); cellParas = [];
        break;
      }
      case 'row': {
        if (!row) break;
        tableRows.push(`<tr>${row.cells.map((c) => `<td>${c || '<p></p>'}</td>`).join('')}</tr>`);
        row = null; cellParas = []; runs = [];
        break;
      }
      default:
        if (SYMBOLS[word] != null) emit(SYMBOLS[word]);
    }
  }
  if (runs.length) endParagraph();
  if (tableRows.length) out.push(`<table>${tableRows.join('')}</table>`);
  return { html: out.join(''), hadMedia };
}

export async function render(node, ctx) {
  const res = await fetch(ctx.contentUrl, { signal: ctx.signal });
  if (!res.ok) throw new Error(`HTTP ${res.status}`);
  // RTF is 7-bit ASCII with escapes, so Latin-1 decoding is lossless.
  const src = new TextDecoder('latin1').decode(await res.arrayBuffer());
  if (!/^\s*\{\\rtf/.test(src)) throw new Error('Not an RTF file');
  const { html, hadMedia } = rtfToHtml(src);
  const doc = el('div', { class: 'rtf-doc' });
  doc.innerHTML = html || '<p><em>This document has no readable text.</em></p>';
  const scroll = el('div', { class: 'rtf-scroll' }, [doc, hadMedia ? el('p', { class: 'rtf-note' }, 'Images and embedded objects in RTF files aren\u2019t shown here.') : null]);
  scroll.style.flex = '1 1 0';
  ctx.host.append(scroll);
}
