// Shared draw.io helpers used by the diagram viewer and the diagram cards.
// The official viewer itself (portal/vendor/drawio/) is only loaded when a diagram is shown.
import { CONFIG } from '../../config.js';
import { libs } from './loader.js';
import { contentUrl } from './urls.js';

export class DiagramError extends Error {}

/** "lecture-1.draw.io" -> "lecture-1", "model.xml" -> "model". */
export function diagramTitle(node) {
  const ext = node.ext;
  return ext && node.name.toLowerCase().endsWith(`.${ext}`) ? node.name.slice(0, -(ext.length + 1)) : node.name;
}

/**
 * Parses a draw.io file (.drawio, .dio, .draw.io, or .xml) and checks that it really is one.
 * Accepts <mxfile> (what draw.io saves, one or more pages, compressed or not),
 * a bare <mxGraphModel>, and a lone <diagram> page.
 */
export function parseDiagram(text) {
  const doc = new DOMParser().parseFromString(String(text).replace(/^\uFEFF/, ''), 'application/xml');
  if (doc.querySelector('parsererror') || !doc.documentElement) throw new DiagramError('This file is not valid XML.');
  const name = doc.documentElement.nodeName;
  if (name === 'diagram') {
    const wrapped = new DOMParser().parseFromString('<mxfile/>', 'application/xml');
    wrapped.documentElement.append(wrapped.importNode(doc.documentElement, true));
    return wrapped;
  }
  if (name !== 'mxfile' && name !== 'mxGraphModel') throw new DiagramError('This XML file is not a draw.io diagram.');
  return doc;
}

export const isDarkWanted = () => !!CONFIG.diagrams?.followTheme && document.documentElement.dataset.theme === 'dark';

/**
 * Scales the whole diagram to fit the container (without blowing tiny diagrams up past 125%)
 * and centres it. The viewer's own graph.fit() is a stub in the static build, so this works
 * out the scale and translation directly.
 */
export function fitView(viewer, border = 24) {
  const g = viewer.graph;
  const box = g.container;
  const b = g.getGraphBounds();
  if (!b || !b.width || !b.height || !box.clientWidth || !box.clientHeight) return;
  const { scale: s, translate: t } = g.view;
  const w = b.width / s, h = b.height / s;               // the diagram at 100%
  const mx = b.x / s - t.x, my = b.y / s - t.y;          // its top-left in diagram coordinates
  const ns = Math.max(0.05, Math.min((box.clientWidth - 2 * border) / w, (box.clientHeight - 2 * border) / h, 1.25));
  g.view.scaleAndTranslate(ns, (box.clientWidth / ns - w) / 2 - mx, (box.clientHeight / ns - h) / 2 - my);
}

/**
 * Zooms by `factor` (or to an absolute `scale` with zoomTo), keeping the point (px, py) of the
 * container fixed; the centre by default.
 */
export function zoomBy(viewer, factor, px, py) { return zoomTo(viewer, viewer.graph.view.scale * factor, px, py); }

export function zoomTo(viewer, scale, px, py) {
  const g = viewer.graph;
  const box = g.container;
  const { scale: s, translate: t } = g.view;
  const ns = Math.min(8, Math.max(0.05, scale));
  const x = px ?? box.clientWidth / 2;
  const y = py ?? box.clientHeight / 2;
  const mx = x / s - t.x, my = y / s - t.y;               // the diagram point under (x, y)
  g.view.scaleAndTranslate(ns, x / ns - mx, y / ns - my);
}

/** Drag the background to move the diagram. A plain click still reaches links inside it. */
export function enablePanning(surface, getGraph) {
  let drag = null;
  surface.addEventListener('pointerdown', (e) => {
    if (e.button !== 0 || !getGraph()) return;
    drag = { x: e.clientX, y: e.clientY, moved: false, id: e.pointerId };
  });
  surface.addEventListener('pointermove', (e) => {
    const g = getGraph();
    if (!drag || !g || e.pointerId !== drag.id) return;
    if (!drag.moved) {
      if (Math.hypot(e.clientX - drag.x, e.clientY - drag.y) < 4) return;
      drag.moved = true;
      surface.setPointerCapture(e.pointerId);
      surface.classList.add('is-panning');
    }
    const { scale, translate } = g.view;
    g.view.setTranslate(translate.x + (e.clientX - drag.x) / scale, translate.y + (e.clientY - drag.y) / scale);
    drag.x = e.clientX; drag.y = e.clientY;
  });
  const end = (e) => {
    if (!drag || e.pointerId !== drag.id) return;
    if (drag.moved) {
      // swallow the click that follows a drag so it doesn't open a link by accident
      const stop = (ev) => ev.stopPropagation();
      surface.addEventListener('click', stop, { capture: true, once: true });
      setTimeout(() => surface.removeEventListener('click', stop, { capture: true }), 0);
    }
    surface.classList.remove('is-panning');
    drag = null;
  };
  surface.addEventListener('pointerup', end);
  surface.addEventListener('pointercancel', end);
}

