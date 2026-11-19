import test from 'node:test';
import assert from 'node:assert/strict';
import { mkdtempSync, mkdirSync, writeFileSync, readFileSync, rmSync } from 'node:fs';
import { tmpdir } from 'node:os';
import { join, dirname } from 'node:path';
import { pathToFileURL } from 'node:url';
import { execFileSync } from 'node:child_process';
import { getFileDates, parseFileHistory } from '../file-dates.mjs';

const run = (cwd, ...args) => execFileSync('git', args, { cwd, encoding: 'utf8', stdio: ['ignore', 'pipe', 'ignore'] }).trim();
const OLD = '2026-10-10T12:00:00Z', NOTE = '2026-11-05T12:00:00Z', NEW = '2026-11-07T12:00:00Z', TODAY = '2026-11-08T12:00:00Z';
const paths = ['Cloud Computing/old.pdf', 'Compiler Construction/notes.pdf', 'FYP/new.pdf', 'Subject/اردو\tline\nnotes.pdf'];
function fixture() {
  const base = mkdtempSync(join(tmpdir(), 'portal-dates-')), origin = join(base, 'origin');
  mkdirSync(origin); run(origin, 'init', '-q'); run(origin, 'config', 'user.name', 'Fixture'); run(origin, 'config', 'user.email', 'fixture@example.invalid');
  const write = (path, text) => { const full = join(origin, path); mkdirSync(dirname(full), { recursive: true }); writeFileSync(full, text); };
  const commit = (message, date, author = date) => {
    run(origin, 'add', '.');
    execFileSync('git', ['commit', '-qm', message], { cwd: origin, env: { ...process.env, GIT_AUTHOR_DATE: author, GIT_COMMITTER_DATE: date }, stdio: 'ignore' });
  };
  for (const path of [paths[0], paths[1], paths[3]]) write(path, 'academic content');
  commit('Original documents', OLD);
  write(paths[1], 'revised compiler notes'); commit('Revise notes', NOTE, OLD);
  write(paths[2], 'new project'); commit('New project', NEW);
  write('portal.js', 'frontend update'); commit('Frontend only', TODAY);
  const clone = (depth = 1) => {
    const dest = join(base, `clone-${depth}`);
    run(base, 'clone', '--quiet', '--depth', String(depth), pathToFileURL(origin).href, dest);
    return dest;
  };
  return { base, origin, clone, clean: () => rmSync(base, { recursive: true, force: true }) };
}
const equalDate = (a, b) => assert.equal(Date.parse(a), Date.parse(b));

test('depth-one clone reproduces the old all-today bug; fetching ancestors recovers distinct dates', async () => {
  const f = fixture();
  try {
    const root = f.clone();
    const oldLog = run(root, 'log', '--format=%aI', '--name-only', '--diff-filter=AM', '--no-renames');
    equalDate(oldLog.split('\n')[0], TODAY);
    for (const path of paths.slice(0, 3)) assert.ok(oldLog.includes(path), 'old code sees every file as added today');
    const head = run(root, 'rev-parse', 'HEAD'), content = readFileSync(join(root, paths[1]));
    const dates = await getFileDates({ root, paths, env: {}, warn: () => {} });
    equalDate(dates.get(paths[0]), OLD); equalDate(dates.get(paths[1]), NOTE); equalDate(dates.get(paths[2]), NEW); equalDate(dates.get(paths[3]), OLD);
    assert.equal(run(root, 'rev-parse', '--is-shallow-repository'), 'false');
    assert.equal(run(root, 'rev-parse', 'HEAD'), head);
    assert.deepEqual(readFileSync(join(root, paths[1])), content);
  } finally { f.clean(); }
});

test('unavailable full history never assigns the shallow boundary date to untouched files', async () => {
  const f = fixture();
  try {
    const root = f.clone(), warnings = []; run(root, 'remote', 'remove', 'origin');
    const dates = await getFileDates({ root, paths, env: {}, warn: msg => warnings.push(msg) });
    assert.equal(dates.size, 0);
    assert.ok(warnings.some(msg => msg.includes('Dates are omitted')));
  } finally { f.clean(); }
});

test('verified changes above a shallow boundary remain usable without full history', async () => {
  const f = fixture();
  try {
    const dates = await getFileDates({ root: f.clone(3), paths, env: {}, fetchHistory: false, warn: () => {} });
    assert.deepEqual([...dates.keys()], [paths[2]]);
    equalDate(dates.get(paths[2]), NEW);
  } finally { f.clean(); }
});

test('a complete history uses committer dates and preserves unusual file names', async () => {
  const f = fixture();
  try {
    let network = 0;
    const dates = await getFileDates({ root: f.origin, paths, env: {}, fetchImpl: async () => { network++; }, warn: () => {} });
    equalDate(dates.get(paths[1]), NOTE); equalDate(dates.get(paths[3]), OLD);
    assert.equal(network, 0);
  } finally { f.clean(); }
});

test('private GitHub fallback is scoped to unresolved paths and the deployed commit', async () => {
  const f = fixture();
  try {
    const root = f.clone(3), calls = [], warnings = [];
    const expected = new Map([[paths[0], OLD], [paths[1], NOTE], [paths[3], OLD]]);
    const sha = run(root, 'rev-parse', 'HEAD');
    const dates = await getFileDates({ root, paths, repo: { owner: 'hamnasz', name: 'Semester-VII', branch: 'main' }, env: { GITHUB_TOKEN: 'fixture-secret' }, fetchHistory: false, warn: msg => warnings.push(msg), fetchImpl: async (url, options) => {
      calls.push(String(url));
      assert.equal(url.origin, 'https://api.github.com');
      assert.equal(url.searchParams.get('sha'), sha);
      assert.equal(url.searchParams.get('per_page'), '1');
      assert.equal(options.headers.Authorization, 'Bearer fixture-secret');
      return { ok: true, json: async () => [{ commit: { committer: { date: expected.get(url.searchParams.get('path')) } } }] };
    } });
    assert.equal(calls.length, 3);
    for (const path of paths) assert.ok(dates.has(path));
    assert.ok(!JSON.stringify([...dates]).includes('fixture-secret'));
    assert.equal(warnings.length, 0);
  } finally { f.clean(); }
});

test('GitHub auth/rate-limit failures leave dates absent, with no token in diagnostics', async () => {
  const f = fixture();
  try {
    const warnings = [];
    const dates = await getFileDates({ root: f.clone(), paths, repo: { owner: 'hamnasz', name: 'Semester-VII' }, env: { GITHUB_TOKEN: 'fixture-secret' }, fetchHistory: false, warn: msg => warnings.push(msg), fetchImpl: async () => ({ ok: false, status: 403 }) });
    assert.equal(dates.size, 0); assert.ok(warnings.length);
    assert.ok(!warnings.join('\n').includes('fixture-secret'));
  } finally { f.clean(); }
});

test('a ZIP without Git metadata leaves dates absent and does not use current time', async () => {
  const root = mkdtempSync(join(tmpdir(), 'portal-dates-zip-'));
  try {
    const dates = await getFileDates({ root, paths, env: {}, warn: () => {} });
    assert.equal(dates.size, 0);
  } finally { rmSync(root, { recursive: true, force: true }); }
});

test('NUL history parser handles both additions and modifications without line splitting', () => {
  const sha = 'a'.repeat(40), path = 'Subject/\nweird\tname.pdf';
  const log = `\0${sha}\0${OLD}\0\nA\0${path}\0`;
  assert.equal(parseFileHistory(log).get(path), OLD);
  assert.equal(parseFileHistory(log, new Set([sha])).size, 0);
});
