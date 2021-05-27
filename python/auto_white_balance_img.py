#!/usr/bin/python3

"""
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

Gabriel Staples
30 Apr. 2021

Demonstrate how to manually do the equivalent of GIMP's `Colors --> Auto --> White Balance` feature
using Python. This is useful to apply to photos taken with your phone of documents, to lighten them
up.

To run this script:
    ./auto_white_balance_img.py
    # OR
    python3 auto_white_balance_img.py

References:
1. [my answer] https://stackoverflow.com/a/67343271/4561887

"""

import cv2
import numpy as np

file_in = '../test_photos/test1.jpg'
print(f"File to process = {file_in}")
print(f"See https://stackoverflow.com/a/67343271/4561887.")

file_in_base = file_in[:-4] # strip file extension
file_in_extension = file_in[-4:]

img = cv2.imread(file_in)

# From @banderlog013's answer: https://stackoverflow.com/a/54864315/4561887
print("Processing img using @banderlog013's technique.")
x = []
# get histogram for each channel
for i in cv2.split(img):
    hist, bins = np.histogram(i, 256, (0, 256))
    # discard colors at each end of the histogram which are used by only 0.05%
    img_out1 = np.where(hist > hist.sum() * 0.0005)[0]
    i_min = img_out1.min()
    i_max = img_out1.max()
    # stretch hist
    img_out1 = (i.astype(np.int32) - i_min) / (i_max - i_min) * 255
    img_out1 = np.clip(img_out1, 0, 255)
    x.append(img_out1.astype(np.uint8))

# From @Canette Ouverture's answer: https://stackoverflow.com/a/56365560/4561887
print("Processing img using @Canette Ouverture's technique.")
img_out2 = np.zeros_like(img) # Initialize final image
for channel_index in range(3):
    hist, bins = np.histogram(img[..., channel_index].ravel(), 256, (0, 256))
    bmin = np.min(np.where(hist>(hist.sum()*0.0005)))
    bmax = np.max(np.where(hist>(hist.sum()*0.0005)))
    img_out2[...,channel_index] = np.clip(img[...,channel_index], bmin, bmax)
    img_out2[...,channel_index] = ((img_out2[...,channel_index]-bmin) /
        (bmax - bmin) * 255)

# Write new files
file_out1 = file_in_base + '_out1' + file_in_extension
file_out2 = file_in_base + '_out2' + file_in_extension
print("Writing new files:\n" +
     f"  {file_out1}\n" +
     f"  {file_out2}")
cv2.imwrite(file_out1, img_out1)
cv2.imwrite(file_out2, img_out2)

print("Done!")
