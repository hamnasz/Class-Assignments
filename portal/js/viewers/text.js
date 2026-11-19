import { renderCode } from './code.js';

export const render = (node, ctx) => renderCode(node, ctx, { lang: null, numbers: false, wrap: true });
