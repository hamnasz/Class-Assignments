// Post-render fixes for docx-preview output. Runs after the pages exist in the DOM.
// See docx-prepare.js for the matching fixes that have to happen on the file itself.

import { TOKEN } from './docx-prepare.js';

const LINK_SCHEMES = new Set(['http:', 'https:', 'mailto:', 'tel:']);
const GENERIC = /\b(serif|sans-serif|monospace|cursive|fantasy|system-ui)\b/i;

// ---- fonts -----------------------------------------------------------------------------------

/** A font name the browser doesn't know would otherwise fall back to Times; pick a sane generic. */
function genericFor(stack) {
  const first = stack.split(',')[0].toLowerCase();
  if (/courier|consolas|monaco|menlo|lucida console|mono|fixed/.test(first)) return 'monospace';
  if (/times|cambria|georgia|garamond|palatino|book antiqua|bookman|century(?! gothic)|constantia|baskerville|didot|minion|caslon|(^|[^s])serif/.test(first)) return 'serif';
  return 'sans-serif';
}
const withGeneric = (stack) => (/var\(/.test(stack) || GENERIC.test(stack) ? stack : `${stack.trim()}, ${genericFor(stack)}`);

function addFontFallbacks(styleHost, docHost) {
  for (const style of styleHost.querySelectorAll('style')) {
    // A border with size 0 comes out as "null solid null" (invalid, dropped); Word draws a hairline.
    style.textContent = style.textContent.replace(/(border[\w-]*\s*:\s*)null solid null/g, '$10.5pt solid currentColor').replace(
      /((?:font-family|--docx-[\w-]*font)\s*:\s*)([^;}]+)/g,
      (_, head, stack) => head + withGeneric(stack),
    );
  }
  for (const node of docHost.querySelectorAll('[style*="font-family"]')) {
    node.style.fontFamily = withGeneric(node.style.fontFamily);
  }
}

/**
 * docx-preview applies the document's default font and size to text spans only. Everything else
 * (list markers, empty paragraphs) would inherit the portal's own typography, so give the page
 * itself the document's defaults.
 */
function applyDocumentDefaults(styleHost) {
  const css = [...styleHost.querySelectorAll('style')].map((s) => s.textContent).join('\n');
  const rule = [...css.matchAll(/\.docx\s+span\s*\{([^}]*)\}/g)].map((m) => m[1]).find((r) => /font-(family|size)/.test(r)) || '';
  const pick = (prop) => new RegExp(`${prop}\\s*:\\s*([^;]+)`).exec(rule)?.[1].trim();
  // With no defaults in the file, Word itself falls back to Times New Roman 10pt.
  const family = pick('font-family') || "'Times New Roman', Times, serif";
  const size = pick('font-size') || '10pt';
  const style = document.createElement('style');
  style.textContent = `.docx-wrapper > section.docx { font-family: ${family}; font-size: ${size}; }`;
  styleHost.append(style);
}

/** Word's "don't add space between paragraphs of the same style" (lists stay tight). */
function applyContextualSpacing(styleHost, ids) {
  const rules = ids
    .filter((id) => /^[\w-]+$/.test(id))
    .map((id) => {
      const cls = `p.docx_${id.toLowerCase()}`;
      return `.docx-wrapper ${cls}:has(+ ${cls}) { margin-bottom: 0; } .docx-wrapper ${cls} + ${cls} { margin-top: 0; }`;
    });
  if (!rules.length) return;
  const style = document.createElement('style');
  style.textContent = rules.join('\n');
  styleHost.append(style);
}

// ---- links -----------------------------------------------------------------------------------

/** Make links safe and keep them from navigating the portal away or colliding with its router. */
function hardenLinks(docHost) {
  for (const a of docHost.querySelectorAll('a[href]')) {
    const href = a.getAttribute('href');
    if (href.startsWith('#')) {                       // bookmark inside the document
      a.dataset.docxAnchor = href.slice(1);
      a.removeAttribute('href');
      a.setAttribute('role', 'link');
      a.tabIndex = 0;
      continue;
    }
    let url;
    try { url = new URL(href, location.href); } catch { /* malformed */ }
    if (!url || !LINK_SCHEMES.has(url.protocol)) { a.removeAttribute('href'); continue; }   // e.g. javascript:
    a.target = '_blank';
    a.rel = 'noopener noreferrer';
  }
  const jump = (a) => {
    const id = a.dataset.docxAnchor;
    let id2 = id;
    try { id2 = decodeURIComponent(id); } catch { /* keep raw */ }
    const target = [...docHost.querySelectorAll('[id]')].find((n) => n.id === id || n.id === id2);
    target?.scrollIntoView({ behavior: 'smooth', block: 'start' });
  };
  docHost.addEventListener('click', (e) => {
    const a = e.target.closest?.('[data-docx-anchor]');
    if (a) { e.preventDefault(); jump(a); }
  });
  docHost.addEventListener('keydown', (e) => {
    const a = e.target.closest?.('[data-docx-anchor]');
    if (a && e.key === 'Enter') { e.preventDefault(); jump(a); }
  });
}

