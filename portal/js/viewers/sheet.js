import { el, clear } from '../core/dom.js';
import { fetchChecked } from '../core/net.js';
import { libs } from '../core/loader.js';

const ROW_CAP = 1000;
const COL_CAP = 60;

function buildTable(rows) {
  const table = el('table', { class: 'sheet-table' });
  const capped = rows.slice(0, ROW_CAP);
  const [head, ...body] = capped;
  const colCount = Math.min(COL_CAP, Math.max(0, ...capped.map((r) => r.length)));

  if (head) {
    const tr = el('tr', {}, [el('th', {}, ''), ...Array.from({ length: colCount }, (_, i) => el('th', {}, String(head[i] ?? '')))]);
    table.append(el('thead', {}, tr));
  }
  const tbody = el('tbody');
  body.forEach((row, i) => {
    const tr = el('tr', {}, [el('th', { scope: 'row' }, String(i + 1)), ...Array.from({ length: colCount }, (_, c) => el('td', {}, String(row[c] ?? '')))]);
    tbody.append(tr);
  });
  table.append(tbody);
  return { table, truncated: rows.length > ROW_CAP, total: rows.length };
}

export async function render(node, ctx) {
  const XLSX = await libs.xlsx();
  if (ctx.signal.aborted) return;
  const isCsv = node.type.id === 'csv';
  const readOptions = { sheetRows: ROW_CAP + 1 };
  let wb;
  if (isCsv) {
    const text = await (await fetchChecked(ctx.contentUrl, { signal: ctx.signal })).text();
    wb = XLSX.read(text, { ...readOptions, type: 'string' });
  } else {
    const buf = await (await fetchChecked(ctx.contentUrl, { signal: ctx.signal })).arrayBuffer();
    wb = XLSX.read(buf, { ...readOptions, type: 'array' });
  }

  const tabs = el('div', { class: 'sheet-tabs', role: 'tablist' });
  const scroll = el('div', { class: 'sheet-scroll' });
  const note = el('p', { class: 'state__desc', style: 'padding:0.5rem 1rem 0;margin:0' });
  ctx.host.append(scroll);

  const showSheet = (name) => {
    [...tabs.children].forEach((t) => t.setAttribute('aria-selected', String(t.dataset.name === name)));
    const rows = XLSX.utils.sheet_to_json(wb.Sheets[name], { header: 1, raw: false, defval: '' });
    const { table, truncated, total } = buildTable(rows);
    const fullRows = wb.Sheets[name]['!fullref'];
    const fullCount = fullRows ? XLSX.utils.decode_range(fullRows).e.r + 1 : total;
    clear(scroll);
    if (!rows.length) { scroll.append(el('p', { class: 'state__desc', style: 'padding:2rem' }, 'This sheet is empty.')); return; }
    scroll.append(table);
    note.textContent = truncated || fullCount > ROW_CAP ? `Showing the first ${ROW_CAP.toLocaleString('en')} of ${fullCount.toLocaleString('en')} rows.` : '';
  };

  for (const name of wb.SheetNames) {
    const tab = el('button', { class: 'sheet-tab', role: 'tab', dataset: { name }, onClick: () => showSheet(name) }, isCsv ? node.name : name);
    tabs.append(tab);
  }
  if (wb.SheetNames.length > 1) ctx.toolbar.append(tabs);      // nothing to navigate in a single sheet
  ctx.host.append(note);
  showSheet(wb.SheetNames[0]);
}
