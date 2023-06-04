from pdfreader import PDFDocument

with open('SecretFacilityAccess.pdf', 'rb') as file:
    pdf = PDFDocument(file)
    page = next(pdf.pages())
    page.Resources.XObject['Im1'].to_Pillow().save('Unredacted.png')
