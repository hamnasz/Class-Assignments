// Lazy loader for the vendored preview libraries. Nothing is fetched until a viewer needs it.
import { CONFIG } from '../../config.js';

const base = new URL('../../vendor/', import.meta.url);
const inflight = new Map();

function once(key, create) {
  if (!inflight.has(key)) {
    const p = create();
    p.catch(() => inflight.delete(key));   // allow a retry after a failure
    inflight.set(key, p);
  }
  return inflight.get(key);
}

const script = (rel) => once(rel, () => new Promise((resolve, reject) => {
  const s = document.createElement('script');
  s.src = new URL(rel, base).href;
  s.async = true;
  s.onload = () => resolve();
  s.onerror = () => { s.remove(); reject(new Error(`Could not load ${rel}`)); };
  document.head.append(s);
}));

const style = (rel) => once(rel, () => new Promise((resolve, reject) => {
  const l = document.createElement('link');
  l.rel = 'stylesheet';
  l.href = new URL(rel, base).href;
  l.onload = () => resolve();
  l.onerror = () => { l.remove(); reject(new Error(`Could not load ${rel}`)); };
  document.head.append(l);
}));

export const libs = {
  async pdfjs() {
    return once('pdfjs', async () => {
      const m = await import(new URL('pdfjs/pdf.min.mjs', base).href);
      m.GlobalWorkerOptions.workerSrc = new URL('pdfjs/pdf.worker.min.mjs', base).href;
      return m;
    });
  },
  async docx() {
    // The font sheet is optional: a failure to load it must not stop a document from opening.
    const fonts = style('docx/docx-fonts.css').catch(() => {});
    // Order matters: docx-preview binds the JSZip global when it is evaluated.
    await script('docx/jszip.min.js');
    await script('docx/docx-preview.min.js');
    await fonts;
    return { docx: window.docx, JSZip: window.JSZip };
  },
  async jszip() { await script('docx/jszip.min.js'); return window.JSZip; },
  async xlsx() { await script('xlsx/xlsx.full.min.js'); return window.XLSX; },
  async pptx() { await script('pptx/pptx-preview.umd.js'); return window.pptxPreview; },
  /**
   * The official draw.io viewer ("viewer-static.min.js"). It reads its resource locations from
   * window variables at load time, so they are pointed at the vendored copies first. Left
   * alone they would default to https://viewer.diagrams.net.
   */
  async drawio() {
    return once('drawio', async () => {
      const root = new URL('drawio', base).href;
      // "img/lib/..." icons are resolved against DRAWIO_BASE_URL (see config.js, diagrams.iconBase).
      const icons = (CONFIG.diagrams?.iconBase || '').replace(/\/+$/, '') || root;
      Object.assign(window, {
        STENCIL_PATH: `${root}/stencils`,
        SHAPES_PATH: `${root}/shapes`,
        STYLE_PATH: `${root}/styles`,
        DRAW_MATH_URL: `${root}/math`,
        DRAWIO_BASE_URL: icons,
        mxBasePath: `${root}/mxgraph`,
        mxImageBasePath: `${root}/mxgraph/images`,
        GRAPH_IMAGE_PATH: `${icons}/img`,
        // Without this the script would scan the page for ".mxgraph" elements by itself.
        onDrawioViewerLoad() {},
      });
      await script('drawio/viewer-static.min.js');
      if (!window.GraphViewer) throw new Error('The draw.io viewer did not start');
      return { GraphViewer: window.GraphViewer, mxEvent: window.mxEvent, mxUtils: window.mxUtils };
    });
  },
  async highlight() { await script('markdown/highlight.min.js'); return { hljs: window.hljs }; },
  async markdown() {
    await Promise.all([
      script('markdown/marked.umd.js'), script('markdown/purify.min.js'), script('markdown/highlight.min.js'),
      script('markdown/katex/katex.min.js'), style('markdown/katex/katex.min.css'),
    ]);
    return { marked: window.marked, DOMPurify: window.DOMPurify, hljs: window.hljs, katex: window.katex };
  },
};
