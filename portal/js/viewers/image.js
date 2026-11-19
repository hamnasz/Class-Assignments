import { el } from '../core/dom.js';
import { icon } from '../core/icons.js';

const MIN_ZOOM = 0.05, MAX_ZOOM = 16;
const clamp = (v, lo, hi) => Math.min(Math.max(v, lo), hi);

/** Zoom, fit, 100%, rotate and drag-to-pan. Fitting never enlarges an image beyond its real size. */
export async function render(node, ctx) {
  const img = el('img', { src: ctx.contentUrl, alt: node.name, draggable: 'false' });
  const canvas = el('div', { class: 'image-canvas' }, img);
  const stage = el('div', { class: 'image-stage', tabindex: '0', 'aria-label': `${node.name}. Use plus and minus to zoom, R to rotate, 0 to fit.` }, canvas);
  ctx.host.append(stage);
  await new Promise((resolve, reject) => { img.onload = resolve; img.onerror = () => reject(new Error('Image could not be loaded')); });

  const natural = { w: img.naturalWidth || 300, h: img.naturalHeight || 150 };
  let rotation = 0;
  let manual = null;                                       // null = fit to the pane

  const fitZoom = () => {
    const turned = rotation % 180 !== 0;
    const bw = turned ? natural.h : natural.w, bh = turned ? natural.w : natural.h;
    const pad = 2 * parseFloat(getComputedStyle(stage).paddingLeft || 0);
    return clamp(Math.min((stage.clientWidth - pad) / bw, (stage.clientHeight - pad) / bh, 1), MIN_ZOOM, 1);
  };
  const zoom = () => manual ?? fitZoom();

  const out = el('button', { class: 'btn btn-icon', type: 'button', 'aria-label': 'Zoom out', title: 'Zoom out ( - )', html: icon('zoom-out') });
  const inn = el('button', { class: 'btn btn-icon', type: 'button', 'aria-label': 'Zoom in', title: 'Zoom in ( + )', html: icon('zoom-in') });
  const level = el('span', { class: 'tool-label', 'aria-live': 'polite' });
  const fit = el('button', { class: 'btn btn-icon', type: 'button', 'aria-label': 'Fit to screen', title: 'Fit to screen ( 0 )', html: icon('fit') });
  const actual = el('button', { class: 'btn', type: 'button', title: 'Actual size' }, '100%');
  const left = el('button', { class: 'btn btn-icon', type: 'button', 'aria-label': 'Rotate left', title: 'Rotate left', html: icon('rotate-ccw') });
  const right = el('button', { class: 'btn btn-icon', type: 'button', 'aria-label': 'Rotate right', title: 'Rotate right ( R )', html: icon('rotate-cw') });
  const dims = el('span', { class: 'tool-chip' }, `${natural.w} \u00d7 ${natural.h}`);
  ctx.toolbar.append(left, right, el('span', { class: 'tool-sep' }), out, level, inn, el('span', { class: 'tool-sep' }), fit, actual, el('span', { class: 'tool-sep' }), dims);

  const apply = () => {
    const z = zoom();
    const turned = rotation % 180 !== 0;
    canvas.style.width = `${(turned ? natural.h : natural.w) * z}px`;
    canvas.style.height = `${(turned ? natural.w : natural.h) * z}px`;
    img.style.width = `${natural.w * z}px`;
    img.style.height = `${natural.h * z}px`;
    img.style.transform = `translate(-50%, -50%) rotate(${rotation}deg)`;
    level.textContent = `${Math.round(z * 100)}%`;
    fit.classList.toggle('is-on', manual === null);
    actual.classList.toggle('is-on', manual === 1);
  };
  const zoomBy = (factor) => { manual = clamp(zoom() * factor, MIN_ZOOM, MAX_ZOOM); apply(); };
  const rotate = (deg) => { rotation = (rotation + deg + 360) % 360; apply(); };

  out.addEventListener('click', () => zoomBy(1 / 1.25));
  inn.addEventListener('click', () => zoomBy(1.25));
  fit.addEventListener('click', () => { manual = null; apply(); });
  actual.addEventListener('click', () => { manual = 1; apply(); });
  left.addEventListener('click', () => rotate(-90));
  right.addEventListener('click', () => rotate(90));
  stage.addEventListener('dblclick', () => { manual = manual === null ? 1 : null; apply(); });
  stage.addEventListener('keydown', (e) => {
    if (e.metaKey || e.ctrlKey || e.altKey) return;
    if (e.key === '+' || e.key === '=') zoomBy(1.25);
    else if (e.key === '-' || e.key === '_') zoomBy(1 / 1.25);
    else if (e.key === '0') { manual = null; apply(); }
    else if (e.key.toLowerCase() === 'r') rotate(e.shiftKey ? -90 : 90);
    else return;
    e.preventDefault();
  });
  stage.addEventListener('wheel', (e) => {                // pinch on a trackpad / ctrl+wheel
    if (!e.ctrlKey) return;
    e.preventDefault();
    zoomBy(Math.exp(-e.deltaY * 0.01));
  }, { passive: false });

  // drag to pan once the image is larger than the pane
  stage.addEventListener('pointerdown', (e) => {
    if (e.button !== 0 || e.pointerType === 'touch') return;      // touch scrolls natively
    const startX = e.clientX, startY = e.clientY, sl = stage.scrollLeft, st = stage.scrollTop;
    stage.setPointerCapture(e.pointerId);
    stage.classList.add('is-panning');
    const move = (ev) => { stage.scrollLeft = sl - (ev.clientX - startX); stage.scrollTop = st - (ev.clientY - startY); };
    const up = () => { stage.classList.remove('is-panning'); stage.removeEventListener('pointermove', move); stage.removeEventListener('pointerup', up); stage.removeEventListener('pointercancel', up); };
    stage.addEventListener('pointermove', move); stage.addEventListener('pointerup', up); stage.addEventListener('pointercancel', up);
  });

  const watch = new ResizeObserver(() => { if (manual === null) apply(); });
  watch.observe(stage);
  ctx.onDispose(() => watch.disconnect());
  apply();
}
