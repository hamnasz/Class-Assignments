# Correct GitHub file dates

This update fixes the portal showing the frontend deployment date on every file.

## Apply to your existing repository

From this archive, replace **scripts/build.mjs** and add **scripts/file-dates.mjs**. Keep both in scripts/. Commit them to GitHub and let Vercel redeploy. The existing portal JS already reads the generated per-file dates; no academic documents, folder names or Vercel configuration need changing for this fix.

The other updated files are regression tests and documentation. You do not need to replace your whole portal or subject folders.

## Where dates come from

- Each file gets the committer date of the latest commit that actually changed its path.
- The build detects a shallow checkout and attempts to fetch the missing ancestors from origin without checking out another revision or changing documents.
- Commits at an unresolved shallow boundary are excluded. Such a commit can falsely appear to add every file in the checkout.
- If history remains incomplete, a build-only GitHub API fallback resolves missing dates at the deployed commit, one file path at a time, with four concurrent requests.
- Folder and subject dates remain the latest verified date among their existing child files. A frontend-only deployment does not advance academic file dates.
- The build date remains separate in manifest.generatedAt. It is never used as a document update date.
- If neither source is available, the file date is omitted rather than replaced with today. The build log identifies that condition.

## Private GitHub repository fallback

The build first uses the authenticated Git checkout's existing access. If Vercel's build log says full history could not be retrieved or some file dates were omitted:

1. Create a GitHub fine-grained personal access token restricted to this repository, with **Contents: Read-only** access.
2. Add it to the Vercel project's server-side environment variables as **GITHUB_TOKEN**, for the deployment environment you use.
3. Redeploy so the build can retrieve the historical dates.

Keep that token out of source files, portal/config.js, browser JavaScript, and any public-prefixed environment variable. The helper reads it only during the build and never writes it to dist/ or the manifest. API authentication failures omit unknown dates and log a generic message without credentials.

No token is needed if the Git history fetch succeeds.

## Verification

Run from the repository root:

```sh
node --test scripts/tests/*.test.mjs
node scripts/build.mjs
```

Eight new tests exercise real Git repositories: the all-today bug in a depth-one clone; automatic unshallowing; unavailable origins; verified changes above a shallow boundary; committer versus author dates; unusual file names; private API fallback; API authentication failures; and ZIP sources with no history. The existing 12 checks also remain in the suite.

The GitHub connection available in this chat returned 404 for the private repository, so this fix has not been pushed or deployed. Actual Vercel access to origin/the optional token must be confirmed on the next deployment. Browser rendering behavior is unchanged by this fix.

Reference documentation:

- https://git-scm.com/docs/shallow
- https://git-scm.com/docs/git-fetch
- https://docs.github.com/en/rest/commits/commits#list-commits
