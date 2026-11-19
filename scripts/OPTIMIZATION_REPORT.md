# Study Portal implementation and verification

Date: 8 November 2026

## Result

Implemented the PDF rendering replacement and interface updates in the supplied vanilla JavaScript project. The architecture, local vendor libraries, configuration, repository discovery and static Vercel build remain in place. No production dependencies were added. This source archive contains the portal, not the user's academic repository; apply its frontend/build files to the existing repository.

The local Vercel build command succeeds. Twenty automated tests pass, including eight additional Git-history regression tests. Real browser rendering and deployed performance remain unverified because this environment has no Chromium executable and the browser download failed. Do not treat this package as having passed visual acceptance or live deployment testing.

## Original bottlenecks

- PDF loading used a complete fetch/ArrayBuffer before initializing PDF.js.
- Startup requested dimensions for up to 300 pages, including distant pages.
- All pages and their text layers were rendered sequentially before attaching the document to the visible DOM.
- Zoom removed the document and repeated the full rendering loop.
- Canvases and asynchronous render tasks had no viewport-based lifetime.
- The diagram viewer retained document event listeners, observers and old graph instances.
- Code highlighting unnecessarily loaded the entire Markdown/math library group.
- Word and PowerPoint started network requests only after loading their libraries; Markdown/notebook startup had a similar serial wait.
- The build omitted modification dates and the client discarded them, preventing the existing Recently updated section from working.

## New PDF architecture

1. Mount the reading surface and an announced loading message immediately. Import PDF.js lazily and use getDocument({ url, rangeChunkSize: 65536 }) with the existing local worker.
2. Get only page 1's dimensions initially. Create lightweight page placeholders using that estimate. Actual dimensions and rotations are discovered when individual pages enter the reading window.
3. Use an animation-frame-coalesced scroll scheduler, binary page lookup and distance/visibility priorities. A scroll scheduler is used instead of IntersectionObserver so programmatic page jumps and zoom invalidation use the same queue.
4. Paint the reading position first, then visible/adjacent pages. At most two page jobs run concurrently and at most eight page slots retain canvas/text resources. Placeholders and dimension records still scale with document length.
5. Display the canvas as soon as rendering completes; text extraction follows. Text selection is retained for resident pages. Offscreen text layers are regenerated when revisited; whole-document text selection across evicted pages is not provided.
6. Apply zoom sizes to placeholders while repainting only the reading window. Preserve a page-relative vertical anchor; preserve a fixed inset when the viewport starts in an inter-page gap. Horizontal position is retained in pixels.
7. Debounce fit-width raster work by 240 ms while resizing. Manual zoom survives resizing. Height-only changes update the reading window. Mixed-size pages fit independently, and the zoom label follows the active page.
8. Limit DPR to 2, each canvas to roughly 3 megapixels and either dimension to 4096 pixels. Extreme zoom trades raster sharpness for bounded bitmap allocation. Eight resident slots imply a bitmap budget of roughly 96 MiB, excluding PDF.js caches, font/image decoding and browser overhead; this is not a measured process-memory cap.
9. On zoom/switch/close, cancel render and text tasks, zero and detach canvases, remove text layers, release page resources and disconnect events/observers. Destroying the loading task aborts PDF.js transport and worker resources. A slot is not reused until its cancelled job settles.
10. Expose page retry for genuine rendering failures. Expected cancellation does not become a page error. Loading errors use the existing file-level retry path.

PDF.js detects transport capabilities from actual response headers. Streaming/range defaults remain enabled, and full-response fallback is available. The implementation does not add a misleading Accept-Ranges header or assume that every PDF can display before its complete download. Non-linearized PDFs and origins without suitable range responses may still need much of the file before the first page.

Text layers use PDF.js viewport scaling, page user units, and CSS transforms for 90/180/270-degree rotation. Real-browser text alignment and copying still require verification.

Primary API reference consulted: https://mozilla.github.io/pdf.js/api/draft/module-pdfjsLib.html

## Interface changes

- A calmer dashboard with a red accent, a clear study-space heading, subject/file/storage statistics and a wide search entry point.
- Subject cards with clearer spacing, readable long titles, subject icon tints and separated metadata.
- A framed folder heading, local file/folder filtering and result counts, clearer file rows and wrapping long names.
- Large file lists use content-visibility to reduce offscreen layout/paint work. This reduces browser rendering work but does not virtualize the list's DOM construction.
- A neutral document reading surface, stable page placeholders, cleaner shadows, first-page status and page error/retry feedback.
- Larger preview controls, responsive toolbar spacing and keyboard focus containment when the pane covers the page.
- Immediate resource disposal on pane close, while retaining the pane's closing animation.
- Both themes and the existing reduced-motion rules remain supported. No new animation system or external fonts were introduced.

## Other performance and lifecycle changes

- Preview fetches receive the existing AbortSignal.
- Cleanup registered after a preview has closed executes immediately.
- Word/PowerPoint library startup runs alongside file fetching; aborted documents avoid further expensive work where possible.
- Markdown/notebook fetches start alongside their library group; source-code preview loads only the highlighting library.
- Spreadsheet parsing limits rows before creating the full display matrix and reports truncation.
- Diagram graph instances, global listeners and resize observers are disposed on close/theme remount; stale asynchronous mounts cannot replace a newer one.
- Diagram thumbnails remain viewport-triggered. Detached cards are unobserved, completed work checks connectivity, and the SVG cache is capped at 32 entries. Thumbnail rendering already used a serial queue and is preserved.
- Build-time Git history supplies per-file committer dates, fetching missing ancestors for shallow checkouts. Unresolved shallow boundary commits are excluded. A build-only GitHub API fallback can recover missing dates with GITHUB_TOKEN; unavailable dates remain omitted. See scripts/DATE_FIX.md. Ignored frontend/vendor directories are skipped while scanning for content.
- Unversioned portal modules and the worker use cache revalidation. They are not marked immutable. Compression remains the hosting provider's responsibility.

