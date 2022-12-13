<!--
GS
- written approx. Summer 2022
-->


## SymPy symbolic Python library demo: symbolically solving math and integrals & pretty-printing the output

[From @Autoplectic:](https://stackoverflow.com/a/1642479/4561887)

> [sympy](http://sympy.org/) is exactly what you're looking for.

While I have a tendency to write some of the _longest_ answers on Stack Overflow, that is the _shortest_ answer I've seen on Stack Overflow. 

Let's add a basic demo.


## References and tutorials you'll need:
1. https://www.sympy.org/en/index.html --> click "Get started with the tutorial"
    1. Tutorial index: https://docs.sympy.org/latest/tutorial/index.html Example pages:
        1. [Basic Operations](https://docs.sympy.org/latest/tutorial/basic_operations.html)
        1. [Printing](https://docs.sympy.org/latest/tutorial/printing.html)
        1. [Simplification](https://docs.sympy.org/latest/tutorial/simplification.html)
        1. [Calculus](https://docs.sympy.org/latest/tutorial/calculus.html)
1. Source code: https://github.com/sympy/sympy
    1. Wiki: https://github.com/sympy/sympy/wiki
    1. Documentation section on Wiki: https://github.com/sympy/sympy/wiki#documentation
    1. FAQ: https://github.com/sympy/sympy/wiki/FAQ
        1. \*\*\*\*\* What is the best way to create symbols?: https://github.com/sympy/sympy/wiki/FAQ#what-is-the-best-way-to-create-symbols


## Interactive calculator mode

From: https://docs.sympy.org/latest/tutorial/printing.html:

> If you plan to work in an interactive calculator-type session, the `init_session()` function will automatically import everything in SymPy, create some common Symbols, setup plotting, and run `init_printing()`.

Note: if running in interactive mode, printing explicitly with `pprint()` is _not_ necessary! Rather, the output will display automatically after running each command. I show the print commands to be thorough and to show how to print when _not_ in an interactive python session.

```python
from sympy import init_session
init_session() 
```

Now do whatever symbolic math you want!

Example: solve this specific quadratic equation, in the form `a*x^2 + b*x + c` (see also: [How to solve a simple quadratic equation with Sympy?](https://stackoverflow.com/a/26787994/4561887)):

```python
eqn = -14.4*(x**2)+71.8*x+5.083
pprint(eqn)   # pretty print the eqn
roots = solve(eqn, x)
pprint(roots) # print output
```

Output:

```
        2                 
- 14.4⋅x  + 71.8⋅x + 5.083
[-0.069816293405592, 5.0559274045167]
```

Or, solve generally for the quadratic formula:

```python
var('x a b c')  # declare x, a, b, and c as symbolic variables

```


## Calculus demo

Calculus demo I came up with (see [here](https://docs.sympy.org/latest/tutorial/calculus.html) for the main tutorial I looked at to get started):

**Short version:**

```python
#!/usr/bin/env python3

from sympy import *
x, y, z = symbols('x y z')
init_printing(use_unicode=True)

integral = Integral(exp(-x**2 - y**2), (x, -oo, oo), (y, -oo, oo))
print(pretty(integral))
result = integral.doit() # "do it": evaluate the integral
print(pretty(result))
```

**Longer version:**

[eRCaGuy_hello_world/math/sympy_integral_and_printing.py](https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world/tree/master/math/sympy_integral_and_printing.py):

```python
#!/usr/bin/env python3

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
```

Note that using `pprint(integral)` is the same as `print(pretty(integral))`.


Output of running the above commands:

```
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
```

The SymPy symbolic math library in Python can do pretty much any kind of math, solving equations, simplifying, factoring, substituting values for variables, pretty printing, converting to LaTeX format, etc. etc. It seems to be a pretty robust solver in my very limited use so far. I recommend trying it out. 

Installing it, for me (tested on Linux Ubuntu), was as simple as:

```bash
pip3 install sympy
```
