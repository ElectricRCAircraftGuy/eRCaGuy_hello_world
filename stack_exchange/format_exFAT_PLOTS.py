#!/usr/bin/env python3

"""
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
22 May 2023

Do some plots for this article.

Status: works!

keywords: (keywords)

Check this script with `pylint` v2.0.0 or later. See "eRCaGuy_hello_world/python/README.md" for
installation instructions to install the latest version from GitHub.
For a list of all error codes, such as `C0301`, `C0116`, `W0105`, etc., see here:
https://pylint.pycqa.org/en/latest/messages/messages_list.html
```bash
pylint hello_world.py
```

Run command:
```bash
./hello_world.py
# OR
python3 hello_world.py
```

References:
1. ***** https://matplotlib.org/stable/tutorials/introductory/pyplot.html
1. Log bases in matplotlib: https://stackoverflow.com/a/8888110/4561887
1. My answer where I post some of this code to show how to label x,y data in plots:
   https://stackoverflow.com/a/76309590/4561887

"""

import matplotlib
import matplotlib.pyplot as plt
from numpy.polynomial import Polynomial
from statistics import mean

# gibibytes to tebibytes
def gb_to_tb(gb):
    return gb/1024

# ==================================================================================================
# Figure 1
# ==================================================================================================

# Specify the figure width and height in inches: (width, height)!
# See:
# 1. https://matplotlib.org/stable/api/_as_gen/matplotlib.pyplot.figure.html
# 2. https://stackoverflow.com/a/28575650/4561887
f1 = plt.figure(figsize=(14, 9.6)) # default is `(6.4, 4.8)` inches

# --------------------------------------------------
# subplot: top-left
# --------------------------------------------------

f1.add_subplot(2, 2, 1)  # 2 rows, 2 columns, plot 1

# speed (MB/s) vs cluster size (KiB)
x_cluster_size = [0.5, 4, 8, 32, 128, 32768]

y_speed = [
    mean([87.36, 96.84]),
    mean([285.36, 352.37, 309.35]),
    mean([333.19, 320.87, 360.62]),
    mean([360.59, 329.26, 387.60]),
    mean([392.01, 363.88, 413.63]),
    mean([437.09, 409.12, 436.98]),
]

plt.plot(x_cluster_size, y_speed, 'b-o', label='When writing a 5.3 GB file')
plt.legend(loc='lower right')
plt.xscale('log', base=2)
plt.ylabel('Speed (MB/sec)')
plt.xlabel('exFAT cluster size (KiB)')
plt.title("exFAT cluster size vs speed")
# display (x, y) values next to each point
for i, x in enumerate(x_cluster_size):
    y = y_speed[i]
    # first element
    if i == 0:
        plt.text(x+.2, y, f"({x} KiB, {y:.0f} MB/sec)", horizontalalignment="left")
    # last element
    elif i == len(x_cluster_size) - 1:
        plt.text(x-10000, y, f"({x} KiB, {y:.0f} MB/sec)", horizontalalignment="right")
    else:
        plt.text(x, y-20, f"({x} KiB, {y:.0f} MB/sec)", horizontalalignment="left")

# --------------------------------------------------
# subplot: top-right
# Wasted space as a function of exFAT cluster size
# --------------------------------------------------
axes2 = f1.add_subplot(2, 2, 2)

gb_0_5 = 74  # GB used for a cluster size of 0.5 KiB (measured)
gb_128 = 194 # GB used for a cluster size of 128 KiB (measured)
wasted_gb = gb_128 - gb_0_5
# In GB; estimated. This assumes that *all* of the wasted space is due to small, individual files
# which take up a *single* cluster each. So, the decreased space they'd take up is directly
# proportional to the cluster size difference.
# We do cluster_size_KiB / 128_KiB, since the 128 KiB cluster size is the one we actually
# measured with real data, post-copy!
y_size_on_disk_gb = [
    # gb_0_5,
    gb_0_5 + wasted_gb*(0.5/128),
    gb_0_5 + wasted_gb*(4/128),
    gb_0_5 + wasted_gb*(8/128),
    gb_0_5 + wasted_gb*(32/128),
    gb_0_5 + wasted_gb*(128/128),
    gb_0_5 + wasted_gb*(32768/128),
]
# Convert to tebibytes, using a list comprehension
# y_size_on_disk_tb = [gb_to_tb(y) for y in y_size_on_disk_gb]

plt.plot(x_cluster_size, y_size_on_disk_gb, 'b-o',
         label='For a representative MacOS system with\n~1M files and 74 GB of data')

plt.legend(loc='upper left')
plt.xscale('log', base=2)
plt.yscale('log', base=2)
plt.ylabel('Size on Disk (GB)')
plt.xlabel('exFAT cluster size (KiB)')
plt.title("Wasted space: Size on disk as a function of exFAT cluster size\n" +
          "(for a filesystem of ~74 GB of data)")

# show zeros on y-axis, instead of powers of 2; see: https://stackoverflow.com/a/40336300/4561887
axes2.yaxis.set_major_formatter(matplotlib.ticker.ScalarFormatter())
axes2.yaxis.get_major_formatter().set_scientific(False)
axes2.yaxis.get_major_formatter().set_useOffset(False)

