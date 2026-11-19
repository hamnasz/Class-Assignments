import { el, clear } from '../core/dom.js';
import { icon, iconEl } from '../core/icons.js';
import { TypeGlyph } from './typeGlyph.js';
import { DownloadButton } from './downloadButton.js';
import { showFile } from './fileContent.js';
import { downloadUrl } from '../core/urls.js';
import { formatBytes, formatDate } from '../core/format.js';
import {
  subscribe, previewState, isOpen, close, toggleFull, open, step, siblings, siblingIndex, takeTrigger,
  currentWidth, setWidth, resetWidth, maxWidth, clampWidth, MIN_WIDTH, OVERLAY_QUERY,
} from '../core/preview.js';

const root = document.documentElement;
const iconButton = (name, label, onClick, extra = {}) =>
  el('button', { class: 'btn btn-icon', type: 'button', 'aria-label': label, title: label, onClick, html: icon(name), ...extra });

/**
 * The right-hand file pane. Mounted once; opens, switches and closes in response to preview.js.
 * Layout is driven by data attributes on <html>:
 *   data-preview="closed | pane | full"   data-preview-cover  (pane hides the page: full screen or small screen)
 * and the --preview-w custom property (see css/preview.css).
 */
export function PreviewPane() {
  const overlayQuery = window.matchMedia(OVERLAY_QUERY);

  // ---- header -----------------------------------------------------------------------------
  const title = el('div', { class: 'preview-title' });
  const backBtn = iconButton('arrow-left', 'Back to files', () => close(), { class: 'btn btn-icon preview-back' });
  const prevBtn = iconButton('chevron-left', 'Previous file ( [ )', () => step(-1));
  const nextBtn = iconButton('chevron', 'Next file ( ] )', () => step(1));
  const position = el('span', { class: 'preview-step__count', 'aria-live': 'polite' });
  const stepper = el('div', { class: 'preview-step', role: 'group', 'aria-label': 'Files in this folder' }, [prevBtn, position, nextBtn]);
  const filesBtn = iconButton('list', 'Files in this folder', () => toggleFiles(), { 'aria-haspopup': 'true', 'aria-expanded': 'false', class: 'btn btn-icon preview-filesbtn' });
  const linkSlot = el('span', { class: 'preview-slot' });
  const downloadSlot = el('span', { class: 'preview-slot' });
  const fullBtn = iconButton('expand', 'Full screen', () => toggleFull(), { class: 'btn btn-icon preview-fullbtn' });
  const closeBtn = iconButton('close', 'Close preview ( Esc )', () => close(), { class: 'btn btn-icon preview-closebtn' });
  const head = el('header', { class: 'preview-head' }, [
    backBtn, title,
    el('div', { class: 'preview-actions' }, [stepper, filesBtn, linkSlot, downloadSlot, fullBtn, closeBtn]),
  ]);

  // ---- file switcher -----------------------------------------------------------------------
  const filesPanel = el('div', { class: 'preview-files', role: 'dialog', 'aria-label': 'Files in this folder', hidden: true });
  function renderFiles() {
    clear(filesPanel);
    const { node } = previewState();
    const list = siblings();
    const folder = node?.parent?.name || 'Files';
    const filter = el('input', { type: 'search', class: 'preview-files__filter', placeholder: 'Filter files\u2026', 'aria-label': 'Filter files' });
    const items = el('div', { class: 'preview-files__list', role: 'list' });
    const draw = (q = '') => {
      clear(items);
      const shown = list.filter((n) => n.name.toLowerCase().includes(q.toLowerCase()));
      if (!shown.length) items.append(el('p', { class: 'preview-files__empty' }, 'No files match.'));
      for (const n of shown) {
        const current = n.path === node.path;
        items.append(el('button', {
          class: 'preview-files__item', type: 'button', role: 'listitem', 'aria-current': current ? 'true' : null,
          onClick: () => { toggleFiles(false); if (!current) open(n.path, { push: false }); },
        }, [TypeGlyph(n, { size: 'sm' }), el('span', { class: 'preview-files__name' }, n.name), el('span', { class: 'preview-files__size' }, n.size != null ? formatBytes(n.size) : '')]));
      }
    };
    filter.addEventListener('input', () => draw(filter.value));
    filter.addEventListener('keydown', (e) => { if (e.key === 'ArrowDown') { e.preventDefault(); items.querySelector('button')?.focus(); } });
    items.addEventListener('keydown', (e) => {
      if (e.key !== 'ArrowDown' && e.key !== 'ArrowUp') return;
      e.preventDefault();
      const btns = [...items.querySelectorAll('button')];
      const i = btns.indexOf(document.activeElement);
      btns[Math.min(Math.max(i + (e.key === 'ArrowDown' ? 1 : -1), 0), btns.length - 1)]?.focus();
    });
    filesPanel.append(
      el('div', { class: 'preview-files__head' }, [el('strong', {}, folder), el('span', {}, `${list.length} file${list.length === 1 ? '' : 's'}`)]),
      list.length > 8 ? filter : null,
      items,
    );
    draw();
    return { filter, items };
  }
  function toggleFiles(force) {
    const show = force ?? filesPanel.hidden;
    filesPanel.hidden = !show;
    filesBtn.setAttribute('aria-expanded', String(show));
    if (show) { const { filter, items } = renderFiles(); (filter.isConnected ? filter : items.querySelector('[aria-current]') || items.querySelector('button'))?.focus(); }
    else if (pane.contains(document.activeElement)) filesBtn.focus();
  }

  // ---- body ----------------------------------------------------------------------------------
  const tools = el('div', { class: 'preview-tools', dataset: { empty: 'true' } });
  const body = el('div', { class: 'preview-body' });
  new MutationObserver(() => { tools.dataset.empty = String(![...tools.querySelectorAll('.preview-tools__set')].some((s) => s.childElementCount)); })
    .observe(tools, { childList: true, subtree: true });

  const resizer = el('div', {
    class: 'preview-resizer', role: 'separator', 'aria-orientation': 'vertical', 'aria-label': 'Resize preview',
    tabindex: '0', 'aria-valuemin': String(MIN_WIDTH),
  });

  const pane = el('aside', { class: 'preview-pane', id: 'preview-pane', 'aria-label': 'File preview', tabindex: '-1', inert: true }, [
    resizer,
    el('div', { class: 'preview-pane__inner' }, [head, tools, filesPanel, body]),
  ]);

  // ---- current content -----------------------------------------------------------------------
  let disposeContent = null;
  let shownPath = null;
  let closeTimer = null;
  let lockTimer = null;

  function renderHead({ node }) {
    clear(title);
    const meta = [node.type.label];
    if (node.size != null) meta.push(formatBytes(node.size));
    if (node.modified) meta.push(formatDate(node.modified));
    title.append(TypeGlyph(node, { size: 'sm' }), el('div', { class: 'preview-title__text' }, [
      el('div', { class: 'preview-title__name', title: node.path }, node.name),
      el('div', { class: 'preview-title__meta' }, meta.join(' \u00b7 ')),
    ]));
    const list = siblings(), i = siblingIndex();
    stepper.hidden = list.length < 2;
    filesBtn.hidden = list.length < 2;
    position.textContent = `${i + 1} / ${list.length}`;
    prevBtn.disabled = i <= 0;
    nextBtn.disabled = i >= list.length - 1;

    clear(linkSlot); clear(downloadSlot);
    const raw = downloadUrl(node);        // null for view-only files: their raw URL is never exposed
    if (raw && node.type.viewer !== 'diagram') linkSlot.append(el('a', { class: 'btn btn-icon', href: raw, target: '_blank', rel: 'noopener', 'aria-label': 'Open in a new tab', title: 'Open in a new tab', html: icon('external') }));
    downloadSlot.append(DownloadButton(node, { compact: true }));
  }

  function renderContent(st) {
    renderHead(st);
    if (shownPath === st.path) return;
    shownPath = st.path;
    disposeContent?.();
    toggleFiles(false);
    disposeContent = showFile({ body, tools }, st.node);
    body.scrollTop = 0;
  }

  // ---- layout (data attributes on <html>) ------------------------------------------------------
  const appShell = () => document.querySelector('.app-shell');
  function applyLayout(st = previewState()) {
    const open = st.mode !== 'closed';
    const overlay = overlayQuery.matches;
    const cover = open && (st.mode === 'full' || overlay);
    root.dataset.preview = st.mode;
    if (cover) root.setAttribute('data-preview-cover', ''); else root.removeAttribute('data-preview-cover');
    // Lock page scrolling once the pane has finished covering it; unlock the moment it starts to uncover it.
    clearTimeout(lockTimer);
    if (cover) lockTimer = setTimeout(() => root.classList.add('preview-locked'), 340);
    else root.classList.remove('preview-locked');
    root.style.setProperty('--preview-w', `${currentWidth()}px`);
    const full = st.mode === 'full';
    fullBtn.innerHTML = icon(full ? 'shrink' : 'expand');
    const label = full ? 'Exit full screen' : 'Full screen';
    fullBtn.setAttribute('aria-label', label); fullBtn.title = label;
    fullBtn.setAttribute('aria-pressed', String(full));
    fullBtn.hidden = overlay;                         // already covering the screen on small devices
    pane.inert = !open;
    pane.setAttribute('aria-hidden', String(!open));
    const shell = appShell();
    if (shell) { shell.inert = cover; if (cover) shell.setAttribute('aria-hidden', 'true'); else shell.removeAttribute('aria-hidden'); }
    resizer.setAttribute('aria-valuenow', String(currentWidth()));
    resizer.setAttribute('aria-valuemax', String(maxWidth()));
  }

  subscribe((type, st) => {
    if (type === 'width') { applyLayout(st); return; }
    if (type === 'close') {
      disposeContent?.(); disposeContent = null; shownPath = null;
      applyLayout(st);
      clearTimeout(closeTimer);
      closeTimer = setTimeout(() => { if (!isOpen()) { disposeContent?.(); disposeContent = null; shownPath = null; clear(title); } }, 320);   // after the slide-out
      const back = takeTrigger();
      (back?.isConnected ? back : document.getElementById('main'))?.focus?.({ preventScroll: true });
      return;
    }
    clearTimeout(closeTimer);
    applyLayout(st);
    renderContent(st);
    if (type === 'open') requestAnimationFrame(() => pane.focus({ preventScroll: true }));
  });
  overlayQuery.addEventListener?.('change', () => applyLayout());
  window.addEventListener('resize', () => applyLayout());
  applyLayout();

  // ---- resizing ---------------------------------------------------------------------------------
  resizer.addEventListener('pointerdown', (e) => {
    if (e.button !== 0 || overlayQuery.matches || previewState().mode !== 'pane') return;
    e.preventDefault();
    const startX = e.clientX, startW = currentWidth();
    resizer.setPointerCapture(e.pointerId);
    root.classList.add('is-resizing');
    const move = (ev) => { root.style.setProperty('--preview-w', `${clampWidth(startW + (startX - ev.clientX))}px`); };
    const up = (ev) => {
      resizer.removeEventListener('pointermove', move);
      resizer.removeEventListener('pointerup', up); resizer.removeEventListener('pointercancel', up);
      root.classList.remove('is-resizing');
      setWidth(startW + (startX - ev.clientX));
    };
    resizer.addEventListener('pointermove', move);
    resizer.addEventListener('pointerup', up); resizer.addEventListener('pointercancel', up);
  });
  resizer.addEventListener('keydown', (e) => {
    const big = e.shiftKey ? 96 : 24;
    if (e.key === 'ArrowLeft') setWidth(currentWidth() + big);
    else if (e.key === 'ArrowRight') setWidth(currentWidth() - big);
    else if (e.key === 'Home') setWidth(maxWidth());
    else if (e.key === 'End') setWidth(MIN_WIDTH);
    else return;
    e.preventDefault();
  });
  resizer.addEventListener('dblclick', () => resetWidth());

  // ---- keyboard -----------------------------------------------------------------------------------
  const typing = (t) => t && (t.isContentEditable || ['INPUT', 'TEXTAREA', 'SELECT'].includes(t.tagName));
  document.addEventListener('keydown', (e) => {
    if (!isOpen() || e.defaultPrevented || e.metaKey || e.ctrlKey || e.altKey) return;
    if (e.key === 'Tab' && root.hasAttribute('data-preview-cover')) {
      const focusable = [...pane.querySelectorAll('button, a[href], input, select, [tabindex="0"]')]
        .filter((n) => !n.disabled && !n.closest('[hidden], [inert]') && n.getClientRects().length);
      const first = focusable[0], last = focusable.at(-1);
      if (e.shiftKey && (document.activeElement === first || document.activeElement === pane)) { e.preventDefault(); last?.focus(); }
      else if (!e.shiftKey && (document.activeElement === last || document.activeElement === pane)) { e.preventDefault(); first?.focus(); }
      return;
    }
    if (e.key === 'Escape') {
      if (document.querySelector('.search-overlay')) return;           // the search dialog owns Escape
      e.preventDefault();
      if (!filesPanel.hidden) toggleFiles(false);
      else if (previewState().mode === 'full') toggleFull();
      else close();
    } else if ((e.key === '[' || e.key === ']') && !typing(e.target)) {
      e.preventDefault(); step(e.key === '[' ? -1 : 1);
    }
  }, true);                                   // capture: see Escape before a dialog removes itself
  document.addEventListener('pointerdown', (e) => { if (!filesPanel.hidden && !filesPanel.contains(e.target) && !filesBtn.contains(e.target)) toggleFiles(false); });

  return pane;
}
