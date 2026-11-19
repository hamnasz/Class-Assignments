import { el } from '../core/dom.js';
import { libs } from '../core/loader.js';
import { prepareDocx } from './docx-prepare.js';
import { polishDocument } from './docx-fidelity.js';

// docx-preview options. Word's saved "last rendered page break" hints stay ignored: with them on,
// the library drops whole sections from some files (a landscape section vanished in testing), and
// the hints go stale when a file is edited elsewhere. Pages therefore break at explicit page and
// section breaks, and docx-fidelity.js splits any page that overflows its paper size.
// experimental enables tab-stop layout (table-of-contents leaders, right-aligned columns).
const OPTIONS = {
  className: 'docx', inWrapper: true, breakPages: true, ignoreLastRenderedPageBreak: true,
  experimental: true, useBase64URL: true,
  renderHeaders: true, renderFooters: true, renderFootnotes: true, renderEndnotes: true,
};
const MIN_ZOOM = 0.25;
const MAX_ZOOM = 3;

export async function render(node, ctx) {
  const [{ docx, JSZip }, res] = await Promise.all([libs.docx(), fetch(ctx.contentUrl, { signal: ctx.signal })]);
  if (ctx.signal.aborted) return;
  if (!res.ok) throw new Error(`The document could not be downloaded (HTTP ${res.status}).`);
  const { buffer, contextualStyles } = await prepareDocx(await res.arrayBuffer(), JSZip);

  if (ctx.signal.aborted) return;

  // docx-preview empties both containers it is given and puts its <style> elements in the style
  // container. The style container must therefore NOT live inside the document container, or it is
  // detached from the page by that very call and every generated stylesheet is silently lost.
  const styleHost = el('div', { class: 'docx-styles' });
  const docHost = el('div', { class: 'docx-host' });
  const stage = el('div', { class: 'docx-stage' }, docHost);
  const scroll = el('div', { class: 'docx-scroll' }, [styleHost, stage]);

  const zoomOut = el('button', { class: 'btn btn-icon', 'aria-label': 'Zoom out', text: '\u2212' });
  const zoomIn = el('button', { class: 'btn btn-icon', 'aria-label': 'Zoom in', text: '+' });
  const fit = el('button', { class: 'btn', 'aria-label': 'Fit to width', text: 'Fit' });
  const level = el('span', { class: 'docx-zoom', 'aria-live': 'polite' }, '100%');
  const count = el('span');
  const controls = el('div', { class: 'pdf-controls docx-controls' }, [zoomOut, level, zoomIn, fit, el('span', { class: 'tool-sep' }), count]);
  ctx.toolbar.append(controls);
  ctx.host.append(scroll);

  await docx.renderAsync(buffer, docHost, styleHost, OPTIONS);
  if (ctx.signal.aborted) return;
  const wrapper = docHost.querySelector('.docx-wrapper');
  if (!wrapper) throw new Error('This document has no content that can be previewed.');
  const pages = await polishDocument({ wrapper, styleHost, docHost, contextualStyles });
  if (ctx.signal.aborted) return;
  count.textContent = `${pages} page${pages === 1 ? '' : 's'}`;

  // Pages are fixed-size sheets (Word's real paper size). To fit narrow screens they are scaled
  // as a whole with a transform: layout is computed at 100%, so line and page breaks never change.
  let manual = null;                                      // null = fit to width
  const current = () => {
    if (manual) return manual;
    const cs = getComputedStyle(scroll);
    const room = scroll.clientWidth - parseFloat(cs.paddingLeft) - parseFloat(cs.paddingRight);
    return Math.min(1, room / (docHost.offsetWidth || 1));
  };
  const apply = () => {
    const s = current();
    docHost.style.transform = s === 1 ? '' : `scale(${s})`;
    stage.style.width = `${docHost.offsetWidth * s}px`;
    stage.style.height = `${docHost.offsetHeight * s}px`;
    level.textContent = `${Math.round(s * 100)}%`;
    fit.setAttribute('aria-pressed', String(!manual));
  };
  zoomOut.addEventListener('click', () => { manual = Math.max(MIN_ZOOM, current() / 1.25); apply(); });
  zoomIn.addEventListener('click', () => { manual = Math.min(MAX_ZOOM, current() * 1.25); apply(); });
  fit.addEventListener('click', () => { manual = null; apply(); });
  if (typeof ResizeObserver === 'function') {
    const watch = new ResizeObserver(apply);
    watch.observe(scroll);
    watch.observe(docHost);
    ctx.onDispose(() => watch.disconnect());
  } else {
    window.addEventListener('resize', apply);
    ctx.onDispose(() => window.removeEventListener('resize', apply));
  }
  apply();
}
