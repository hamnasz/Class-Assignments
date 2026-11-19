// One registry that maps file extensions to how the portal treats them.
// To support a new extension, add it to a row below; nothing else needs to change.
// A plain ".xml" file is source code unless the build step finds a draw.io diagram inside it
// (scripts/build.mjs marks those in manifest.json; see the "diagram" hint in getFileType).

/** Groups drive the coloured icons, the type filters and the file-type bars. */
export const GROUPS = [
  { id: 'pdf', label: 'PDFs', hue: 6 },
  { id: 'word', label: 'Word documents', hue: 214 },
  { id: 'slides', label: 'Slides', hue: 24 },
  { id: 'sheets', label: 'Spreadsheets', hue: 146 },
  { id: 'notebooks', label: 'Notebooks', hue: 38 },
  { id: 'diagrams', label: 'Diagrams', hue: 168 },
  { id: 'web', label: 'Web pages', hue: 272 },
  { id: 'images', label: 'Images', hue: 182 },
  { id: 'text', label: 'Text and Markdown', hue: 205 },
  { id: 'code', label: 'Code', hue: 250 },
  { id: 'media', label: 'Audio and video', hue: 322 },
  { id: 'archives', label: 'Archives', hue: 30 },
  { id: 'other', label: 'Other files', hue: null },
];
export const groupById = Object.fromEntries(GROUPS.map((g) => [g.id, g]));

// [id, label, group, viewer, glyph, extensions]
const ROWS = [
  ['pdf', 'PDF document', 'pdf', 'pdf', 'doc', ['pdf']],
  ['docx', 'Word document', 'word', 'docx', 'doc', ['docx', 'docm', 'dotx']],
  ['doc', 'Word document (legacy)', 'word', 'legacy', 'doc', ['doc', 'dot']],
  ['rtf', 'Rich Text document', 'word', 'rtf', 'doc', ['rtf']],
  ['pptx', 'PowerPoint presentation', 'slides', 'pptx', 'slides', ['pptx', 'pptm', 'potx', 'ppsx']],
  ['ppt', 'PowerPoint (legacy)', 'slides', 'legacy', 'slides', ['ppt', 'pps']],
  ['xlsx', 'Excel workbook', 'sheets', 'sheet', 'sheet', ['xlsx', 'xlsm', 'xls', 'xlsb', 'ods']],
  ['csv', 'CSV data', 'sheets', 'csv', 'sheet', ['csv', 'tsv']],
  ['html', 'Web page', 'web', 'html', 'web', ['html', 'htm']],
  ['ipynb', 'Jupyter notebook', 'notebooks', 'notebook', 'notebook', ['ipynb']],
  // draw.io / diagrams.net. "draw.io" and "drawio.xml" are two-part extensions (see getFileType).
  ['drawio', 'draw.io diagram', 'diagrams', 'diagram', 'diagram', ['drawio', 'dio', 'draw.io', 'drawio.xml']],
  ['md', 'Markdown', 'text', 'markdown', 'text', ['md', 'markdown', 'mdown']],
  ['txt', 'Text file', 'text', 'text', 'text', ['txt', 'text', 'log', 'rst']],
  ['image', 'Image', 'images', 'image', 'image', ['png', 'jpg', 'jpeg', 'gif', 'webp', 'avif', 'bmp', 'svg', 'ico']],
  ['zip', 'ZIP archive', 'archives', 'archive', 'archive', ['zip']],
  ['archive', 'Archive', 'archives', 'legacy', 'archive', ['tar', 'gz', 'tgz', '7z', 'rar', 'bz2', 'xz']],
  ['code', 'Source code', 'code', 'code', 'code', [
    'py', 'js', 'mjs', 'ts', 'jsx', 'tsx', 'json', 'yml', 'yaml', 'css', 'scss', 'sh', 'bash', 'sql', 'c', 'h',
    'cpp', 'cc', 'hpp', 'java', 'r', 'rs', 'go', 'php', 'rb', 'kt', 'swift', 'xml', 'toml', 'ini', 'cfg',
    'tex', 'bib', 'm', 'cs', 'lua', 'pl', 'ps1', 'bat',
  ]],
  ['audio', 'Audio', 'media', 'media', 'media', ['mp3', 'wav', 'ogg', 'm4a', 'flac', 'aac', 'oga']],
  ['video', 'Video', 'media', 'media', 'media', ['mp4', 'webm', 'mov', 'm4v', 'ogv']],
];

const LANG = {
  py: 'python', js: 'javascript', mjs: 'javascript', ts: 'typescript', jsx: 'javascript', tsx: 'typescript',
  json: 'json', yml: 'yaml', yaml: 'yaml', css: 'css', scss: 'scss', sh: 'bash', bash: 'bash', sql: 'sql',
  c: 'c', h: 'c', cpp: 'cpp', cc: 'cpp', hpp: 'cpp', java: 'java', r: 'r', rs: 'rust', go: 'go', php: 'php',
  rb: 'ruby', kt: 'kotlin', swift: 'swift', xml: 'xml', toml: 'ini', ini: 'ini', cfg: 'ini', cs: 'csharp',
  lua: 'lua', pl: 'perl', m: 'objectivec', md: 'markdown',
};

const byExt = new Map();
for (const [id, label, group, viewer, glyph, exts] of ROWS)
  for (const ext of exts) byExt.set(ext, { id, label, group, viewer, glyph });

const OTHER = { id: 'file', label: 'File', group: 'other', viewer: 'unsupported', glyph: 'file' };

const cache = new Map();
export function typeForExtension(ext) {
  const e = String(ext || '').toLowerCase();
  if (cache.has(e)) return cache.get(e);
  const base = byExt.get(e);
  let t;
  if (!base) t = { ...OTHER, ext: e, label: e ? `${e.toUpperCase()} file` : 'File' };
  else {
    t = { ...base, ext: e, lang: LANG[e] || null };
    if (base.id === 'image') t.label = `${e === 'jpeg' ? 'JPEG' : e.toUpperCase()} image`;
    if (base.id === 'code') t.label = LANG[e] ? `${LANG[e][0].toUpperCase()}${LANG[e].slice(1)} source` : 'Source code';
  }
  t.hue = groupById[t.group].hue;
  cache.set(e, t);
  return t;
}

// Extensions made of two parts (".draw.io", ".drawio.xml") are matched against the end of the name.
const compound = [...byExt.keys()].filter((e) => e.includes('.'));

/**
 * hints.diagram: set by the build step for a ".xml" file that holds a draw.io diagram, so that
 * it opens in the diagram viewer while every other .xml file stays plain source code.
 */
export function getFileType(name, hints = {}) {
  const lower = String(name).toLowerCase();
  const multi = compound.find((e) => lower.length > e.length + 1 && lower.endsWith(`.${e}`));
  let ext = multi || '';
  if (!ext) {
    const i = name.lastIndexOf('.');
    ext = i > 0 && i < name.length - 1 ? name.slice(i + 1) : '';
  }
  const type = typeForExtension(ext);
  if (hints.diagram && type.id === 'code') return { ...typeForExtension('drawio'), ext: type.ext };
  return type;
}
