import { el, clear } from '../core/dom.js';
import { fetchChecked } from '../core/net.js';
import { icon } from '../core/icons.js';
import { libs } from '../core/loader.js';
import { canDownload } from '../core/permissions.js';
import { createViewer, enablePanning, fitView, isDarkWanted, parseDiagram, zoomBy, zoomTo } from '../core/diagrams.js';
import { ErrorState } from '../components/states.js';

const SOURCE_CAP = 400_000; // characters of XML shown in the source tab

/**
 * draw.io diagrams (.drawio, .dio, .draw.io, .xml) drawn by the official draw.io viewer.
 * Pan by dragging, zoom with the buttons or Ctrl/Cmd + scroll. Multi-page files get page tabs,
 * files with several layers get a layer menu. In dark mode the diagram is drawn in draw.io's
 * dark mode (config.js: diagrams.followTheme).
 */
export async function render(node, ctx) {
  const text = await (await fetchChecked(ctx.contentUrl, { signal: ctx.signal })).text();

  let doc;
  try { doc = parseDiagram(text); }
  catch (err) { renderBroken(node, ctx, text, err.message); return; }

  // View-only folders never expose the raw file, so the XML tab is left out there too.
  const showSource = canDownload(node.path);

  const stage = el('div', { class: 'diagram-stage' });
  const bar = el('div', { class: 'diagram-bar' });
  const canvas = el('div', { class: 'diagram-canvas', tabindex: '0', 'aria-label': `Diagram: ${node.name}` });
  const tabs = el('div', { class: 'sheet-tabs diagram-pages', role: 'tablist', 'aria-label': 'Pages' });
  const source = el('div', { class: 'diagram-source', hidden: true });
  stage.append(bar, canvas, tabs, source);
  ctx.host.append(stage);

  let viewer = null;
  let page = 0;
  let disposed = false, mountId = 0;
  let ro;
  const events = new AbortController();
  ctx.onDispose(() => {
    disposed = true; mountId++; events.abort(); ro?.disconnect();
    viewer?.graph?.destroy(); viewer = null;
  });

  // ---- controls -----------------------------------------------------------------------------
  const button = (name, label, onClick) => el('button', {
    class: 'btn btn-icon', type: 'button', 'aria-label': label, title: label, html: icon(name), onClick,
  });
  const graph = () => viewer?.graph;

  const ZOOM_STEP = 1.2;
  const zoomOut = button('zoom-out', 'Zoom out', () => viewer && zoomBy(viewer, 1 / ZOOM_STEP));
  const zoomIn = button('zoom-in', 'Zoom in', () => viewer && zoomBy(viewer, ZOOM_STEP));
  const zoomLabel = el('button', {
    class: 'diagram-bar__zoom', type: 'button', title: 'Actual size (100%)', 'aria-label': 'Reset to actual size',
    onClick: () => { if (viewer) zoomTo(viewer, 1); },
  }, '100%');
  const fit = button('fit', 'Fit to window', () => doFit());
  const layersBtn = button('layers', 'Layers', () => toggleLayers());
  layersBtn.setAttribute('aria-haspopup', 'true');
  layersBtn.setAttribute('aria-expanded', 'false');
  const layersPanel = el('div', { class: 'diagram-layers', hidden: true, role: 'group', 'aria-label': 'Layers' });
  const layersWrap = el('div', { class: 'diagram-bar__layers', hidden: true }, [layersBtn, layersPanel]);
  const fullscreen = button('expand', 'Full screen', () => {
    if (document.fullscreenElement === stage) document.exitFullscreen?.();
    else stage.requestFullscreen?.().catch(() => {});
  });
  if (!stage.requestFullscreen) fullscreen.hidden = true;

  // Diagram | XML switch (only where the raw file may be shown)
  const modeDiagram = el('button', { class: 'diagram-seg', type: 'button', 'aria-pressed': 'true' }, 'Diagram');
  const modeXml = el('button', { class: 'diagram-seg', type: 'button', 'aria-pressed': 'false' }, 'XML');
  const modes = showSource ? el('div', { class: 'diagram-bar__modes', role: 'group', 'aria-label': 'View' }, [modeDiagram, modeXml]) : null;

  const tools = el('div', { class: 'diagram-bar__tools' }, [zoomOut, zoomLabel, zoomIn, fit, layersWrap, fullscreen]);
  bar.append(modes || el('span'), el('span', { class: 'diagram-bar__hint' }, 'Drag to move, Ctrl/\u2318 + scroll to zoom'), tools);

  function updateZoom() {
    const g = graph();
    if (g) zoomLabel.textContent = `${Math.round(g.view.scale * 100)}%`;
  }

  // Fit to the window, and remember the result so that a resize only re-fits a diagram the
  // person hasn't zoomed or moved since.
  let fitState = null;
  function doFit() {
    if (!viewer) return;
    fitView(viewer);
    const { scale, translate } = viewer.graph.view;
    fitState = [scale, translate.x, translate.y];
    updateZoom();
  }
  function isFitted() {
    if (!viewer || !fitState) return false;
    const { scale, translate } = viewer.graph.view;
    return [scale, translate.x, translate.y].every((v, i) => Math.abs(v - fitState[i]) < 1e-6);
  }

  // ---- layers -------------------------------------------------------------------------------
  function layerCells() {
    const m = graph()?.getModel();
    if (!m) return [];
    const root = m.getRoot();
    return Array.from({ length: m.getChildCount(root) }, (_, i) => m.getChildAt(root, i));
  }

  function buildLayers() {
    clear(layersPanel);
    const layers = layerCells();
    layersWrap.hidden = layers.length < 2;
    layersPanel.hidden = true;
    layersBtn.setAttribute('aria-expanded', 'false');
    const g = graph();
    layers.forEach((cell, i) => {
      const name = String(g.convertValueToString(cell) || '').trim() || `Layer ${i + 1}`;
      const box = el('input', { type: 'checkbox' });
      box.checked = g.getModel().isVisible(cell);
      box.addEventListener('change', () => g.getModel().setVisible(cell, box.checked));
      layersPanel.append(el('label', { class: 'diagram-layers__row' }, [box, el('span', {}, name)]));
    });
  }

  function toggleLayers(force) {
    const open = force ?? layersPanel.hidden;
    layersPanel.hidden = !open;
    layersBtn.setAttribute('aria-expanded', String(open));
  }
  document.addEventListener('click', (e) => { if (!layersWrap.contains(e.target)) toggleLayers(false); }, { signal: events.signal });

  // ---- pages --------------------------------------------------------------------------------
  function buildTabs() {
    clear(tabs);
    const pages = viewer.diagrams ? Array.from(viewer.diagrams) : [];
    tabs.hidden = pages.length < 2;
    pages.forEach((d, i) => {
      tabs.append(el('button', {
        class: 'sheet-tab', type: 'button', role: 'tab', 'aria-selected': String(i === page),
        onClick: () => selectPage(i),
      }, d.getAttribute('name') || `Page ${i + 1}`));
    });
  }

  function selectPage(i) {
    if (!viewer || i === page) return;
    page = i;
    viewer.selectPage(i);
    [...tabs.children].forEach((t, n) => t.setAttribute('aria-selected', String(n === i)));
    doFit();
    buildLayers();
  }

  // ---- mounting the viewer ------------------------------------------------------------------
  async function mount() {
    const mine = ++mountId;
    viewer?.graph?.destroy(); viewer = null;
    clear(canvas);
    const inner = el('div', { class: 'diagram-canvas__inner', style: 'width:100%;height:100%' });
    canvas.append(inner);
    const next = await createViewer(inner, doc, { dark: isDarkWanted(), page });
    if (disposed || mine !== mountId) { next.graph?.destroy(); return; }
    viewer = next;
    const { mxEvent } = await libs.drawio();
    if (disposed || mine !== mountId) return;
    for (const evt of [mxEvent.SCALE, mxEvent.SCALE_AND_TRANSLATE]) viewer.graph.view.addListener(evt, updateZoom);
    doFit();
    buildTabs();
    buildLayers();
  }

  enablePanning(canvas, graph);

  // Ctrl/Cmd + scroll zooms; plain scroll keeps scrolling the page.
  canvas.addEventListener('wheel', (e) => {
    if (!(e.ctrlKey || e.metaKey) || !viewer) return;
    e.preventDefault();
    const r = canvas.getBoundingClientRect();
    zoomBy(viewer, e.deltaY < 0 ? ZOOM_STEP : 1 / ZOOM_STEP, e.clientX - r.left, e.clientY - r.top);
  }, { passive: false });

  // ---- source tab ---------------------------------------------------------------------------
  let sourceBuilt = false;
  function setMode(xml) {
    modeDiagram?.setAttribute('aria-pressed', String(!xml));
    modeXml?.setAttribute('aria-pressed', String(xml));
    canvas.hidden = xml;
    tabs.hidden = xml || !viewer?.diagrams || viewer.diagrams.length < 2;
    source.hidden = !xml;
    tools.classList.toggle('is-muted', xml);
    if (xml && !sourceBuilt) {
      sourceBuilt = true;
      const shown = text.length > SOURCE_CAP ? `${text.slice(0, SOURCE_CAP)}\n\n\u2026 (truncated)` : text;
      const pre = el('pre', { class: 'txt-plain' });
      pre.textContent = shown;
      source.append(pre);
    }
    if (!xml && viewer) doFit();
  }
  modeDiagram?.addEventListener('click', () => setMode(false));
  modeXml?.addEventListener('click', () => setMode(true));

  // ---- theme and fullscreen follow-ups --------------------------------------------------------
  const alive = () => document.body.contains(stage);
  function onTheme() {
    if (!alive()) { document.removeEventListener('themechange', onTheme); return; }
    if (canvas.hidden) return;
    mount().catch(console.error);
  }
  document.addEventListener('themechange', onTheme, { signal: events.signal });

  function onFullscreen() {
    if (!alive()) { document.removeEventListener('fullscreenchange', onFullscreen); return; }
    const on = document.fullscreenElement === stage;
    fullscreen.innerHTML = icon(on ? 'shrink' : 'expand');
    fullscreen.title = fullscreen.ariaLabel = on ? 'Exit full screen' : 'Full screen';
    stage.classList.toggle('is-fullscreen', on);
  }
  document.addEventListener('fullscreenchange', onFullscreen, { signal: events.signal });

  // Window resizes and full screen change the canvas size: keep an untouched diagram fitted.
  if ('ResizeObserver' in window) {
    ro = new ResizeObserver(() => {
      if (!alive()) { ro.disconnect(); return; }
      if (!canvas.hidden && canvas.clientWidth && isFitted()) doFit();
    });
    ro.observe(canvas);
  }

  await mount();
}

function renderBroken(node, ctx, text, message) {
  const wrap = el('div', { class: 'viewer-pad' }, ErrorState({
    title: 'This diagram couldn\u2019t be read',
    desc: `${message} It should be a draw.io file (.drawio, .draw.io or .xml saved from diagrams.net).`,
  }));
  if (canDownload(node.path) && text.trim()) {
    const pre = el('pre', { class: 'txt-plain', style: 'margin-top:var(--space-4);border:1px solid var(--border);border-radius:var(--radius);max-height:24rem' });
    pre.textContent = text.slice(0, 20000);
    wrap.append(pre);
  }
  ctx.host.append(wrap);
}
