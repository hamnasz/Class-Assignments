import test from 'node:test';
import assert from 'node:assert/strict';
import { cpSync, mkdtempSync, mkdirSync, writeFileSync, readFileSync, existsSync, rmSync, readdirSync } from 'node:fs';
import { join, dirname, resolve } from 'node:path';
import { tmpdir } from 'node:os';
import { fileURLToPath } from 'node:url';
import { execFileSync } from 'node:child_process';
import { buildRepository } from '../../portal/js/core/repo.js';
import { canDownload } from '../../portal/js/core/permissions.js';
import { buildIndex, search } from '../../portal/js/core/search.js';

const root = resolve(dirname(fileURLToPath(import.meta.url)), '../..');
const entries = [
  { path: 'Compiler Construction/Week 1/notes.pdf', size: 100, modified: '2026-10-30T12:00:00Z' },
  { path: 'FYP/Others/proposal.docx', size: 300 },
  { path: 'Others/hidden.pdf', size: 50 },
  { path: 'New Subject/lecture.pptx', size: 200 },
  { path: 'FYP-old/open.pdf', size: 30 },
];

test('automatic nested discovery, search, modification dates and view-only boundaries survive', () => {
  const repo = buildRepository(entries);
  assert.ok(repo.byPath.has('Compiler Construction/Week 1/notes.pdf'));
  assert.ok(repo.byPath.has('New Subject'));
  assert.ok(repo.byPath.has('FYP/Others/proposal.docx'));
  assert.ok(!repo.byPath.has('Others/hidden.pdf'));
  assert.equal(repo.totals.files, 4);
  assert.equal(repo.latest, '2026-10-30T12:00:00Z');
  assert.equal(canDownload('FYP/Others/proposal.docx'), false);
  assert.equal(canDownload('fyp/proposal.docx'), false);
  assert.equal(canDownload('FYP-old/open.pdf'), true);
  assert.equal(search(buildIndex(repo), 'notes').results[0].node.path, entries[0].path);
});

test('Vercel build discovers new subjects, omits hidden content/tooling and preserves academic bytes', () => {
  const temp = mkdtempSync(join(tmpdir(), 'study-portal-test-'));
  try {
    cpSync(root, temp, { recursive: true, filter: p => !p.includes(`${root}/dist`) });
    for (const e of entries) { const p = join(temp, e.path); mkdirSync(dirname(p), { recursive: true }); writeFileSync(p, `Fixture bytes for ${e.path}`); }
    execFileSync('git', ['init', '-q'], { cwd: temp });
    execFileSync('git', ['add', '.'], { cwd: temp });
    execFileSync('git', ['-c','user.name=Portal Test','-c','user.email=test@example.invalid','commit','-qm','test fixtures'], { cwd: temp, env: { ...process.env, GIT_AUTHOR_DATE: '2026-10-30T12:00:00Z', GIT_COMMITTER_DATE: '2026-10-30T12:00:00Z' } });
    const output = execFileSync(process.execPath, ['scripts/build.mjs'], { cwd: temp, encoding: 'utf8', env: { ...process.env, VERCEL_GIT_REPO_SLUG: 'semester7th' } });
    assert.match(output, /Built dist/);
    const manifest = JSON.parse(readFileSync(join(temp, 'dist/portal/manifest.json')));
    assert.equal(manifest.entries.length, 4);
    assert.equal(Date.parse(manifest.entries.find(e => e.path === entries[0].path).modified), Date.parse('2026-10-30T12:00:00Z'));
    assert.equal(JSON.parse(readFileSync(join(temp, 'dist/portal/site.json'))).title, 'Semester VII');
    assert.equal(existsSync(join(temp, 'dist/Others')), false);
    assert.equal(existsSync(join(temp, 'dist/scripts')), false);
    for (const e of entries.filter(e => !e.path.startsWith('Others/'))) assert.deepEqual(readFileSync(join(temp, e.path)), readFileSync(join(temp, 'dist', e.path)));
    assert.match(readFileSync(join(temp, 'dist/index.html'), 'utf8'), /reader\.css/);
  } finally { rmSync(temp, { recursive: true, force: true }); }
});

test('all local ES module imports and stylesheet references resolve', () => {
  function walk(dir) { return readdirSync(dir, { withFileTypes: true }).flatMap(e => e.isDirectory() ? walk(join(dir, e.name)) : [join(dir, e.name)]); }
  for (const file of walk(join(root, 'portal/js')).filter(p => p.endsWith('.js'))) {
    const code = readFileSync(file, 'utf8');
    for (const m of code.matchAll(/(?:from\s*|import\s*\()\s*['"](\.[^'"]+)['"]/g)) assert.ok(existsSync(resolve(dirname(file), m[1])), `${file}: ${m[1]}`);
  }
  const html = readFileSync(join(root, 'index.html'), 'utf8');
  for (const m of html.matchAll(/(?:href|src)="(portal\/[^"]+)"/g)) assert.ok(existsSync(join(root, m[1])), m[1]);
});

test('Vercel keeps static deployment and revalidates unversioned modules and worker', () => {
  const config = JSON.parse(readFileSync(join(root, 'vercel.json')));
  assert.equal(config.buildCommand, 'node scripts/build.mjs');
  assert.equal(config.outputDirectory, 'dist');
  const rule = config.headers.find(r => r.source === '/portal/(.*)');
  assert.match(rule.headers[0].value, /max-age=0, must-revalidate/);
  assert.ok(!JSON.stringify(config).includes('Accept-Ranges')); // the origin must actually support ranges
});
