// Build-time metadata only. Git/GitHub commit dates never come from checkout mtimes.
import { execFileSync } from 'node:child_process';
import { existsSync, readFileSync } from 'node:fs';
import { resolve } from 'node:path';

const HASH = /^[a-f0-9]{40,64}$/;
const validDate = value => typeof value === 'string' && /^\d{4}-\d\d-\d\dT/.test(value) && Number.isFinite(Date.parse(value));
const git = (root, args) => execFileSync('git', args, {
  cwd: root, encoding: 'utf8', maxBuffer: 32 * 1024 * 1024, timeout: 30000,
  stdio: ['ignore', 'pipe', 'ignore'], env: { ...process.env, GIT_TERMINAL_PROMPT: '0' },
});

function boundaryCommits(root) {
  const path = resolve(root, git(root, ['rev-parse', '--git-path', 'shallow']).trim());
  return new Set(existsSync(path) ? readFileSync(path, 'utf8').trim().split(/\s+/).filter(Boolean) : []);
}

/** Null-delimited statuses preserve spaces, Unicode, tabs and newlines in file names. */
export function parseFileHistory(log, boundaries = new Set()) {
  const dates = new Map(), tokens = log.split('\0');
  let sha = null, date = null;
  for (let i = 0; i < tokens.length; i++) {
    if (HASH.test(tokens[i]) && validDate(tokens[i + 1])) {
      sha = tokens[i]; date = tokens[++i]; continue;
    }
    if (/^[AMT]$/.test(tokens[i].replace(/^\n/, ''))) {
      const path = tokens[++i];
      // A shallow boundary is treated by Git as a root: every existing file
      // appears added there, even when that commit changed only the frontend.
      if (path && sha && date && !boundaries.has(sha) && !dates.has(path)) dates.set(path, date);
    }
  }
  return dates;
}

export async function getFileDates({ root, paths, repo = {}, env = process.env, fetchHistory = true, fetchImpl = globalThis.fetch, warn = console.warn }) {
  let dates = new Map(), ref = env.VERCEL_GIT_COMMIT_SHA || repo.branch;
  try {
    ref = git(root, ['rev-parse', 'HEAD']).trim();
    if (fetchHistory && git(root, ['rev-parse', '--is-shallow-repository']).trim() === 'true') {
      try {
        // Fetch ancestors without changing HEAD, branches, the index or file contents.
        // Existing checkout credentials are used; no credential is printed or written.
        git(root, ['fetch', '--unshallow', '--no-tags', '--filter=blob:none', 'origin', ref]);
      } catch { warn('File dates: full Git history could not be retrieved; shallow boundary dates will be excluded.'); }
    }
    const boundaries = boundaryCommits(root);
    dates = parseFileHistory(git(root, [
      'log', '--topo-order', '--format=%x00%H%x00%cI', '--name-status', '-z',
      '--diff-filter=AMT', '--no-renames', '--diff-merges=first-parent', 'HEAD', '--',
    ]), boundaries);
  } catch { /* A source ZIP may have no .git directory. Never substitute today's date. */ }

  const missing = paths.filter(path => !dates.has(path));
  // Private GitHub fallback runs ONLY on the build server. This variable must
  // never be prefixed VITE_/NEXT_PUBLIC_ or copied into portal/config.js.
  const token = env.GITHUB_TOKEN || env.GH_TOKEN;
  if (missing.length && token && repo.owner && repo.name && ref) {
    const endpoint = `https://api.github.com/repos/${encodeURIComponent(repo.owner)}/${encodeURIComponent(repo.name)}/commits`;
    let cursor = 0, stopped = false;
    await Promise.all(Array.from({ length: Math.min(4, missing.length) }, async () => {
      while (!stopped && cursor < missing.length) {
        const path = missing[cursor++];
        const url = new URL(endpoint);
        url.search = new URLSearchParams({ sha: ref, path, per_page: '1' }).toString();
        try {
          const response = await fetchImpl(url, {
            headers: { Accept: 'application/vnd.github+json', Authorization: `Bearer ${token}`, 'X-GitHub-Api-Version': '2022-11-28' },
            signal: AbortSignal.timeout(15000), redirect: 'error',
          });
          if (!response.ok) {
            // Do not fan out more requests after an auth/rate-limit/server failure.
            stopped = true; continue;
          }
          const commits = await response.json();
          const date = Array.isArray(commits) && commits[0]?.commit?.committer?.date;
          if (validDate(date)) dates.set(path, date);
        } catch { stopped = true; }
      }
    }));
  }
  const unresolved = paths.filter(path => !dates.has(path)).length;
  if (unresolved) warn(`File dates: ${unresolved} file(s) have no verified history date. Dates are omitted. For a private repository, allow Git history fetching or set a build-only GITHUB_TOKEN with repository Contents read access.`);
  return new Map(paths.filter(path => dates.has(path)).map(path => [path, dates.get(path)]));
}
