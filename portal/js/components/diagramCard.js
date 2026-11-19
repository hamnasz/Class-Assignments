import { el } from '../core/dom.js';
import { href } from '../core/router.js';
import { iconEl } from '../core/icons.js';
import { isRestricted } from '../core/permissions.js';
import { formatBytes } from '../core/format.js';
import { diagramThumbnail, diagramTitle, thumbnailAllowed } from '../core/diagrams.js';

// Previews are only drawn once a card is (nearly) on screen.
const observer = 'IntersectionObserver' in window
  ? new IntersectionObserver((entries) => {
    for (const e of entries) {
      if (!e.isIntersecting) continue;
      observer.unobserve(e.target);
      pending.delete(e.target);
      e.target.__loadPreview?.();
    }
  }, { rootMargin: '240px' })
  : null;

const pending = new Set();
if (observer) {
  // One route-level observer, not one observer per card.
  new MutationObserver(() => {
    for (const card of pending) if (!card.isConnected) { observer.unobserve(card); pending.delete(card); }
  }).observe(document.documentElement, { childList: true, subtree: true });
}

/** The folder a diagram lives in, shown under its title ("Cloud Computing / Week 3"). */
const folderOf = (node) => node.path.split('/').slice(0, -1).join(' / ');

/**
 * A card made for diagrams: a drawing-board thumbnail on a dotted canvas, then the title and
 * where it lives. Unlike a file row it leads with the picture, because that is how a student
 * recognises the diagram they are looking for.
 */
export function DiagramCard(node) {
  const sheet = el('div', { class: 'diagram-card__sheet' }, el('span', { class: 'diagram-card__placeholder', 'aria-hidden': 'true' }, iconEl('diagram')));
  const canvas = el('div', { class: 'diagram-card__canvas', 'aria-hidden': 'true' }, [
    sheet,
    el('span', { class: 'diagram-card__tag' }, [iconEl('diagram'), 'draw.io']),
  ]);

  const folder = folderOf(node);
  const restricted = isRestricted(node.path);
  const card = el('a', { class: 'diagram-card', href: href.node(node), title: node.name }, [
    canvas,
    el('div', { class: 'diagram-card__body' }, [
      el('h3', { class: 'diagram-card__title font-serif' }, diagramTitle(node)),
      folder ? el('div', { class: 'diagram-card__path' }, folder) : null,
      el('div', { class: 'diagram-card__meta' }, [
        restricted ? el('span', { class: 'badge-restricted' }, [iconEl('lock'), 'View only']) : null,
        node.size != null ? el('span', {}, formatBytes(node.size)) : null,
      ]),
    ]),
  ]);

  if (thumbnailAllowed(node)) {
    card.__loadPreview = async () => {
      if (!card.isConnected) return;
      const svg = await diagramThumbnail(node);
      if (!svg || !card.isConnected) return;
      sheet.replaceChildren(svg);
      card.classList.add('has-preview');
    };
    if (observer) { pending.add(card); observer.observe(card); } else requestAnimationFrame(() => card.__loadPreview());
  }
  return card;
}

export const DiagramGrid = (nodes) => el('div', { class: 'diagram-grid' }, nodes.map(DiagramCard));