/**
 * Draws a diagram into `container` with the official viewer. The viewer's own toolbar,
 * lightbox and "edit in diagrams.net" links stay off: the portal supplies its own controls
 * and nothing is ever sent to another site.
 */
export async function createViewer(container, doc, { dark = false, page = 0 } = {}) {
  const { GraphViewer } = await libs.drawio();
  const viewer = new GraphViewer(container, doc.documentElement, {
    lightbox: false, nav: false, resize: false, center: false,
    'auto-fit': false, 'allow-zoom-in': true, border: 24, page,
    'dark-mode': dark ? 'dark' : 'light',
  });
  if (!viewer.graph) throw new DiagramError('The diagram could not be drawn.');
  const g = viewer.graph;
  // The portal positions the diagram itself (fitView, zoomBy, enablePanning), always through
  // the view's scale and translate. The viewer's container would otherwise also scroll
  // internally to compensate, which makes panning and zooming drift, so that is switched off.
  g.sizeDidChange = () => {};
  // The viewer's own size lookup dereferences graph.container, which is gone once a diagram has
  // been torn down (thumbnails, leaving the page) while one of its events is still pending.
  viewer.getAvailableSize = () => ({ x: 0, y: 0, width: container.clientWidth, height: container.clientHeight });
  const svg = container.querySelector('svg');
  if (svg) svg.style.minWidth = svg.style.minHeight = '';
  container.scrollLeft = container.scrollTop = 0;
  // Dragging is handled by enablePanning(); switch off the viewer's own panning so the two
  // don't both move the diagram.
  g.setPanning(false);
  Object.assign(g.panningHandler, { isForcePanningEvent: () => false, useLeftButtonForPanning: false, panningEnabled: false });
  return viewer;
}

// ---- thumbnails ----------------------------------------------------------------------------
// A preview is drawn once by the real viewer, off screen, copied out as a static SVG and the
// viewer is thrown away, so a page full of cards never holds more than one live diagram.
const thumbs = new Map();          // path -> Promise<SVGElement | null>
let queue = Promise.resolve();     // one render at a time keeps the page responsive

export function thumbnailAllowed(node) {
  const d = CONFIG.diagrams || {};
  if (d.thumbnails === false) return false;
  return node.size == null || node.size <= (d.thumbnailMaxKB ?? 1024) * 1024;
}

async function drawThumbnail(node) {
  const response = await fetch(contentUrl(node));
  if (!response.ok) throw new DiagramError(`HTTP ${response.status}`);
  const text = await response.text();
  const doc = parseDiagram(text);
  const host = document.createElement('div');
  host.setAttribute('aria-hidden', 'true');
  host.style.cssText = 'position:fixed;left:-9999px;top:0;width:960px;height:640px;overflow:hidden;visibility:hidden';
  document.body.append(host);
  let viewer;
  try {
    viewer = await createViewer(host, doc, { dark: false });
    const svg = viewer.graph.getSvg(null, 1, 12);
    if (!svg) return null;
    svg.removeAttribute('width');
    svg.removeAttribute('height');
    svg.setAttribute('preserveAspectRatio', 'xMidYMid meet');
    svg.setAttribute('focusable', 'false');
    svg.style.cssText = 'width:100%;height:100%;display:block';
    return svg.cloneNode(true);
  } finally {
    try { viewer?.graph?.destroy(); } catch { /* best effort */ }
    host.remove();
  }
}

/** Resolves to a detached <svg> preview, or null when one can't be made. Cached per file. */
export function diagramThumbnail(node) {
  if (!thumbs.has(node.path)) {
    const job = queue.then(() => drawThumbnail(node)).catch((err) => { console.warn('Diagram preview failed', node.path, err); return null; });
    queue = job.then(() => {}, () => {});
    thumbs.set(node.path, job);
    if (thumbs.size > 32) thumbs.delete(thumbs.keys().next().value);
  }
  return thumbs.get(node.path).then((svg) => (svg ? svg.cloneNode(true) : null));
}
