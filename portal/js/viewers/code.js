import { el } from '../core/dom.js';
import { icon } from '../core/icons.js';
import { libs } from '../core/loader.js';

const HIGHLIGHT_LIMIT = 300_000;      // characters; beyond this the file is shown without colouring

/** Splits highlight.js output into one HTML string per line, re-opening spans that cross a line break. */
export function splitLines(html) {
  const lines = [];
  const open = [];
  let current = '';
  for (const [, openTag, closeTag, newline, text] of html.matchAll(/(<span[^>]*>)|(<\/span>)|(\n)|([^<\n]+|<)/g)) {
    if (openTag) { open.push(openTag); current += openTag; }
    else if (closeTag) { open.pop(); current += closeTag; }
    else if (newline) { lines.push(current + '</span>'.repeat(open.length)); current = open.join(''); }
    else current += text;
  }
  lines.push(current + '</span>'.repeat(open.length));
  return lines;
}

const escapeHtml = (s) => s.replace(/[&<>]/g, (c) => ({ '&': '&amp;', '<': '&lt;', '>': '&gt;' }[c]));

async function copyText(text) {
  try { await navigator.clipboard.writeText(text); return true; } catch { /* fall through */ }
  const area = el('textarea', { style: 'position:fixed;opacity:0' }, text);
  document.body.append(area); area.select();
  let ok = false;
  try { ok = document.execCommand('copy'); } catch { /* ignore */ }
  area.remove();
  return ok;
}

/** Shared by source files (numbers on, no wrapping) and plain text (numbers off, wrapping on). */
export async function renderCode(node, ctx, { lang, numbers, wrap }) {
  const [text, { hljs }] = await Promise.all([fetch(ctx.contentUrl, { signal: ctx.signal }).then((r) => { if (!r.ok) throw new Error(`HTTP ${r.status}`); return r.text(); }), lang ? libs.highlight() : {}]);

  let html;
  if (lang && hljs && text.length <= HIGHLIGHT_LIMIT) {
    try { html = hljs.highlight(text, { language: lang, ignoreIllegals: true }).value; } catch { html = null; }
  }
  const lines = html ? splitLines(html) : text.split('\n').map(escapeHtml);
  if (lines.length > 1 && lines.at(-1) === '') lines.pop();                       // trailing newline is not a line

  const code = el('code', { class: 'hljs code-lines' });
  code.innerHTML = lines.map((l) => `<span class="code-line">${l}</span>`).join('');
  const view = el('div', { class: 'code-view', tabindex: '0', style: `--digits:${String(lines.length).length}` }, el('pre', {}, code));
  ctx.host.append(view);

  const state = { numbers, wrap };
  const apply = () => {
    view.classList.toggle('has-numbers', state.numbers);
    view.classList.toggle('is-wrapped', state.wrap);
    wrapBtn.classList.toggle('is-on', state.wrap); wrapBtn.setAttribute('aria-pressed', String(state.wrap));
    numBtn.classList.toggle('is-on', state.numbers); numBtn.setAttribute('aria-pressed', String(state.numbers));
  };
  const wrapBtn = el('button', { class: 'btn btn-icon', type: 'button', title: 'Wrap long lines', 'aria-label': 'Wrap long lines', html: icon('wrap'), onClick: () => { state.wrap = !state.wrap; apply(); } });
  const numBtn = el('button', { class: 'btn btn-icon', type: 'button', title: 'Line numbers', 'aria-label': 'Line numbers', html: icon('hash'), onClick: () => { state.numbers = !state.numbers; apply(); } });
  const copyLabel = el('span', {}, 'Copy');
  const copyBtn = el('button', { class: 'btn', type: 'button', title: 'Copy the whole file' }, [el('span', { class: 'icon', html: icon('copy') }), copyLabel]);
  let timer;
  copyBtn.addEventListener('click', async () => {
    const ok = await copyText(text);
    copyBtn.firstChild.innerHTML = icon(ok ? 'check' : 'warning').replace(/^<span[^>]*>|<\/span>$/g, '');
    copyLabel.textContent = ok ? 'Copied' : 'Copy failed';
    clearTimeout(timer);
    timer = setTimeout(() => { copyBtn.firstChild.innerHTML = icon('copy').replace(/^<span[^>]*>|<\/span>$/g, ''); copyLabel.textContent = 'Copy'; }, 1600);
  });
  ctx.onDispose(() => clearTimeout(timer));
  const info = `${lines.length.toLocaleString('en')} line${lines.length === 1 ? '' : 's'}`;
  ctx.toolbar.append(el('span', { class: 'tool-chip' }, lang ? node.type.label : 'Plain text'), el('span', { class: 'tool-chip' }, info), el('span', { class: 'tool-sep' }), numBtn, wrapBtn, el('span', { class: 'tool-sep' }), copyBtn);
  apply();
}

export const render = (node, ctx) => renderCode(node, ctx, { lang: node.type.lang, numbers: true, wrap: false });
