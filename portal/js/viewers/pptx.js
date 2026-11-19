import { el } from '../core/dom.js';
import { icon } from '../core/icons.js';
import { libs } from '../core/loader.js';

// Slides are rendered once at a fixed design size and then scaled to fit whatever room the pane has
// (resizing, full screen, phones), so layout inside the slide never changes.
const SLIDE_W = 960;
const MAX_SCALE = 3;

/** Slide aspect ratio (height / width) from ppt/presentation.xml; 16:9 if it can't be read. */
async function slideRatio(buf) {
  try {
    const dv = new DataView(buf);
    let eocd = buf.byteLength - 22;
    while (eocd >= 0 && dv.getUint32(eocd, true) !== 0x06054b50) eocd--;
    let p = dv.getUint32(eocd + 16, true);
    const count = dv.getUint16(eocd + 10, true);
    for (let n = 0; n < count; n++) {
      const method = dv.getUint16(p + 10, true), size = dv.getUint32(p + 20, true);
      const nameLen = dv.getUint16(p + 28, true), extra = dv.getUint16(p + 30, true), comment = dv.getUint16(p + 32, true);
      const local = dv.getUint32(p + 42, true);
      const name = new TextDecoder().decode(new Uint8Array(buf, p + 46, nameLen));
      if (name === 'ppt/presentation.xml') {
        const start = local + 30 + dv.getUint16(local + 26, true) + dv.getUint16(local + 28, true);
        const data = new Uint8Array(buf, start, size);
        const text = method === 0 ? new TextDecoder().decode(data)
          : await new Response(new Blob([data]).stream().pipeThrough(new DecompressionStream('deflate-raw'))).text();
        const m = /<p:sldSz[^>]*\bcx="(\d+)"[^>]*\bcy="(\d+)"/.exec(text) || /<p:sldSz[^>]*\bcy="(\d+)"[^>]*\bcx="(\d+)"/.exec(text);
        if (m) return Math.min(Math.max(Number(m[2]) / Number(m[1]), 0.3), 2);
        break;
      }
      p += 46 + nameLen + extra + comment;
    }
  } catch { /* fall through */ }
  return 9 / 16;
}

export async function render(node, ctx) {
  const [pptxPreview, res] = await Promise.all([libs.pptx(), fetch(ctx.contentUrl, { signal: ctx.signal })]);
  if (ctx.signal.aborted) return;
  if (!res.ok) throw new Error(`HTTP ${res.status}`);
  const buf = await res.arrayBuffer();

  if (ctx.signal.aborted) return;
  const SLIDE_H = Math.round(SLIDE_W * await slideRatio(buf));
  const stage = el('div', { class: 'pptx-stage', style: `width:${SLIDE_W}px;height:${SLIDE_H}px` });
  const box = el('div', { class: 'pptx-box' }, stage);
  const wrap = el('div', { class: 'pptx-wrap' }, box);
  ctx.host.append(wrap);

  const instance = pptxPreview.init(stage, { width: SLIDE_W, height: SLIDE_H, mode: 'slide' });
  ctx.onDispose(() => instance.destroy?.());
  await instance.preview(buf);
  if (ctx.signal.aborted) return;
  const total = instance.slideCount ?? 1;
  let current = 1;

  const prevBtn = el('button', { class: 'btn btn-icon', type: 'button', 'aria-label': 'Previous slide', title: 'Previous slide ( \u2190 )', html: icon('chevron-left') });
  const nextBtn = el('button', { class: 'btn btn-icon', type: 'button', 'aria-label': 'Next slide', title: 'Next slide ( \u2192 )', html: icon('chevron') });
  const count = el('span', { class: 'tool-label pptx-count', 'aria-live': 'polite' });
  ctx.toolbar.append(prevBtn, count, nextBtn);

  const update = () => { count.textContent = `Slide ${current} of ${total}`; prevBtn.disabled = current <= 1; nextBtn.disabled = current >= total; };
  const go = (to) => {
    to = Math.min(Math.max(to, 1), total);
    while (current < to) { instance.renderNextSlide(); current++; }
    while (current > to) { instance.renderPreSlide(); current--; }
    update();
  };
  prevBtn.addEventListener('click', () => go(current - 1));
  nextBtn.addEventListener('click', () => go(current + 1));

  const onKey = (e) => {
    if (e.metaKey || e.ctrlKey || e.altKey || ['INPUT', 'TEXTAREA', 'SELECT'].includes(e.target?.tagName)) return;
    const to = { ArrowRight: current + 1, ArrowDown: current + 1, PageDown: current + 1, ArrowLeft: current - 1, ArrowUp: current - 1, PageUp: current - 1, Home: 1, End: total }[e.key];
    if (to == null) return;
    e.preventDefault(); go(to);
  };
  document.addEventListener('keydown', onKey);

  const fit = () => {
    const cs = getComputedStyle(wrap);
    const w = wrap.clientWidth - parseFloat(cs.paddingLeft) - parseFloat(cs.paddingRight);
    const h = wrap.clientHeight - parseFloat(cs.paddingTop) - parseFloat(cs.paddingBottom);
    const s = Math.max(0.1, Math.min(w / SLIDE_W, h / SLIDE_H, MAX_SCALE));
    stage.style.transform = `scale(${s})`;
    box.style.width = `${SLIDE_W * s}px`;
    box.style.height = `${SLIDE_H * s}px`;
  };
  const watch = new ResizeObserver(fit);
  watch.observe(wrap);
  ctx.onDispose(() => { watch.disconnect(); document.removeEventListener('keydown', onKey); });
  update();
  fit();
}
