// Hash-based routing: works on GitHub Pages without any server rules.
//   #/                     dashboard
//   #/browse/<path>        folder
//   #/view/<path>          file viewer
//   #/search?q=..&type=..  search results
// Any route may also carry the file preview pane's state: ?file=<path>[&mode=full]
// (see preview.js). Changing only those parameters never re-renders the page behind the pane.

const safeDecode = (s) => { try { return decodeURIComponent(s); } catch { return s; } };
const clean = (segs) => segs.map(safeDecode).filter((s) => s && s !== '.' && s !== '..');
const enc = (p) => String(p).split('/').filter(Boolean).map(encodeURIComponent).join('/');

export function parseHash(hash = '') {
  let h = String(hash).replace(/^#/, '');
  if (!h.startsWith('/')) h = '/' + h;
  const [pathPart, query = ''] = h.split('?');
  const [name, ...rest] = pathPart.split('/').filter(Boolean);
  const params = new URLSearchParams(query);
  const pane = { file: params.get('file') || '', mode: params.get('mode') === 'full' ? 'full' : 'pane' };
  switch (name) {
    case undefined: return { name: 'home', ...pane };
    case 'browse': return { name: 'browse', path: clean(rest).join('/'), ...pane };
    case 'view': return { name: 'view', path: clean(rest).join('/'), ...pane };
    case 'search': return { name: 'search', q: params.get('q') || '', type: params.get('type') || '', kind: params.get('kind') || '', ...pane };
    default: return { name: 'notfound', raw: h, ...pane };
  }
}

/** The hash without the preview pane's parameters: this is what identifies the page behind the pane. */
export function stripPane(hash = '') {
  const [path, query = ''] = String(hash).split('?');
  const params = new URLSearchParams(query);
  params.delete('file'); params.delete('mode');
  const q = params.toString();
  return q ? `${path}?${q}` : path;
}

/** Same page, with the pane showing `file` (or closed when `file` is empty). */
export function withPane(hash, file, mode = 'pane') {
  const base = stripPane(hash || '#/');
  if (!file) return base;
  const params = new URLSearchParams(base.split('?')[1] || '');
  params.set('file', file);
  if (mode === 'full') params.set('mode', 'full');
  return `${base.split('?')[0] || '#/'}?${params.toString()}`;
}

export const href = {
  home: () => '#/',
  browse: (path) => (path ? `#/browse/${enc(path)}` : '#/'),
  view: (path) => `#/view/${enc(path)}`,
  search: ({ q = '', type = '', kind = '' } = {}) => {
    const p = new URLSearchParams();
    if (q) p.set('q', q);
    if (type) p.set('type', type);
    if (kind) p.set('kind', kind);
    const s = p.toString();
    return s ? `#/search?${s}` : '#/search';
  },
  node: (node) => (node.kind === 'dir' ? href.browse(node.path) : href.view(node.path)),
};

let pushed = false;
export const markPush = () => { pushed = true; };

// Registered by the preview pane: lets navigate('#/view/...') open the pane instead of a page.
let fileOpener = null;
export const setFileOpener = (fn) => { fileOpener = fn; };

export function startRouter(onRoute, onPaneChange) {
  // Any click on an in-app link counts as a forward navigation (scroll to top);
  // back/forward buttons restore the previous scroll position.
  document.addEventListener('click', (e) => {
    const a = e.target.closest?.('a[href^="#/"]');
    if (a && !e.defaultPrevented) markPush();
  }, true);
  const scrollMemory = new Map();
  let lastKey = location.hash;
  let lastPage = null;                      // hash of the page behind the pane, without pane parameters
  const run = () => {
    const key = location.hash;
    const page = stripPane(key);
    if (lastPage !== null && page === lastPage) {          // only the pane changed: leave the page alone
      lastKey = key;
      Promise.resolve(onPaneChange?.(parseHash(key))).catch(console.error);
      return;
    }
    scrollMemory.set(stripPane(lastKey), window.scrollY);
    const restore = !pushed ? scrollMemory.get(page) : undefined;
    pushed = false;
    lastKey = key; lastPage = page;
    Promise.resolve(onRoute(parseHash(key), { restoreScroll: restore })).catch(console.error);
  };
  window.addEventListener('hashchange', run);
  run();
}

export function navigate(hash, { replace = false } = {}) {
  if (fileOpener && /^#\/view\//.test(hash) && fileOpener(parseHash(hash).path)) return;
  markPush();
  if (replace) history.replaceState(null, '', hash), window.dispatchEvent(new HashChangeEvent('hashchange'));
  else location.hash = hash;
}
