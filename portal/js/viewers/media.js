import { el } from '../core/dom.js';
import { icon } from '../core/icons.js';
import { TypeGlyph } from '../components/typeGlyph.js';
import { ErrorState } from '../components/states.js';

const SPEEDS = [0.5, 0.75, 1, 1.25, 1.5, 2];

/** Native controls give play/pause, timeline, volume and (for video) full screen; this adds speed and loop. */
export async function render(node, ctx) {
  const isAudio = node.type.id === 'audio';
  const player = el(isAudio ? 'audio' : 'video', { src: ctx.contentUrl, controls: true, preload: 'metadata', playsinline: !isAudio, 'aria-label': node.name });
  if (isAudio) {
    ctx.host.append(el('div', { class: 'media-stage' }, el('div', { class: 'media-card' }, [
      TypeGlyph(node, { size: 'lg' }), el('div', { class: 'media-card__name' }, node.name), player,
    ])));
  } else {
    ctx.host.append(el('div', { class: 'media-stage media-stage--video' }, player));
  }

  const speed = el('button', { class: 'btn', type: 'button', title: 'Playback speed', 'aria-label': 'Playback speed' }, '1\u00d7');
  speed.addEventListener('click', () => {
    const next = SPEEDS[(SPEEDS.indexOf(player.playbackRate) + 1) % SPEEDS.length] ?? 1;
    player.playbackRate = next;
    speed.textContent = `${next}\u00d7`;
  });
  const loop = el('button', { class: 'btn btn-icon', type: 'button', title: 'Loop', 'aria-label': 'Loop', 'aria-pressed': 'false', html: icon('rotate-cw') });
  loop.addEventListener('click', () => {
    player.loop = !player.loop;
    loop.classList.toggle('is-on', player.loop); loop.setAttribute('aria-pressed', String(player.loop));
  });
  ctx.toolbar.append(speed, loop);

  // Don't wait for metadata (some mobile browsers defer loading until play); just report a broken file.
  player.addEventListener('error', () => {
    ctx.host.replaceChildren(ErrorState({ title: 'This media can\u2019t be played', desc: 'The file may be damaged, or your browser may not support its format.' }));
  }, { once: true });
  ctx.onDispose(() => { try { player.pause(); player.removeAttribute('src'); player.load(); } catch { /* ignore */ } });
}
