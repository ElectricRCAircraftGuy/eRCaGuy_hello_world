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
pylint sympy_integral_and_printing_detailed_comments.py
```

Run command:
```bash
./sympy_integral_and_printing_detailed_comments.py
# OR
python3 sympy_integral_and_printing_detailed_comments.py
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

# Print the integral in various ways

print("1. pretty print it (this technique works only when " +
      "running in an interactive session)")
integral

print("2. pretty print it with 'print(pretty())'")
print(pretty(integral))

print("3. pretty print it with 'pprint()'")
pprint(integral)

print("4. pretty print it in 2 ways using ASCII instead of unicode")
print(pretty(integral, use_unicode=False))
pprint(integral, use_unicode=False)

print("5. print it as plain text")
print(integral)

print("6. print it in LaTeX format--ex: to copy and paste onto " +
      "https://math.stackexchange.com/ or onto your blog or website which " +
      "uses MathJax for pretty equation rendering.")
print(latex(integral))


# Now solve the integral and output the result by telling it to
# "do it".
result = integral.doit()
print("\nResult in pretty unicode")
print(pretty(result))
print("Result in pretty ASCII")
print(pretty(result, use_unicode=False))
print("Result in plain text")
print(result)
print("Result in LaTeX format")
print(latex(result))



# pylint: disable-next=pointless-string-statement
"""
SAMPLE OUTPUT:

    eRCaGuy_hello_world/math$ ./sympy_integral_and_printing_detailed_comments.py
    1. pretty print it (this technique works only when running in an interactive session)
    2. pretty print it with 'print(pretty())'
    ∞  ∞
    ⌠  ⌠
    ⎮  ⎮      2    2
    ⎮  ⎮   - x  - y
    ⎮  ⎮  ℯ          dx dy
    ⌡  ⌡
    -∞ -∞
    3. pretty print it with 'pprint()'
    ∞  ∞
    ⌠  ⌠
    ⎮  ⎮      2    2
    ⎮  ⎮   - x  - y
    ⎮  ⎮  ℯ          dx dy
    ⌡  ⌡
    -∞ -∞
    4. pretty print it in 2 ways using ASCII instead of unicode
     oo  oo
      /   /
     |   |
     |   |      2    2
     |   |   - x  - y
     |   |  e          dx dy
     |   |
    /   /
    -oo -oo
     oo  oo
      /   /
     |   |
     |   |      2    2
     |   |   - x  - y
     |   |  e          dx dy
     |   |
    /   /
    -oo -oo
    5. print it as plain text
    Integral(exp(-x**2 - y**2), (x, -oo, oo), (y, -oo, oo))
    6. print it in LaTeX format--ex: to copy and paste onto https://math.stackexchange.com/ or onto your blog or website which uses MathJax for pretty equation rendering.
    \int\limits_{-\infty}^{\infty}\int\limits_{-\infty}^{\infty} e^{- x^{2} - y^{2}}\, dx\, dy

    Result in pretty unicode
    π
    Result in pretty ASCII
    pi
    Result in plain text
    pi
    Result in LaTeX format
    \pi

"""
