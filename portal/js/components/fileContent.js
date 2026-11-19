import { el, clear } from '../core/dom.js';
import { EmptyState, ErrorState, SpinnerLine } from './states.js';
import { contentUrl } from '../core/urls.js';
import { formatBytes } from '../core/format.js';
import { getViewer } from '../viewers/index.js';
import { CONFIG } from '../../config.js';

/**
 * Renders `node` with the viewer for its type. This is the one place that loads a viewer (large-file
 * confirmation, spinner, error state with retry), whatever shows the result.
 *
 *   body:  element that receives the viewer's content
 *   tools: element that receives the viewer's type-specific controls (zoom, page/slide/sheet
 *          navigation ...). It stays empty for types that have none, and is hidden then.
 *
 * Every call gets its own host and toolbar, so a viewer that finishes late (the user already moved to
 * another file) can never write into the next file's view. Returns dispose(): removes everything and
 * runs the viewer's cleanup callbacks (observers, key handlers).
 *
 * Viewers receive ctx = { host, toolbar, contentUrl, signal, onDispose(fn) }.
 */
export function showFile({ body, tools }, node) {
  const host = el('div', { class: 'preview-host', dataset: { viewer: node.type.viewer, type: node.type.id } });
  const toolbar = el('div', { class: 'preview-tools__set' });
  body.append(host);
  tools.append(toolbar);

  let disposed = false;
  let disposers = [];
  let confirmed = false;
  const abort = new AbortController();

  const cleanup = () => { const fns = disposers; disposers = []; fns.forEach((fn) => { try { fn(); } catch (e) { console.error(e); } }); };
  const dispose = () => {
    if (disposed) return;
    disposed = true;
    abort.abort();
    cleanup();
    host.remove(); toolbar.remove();
  };

  async function load() {
    cleanup(); clear(host); clear(toolbar);
    host.append(SpinnerLine('Loading preview\u2026'));

    const big = node.size != null && node.size > CONFIG.maxPreviewMB * 1024 * 1024;
    if (big && !confirmed) {
      clear(host);
      host.append(EmptyState({
        title: 'This file is large',
        desc: `It\u2019s about ${formatBytes(node.size)}. Loading a preview may take a moment on a slow connection.`,
        iconName: 'info',
        action: el('button', { class: 'btn btn-primary', onClick: () => { confirmed = true; load(); } }, 'Load preview'),
      }));
      return;
    }

    try {
      const render = await getViewer(node.type.viewer);
      if (disposed) return;
      clear(host);
      await render(node, {
        host, toolbar, contentUrl: contentUrl(node), signal: abort.signal,
        onDispose: (fn) => { if (disposed || abort.signal.aborted) fn(); else disposers.push(fn); },
      });
      if (disposed) cleanup();
    } catch (err) {
      if (disposed) return;
      console.error(err);
      cleanup(); clear(host); clear(toolbar);
      host.append(ErrorState({
        title: 'This preview couldn\u2019t be loaded',
        desc: 'Something went wrong while rendering this file. Check your connection and try again.',
        retry: load,
      }));
    }
  }

  load();
  return dispose;
}
