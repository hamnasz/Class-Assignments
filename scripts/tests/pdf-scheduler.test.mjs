// Deterministic lifecycle tests for the real viewer with a simulated DOM and PDF.js transport.
// These test scheduling/cancellation, not browser layout, font fidelity or real PDF throughput.
import test from 'node:test';
import assert from 'node:assert/strict';
import { readFileSync } from 'node:fs';

const sleep = ms => new Promise(r => setTimeout(r, ms));
class Element extends EventTarget {
  constructor(tag, attrs = {}, children = []) {
    super(); this.tag = tag; this.parent = null; this.children = []; this.attrs = {}; this.dataset = {};
    this.style = { setProperty(k, v) { this[k] = v; } }; this.scrollTop = 0; this.scrollLeft = 0;
    this.clientWidth = 740; this.clientHeight = 780; this.hidden = false;
    this.classList = { add: (...v) => v.forEach(n => this.classes.add(n)), toggle: (n, on) => on ? this.classes.add(n) : this.classes.delete(n) };
    this.classes = new Set();
    for (const [k, v] of Object.entries(attrs)) {
      if (k === 'dataset') Object.assign(this.dataset, v);
      else if (k === 'onClick') this.addEventListener('click', v);
      else this.setAttribute(k, v);
    }
    this.append(...[].concat(children));
  }
  setAttribute(k, v) { this.attrs[k] = String(v); if (k === 'class') this.classes = new Set(v.split(' ')); else this[k] = v; }
  getAttribute(k) { return this.attrs[k]; }
  append(...children) { for (const c of children) if (c != null) {
    if (c.tag === 'fragment') { this.append(...c.children); continue; }
    if (typeof c !== 'object') { this.textContent = (this.textContent || '') + String(c); continue; }
    c.parent = this; this.children.push(c);
  } }
  replaceChildren(...children) { for (const c of this.children) c.parent = null; this.children = []; this.append(...children); }
  remove() { if (this.parent) this.parent.children = this.parent.children.filter(c => c !== this); this.parent = null; }
  get offsetHeight() { return parseFloat(this.style.height) || 780; }
  get offsetTop() {
    if (!this.parent || this.parent.tag === 'fragment') return 0;
    let y = 16;
    for (const child of this.parent.children) { if (child === this) return y; y += child.offsetHeight + 20; }
    return y;
  }
  getContext() { return {}; }
  blur() { globalThis.document.activeElement = null; }
  all(predicate) { return [...this.children.filter(predicate), ...this.children.flatMap(c => c.all(predicate))]; }
}
const el = (...args) => new Element(...args);
let observers;
function environment() {
  observers = [];
  globalThis.window = { devicePixelRatio: 2 };
  globalThis.document = { activeElement: null, createDocumentFragment: () => el('fragment') };
  globalThis.getComputedStyle = () => ({ paddingLeft: '16', paddingRight: '16' });
  globalThis.requestAnimationFrame = fn => setTimeout(fn, 1);
  globalThis.cancelAnimationFrame = clearTimeout;
  globalThis.ResizeObserver = class {
    constructor(fn) { this.fn = fn; this.disconnected = false; observers.push(this); }
    observe() {} disconnect() { this.disconnected = true; }
  };
}
function transport(total, options = {}) {
  const stats = { pages: [], rendered: [], cancelled: 0, active: 0, peak: 0, destroyed: 0, cleaned: 0 };
  const tasks = new Set();
  const doc = { numPages: total, async getPage(num) {
    stats.pages.push(num); await sleep(2);
    return { getViewport: ({ scale }) => ({ width: (num % 7 === 0 ? 842 : 595) * scale, height: (num % 7 === 0 ? 595 : 842) * scale }),
      cleanup() { stats.cleaned++; }, streamTextContent() { return {}; },
      render() {
        stats.rendered.push(num); stats.active++; stats.peak = Math.max(stats.peak, stats.active);
        let timer, reject, settled = false;
        const settle = () => { if (settled) return false; settled = true; stats.active--; tasks.delete(task); return true; };
        const task = { promise: new Promise((resolve, no) => {
          reject = no; timer = setTimeout(() => { if (settle()) options.failPage === num && (!options.failOnce || stats.rendered.filter(n => n === num).length === 1) ? no(new Error('Fixture render failed')) : resolve(); }, options.delay ?? 12);
        }), cancel() { if (settle()) { clearTimeout(timer); stats.cancelled++; reject(Object.assign(new Error('cancelled'), { name: 'RenderingCancelledException' })); } } };
        tasks.add(task); return task;
      },
    };
  } };
  let input;
  return { stats, input: () => input, pdfjs: {
    getDocument(opts) { input = opts; return { promise: sleep(options.loadDelay ?? 1).then(() => doc), async destroy() { stats.destroyed++; for (const task of [...tasks]) task.cancel(); } }; },
    TextLayer: class { constructor({ container }) { this.container = container; } async render() { await sleep(1); this.container.append(el('span', {}, 'Selectable fixture text')); } cancel() {} },
  } };
}
const source = readFileSync(new URL('../../portal/js/viewers/pdf.js', import.meta.url), 'utf8')
  .replace(/^import .*;\n/gm, '').replace('export async function render', 'async function render');