# display (x, y) values next to each point
for i, x in enumerate(x_cluster_size):
    y = y_size_on_disk_gb[i]
    if i > 3:
        plt.text(x+x*.2, y-y*.1, f"({x} KiB, {y:.0f} GB)", horizontalalignment="left", rotation=0)
    else:
        plt.text(x, y+20, f"({x} KiB, {y:.0f} GB)", horizontalalignment="left", rotation=50)

# --------------------------------------------------
# subplot: bottom-left
# Same as just above, but withOUT the last point, to zoom in
# --------------------------------------------------

f1.add_subplot(2, 2, 3)

# Curve fitting
# See:
# 1. https://stackoverflow.com/questions/18767523/fitting-data-with-numpy
# 1. ***** https://numpy.org/doc/stable/reference/generated/numpy.polynomial.polynomial.Polynomial.html#numpy.polynomial.polynomial.Polynomial
#   1. https://numpy.org/doc/stable/reference/generated/numpy.polynomial.polynomial.Polynomial.fit.html#numpy.polynomial.polynomial.Polynomial.fit
#   1. Transition guide to use the new API:
#      https://numpy.org/doc/stable/reference/routines.polynomials.html

poly_series = Polynomial.fit(x_cluster_size, y_size_on_disk_gb, deg=2)
# Use a custom domain (range of x values) to stop prior to the last cluster size, in order to
# thereby "zoom in".
x_fit, y_fit = poly_series.linspace(domain=[x_cluster_size[0], x_cluster_size[-2]])
# print(x_fit)
# print()
# print(y_fit)
plt.plot(x_fit, y_fit, '-', color="orange", linewidth=2,
    label="Polynomial Series 2nd degree\nleast squares best fit curve")

plt.plot(x_cluster_size[:-1], y_size_on_disk_gb[:-1], 'bo',
    label='For a representative MacOS system with\n~1M files and 74 GB of data')
plt.legend(loc='upper left')
plt.xscale('log', base=2)
plt.ylabel('Size on Disk (GB)')
plt.xlabel('exFAT cluster size (KiB)')
plt.title("Wasted space: Size on disk as a function of exFAT cluster size\n" +
          "(for a filesystem of ~74 GB of data) [Zoomed in]")

# display (x, y) values next to each point
for i, x in enumerate(x_cluster_size[:-1]):
    y = y_size_on_disk_gb[i]
    if i == len(x_cluster_size) - 2:
        plt.text(x+x*.2, y-10, f"({x} KiB, {y:.0f} GB)", horizontalalignment="center", rotation=0)
    elif i > 2:
        plt.text(x+x*.2, y-2, f"({x} KiB, {y:.0f} GB)", horizontalalignment="left", rotation=0)
    else:
        plt.text(x, y+3, f"({x} KiB, {y:.0f} GB)", horizontalalignment="left", rotation=50)

# --------------------------------------------------
# subplot: bottom-right
# Same as top-right plot, but in % increase instead
# --------------------------------------------------

axes = f1.add_subplot(2, 2, 4)

y_size_increase_pct = [(y - gb_0_5)/gb_0_5*100 for y in y_size_on_disk_gb]
# artificially modify this to make it plot:
if y_size_increase_pct[0] == 0:
    y_size_increase_pct[0] = .7
# print(y_size_increase_pct)
plt.plot(x_cluster_size, y_size_increase_pct, 'b-o',
    label='For a representative MacOS system with\n~1M files and 74 GB of data')
plt.legend(loc=(0.015, 0.75)) # https://stackoverflow.com/a/61574999/4561887
plt.xscale('log', base=2)
plt.yscale('log', base=10)
plt.ylabel('Percent "size on disk" growth\nover actual disk size (%)')
plt.xlabel('exFAT cluster size (KiB)')
plt.title("Wasted space: Percent wasted space as a function of exFAT cluster size\n" +
          "(for a filesystem of ~74 GB of data)")

axes.yaxis.set_major_formatter(matplotlib.ticker.ScalarFormatter())
axes.yaxis.get_major_formatter().set_scientific(False)
axes.yaxis.get_major_formatter().set_useOffset(False)

# display (x, y) values next to each point
for i, x in enumerate(x_cluster_size):
    y = y_size_increase_pct[i]
    if i == len(x_cluster_size) - 1:
        plt.text(x-x*.2, y-y*.2, f"({x} KiB, {y:.2f}%)", horizontalalignment="right", rotation=0)
    else:
        plt.text(x+x*.4, y-y*.2, f"({x} KiB, {y:.2f}%)", horizontalalignment="left", rotation=0)

# ================================================
# Show all figures
# ================================================

# Figure title
# https://matplotlib.org/3.1.1/gallery/subplots_axes_and_figures/figure_title.html
f1.suptitle("exFAT speed & disk usage vs cluster size", fontsize=18)
# Figure footer
f1.text(0.5, 0.015,
        "Source: Gabriel Staples, 22 May 2023, https://gabrielstaples.com/exfat-clusters/",
        horizontalalignment="center")

plt.subplots_adjust(hspace=0.4)
plt.subplots_adjust(wspace=0.3)
plt.show()


# def main():
#     """
#     The main function of this program.
#     """
#     print("Hello world!")


# # Only run `main()` if this script is **run**, NOT imported
# if __name__ == '__main__':
#     main()



# pylint: disable-next=pointless-string-statement
"""
SAMPLE OUTPUT:

    eRCaGuy_hello_world/python$ ./hello_world.py
    Hello world!

"""
