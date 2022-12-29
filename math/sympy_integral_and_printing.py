#!/usr/bin/env python3

"""
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
19 Aug. 2022

Demonstrate basic symbolic integral calculus and printing using SymPy.

Status: done and works!

Check this script with `pylint` v2.0.0 or later. See "eRCaGuy_hello_world/python/README.md" for
installation instructions to install the latest version from GitHub.
For a list of all error codes, such as `C0301`, `C0116`, `W0105`, etc., see here:
https://pylint.pycqa.org/en/latest/messages/messages_list.html
```bash
pylint sympy_integral_and_printing.py
```

Run command:
```bash
./sympy_integral_and_printing.py
# OR
python3 sympy_integral_and_printing.py
```

References:
1. [my answer with this code] Simplest way to solve mathematical equations in
   Python: "SymPy symbolic Python library demo: symbolically solving math and
   integrals & pretty-printing the output":
   https://stackoverflow.com/a/73424544/4561887
1. https://docs.sympy.org/latest/tutorial/calculus.html
1. https://docs.sympy.org/latest/tutorial/printing.html

"""


from sympy import *
x, y, z = symbols('x y z')
init_printing(use_unicode=True)

# Store an integral
integral = Integral(exp(-x**2 - y**2), (x, -oo, oo), (y, -oo, oo))
# print it in various ways
print("ORIGINAL INTEGRAL:")
print(pretty(integral))
pprint(integral)        # "pretty print": same as above
print(pretty(integral, use_unicode=False))  # pretty print with ASCII instead
                                            # of unicode
print(integral)         # plain text
print(latex(integral))  # in LaTeX format

# Now solve the integral and output the result by telling it to
# "do it".
result = integral.doit()
# print it in various ways
print("\nRESULT:")
print(pretty(result))
pprint(result)
print(pretty(result, use_unicode=False))
print(result)
print(latex(result))



# pylint: disable-next=pointless-string-statement
"""
SAMPLE OUTPUT:

    eRCaGuy_hello_world/math$ ./sympy_integral_and_printing.py
    ORIGINAL INTEGRAL:
    ∞  ∞
    ⌠  ⌠
    ⎮  ⎮      2    2
    ⎮  ⎮   - x  - y
    ⎮  ⎮  ℯ          dx dy
    ⌡  ⌡
    -∞ -∞
    ∞  ∞
    ⌠  ⌠
    ⎮  ⎮      2    2
    ⎮  ⎮   - x  - y
    ⎮  ⎮  ℯ          dx dy
    ⌡  ⌡
    -∞ -∞
     oo  oo
      /   /
     |   |
     |   |      2    2
     |   |   - x  - y
     |   |  e          dx dy
     |   |
    /   /
    -oo -oo
    Integral(exp(-x**2 - y**2), (x, -oo, oo), (y, -oo, oo))
    \int\limits_{-\infty}^{\infty}\int\limits_{-\infty}^{\infty} e^{- x^{2} - y^{2}}\, dx\, dy

    RESULT:
    π
    π
    pi
    pi
    \pi

"""