async function open(total = 120, options = {}) {
  environment();
  const mock = transport(total, options), host = el('host'), toolbar = el('toolbar');
  const abort = new AbortController(), cleanup = [];
  const render = new Function('el', 'icon', 'libs', 'SpinnerLine', `${source}\nreturn render;`)(el, () => '', { pdfjs: async () => mock.pdfjs }, text => el('p', {}, text));
  const pending = render({ name: 'fixture.pdf' }, { host, toolbar, contentUrl: '/fixture.pdf', signal: abort.signal, onDispose: fn => cleanup.push(fn) });
  const find = label => toolbar.all(n => n.attrs['aria-label'] === label)[0];
  const close = () => { abort.abort(); cleanup.splice(0).forEach(fn => fn()); host.replaceChildren(); toolbar.replaceChildren(); };
  return { ...mock, host, toolbar, pending, find, close, canvases: () => host.all(n => n.tag === 'canvas'), scroll: () => host.all(n => n.classes.has('pdf-scroll'))[0], pages: () => host.all(n => n.classes.has('pdf-page')) };
}
const settle = () => sleep(100);

test('first view requests a small reading window for 1/10/50/120 pages', async () => {
  for (const total of [1, 10, 50, 120]) {
    const v = await open(total); await v.pending; await settle();
    assert.equal(v.pages().length, total);
    assert.equal(v.pages()[0].dataset.state, 'rendered');
    assert.ok(new Set(v.stats.pages).size <= 4);
    assert.ok(v.canvases().length <= 4);
    assert.ok(v.stats.peak <= 2);
    assert.deepEqual(v.input(), { url: '/fixture.pdf', rangeChunkSize: 65536 });
    v.close(); assert.equal(v.stats.destroyed, 1);
  }
});
test('jumping deep into a long PDF evicts old canvases and learns landscape sizes', async () => {
  const v = await open(); await v.pending; await settle();
  const old = v.canvases(); const jump = v.find('Page number'); jump.value = '70'; jump.dispatchEvent(new Event('change'));
  await settle();
  assert.equal(v.pages()[69].dataset.state, 'rendered');
  assert.ok(parseFloat(v.pages()[69].style.width) > parseFloat(v.pages()[69].style.height));
  assert.ok(v.canvases().length <= 8);
  assert.ok(old.every(c => c.width === 0 && c.height === 0));
  assert.ok(new Set(v.stats.pages).size < 12);
  v.close();
});
test('rapid scroll and repeated zoom cancel obsolete work, keep the anchor and bound rasters', async () => {
  const v = await open(120, { delay: 35 }); await v.pending;
  for (const n of [20, 100, 6, 119]) {
    const jump = v.find('Page number'); jump.value = String(n); jump.dispatchEvent(new Event('change'));
    v.find('Zoom in').dispatchEvent(new Event('click'));
    await sleep(4);
  }
  await settle();
  assert.ok(v.canvases().length <= 8);
  assert.ok(v.stats.peak <= 2);
  assert.ok(v.stats.cancelled > 0);
  const jump = v.find('Page number'); jump.value = '70'; jump.dispatchEvent(new Event('change')); await settle();
  v.scroll().scrollTop += 116; v.scroll().dispatchEvent(new Event('scroll')); await settle();
  const before = (v.scroll().scrollTop - v.pages()[69].offsetTop) / v.pages()[69].offsetHeight;
  v.find('Zoom in').dispatchEvent(new Event('click')); await settle();
  const after = (v.scroll().scrollTop - v.pages()[69].offsetTop) / v.pages()[69].offsetHeight;
  assert.ok(Math.abs(before - after) < 0.001);
  jump.value = '70'; jump.dispatchEvent(new Event('change')); await settle();
  v.find('Zoom in').dispatchEvent(new Event('click')); await settle();
  assert.ok(Math.abs(v.scroll().scrollTop - v.pages()[69].offsetTop + 16) < 0.001);
  assert.ok(v.canvases().every(c => c.width <= 4096 && c.height <= 4096 && c.width * c.height <= 3 * 1024 * 1024));
  v.close(); await settle(); assert.equal(v.stats.active, 0);
});
test('resize is debounced and manual zoom is retained until fit is restored', async () => {
  const v = await open(); await v.pending; await settle();
  v.find('Zoom in').dispatchEvent(new Event('click')); await settle();
  const count = v.stats.rendered.length;
  v.scroll().clientWidth = 400; observers[0].fn(); await sleep(280);
  assert.equal(v.stats.rendered.length, count);
  v.find('Fit to width').dispatchEvent(new Event('click')); await settle();
  v.scroll().clientWidth = 350;
  for (let n = 0; n < 20; n++) observers[0].fn();
  await sleep(300);
  assert.ok(v.stats.rendered.length - count < 12);
  assert.ok(parseFloat(v.pages()[0].style.width) <= 318);
  v.close(); assert.ok(observers.every(o => o.disconnected));
});
test('closing during loading or rendering prevents late canvases and destroys transport', async () => {
  for (const options of [{ loadDelay: 30 }, { delay: 50 }]) {
    const v = await open(120, options);
    await sleep(8); v.close(); await v.pending; await settle();
    assert.equal(v.canvases().length, 0);
    assert.equal(v.stats.destroyed, 1);
    assert.equal(v.stats.active, 0);
  }
});
test('repeated open/close cycles release all bitmap storage and render slots', async () => {
  for (let i = 0; i < 12; i++) {
    const v = await open(50); await v.pending; await settle(); const canvases = v.canvases();
    v.close(); await sleep(5);
    assert.ok(canvases.every(c => c.width === 0 && c.height === 0));
    assert.equal(v.stats.active, 0); assert.equal(v.stats.destroyed, 1);
  }
});

