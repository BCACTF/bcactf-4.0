from PIL import Image
import numpy as np
img = Image.open("original.jpg")
arr = np.array(img)
bits = np.unpackbits(np.fromfile("flag.txt",dtype="uint8"))[::-1]
for ind, bit in enumerate(bits):
    img.putpixel((ind,ind), tuple((arr[ind][ind][i] & ~1) | (1-bit) if i == ind % 3 else arr[ind][ind][i] for i in range(3)))
img.save("subpixels.png")