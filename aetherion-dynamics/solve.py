from pypdf import PdfReader, PdfWriter

reader = PdfReader('SecretFacilityAccess.pdf')

writer = PdfWriter()
writer.add_page(reader.pages[0])
writer.remove_annotations('/Square')
writer.write('Unredacted.pdf')