// ---- pagination --------------------------------------------------------------------------------

const isHeadingLike = (n) => n.tagName === 'P' && /(^|[\s_-])(heading|title|subtitle|caption)/i.test(n.className);

/**
 * docx-preview only starts a new page at explicit breaks and at Word's saved "last rendered page
 * break" hints. Files from Google Docs, LibreOffice, Pages or scripts carry no hints, so a
 * 10-page document would show as one very tall sheet. Where a page is clearly longer than its
 * paper size, split it between blocks (never inside a paragraph or table), like Word would.
 */
function paginate(wrapper) {
  for (const page of [...wrapper.querySelectorAll(':scope > section.docx')]) {
    const article = page.querySelector(':scope > article');
    if (!article || article.children.length < 2) continue;
    const cs = getComputedStyle(page);
    if (getComputedStyle(article).columnCount !== 'auto') continue;           // multi-column section: leave alone
    const limit = parseFloat(cs.minHeight) - parseFloat(cs.paddingTop) - parseFloat(cs.paddingBottom);
    const box = article.getBoundingClientRect();
    if (!(limit > 0) || box.height <= limit * 1.06) continue;                   // fits (small overrun = font differences)

    const blocks = [...article.children];
    const tops = blocks.map((b) => b.getBoundingClientRect().top);
    const advance = blocks.map((_, i) => (i < blocks.length - 1 ? tops[i + 1] : box.bottom) - tops[i]);
    const size = (list) => list.reduce((sum, b) => sum + advance[blocks.indexOf(b)], 0);

    const groups = [];
    let current = [];
    for (const block of blocks) {
      if (current.length && size(current) + advance[blocks.indexOf(block)] > limit) {
        const carry = [];
        while (current.length > 1 && isHeadingLike(current.at(-1))) carry.unshift(current.pop());   // no stranded headings
        groups.push(current);
        current = carry;
      }
      current.push(block);
    }
    groups.push(current);

    let previous = page;
    for (const group of groups.slice(1)) {
      const next = page.cloneNode(false);
      const body = article.cloneNode(false);
      for (const part of page.children) {
        if (part === article) next.append(body);
        else next.append(part.cloneNode(true));     // header / footer repeat on every page
      }
      body.append(...group);
      previous.after(next);
      previous = next;
    }
  }
}

// ---- page numbers ------------------------------------------------------------------------------

function fillPageNumbers(wrapper) {
  const pages = [...wrapper.querySelectorAll(':scope > section.docx')];
  if (!wrapper.textContent.includes('\uE000')) return pages.length;
  pages.forEach((page, i) => {
    for (const part of page.querySelectorAll(':scope > header, :scope > footer')) {
      const walker = document.createTreeWalker(part, NodeFilter.SHOW_TEXT);
      for (let n = walker.nextNode(); n; n = walker.nextNode()) {
        if (!n.nodeValue.includes('\uE000')) continue;
        n.nodeValue = n.nodeValue.replaceAll(TOKEN.PAGE, String(i + 1)).replaceAll(TOKEN.NUMPAGES, String(pages.length));
      }
    }
  });
  return pages.length;
}

// ---- entry point -------------------------------------------------------------------------------

async function settle(root) {
  void root.offsetHeight;                                                    // start loading the fonts in use
  const wait = (p) => Promise.race([p, new Promise((r) => setTimeout(r, 4000))]);
  await wait(document.fonts?.ready);
  await wait(Promise.all([...root.querySelectorAll('img')].map((i) => i.decode?.().catch(() => {}))));
}

/** Returns the number of pages shown. */
export async function polishDocument({ wrapper, styleHost, docHost, contextualStyles = [] }) {
  addFontFallbacks(styleHost, docHost);
  applyDocumentDefaults(styleHost);
  applyContextualSpacing(styleHost, contextualStyles);
  hardenLinks(docHost);
  await settle(docHost);
  paginate(wrapper);
  return fillPageNumbers(wrapper);
}
