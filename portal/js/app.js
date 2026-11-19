import { el, mount, clear } from './core/dom.js';
import { initTheme } from './core/theme.js';
import { startRouter, parseHash, navigate, href, withPane } from './core/router.js';
import { initPreview, applyRoute, markActive } from './core/preview.js';
import { loadRepository, RepoError, getNode } from './core/repo.js';
import { buildIndex } from './core/search.js';
import { CONFIG } from '../config.js';
import { Navigation } from './components/navigation.js';
import { ErrorState, EmptyState, SkeletonGrid } from './components/states.js';
import { PreviewPane } from './components/previewPane.js';
import { icon, iconEl } from './core/icons.js';
import { repoUrl } from './core/urls.js';
import { loadSite } from './core/site.js';

import { DashboardView } from './views/dashboard.js';
import { BrowseView } from './views/browse.js';
import { SearchResultsView } from './views/searchResults.js';

// Settings left on 'auto' in config.js are resolved before anything reads them.
await loadSite();

initTheme();

const state = { repo: null, index: [], error: null };

const app = el('div', { class: 'app-shell' });
document.body.prepend(app);

app.append(el('a', { class: 'skip-link', href: '#main' }, 'Skip to content'));

const nav = Navigation({ index: () => state.index });
app.append(nav);

const banner = el('div');
const main = el('main', { id: 'main', class: 'main container route-fade', tabindex: '-1' });
app.append(banner, main);

app.append(el('footer', { class: 'site-footer' }, el('div', { class: 'container site-footer__row' }, [
  el('span', {}, `${CONFIG.site.title} study portal`),
  CONFIG.showRepoLink && CONFIG.repo.owner && CONFIG.repo.name ? el('a', { href: repoUrl(), target: '_blank', rel: 'noopener' }, [iconEl('external'), ' Repository on GitHub']) : null,
].filter(Boolean))));

document.body.append(PreviewPane());

function titleFor(route, repo) {
  const site = CONFIG.site.title;
  if (route.name === 'home') return site;
  if (route.name === 'browse') { const n = route.path ? repo?.byPath.get(route.path) : null; return n ? `${n.name} \u2013 ${site}` : site; }
  if (route.name === 'search') return route.q ? `\u201c${route.q}\u201d \u2013 Search \u2013 ${site}` : `Search \u2013 ${site}`;
  return site;
}

function render(node) {
  clear(main);
  main.append(node);
  main.classList.remove('route-fade');
  void main.offsetWidth;
  main.classList.add('route-fade');
}

function renderRoute(route) {
  if (state.error) { render(errorView()); return; }
  const repo = state.repo;
  switch (route.name) {
    case 'home': render(DashboardView(repo)); break;
    case 'browse': render(BrowseView(repo, route.path)); break;
    case 'view': openFromLegacyLink(repo, route.path); break;
    case 'search': render(SearchResultsView(repo, state.index, { q: route.q, group: route.type })); break;
    default: render(ErrorState({ title: 'Page not found', desc: 'That address doesn\u2019t match anything in this portal.' }));
  }
}

/**
 * Files no longer have a page of their own. An old "#/view/<path>" link (bookmark, link from another
 * tab) is turned into: the file's folder behind, the file open in the side pane.
 */
function openFromLegacyLink(repo, path) {
  const node = repo && getNode(repo, path);
  if (node?.kind !== 'file') {
    render(EmptyState({ title: 'File not found', desc: `\u201c${path}\u201d doesn\u2019t exist in this repository.`, iconName: 'warning' }));
    return;
  }
  navigate(withPane(href.browse(node.parent?.path || ''), node.path), { replace: true });
}

function errorView() {
  const err = state.error;
  const copy = {
    'not-found': { title: 'File list not found', desc: 'The portal builds its file list when the site is deployed. When running locally, run \u201cnode scripts/build.mjs\u201d and open the dist folder.' },
    network: { title: 'Couldn\u2019t connect', desc: 'Check your connection and try again.' },
  }[err.kind] || { title: 'Something went wrong', desc: err.message || 'The file list couldn\u2019t be loaded.' };
  return ErrorState({ ...copy, retry });
}

async function loadData() {
  clear(banner);
  try {
    state.repo = await loadRepository();
    state.index = buildIndex(state.repo);
    state.error = null;
  } catch (err) {
    state.repo = null; state.index = [];
    state.error = err instanceof RepoError ? err : new RepoError('unknown', err.message);
  }
  nav.querySelector('.search-trigger')?.removeAttribute('aria-disabled');
}

function retry() {
  render(el('div', { class: 'main--tight' }, [
    el('div', { class: 'skeleton skeleton-card', style: 'height:9rem;margin-bottom:var(--space-10)' }),
    SkeletonGrid(),
  ]));
  loadData().then(() => {
    const route = parseHash(location.hash);
    renderRoute(route);
    applyRoute(route, { routeChanged: true });
    document.title = titleFor(route, state.repo);
  });
}

async function init() {
  nav.querySelector('.search-trigger')?.setAttribute('aria-disabled', 'true');
  render(el('div', { class: 'main--tight' }, [
    el('div', { class: 'skeleton skeleton-card', style: 'height:9rem;margin-bottom:var(--space-10)' }),
    SkeletonGrid(),
  ]));
  await loadData();
  initPreview({ repo: () => state.repo });   // before the router, so its link handler runs first
  startRouter((route, { restoreScroll } = {}) => {
    renderRoute(route);
    if (route.name !== 'view') {
      applyRoute(route, { routeChanged: true });
      document.title = titleFor(route, state.repo);
      window.scrollTo(0, restoreScroll ?? 0);
    }
  }, (route) => applyRoute(route, { routeChanged: false }));
}

init();
