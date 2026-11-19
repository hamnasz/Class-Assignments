import { el } from '../core/dom.js';
import { href } from '../core/router.js';
import { CONFIG } from '../../config.js';
import { SubjectCard } from '../components/subjectCard.js';
import { NodeList } from '../components/nodeRow.js';
import { DiagramGrid } from '../components/diagramCard.js';
import { EmptyState } from '../components/states.js';
import { plural, formatDate, relativeTime, formatBytes } from '../core/format.js';
import { icon, iconEl } from '../core/icons.js';

function recentFiles(repo, count) {
  return [...repo.files].filter((f) => f.modified).sort((a, b) => (a.modified < b.modified ? 1 : -1)).slice(0, count);
}

export function DashboardView(repo) {
  const root = el('div');

  root.append(el('section', { class: 'hero' }, [
    el('p', { class: 'hero__eyebrow' }, [iconEl('notebook'), 'Your study space']),
    el('h1', { class: 'hero__title font-serif' }, CONFIG.site.title),
    el('p', { class: 'hero__desc' }, CONFIG.site.description),
    repo.latest ? el('p', { class: 'hero__summary' }, `Last updated ${formatDate(repo.latest)}`) : null,
    el('button', { class: 'hero__search', type: 'button', onClick: () => document.querySelector('.search-trigger')?.click() }, [
      iconEl('search'), 'Search all files', el('span', { class: 'kbd' }, '/'),
    ]),
    el('div', { class: 'dashboard-stats', 'aria-label': 'Study collection' }, [
      [repo.subjects.length.toLocaleString('en'), 'Subjects'],
      [repo.totals.files.toLocaleString('en'), 'Study files'],
      [formatBytes(repo.totals.size), 'Resources'],
    ].map(([value, label]) => el('div', { class: 'dashboard-stat' }, [el('strong', {}, value), el('span', {}, label)]))),
  ]));

  root.append(el('section', { class: 'section' }, [
    el('div', { class: 'section__head' }, [el('h2', { class: 'section__title font-serif' }, 'Subjects'), el('span', { class: 'section__count' }, plural(repo.subjects.length, 'subject'))]),
    repo.subjects.length
      ? el('div', { class: 'subject-grid' }, repo.subjects.map(SubjectCard))
      : EmptyState({ title: 'No subjects yet', desc: 'Folders you add to the repository will appear here automatically \u2014 nothing to configure.', iconName: 'folder' }),
  ]));

  // Diagrams get their own section, led by pictures instead of file rows.
  if (repo.diagrams.length) {
    const shown = repo.diagrams.slice(0, CONFIG.diagrams?.dashboardCount ?? 6);
    root.append(el('section', { class: 'section' }, [
      el('div', { class: 'section__head' }, [
        el('h2', { class: 'section__title font-serif' }, 'Diagrams'),
        el('span', { style: 'display:flex;align-items:baseline;gap:var(--space-4)' }, [
          el('span', { class: 'section__count' }, plural(repo.diagrams.length, 'diagram')),
          repo.diagrams.length > shown.length
            ? el('a', { class: 'section__link', href: href.search({ type: 'diagrams' }) }, 'View all')
            : null,
        ]),
      ]),
      DiagramGrid(shown),
    ]));
  }

  if (repo.rootFiles.length) {
    root.append(el('section', { class: 'section' }, [
      el('div', { class: 'section__head' }, el('h2', { class: 'section__title font-serif' }, 'In the repository root')),
      NodeList(repo.rootFiles),
    ]));
  }

  const recent = repo.hasDates ? recentFiles(repo, CONFIG.recentCount) : [];
  if (recent.length) {
    root.append(el('section', { class: 'section' }, [
      el('div', { class: 'section__head' }, el('h2', { class: 'section__title font-serif' }, 'Recently updated')),
      el('div', { class: 'recent-grid' }, recent.map((f) => el('a', { class: 'recent-card', href: href.view(f.path) }, [
        el('span', { class: 'icon', style: 'color:var(--ink-faint);font-size:1.3rem', html: icon(f.type.glyph) }),
        el('span', {}, [
          el('div', { class: 'recent-card__title' }, f.name),
          el('div', { class: 'recent-card__meta' }, `${f.type.label}, ${relativeTime(f.modified)}`),
        ]),
      ]))),
    ]));
  }

  return root;
}
