// Optional real-browser integration suite. Dev dependencies only; no production dependencies.
// npm install --no-save playwright && npx playwright install chromium
// python -m pip install reportlab python-docx python-pptx openpyxl Pillow
// node scripts/tests/browser-smoke.mjs
import assert from 'node:assert/strict';
import { createServer } from 'node:http';
import { cpSync, mkdtempSync, readFileSync, writeFileSync, readdirSync, statSync, rmSync, existsSync } from 'node:fs';
import { execFileSync } from 'node:child_process';
import { tmpdir } from 'node:os';
import { dirname, resolve, join, extname } from 'node:path';
import { fileURLToPath } from 'node:url';
const { chromium } = await import(process.env.PLAYWRIGHT_MODULE || 'playwright');
const root = resolve(dirname(fileURLToPath(import.meta.url)), '../..');
const temp = mkdtempSync(join(tmpdir(), 'portal-browser-'));
let browser, server;
try {
  execFileSync(process.execPath, ['scripts/build.mjs'], { cwd: root, stdio: 'inherit' });
  cpSync(join(root, 'dist'), temp, { recursive: true });
  execFileSync(process.env.PYTHON || 'python3', [join(root, 'scripts/tests/generate-fixtures.py'), join(temp, 'QA')], { stdio: 'inherit' });
  cpSync(join(temp, 'QA'), join(temp, 'FYP/QA'), { recursive: true });
  const manifest = JSON.parse(readFileSync(join(temp, 'portal/manifest.json')));
  for (const folder of ['QA', 'FYP/QA']) for (const name of readdirSync(join(temp, folder))) manifest.entries.push({ path: `${folder}/${name}`, size: statSync(join(temp, folder, name)).size, modified: '2026-11-01T00:00:00Z' });
  writeFileSync(join(temp, 'portal/manifest.json'), JSON.stringify(manifest));
  const mime = { '.html': 'text/html', '.js': 'text/javascript', '.mjs': 'text/javascript', '.css': 'text/css', '.json': 'application/json', '.pdf': 'application/pdf', '.png': 'image/png', '.woff2': 'font/woff2' };
  server = createServer((req, res) => {
    const path = resolve(temp, '.' + decodeURIComponent(new URL(req.url, 'http://localhost').pathname).replace(/\/$/, '/index.html'));
    if (!path.startsWith(temp + '/') || !existsSync(path) || statSync(path).isDirectory()) { res.writeHead(404); res.end(); return; }
    const data = readFileSync(path), headers = { 'Content-Type': mime[extname(path)] || 'application/octet-stream', 'Accept-Ranges': 'bytes' };
    if (req.headers.range) {
      const match = /bytes=(\d+)-(\d*)/.exec(req.headers.range);
      if (match) { const start = +match[1], end = Math.min(match[2] ? +match[2] : data.length - 1, data.length - 1);
        res.writeHead(206, { ...headers, 'Content-Range': `bytes ${start}-${end}/${data.length}`, 'Content-Length': end - start + 1 }); res.end(data.subarray(start, end + 1)); return; }
    }
    res.writeHead(200, { ...headers, 'Content-Length': data.length }); res.end(data);
  });
  await new Promise(r => server.listen(0, '127.0.0.1', r));
  const base = `http://127.0.0.1:${server.address().port}`;
  const range = await fetch(`${base}/QA/120.pdf`, { headers: { Range: 'bytes=0-99' } });
  assert.equal(range.status, 206); assert.equal((await range.arrayBuffer()).byteLength, 100);
  browser = await chromium.launch({ headless: true, ...(process.env.CHROMIUM_PATH ? { executablePath: process.env.CHROMIUM_PATH } : {}) });
  const page = await browser.newPage({ viewport: { width: 1440, height: 900 }, deviceScaleFactor: 2 });
  const errors = []; page.on('pageerror', e => errors.push(e.message));
  let requests = []; page.on('request', req => requests.push(req.url()));
  await page.goto(base); await page.locator('.subject-card').first().waitFor();
  assert.ok(!requests.some(u => /\/vendor\/(pdfjs|pptx|xlsx|docx)\//.test(u)), 'homepage keeps Office/PDF libraries lazy');
  assert.ok(await page.locator('.dashboard-stats').isVisible());
  const open = async path => {
    await page.evaluate(async path => (await import('./portal/js/core/preview.js')).open(path), path);
    await page.locator('.preview-title__name').waitFor();
  };
  const rendered = async n => page.locator(`.pdf-page[data-page="${n}"][data-state="rendered"] canvas:not([hidden])`).waitFor();
  const jump = async n => { const input = page.getByRole('spinbutton', { name: 'Page number' }); await input.fill(String(n)); await input.press('Enter'); await rendered(n); };
  const measurements = [];
  for (const count of [1, 10, 50, 120]) {
    const start = Date.now(); await open(`QA/${count}.pdf`); await rendered(1);
    measurements.push({ pages: count, firstVisibleMs: Date.now() - start });
    assert.ok(await page.locator('.pdf-page canvas').count() <= 8);
    if (count > 10) { await jump(count); assert.ok(await page.locator('.pdf-page canvas').count() <= 8); }
  }
  await jump(70); await page.getByRole('button', { name: 'Zoom in', exact: true }).click(); await rendered(70);
  assert.ok(await page.locator('.pdf-page canvas').count() <= 8);
  await page.getByRole('button', { name: 'Fit to width', exact: true }).click(); await rendered(70);
  await page.getByRole('button', { name: 'Full screen', exact: true }).click();
  await page.waitForTimeout(650); await rendered(70);
  await page.getByRole('button', { name: 'Exit full screen', exact: true }).click();
  await page.waitForTimeout(650);
  const separator = page.getByRole('separator', { name: 'Resize preview' });
  await separator.focus(); await separator.press('ArrowLeft'); await page.waitForTimeout(650);
  for (const n of [5, 100, 20, 119]) await jump(n);
  await page.locator('.textLayer span').first().waitFor();
  const selected = await page.locator('.textLayer span').first().evaluate(span => { const r = document.createRange(); r.selectNodeContents(span); const selection = window.getSelection(); selection.removeAllRanges(); selection.addRange(r); return selection.toString(); });
  assert.ok(selected.length > 0);
  await open('FYP/QA/10.pdf'); await rendered(1);
  assert.equal(await page.locator('.preview-actions a').count(), 0, 'restricted pane has no raw/download links');
  for (const file of ['notes.docx', 'slides.pptx', 'marks.xlsx', 'table.csv', 'image.png', 'notes.md', 'plain.txt', 'diagram.drawio']) {
    await open(`QA/${file}`); await page.waitForTimeout(1800);
    assert.equal(await page.locator('.preview-host .state--error').count(), 0, `${file} loads`);
    assert.ok(await page.locator('.preview-host').innerText() || await page.locator('.preview-host img, .preview-host canvas, .preview-host svg').count());
  }
  for (let n = 0; n < 10; n++) { await open('QA/120.pdf'); await page.waitForTimeout(15); await open('QA/1.pdf'); await rendered(1); }
  await page.getByRole('button', { name: 'Close preview ( Esc )' }).click();
  assert.equal(await page.locator('.pdf-page canvas').count(), 0);
  await open('QA/10.pdf'); await rendered(1); await page.goBack(); await page.waitForTimeout(100);
  assert.equal(await page.locator('.pdf-page canvas').count(), 0);
  await page.goForward(); await rendered(1);
  await page.setViewportSize({ width: 390, height: 844 }); await page.waitForTimeout(700); await rendered(1);
  assert.ok(await page.evaluate(() => document.documentElement.scrollWidth <= innerWidth));
  await page.evaluate(() => { document.documentElement.dataset.theme = 'dark'; document.dispatchEvent(new Event('themechange')); });
  await rendered(1);
  assert.equal(errors.length, 0, errors.join('\n'));
  console.log(JSON.stringify({ result: 'passed', measurements, note: 'Local synthetic PDFs, warm host; these are not deployed performance benchmarks.' }, null, 2));
} finally {
  await browser?.close(); if (server) await new Promise(r => server.close(r)); rmSync(temp, { recursive: true, force: true });
}
