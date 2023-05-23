#!/usr/bin/env python3

"""
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
22 May 2023

Learn how to do polynomial best fits in Python, using `numpy`!
We will plot with `matplotlib`.

This code was modified from the code from the bottom of this page:
https://numpy.org/doc/stable/reference/routines.polynomials.classes.html

Status: done and works!

keywords: (keywords)

Check this script with `pylint` v2.0.0 or later. See "eRCaGuy_hello_world/python/README.md" for
installation instructions to install the latest version from GitHub.
For a list of all error codes, such as `C0301`, `C0116`, `W0105`, etc., see here:
https://pylint.pycqa.org/en/latest/messages/messages_list.html
```bash
pylint plot_best_fit_polynomial.py
```

Run command:
```bash
./plot_best_fit_polynomial.py
# OR
python3 plot_best_fit_polynomial.py
```

References:
1. *****+ See the example at the bottom of this page, which is where I
   originally modified this code from:
   https://numpy.org/doc/stable/reference/routines.polynomials.classes.html
1. ---
1. https://stackoverflow.com/questions/18767523/fitting-data-with-numpy
1. ***** https://numpy.org/doc/stable/reference/generated/numpy.polynomial.polynomial.Polynomial.html#numpy.polynomial.polynomial.Polynomial
  1. https://numpy.org/doc/stable/reference/generated/numpy.polynomial.polynomial.Polynomial.fit.html#numpy.polynomial.polynomial.Polynomial.fit
  1. Transition guide to use the new API:
     https://numpy.org/doc/stable/reference/routines.polynomials.html

"""

# ORIGINAL CODE:
# From the bottom of here: https://numpy.org/doc/stable/reference/routines.polynomials.classes.html
"""
import numpy as np
import matplotlib.pyplot as plt
from numpy.polynomial import Chebyshev as T

np.random.seed(11)
x = np.linspace(0, 2*np.pi, 20)
y = np.sin(x) + np.random.normal(scale=.1, size=x.shape)
p = T.fit(x, y, 5)
plt.plot(x, y, 'o')
xx, yy = p.linspace()
plt.plot(xx, yy, lw=2)
p.domain
p.window
plt.show()
"""

# MY VERSION:

import matplotlib.pyplot as plt
import numpy as np
from numpy.polynomial import Chebyshev
from numpy.polynomial import Polynomial

# https://numpy.org/doc/stable/reference/random/generated/numpy.random.seed.html
np.random.seed(11)

# Line-space: get evenly-spaced points to plot a line. See:
# https://numpy.org/doc/stable/reference/generated/numpy.linspace.html
# Returns a numpy ndarray: https://numpy.org/doc/stable/reference/generated/numpy.ndarray.html
x = np.linspace(0, 2*np.pi, num=20)

# Create some points from numpy ndarray `x` which are sinusoidal + some normal (Gaussian) noise.
# See `numpy.random.normal()` here:
# https://numpy.org/doc/stable/reference/random/generated/numpy.random.normal.html
y = np.sin(x) + np.random.normal(scale=.1, size=x.shape)

# For Chebyshev Series, see:
# 1. https://numpy.org/doc/stable/reference/routines.polynomials.chebyshev.html
# 1. Class definition:
#    https://numpy.org/doc/stable/reference/generated/numpy.polynomial.chebyshev.Chebyshev.html
#
# Obtain a 5th degree (order) least-squares fit curve to the x, y data
cheby = Chebyshev.fit(x, y, deg=5)
# Lines-space: get evenly-spaced points to plot a line; see:
# https://numpy.org/doc/stable/reference/generated/numpy.polynomial.chebyshev.Chebyshev.linspace.html
xx_cheby, yy_cheby = cheby.linspace()

print(f"cheby.domain = \n{cheby.domain}")
print(f"cheby.window = \n{cheby.window}")

# let's do it for a Polynomial series too; see:
# https://numpy.org/doc/stable/reference/generated/numpy.polynomial.polynomial.Polynomial.html
poly = Polynomial.fit(x, y, deg=5)
xx_poly, yy_poly = poly.linspace()

# plot

f1 = plt.figure()

plt.plot(x, y, 'o')
plt.plot(xx_cheby, yy_cheby, linewidth=4,
   label="Chebyshev Series 5th degree\nleast squares best fit curve")
plt.plot(xx_poly, yy_poly, 'k', linewidth=1,
   label="Polynomial Series 5th degree\nleast squares best fit curve")

plt.legend()
plt.show()


# pylint: disable-next=pointless-string-statement
"""
SAMPLE OUTPUT:

A single figure is displayed in its own GUI window. It consists of some dosts scattered around the
shape of a sine wave, with a thick Chebyshev best fit curve and a thin black Polynomial best fit
curve on top of that, both in the shape of a sine wave.

"""
