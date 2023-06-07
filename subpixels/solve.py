from PIL import Image
import numpy as np
import re
# Find the original image online and compare pixel-by-pixel
# to see the difference
original = np.array(Image.open("original.jpg"))
new = np.array(Image.open("subpixels.png"))
for r in range(1498):
    for p in range(1870):
        if any([original[r][p][i] != new[r][p][i] for i in range(3)]):
            print(f"({r},{p}): {[new[r][p][i] - original[r][p][i] for i in range(3)]}")
# It can be seen that the images only differ along the main
# diagonal, and only in the LSB of one channel. Notice that
# the channel that differs is R if the coordinate is 0 mod
# 3, G if the coordinate is 1 mod 3, B if the coordinate is
# 2 mod 3 (essentially, the channel used cycles between
# R, G, B, R, G, B, etc) - notice with e.g. pixels 18
# through 23 changing RGBRGB
# Also, the differences stop at around the 256th pixel,
# which is a nice round multiple of 8.
# So we extract the LSBs
bits = ''.join([str(new[i][i][i%3]%2) for i in range(256)])
print(bits)
# This looks like the flag
# For readability let's split it into bytes
_bytes = re.findall('.{8}', bits)
print('\n'.join(_bytes))
# And convert to ASCII
chars = [chr(int("0b"+byte,2)) for byte in _bytes]
print(''.join(chars))
