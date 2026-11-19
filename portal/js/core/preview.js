// State and behaviour of the file preview pane. No DOM of its own: components/previewPane.js
// renders it and subscribes to changes.
//
// How "open a file without leaving the page" works:
//   * Clicks on file links (and navigate('#/view/...')) are intercepted and open the pane instead.
//     The route never changes, so the page behind the pane is not re-rendered and keeps its
//     scroll position, search results and everything else.
//   * The pane's state is mirrored into the URL as ?file=<path>[&mode=full] with history.replaceState /
//     pushState, which do not fire hashchange. Refreshing or sharing the URL reopens the same file.
//   * Opening from closed pushes one history entry, so the browser/phone Back button closes the pane
//     (rather than leaving the page). Switching files, resizing and full screen only replace it.
//   * Old "#/view/<path>" links (bookmarks, other tabs) become: parent folder + pane open.

import { prefs } from './store.js';
import { getNode } from './repo.js';
import { href, parseHash, withPane, setFileOpener } from './router.js';

export const MIN_WIDTH = 340;
export const MIN_PAGE_WIDTH = 360;                 // room always left for the page behind the pane
export const OVERLAY_QUERY = '(max-width: 960px)'; // below this the pane covers the whole screen

const state = { path: null, node: null, mode: 'closed', width: null };
const subscribers = new Set();
let getRepo = () => null;
let trigger = null;                                // link that opened the pane, to restore focus on close
let pushedEntry = false;                           // did we push the current history entry?

export const previewState = () => ({ ...state });
export const isOpen = () => state.mode !== 'closed';
export const subscribe = (fn) => { subscribers.add(fn); return () => subscribers.delete(fn); };
const notify = (type) => {
  subscribers.forEach((fn) => { try { fn(type, previewState()); } catch (e) { console.error(e); } });
  if (type !== 'width') markActive();            // keep the page behind in step: highlight the open file, clear it on close
};

// ---- width -----------------------------------------------------------------------------------

export const maxWidth = () => Math.max(MIN_WIDTH, window.innerWidth - MIN_PAGE_WIDTH);
export const defaultWidth = () => Math.round(Math.min(Math.max(window.innerWidth * 0.46, 400), 780));
export const clampWidth = (w) => Math.round(Math.min(Math.max(w, MIN_WIDTH), maxWidth()));
export const currentWidth = () => clampWidth(state.width ?? prefs.get('previewWidth', null) ?? defaultWidth());
export function setWidth(w, { persist = true } = {}) {
  state.width = clampWidth(w);
  if (persist) prefs.set('previewWidth', state.width);
  notify('width');
}
export function resetWidth() { state.width = null; prefs.remove('previewWidth'); notify('width'); }

// ---- URL mirror ------------------------------------------------------------------------------

function writeUrl({ push = false } = {}) {
  const hash = withPane(location.hash, state.mode === 'closed' ? '' : state.path, state.mode);
  if (hash === location.hash) return;
  const url = `${location.pathname}${location.search}${hash}`;
  if (push) { history.pushState({ pane: 1 }, '', url); pushedEntry = true; }
  else history.replaceState(history.state, '', url);
}

// ---- actions ---------------------------------------------------------------------------------

/** Opens `path` in the pane, keeping the current mode if the pane is already open. Returns false if it isn't a file. */
export function open(path, { mode, from = null, push = true } = {}) {
  const node = getNode(getRepo(), path);
  if (!node || node.kind !== 'file') return false;
  const wasOpen = isOpen();
  const sameFile = wasOpen && state.path === node.path;
  state.path = node.path; state.node = node;
  state.mode = mode || (wasOpen ? state.mode : 'pane');
  if (from) trigger = from;
  writeUrl({ push: push && !wasOpen });
  notify(!wasOpen ? 'open' : sameFile ? 'mode' : 'switch');
  return true;
}

export function close() {
  if (!isOpen()) return;
  state.mode = 'closed'; state.path = null; state.node = null;
  if (pushedEntry && history.state?.pane) { pushedEntry = false; history.back(); }   // pops our own entry
  else writeUrl();
  notify('close');
}

export function setMode(mode) {
  if (!isOpen() || state.mode === mode) return;
  state.mode = mode;
  writeUrl();
  notify('mode');
}
export const toggleFull = () => setMode(state.mode === 'full' ? 'pane' : 'full');

/** Files in the opened file's folder, in the order the folder lists them. */
export const siblings = () => (state.node?.parent?.children || []).filter((n) => n.kind === 'file');
export const siblingIndex = () => siblings().findIndex((n) => n.path === state.path);

export function step(delta) {
  const list = siblings();
  const target = list[siblingIndex() + delta];
  return target ? open(target.path, { push: false }) : false;
}

export const takeTrigger = () => { const t = trigger; trigger = null; return t; };

// ---- integration with the router -----------------------------------------------------------------

/**
 * Called with the parsed route after the page behind the pane was rendered (routeChanged: true) or
 * when only the pane parameters changed (false: browser Back/Forward or an edited URL).
 */
export function applyRoute(route, { routeChanged }) {
  if (route.file) {
    if (route.file !== state.path || route.mode !== state.mode) {
      if (!open(route.file, { mode: route.mode, push: false }) && isOpen()) {     // the URL names a file that doesn't exist
        state.mode = 'closed'; state.path = null; state.node = null; pushedEntry = false;
        writeUrl(); notify('close');
      }
    }
  } else if (isOpen()) {
    if (routeChanged) { pushedEntry = false; writeUrl(); }      // user moved to another page: keep the file open
    else { state.mode = 'closed'; state.path = null; state.node = null; pushedEntry = false; notify('close'); }
  }
  markActive();
}

/** Highlights the row/card of the open file in whatever list the page behind the pane shows. */
export function markActive() {
  const current = state.path ? href.view(state.path) : null;
  for (const a of document.querySelectorAll('main a[href^="#/view/"]')) {
    const on = a.getAttribute('href') === current;
    a.classList.toggle('is-previewing', on);
    a.closest('.node-row, .diagram-card, .recent-card, .search-result')?.classList.toggle('is-previewing', on);
    if (on) a.setAttribute('aria-current', 'true'); else a.removeAttribute('aria-current');
  }
}

/** Call once, before the router starts, so these click handlers run first. */
export function initPreview({ repo }) {
  getRepo = repo;
  setFileOpener((path) => open(path, { from: document.activeElement }));
  document.addEventListener('click', (e) => {
    if (e.defaultPrevented || e.button !== 0 || e.metaKey || e.ctrlKey || e.shiftKey || e.altKey) return;   // modified clicks open a new tab
    const a = e.target.closest?.('a[href^="#/view/"]');
    if (a && open(parseHash(a.getAttribute('href')).path, { from: a })) e.preventDefault();
  }, true);
}
