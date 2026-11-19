import { el } from '../core/dom.js';
import { icon } from '../core/icons.js';
import { libs } from '../core/loader.js';
import { SpinnerLine } from '../components/states.js';

const MIN_SCALE = 0.05, MAX_SCALE = 4;
const CONCURRENCY = 2, MAX_RESIDENT = 8;
const MAX_PIXELS = 3 * 1024 * 1024, MAX_DIMENSION = 4096;
const clamp = (n, min, max) => Math.min(max, Math.max(min, n));
const cancelled = (err) => ['RenderingCancelledException', 'AbortException', 'AbortError'].includes(err?.name);

/** A small raster working set over lightweight, stable page placeholders.
 * PDF.js owns transport/range detection; only the reading window owns canvases and text layers.
 * A slot stays busy until cancelled work settles, so it never has two render tasks on one canvas.
 */
export async function render(node, ctx) {
  const scroll = el('div', { class: 'pdf-scroll', tabindex: '0', 'aria-label': `PDF: ${node.name}`, 'aria-busy': 'true' });
  const status = el('div', { class: 'pdf-status', role: 'status', 'aria-live': 'polite' }, SpinnerLine('Opening PDF…'));
  ctx.host.append(status, scroll);
  let disposed = false, loadingTask, doc, resizeTimer, resizeObserver, frame = 0;
  let revision = 0, active = 0, current = 1, manual = null, firstPaint = false;
  let slots = [], wanted = [], wantedSet = new Set();
  const events = new AbortController();
  const release = (s) => {
    s.renderTask?.cancel(); s.textTask?.cancel();
    if (s.canvas) { s.canvas.width = s.canvas.height = 0; s.canvas.remove(); s.canvas = null; }
    s.layer?.remove(); s.layer = null;
    s.ready = -1;
    s.el.dataset.state = 'waiting';
    if (!s.busy) { s.page?.cleanup(); s.page = null; }
  };
  // Register cleanup BEFORE awaiting imports or transport. Closing while loading is safe.
  ctx.onDispose(() => {
    disposed = true; revision++;
    clearTimeout(resizeTimer); cancelAnimationFrame(frame); events.abort();
    resizeObserver?.disconnect();
    for (const s of slots) release(s);
    // Destroy the loading task also aborts network work and destroys its document/worker.
    loadingTask?.destroy().catch(() => {});
  });
  const pdfjs = await libs.pdfjs();
  if (disposed || ctx.signal.aborted) return;
  loadingTask = pdfjs.getDocument({ url: ctx.contentUrl, rangeChunkSize: 64 * 1024 });
  doc = await loadingTask.promise;
  if (disposed) return;
  const first = await doc.getPage(1);
  if (disposed) return;
  const natural = first.getViewport({ scale: 1 });
  const total = doc.numPages;
  const room = () => {
    const css = getComputedStyle(scroll);
    return Math.max(1, scroll.clientWidth - parseFloat(css.paddingLeft) - parseFloat(css.paddingRight));
  };
  // Fit each page independently, including landscape/rotated pages discovered later.
  const scaleFor = (s) => manual ?? clamp(room() / s.width, MIN_SCALE, MAX_SCALE);
  function sizeSlot(s) {
    s.scale = scaleFor(s);
    s.el.style.width = `${s.width * s.scale}px`;
    s.el.style.height = `${s.height * s.scale}px`;
  }
  slots = Array.from({ length: total }, (_, i) => ({
    num: i + 1, width: natural.width, height: natural.height, ready: -1, busy: false,
    el: el('div', { class: 'pdf-page', id: `pdf-page-${i + 1}`, role: 'group', 'aria-label': `Page ${i + 1}`, dataset: { page: i + 1, state: 'waiting' } }),
  }));
  slots[0].page = first;
  slots.forEach(sizeSlot);
  const fragment = document.createDocumentFragment();
  for (const s of slots) fragment.append(s.el);
  scroll.append(fragment);

  const button = (name, label, fn) => el('button', { class: 'btn btn-icon', type: 'button', title: label, 'aria-label': label, html: icon(name), onClick: fn });
  const prev = button('chevron-left', 'Previous page', () => goTo(current - 1));
  const next = button('chevron', 'Next page', () => goTo(current + 1));
  const jump = el('input', { type: 'number', min: 1, max: total, value: 1, 'aria-label': 'Page number', inputmode: 'numeric' });
  const level = el('span', { class: 'tool-label pdf-level', 'aria-live': 'polite' });
  const zoomOut = button('zoom-out', 'Zoom out', () => zoom(clamp(scaleFor(slots[current - 1]) / 1.2, MIN_SCALE, MAX_SCALE)));
  const zoomIn = button('zoom-in', 'Zoom in', () => zoom(clamp(scaleFor(slots[current - 1]) * 1.2, MIN_SCALE, MAX_SCALE)));
  const fit = button('fit', 'Fit to width', () => zoom(null));
  ctx.toolbar.append(el('div', { class: 'pdf-controls', role: 'group', 'aria-label': 'PDF controls' }, [
    prev, jump, el('span', { class: 'tool-label' }, `of ${total}`), next,
    el('span', { class: 'tool-sep' }), zoomOut, level, zoomIn, fit,
  ]));
  function updateControls() {
    if (document.activeElement !== jump) jump.value = String(current);
    prev.disabled = current === 1; next.disabled = current === total;
    const scale = scaleFor(slots[current - 1]);
    const label = `${Math.round(scale * 100)}%`;
    if (level.textContent !== label) level.textContent = label;
    zoomOut.disabled = manual !== null && scale <= MIN_SCALE;
    zoomIn.disabled = scale >= MAX_SCALE;
    fit.classList.toggle('is-on', manual === null);
    fit.setAttribute('aria-pressed', String(manual === null));
  }
  // Binary search avoids walking hundreds of DOM nodes on each scroll event.
  function indexAt(y) {
    let lo = 0, hi = slots.length - 1;
    while (lo < hi) {
      const mid = Math.ceil((lo + hi) / 2);
      if (slots[mid].el.offsetTop <= y) lo = mid; else hi = mid - 1;
    }
    return lo;
  }
  function anchor() {
    let i = indexAt(scroll.scrollTop + 1);
    // In a page gap, anchor the next sheet with a fixed pixel inset. Scaling a
    // fraction of the preceding sheet would otherwise shift the reading position.
    if (i < total - 1 && scroll.scrollTop >= slots[i].el.offsetTop + slots[i].el.offsetHeight) i++;
    const s = slots[i], offset = scroll.scrollTop - s.el.offsetTop;
    return { s, fraction: Math.max(0, offset) / Math.max(1, s.el.offsetHeight), gap: Math.min(0, offset), left: scroll.scrollLeft };
  }
  function restore(a) {
    scroll.scrollTop = a.s.el.offsetTop + a.fraction * a.s.el.offsetHeight + a.gap;
    scroll.scrollLeft = a.left;
  }
  function goTo(n) {
    n = clamp(Math.round(n), 1, total);
    // Direct jumps avoid scheduling every intermediate page of a smooth scroll.
    scroll.scrollTop = slots[n - 1].el.offsetTop - 16;
    current = n; jump.value = String(n); updateControls(); schedule();
  }
  jump.addEventListener('change', () => goTo(Number(jump.value) || 1));
  jump.addEventListener('keydown', (e) => { if (e.key === 'Enter') { goTo(Number(jump.value) || 1); jump.blur(); } });

  function zoom(value) {
    if (disposed) return;
    const a = anchor();
    manual = value; revision++;
    for (const s of slots) { release(s); s.error = false; sizeSlot(s); }
    restore(a); updateControls(); schedule();
  }
  function requestSchedule() {
    if (!frame && !disposed) frame = requestAnimationFrame(() => { frame = 0; schedule(); });
  }
  function schedule() {
    if (disposed) return;
    const top = scroll.scrollTop, height = scroll.clientHeight;
    current = indexAt(top + Math.min(height * 0.25, 100)) + 1;
    updateControls();
    const visibleStart = indexAt(top + 1), visibleEnd = indexAt(top + height);
    const candidates = [];
    for (let i = Math.max(0, visibleStart - 1); i <= Math.min(total - 1, visibleEnd + 1); i++) candidates.push(slots[i]);
    wanted = candidates.sort((a, b) => {
      const priority = (s) => (s.num - 1 >= visibleStart && s.num - 1 <= visibleEnd ? 0 : total) + Math.abs(s.num - current);
      return priority(a) - priority(b);
    }).slice(0, MAX_RESIDENT);
    wantedSet = new Set(wanted);
    for (const s of slots) {
      if (!wantedSet.has(s) && (s.canvas || s.busy || s.page)) release(s);
    }
    pump();
  }
  function pump() {
    if (disposed) return;
    for (const s of wanted) {
      if (active >= CONCURRENCY) break;
      if (s.busy || s.ready === revision || s.error) continue;
      if (!firstPaint && active > 0) break;
      s.busy = true; active++;
      paint(s, revision).catch((err) => {
        if (disposed || cancelled(err)) return;
        s.error = true;
        s.el.dataset.state = 'error';
        const retry = el('button', { class: 'btn', type: 'button', onClick: () => { retry.remove(); s.error = false; pump(); } }, `Retry page ${s.num}`);
        s.el.append(retry);
        if (!firstPaint) { status.textContent = 'This page could not be rendered. Use Retry on the page.'; }
        console.error(`PDF page ${s.num}:`, err);
      }).finally(() => {
        s.busy = false; active--; s.renderTask = s.textTask = null;
        if (disposed || !wantedSet.has(s) || s.ready !== revision) {
          // Do not reset the page's error state: it needs an explicit retry.
          const error = s.el.dataset.state === 'error';
          release(s);
          if (error) s.el.dataset.state = 'error';
        }
        requestSchedule();
      });
    }
  }
  async function paint(s, mine) {
    const valid = () => !disposed && mine === revision && wantedSet.has(s);
    s.el.dataset.state = 'loading';
    const page = s.page ?? await doc.getPage(s.num);
    if (!valid()) { page.cleanup(); return; }
    s.page = page;
    const vp = page.getViewport({ scale: 1 });
    if (s.width !== vp.width || s.height !== vp.height) {
      const a = anchor();
      s.width = vp.width; s.height = vp.height; sizeSlot(s); restore(a);
      updateControls();
    }
    const viewport = page.getViewport({ scale: s.scale });
    const dpr = Math.min(window.devicePixelRatio || 1, 2,
      Math.sqrt(MAX_PIXELS / (viewport.width * viewport.height)),
      MAX_DIMENSION / viewport.width, MAX_DIMENSION / viewport.height);
    const canvas = el('canvas', { width: Math.max(1, Math.floor(viewport.width * dpr)), height: Math.max(1, Math.floor(viewport.height * dpr)), 'aria-hidden': 'true' });
    canvas.style.width = `${viewport.width}px`; canvas.style.height = `${viewport.height}px`;
    canvas.hidden = true;
    s.canvas = canvas; s.el.append(canvas);
    s.renderTask = page.render({ canvasContext: canvas.getContext('2d'), viewport, transform: [dpr, 0, 0, dpr, 0, 0] });
    await s.renderTask.promise;
    if (!valid()) return;
    canvas.hidden = false;
    s.el.dataset.state = 'rendered';
    // Mark visibility before text extraction: selecting text never delays first paint.
    if (!firstPaint) {
      firstPaint = true; status.textContent = 'PDF ready'; status.classList.add('visually-hidden');
      scroll.setAttribute('aria-busy', 'false');
    }
    const layer = el('div', { class: 'textLayer' });
    layer.style.setProperty('--total-scale-factor', String(s.scale * (page.userUnit || 1)));
    layer.style.setProperty('--scale-round-x', '1px');
    layer.style.setProperty('--scale-round-y', '1px');
    s.layer = layer; s.el.append(layer);
    s.textTask = new pdfjs.TextLayer({ textContentSource: page.streamTextContent(), container: layer, viewport });
    await s.textTask.render();
    if (valid()) s.ready = mine;
  }
  scroll.addEventListener('scroll', requestSchedule, { passive: true, signal: events.signal });
  let lastWidth = scroll.clientWidth;
  resizeObserver = new ResizeObserver(() => {
    requestSchedule();
    clearTimeout(resizeTimer);
    if (manual !== null || Math.abs(scroll.clientWidth - lastWidth) < 2) return;
    resizeTimer = setTimeout(() => {
      if (disposed) return;
      lastWidth = scroll.clientWidth;
      zoom(null);
    }, 240);
  });
  resizeObserver.observe(scroll);
  status.replaceChildren(SpinnerLine('Rendering first page…'));
  updateControls(); schedule();
}