test('a genuine page failure offers a working retry instead of looping', async (t) => {
  t.mock.method(console, 'error', () => {});
  const v = await open(1, { failPage: 1, failOnce: true }); await v.pending; await settle();
  assert.equal(v.stats.rendered.length, 1);
  assert.equal(v.pages()[0].dataset.state, 'error');
  const retry = v.pages()[0].children.find(n => n.tag === 'button');
  assert.ok(retry); retry.dispatchEvent(new Event('click')); await settle();
  assert.equal(v.pages()[0].dataset.state, 'rendered');
  assert.equal(v.stats.rendered.length, 2);
  v.close();
});

test('showFile runs cleanup registered after the user has already closed the preview', async () => {
  environment();
  let cleaned = 0;
  const moduleSource = readFileSync(new URL('../../portal/js/components/fileContent.js', import.meta.url), 'utf8')
    .replace(/^import .*;\n/gm, '').replace('export function showFile', 'function showFile');
  const showFile = new Function('el', 'clear', 'EmptyState', 'ErrorState', 'SpinnerLine', 'contentUrl', 'formatBytes', 'getViewer', 'CONFIG', `${moduleSource}\nreturn showFile;`)(
    el, n => n.replaceChildren(), () => el('p'), () => el('p'), text => el('p', {}, text), () => '/fixture', () => '',
    async () => async (node, ctx) => { await sleep(20); ctx.onDispose(() => cleaned++); }, { maxPreviewMB: 40 }
  );
  const body = el('body'), tools = el('tools');
  const close = showFile({ body, tools }, { type: { viewer: 'fake', id: 'fake' }, size: 1 });
  await sleep(5); close(); await sleep(30);
  assert.equal(cleaned, 1); assert.equal(body.children.length, 0); assert.equal(tools.children.length, 0);
});
