import { el } from '../core/dom.js';
import { icon } from '../core/icons.js';
import { DownloadButton } from '../components/downloadButton.js';
import { downloadUrl } from '../core/urls.js';
import { formatBytes, formatDate } from '../core/format.js';

const REASON = {
  legacy: 'This older binary format can\u2019t be rendered reliably in a browser.',
  unsupported: 'This file type doesn\u2019t have an in-browser preview.',
};

/** Fallback for anything that can't be previewed: what the file is, plus a way to get it. */
export async function render(node, ctx) {
  const url = downloadUrl(node);
  const facts = [['Name', node.name], ['Type', node.type.label], node.size != null ? ['Size', formatBytes(node.size)] : null, node.modified ? ['Modified', formatDate(node.modified)] : null, ['Location', node.path]].filter(Boolean);
  ctx.host.append(el('div', { class: 'file-info' }, [
    el('span', { class: 'state__icon', html: icon(node.type.glyph) }),
    el('p', { class: 'state__title' }, 'No preview available'),
    el('p', { class: 'state__desc' }, `${REASON[node.type.viewer] || REASON.unsupported} ${url
      ? 'Download it to open it in the right application.'
      : 'This file is available to view only, so it can\u2019t be downloaded from here.'}`),
    el('dl', { class: 'file-info__facts' }, facts.flatMap(([k, v]) => [el('dt', {}, k), el('dd', {}, v)])),
    url ? el('div', { class: 'file-info__actions' }, DownloadButton(node)) : null,
  ].filter(Boolean)));
}
