import { el, clear } from '../core/dom.js';
import { Breadcrumbs } from '../components/breadcrumbs.js';
import { NodeList } from '../components/nodeRow.js';
import { DiagramGrid } from '../components/diagramCard.js';
import { EmptyState } from '../components/states.js';
import { getNode, ancestors, subjectInfo } from '../core/repo.js';
import { plural } from '../core/format.js';
import { iconEl } from '../core/icons.js';

export function BrowseView(repo, path) {
  const dir = getNode(repo, path);
  if (!dir || dir.kind !== 'dir') return NotFound(path);

  const root = el('div');
  root.append(Breadcrumbs(ancestors(dir), dir));

  const isSubject = dir.parent && !dir.parent.parent;
  const info = isSubject ? subjectInfo(dir) : null;
  root.append(el('header', { class: 'browse-header' }, [
    el('h1', { class: 'font-serif', style: 'font-size:var(--text-2xl)' }, info?.title || dir.name),
    info ? el('p', { style: 'color:var(--ink-soft);margin-top:.5rem;max-width:var(--measure)' }, info.description) : null,
    dir.restricted ? el('p', { class: 'badge-restricted', style: 'margin-top:.75rem' }, [iconEl('lock'), 'Files in this folder are available to view only.']) : null,
  ].filter(Boolean)));

  if (!dir.children.length) {
    root.append(EmptyState({ title: 'This folder is empty', desc: 'Nothing has been added here yet.', iconName: 'folder' }));
    return root;
  }

  // Diagrams in this folder are shown as cards; everything else stays in the normal list.
  const diagrams = dir.children.filter((n) => n.kind === 'file' && n.type.group === 'diagrams');
  const others = diagrams.length ? dir.children.filter((n) => n.kind !== 'file' || n.type.group !== 'diagrams') : dir.children;

  if (diagrams.length) {
    root.append(el('section', { class: 'section', style: 'margin-bottom:var(--space-6)' }, [
      el('div', { class: 'section__head' }, [
        el('h2', { class: 'section__title font-serif' }, 'Diagrams'),
        el('span', { class: 'section__count' }, plural(diagrams.length, 'diagram')),
      ]),
      DiagramGrid(diagrams),
    ]));
  }
  if (others.length) {
    const count = el('span', { class: 'node-toolbar__count', role: 'status' }, plural(others.length, diagrams.length ? 'other item' : 'item'));
    const list = NodeList(others);
    const filter = el('input', { class: 'browse-filter', type: 'search', placeholder: 'Find in this folder…', 'aria-label': 'Filter files and folders' });
    const empty = el('p', { class: 'state__desc', hidden: true }, 'No matching files or folders.');
    let timer;
    filter.addEventListener('input', () => {
      clearTimeout(timer);
      timer = setTimeout(() => {
        if (!list.isConnected) return;
        const q = filter.value.trim().toLocaleLowerCase();
        let shown = 0;
        [...list.children].forEach((row, i) => {
          const match = others[i].name.toLocaleLowerCase().includes(q);
          row.hidden = !match;
          if (match) shown++;
        });
        count.textContent = q ? `${shown} of ${others.length} items` : plural(others.length, 'item');
        empty.hidden = shown !== 0;
      }, 100);
    });
    root.append(el('div', { class: 'node-toolbar' }, [count, filter]), list, empty);
  }
  return root;
}

function NotFound(path) {
  return EmptyState({ title: 'Folder not found', desc: `\u201c${path}\u201d doesn\u2019t exist in this repository.`, iconName: 'warning' });
}