## Changed files

| Area | Files |
| --- | --- |
| PDF reader | portal/js/viewers/pdf.js; new portal/css/reader.css |
| Dashboard and browsing | portal/js/views/dashboard.js; portal/js/views/browse.js; portal/js/components/nodeRow.js |
| Pane and lifecycle | portal/js/components/previewPane.js; portal/js/components/fileContent.js; portal/js/components/states.js |
| Diagrams | portal/js/components/diagramCard.js; portal/js/core/diagrams.js; portal/js/viewers/diagram.js |
| Resource loading | portal/js/core/loader.js; portal/js/viewers/code.js; portal/js/viewers/markdown.js; portal/js/viewers/notebook.js; portal/js/viewers/docx.js; portal/js/viewers/pptx.js; portal/js/viewers/sheet.js |
| Abortable transports | portal/js/viewers/archive.js; portal/js/viewers/html.js; portal/js/viewers/rtf.js |
| Build and delivery | scripts/build.mjs; scripts/file-dates.mjs; portal/js/core/repo.js; index.html; vercel.json; README.md |
| New verification files | scripts/tests/pdf-scheduler.test.mjs; scripts/tests/build-and-routing.test.mjs; scripts/tests/browser-smoke.mjs; scripts/tests/generate-fixtures.py; this report |

## Verification completed

Command: `node --test scripts/tests/*.test.mjs`

**20 passed, 0 failed.**

- Simulated 1/10/50/120-page documents start with a small reading window (no more than four requested pages in those initial-view fixtures), rather than requesting/rendering all pages.
- A deep page jump releases earlier canvases and discovers a landscape page's real dimensions.
- Rapid jumps and repeated zoom stay within two active tasks and eight resident canvases.
- Zoom preserves both an in-page reading fraction and an inter-page inset.
- DPR/canvas dimensions and area remain capped under the tested zoom sequence.
- Resize is debounced; manual zoom is retained until fit mode is restored.
- Closing during loading/rendering destroys transport and prevents late canvases.
- Twelve open/close cycles zero every tracked bitmap and leave no active render task.
- A genuine page failure waits for explicit retry and then recovers.
- Late cleanup registration after preview disposal executes immediately.
- Automatic nested discovery, search, real modification dates and view-only folder boundaries remain intact.
- A temporary Git repository builds successfully with added subjects; hidden root folders and tooling are excluded, academic fixture bytes are preserved, and the automatic semester title resolves.
- Local module imports and stylesheet references resolve; Vercel keeps the static build configuration and safe cache rules.

JavaScript syntax checks passed for all application modules, the build script and browser suite. Twelve real-format fixtures (including 1/10/50/120-page PDFs with mixed orientation and rotation, DOCX, PPTX, XLSX, CSV, PNG, Markdown, plain text and draw.io) were generated successfully.

The optional browser suite's local HTTP setup verified an actual 206 response and a 100-byte body for bytes=0-99. This verifies only the test server. It does not verify Vercel's live headers.

**These scheduler/lifecycle tests use a simulated DOM/PDF.js transport. They prove control flow and resource ownership under controlled conditions, not browser layout, PDF font fidelity, elapsed loading speed or heap memory.**

## Browser verification still required

The real browser suite was attempted but could not launch: the Chromium executable is absent. Browser installation returned an invalid download. Consequently no before/after time-to-first-page numbers, FPS numbers, heap measurements or visual screenshots are claimed.

Pending checks include actual first-page timing; browser page/text alignment (especially rotation); clipboard interaction; long/rapid scrolling under real PDF.js workloads; fullscreen and drag resizing; mobile toolbar overflow; focus/tab behavior; browser back/forward; both themes; repeated-switch heap behavior; and real DOCX/PPTX/XLSX/image/Markdown/diagram previews. The optional suite covers many of these interactions but has not completed here. Clipboard fidelity, touch devices, detailed visual review and heap profiling also need manual checks.

A live deployment URL was not supplied. Production Content-Length/Content-Encoding/Accept-Ranges and a real Range request's 206/Content-Range should be inspected after deployment. Do not manufacture those headers in application configuration. The Vercel build was run locally; no deployment was published.

## Reproduce the checks

Apply the source files to the existing academic repository without replacing its subject folders or academic documents.

```sh
node scripts/build.mjs
node --test scripts/tests/*.test.mjs
```

For optional real-browser checks (development tools only):

```sh
npm install --no-save playwright
npx playwright install chromium
python3 -m pip install reportlab python-docx python-pptx openpyxl Pillow
node scripts/tests/browser-smoke.mjs
```

Use CHROMIUM_PATH to point to an existing browser executable if needed. The browser suite generates fixtures in a temporary directory, serves a local test copy, and removes that copy when finished. It reports local synthetic-document timing only after a successful browser run. It does not save screenshots or add fixtures to the academic source repository.

The original view-only UI rules remain. Academic content is still served by the static host, so those UI rules are not server-side file access control.

## Date correctness follow-up

A shallow-checkout regression was reproduced and corrected after the first package: a frontend-only boundary commit falsely appeared to add every academic file. The original tests covered only complete repositories. Eight new date tests now cover automatic ancestor fetching, boundary exclusion, missing history, committer timestamps, unusual paths and private GitHub API fallback. See [DATE_FIX.md](DATE_FIX.md) for the two production files to apply and conditional private-repository setup.
