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

Status: wip

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


# pylint: disable-next=pointless-string-statement
"""
SAMPLE OUTPUT:

A single figure is displayed in its own GUI window.

"""
