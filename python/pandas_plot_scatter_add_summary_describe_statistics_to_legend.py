#!/usr/bin/env python3

"""
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
Oct. 2023

Make a simple line/scatter plot with summary statistics in the legend.

Status: Done and works! Outputs a nice since wave with noise plot with summary
statistics in the legend.

keywords: scatter plot line plot sine wave with noise gaussian normal
distribution bell curve summary statistics in legend mean median mode standard
deviation

Check this script with `pylint` v2.0.0 or later. See "eRCaGuy_hello_world/python/README.md" for
installation instructions to install the latest version from GitHub.
For a list of all error codes, such as `C0301`, `C0116`, `W0105`, etc., see here:
https://pylint.pycqa.org/en/latest/messages/messages_list.html
```bash
pylint pandas_plot_scatter_add_summary_describe_statistics_to_legend.py
```

Run command:
```bash
./pandas_plot_scatter_add_summary_describe_statistics_to_legend.py
# OR
python3 pandas_plot_scatter_add_summary_describe_statistics_to_legend.py
```

References:
1. GitHub Copilot
1. https://numpy.org/doc/stable/reference/generated/numpy.linspace.html
1. https://numpy.org/doc/stable/reference/random/generated/numpy.random.normal.html
1.

"""

import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# generate sinusoidal data with some random Gaussian (normal distribution, or
# "bell curve") noise added to it

NUM_POINTS = 200
ONE_PERIOD = 2*np.pi  # 2*pi radians = 360 degrees = 1 full period
x = np.linspace(0, 2*ONE_PERIOD, NUM_POINTS)
# the standard deviation, or "width", of the noise; see:
# https://numpy.org/doc/stable/reference/random/generated/numpy.random.normal.html
CENTER = 0  # mean (center) of the normal distribution
SCALE = 0.3  # standard deviation (scale) of the normal distribution
NOISE_SIZE = NUM_POINTS  # number of points in the noise
noise_array = np.random.normal(CENTER, SCALE, NUM_POINTS)
y = np.sin(x) + noise_array

# create a dataframe from the numpy arrays above
df = pd.DataFrame({'x': x, 'y': y})
print(df)

# plot the data

# fig = plt.figure(figsize=(18, 10.8))  # default is `(6.4, 4.8)` inches
fig = plt.figure()
plt.title("Sine wave with noise")
plt.plot(
    df["x"].to_numpy(),
    df["y"].to_numpy(),
    # 'bo', # blue circles, no line
    'b-o', # blue line with circles
    # add summary statistics to the legend; NB: "The 50 percentile is the same
    # as the median."; see:
    # https://pandas.pydata.org/docs/reference/api/pandas.DataFrame.describe.html
    label=f"{df['y'].describe()}"
)
# fontsize: int or 'xx-small', 'x-small', 'small', 'medium', 'large', 'x-large',
# 'xx-large'; see:
# https://matplotlib.org/stable/api/_as_gen/matplotlib.pyplot.legend.html
plt.legend(fontsize="x-small")
plt.xlabel("radians (rad)")
plt.ylabel("amplitude (-)")

plt.show()


# pylint: disable-next=pointless-string-statement
"""
SAMPLE OUTPUT:

eRCaGuy_hello_world$ python/pandas_plot_scatter_add_summary_describe_statistics_to_legend.py
             x         y
0     0.000000  0.170997
1     0.063148 -0.167844
2     0.126295 -0.319292
3     0.189443 -0.016271
4     0.252590  0.640195
..         ...       ...
195  12.313780 -0.237526
196  12.376928 -0.566675
197  12.440075 -0.445570
198  12.503223  0.622308
199  12.566371  0.156042

[200 rows x 2 columns]

"""
