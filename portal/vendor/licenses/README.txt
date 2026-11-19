Third-party libraries vendored in this folder, self-hosted so the site needs
no external CDN and no API keys.

  pdfjs/      pdf.js (Apache-2.0)                     -> pdfjs-LICENSE.txt
  docx/       docx-preview (MIT), jszip (MIT/GPLv3)    -> docx-preview-LICENSE.txt, jszip-LICENSE.txt
              docx/fonts/ Carlito, Caladea, Liberation Sans/Serif/Mono (OFL-1.1) -> font-docx-metric-compatible-LICENSE.txt
              (Latin subsets as WOFF2; metric-compatible stand-ins for Calibri, Cambria, Arial, Times New Roman,
               Courier New, used only where the visitor's device lacks the real font. Safe to delete: the
               viewer then falls back to system fonts. Declared in docx/docx-fonts.css.)
  pptx/       pptx-preview (MIT per its package.json)  -- upstream ships no LICENSE file in the npm
                                                           package itself; check the project's GitHub
                                                           repository if you need the exact license text.
  xlsx/       SheetJS "xlsx" (Apache-2.0)               -> sheetjs-LICENSE.txt
  markdown/   marked (MIT), DOMPurify (Apache-2.0/MPL-2.0),
              highlight.js (BSD-3-Clause), KaTeX (MIT)  -> marked-LICENSE.txt, dompurify-LICENSE.txt,
                                                            highlightjs-LICENSE.txt, katex-LICENSE.txt
  fonts/      Bricolage Grotesque, Public Sans, JetBrains Mono  -> font-*-LICENSE.txt (all OFL-1.1)
  drawio/     draw.io viewer, shapes, stencils, MathJax build (Apache-2.0) -> drawio-LICENSE.txt
              (the viewer bundles mxGraph, Apache-2.0, and DOMPurify; see ../drawio/README.txt)
