draw.io viewer (vendored)
=========================

Used by portal/js/viewers/diagram.js and portal/js/core/diagrams.js to display .drawio, .dio,
.draw.io and draw.io .xml files. Licence: Apache-2.0 (../licenses/drawio-LICENSE.txt).
Source: https://github.com/jgraph/drawio

  viewer-static.min.js   tag v32.6.9   src/main/webapp/js/viewer-static.min.js
                         The documented "static embed" build. It bundles mxGraph and the
                         shape definitions that the smaller viewer.min.js loads on demand.
  shapes/*.js            tag v32.6.9   src/main/webapp/shapes/   (loaded on demand, SHAPES_PATH)
  styles/default.xml     tag v32.6.9   src/main/webapp/styles/   (STYLE_PATH)
  math/                  tag v32.6.9   src/main/webapp/math4/es5/drawio-mathjax.min.js
                         Only fetched for diagrams that use LaTeX (math enabled).
  stencils/**/*.xml      tag v31.7.0   src/main/webapp/stencils/ (loaded on demand, STENCIL_PATH)
                         Newer releases stopped shipping the stencil XML files in the
                         repository, so v31.7.0 is the newest copy; the format is unchanged.

Left out to keep the site small (about 7 MB): stencils/cisco_safe/ and stencils/veeam/.
Diagrams that use those two icon sets show plain boxes for them. To add a set, copy its file
from the same path in the GitHub repository (tag v31.7.0) into stencils/.

The paths are pointed at this folder by window variables set in portal/js/core/loader.js
(STENCIL_PATH, SHAPES_PATH, STYLE_PATH, DRAW_MATH_URL) before the viewer script is loaded.

To upgrade: replace viewer-static.min.js and shapes/ with a newer tag's copies, then open a
diagram with the AWS, flowchart and UML shapes to check they still render.
