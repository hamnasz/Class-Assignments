"""Development-only fixtures; never writes into an academic source folder.
Usage: python scripts/tests/generate-fixtures.py /tmp/portal-fixtures
Requires reportlab, python-docx, python-pptx, openpyxl and Pillow.
"""
from pathlib import Path
import sys
from reportlab.pdfgen import canvas
from reportlab.lib.pagesizes import A4, landscape
from docx import Document
from pptx import Presentation
from pptx.util import Inches
from openpyxl import Workbook
from PIL import Image, ImageDraw

out = Path(sys.argv[1]); out.mkdir(parents=True, exist_ok=True)
for count in [1, 10, 50, 120]:
    c = canvas.Canvas(str(out / f'{count}.pdf'), pageCompression=1)
    for n in range(1, count + 1):
        size = landscape(A4) if n % 7 == 0 else A4
        c.setPageSize(size); c.setPageRotation(90 if n % 11 == 0 else 0)
        c.setFont('Helvetica', 18)
        c.drawString(40, size[1] - 60, f'Study fixture page {n} of {count}')
        c.setFont('Helvetica', 11)
        for line in range(26):
            c.drawString(40, size[1] - 100 - line * 20, f'Line {line + 1}: selectable text for page {n}. Knowledge grows with practice.')
        for i in range(150):
            c.setStrokeColorRGB((i % 5) / 5, .3, .4)
            c.rect(40 + (i % 20) * 24, 50 + (i // 20) * 5, 16, 3)
        c.showPage()
    c.save()
doc = Document(); doc.add_heading('Document preview fixture', 0)
doc.add_paragraph('Study portal Word preview. This text should remain readable.')
doc.add_table(rows=2, cols=2).cell(0, 0).text = 'Table fixture'
doc.save(out / 'notes.docx')
pres = Presentation()
for n in range(3):
    slide = pres.slides.add_slide(pres.slide_layouts[1]); slide.shapes.title.text = f'Lecture slide {n + 1}'
    slide.placeholders[1].text = 'PowerPoint preview fixture'
pres.save(out / 'slides.pptx')
wb = Workbook(); wb.active.append(['Subject', 'Files']); wb.active.append(['Compiler', 12]); wb.save(out / 'marks.xlsx')
(out / 'table.csv').write_text('Subject,Files\nCompiler,12\nOS,20\n')
(out / 'notes.md').write_text('# Markdown preview\n\nStudy **resources** with math: $x^2 + y^2$.\n')
(out / 'plain.txt').write_text('Plain text preview fixture')
(out / 'diagram.drawio').write_text('<mxfile><diagram name="Overview"><mxGraphModel><root><mxCell id="0"/><mxCell id="1" parent="0"/><mxCell id="2" value="Study resources" vertex="1" parent="1" style="rounded=1;whiteSpace=wrap;html=1;"><mxGeometry x="40" y="40" width="180" height="60" as="geometry"/></mxCell></root></mxGraphModel></diagram></mxfile>')
im = Image.new('RGB', (800, 480), '#eef0f5'); ImageDraw.Draw(im).text((40, 40), 'Image preview fixture', fill='#cc0f2e'); im.save(out / 'image.png')
print(f'Generated {len(list(out.iterdir()))} fixtures in {out}')
