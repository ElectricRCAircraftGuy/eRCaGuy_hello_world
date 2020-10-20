#!/usr/bin/python3

"""
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
19 Oct. 2020

Demonstrate how to use `textwrap.dedent()` to keep long, multi-line strings indented in your code
while having them NOT indented in their printed output! This is a VERY USEFUL trick to keep your
code looking nice! Previously, I had to do what is in my first answer below, which is so much LESS
clean and not as nice to look at!

References:
1. [my old answer] https://stackoverflow.com/questions/10985603/multi-line-string-with-arguments-how-to-declare/54564926#54564926
2. [my NEW answer] https://stackoverflow.com/questions/10985603/multi-line-string-with-arguments-how-to-declare/64437283#64437283
2. [official documentation on `textwrap` module!] https://docs.python.org/3/library/textwrap.html

Run command:

    ./textwrap_practice_1.py

  OR:

    python3 textwrap_practice_1.py


"""

import textwrap

# =================== START OF REQUIRED STUFF FOR THE TESTS BELOW ==================================

def myFunc1():
    """
    Do something.
    Params:  NA
    Returns: NA
    """
    pass

class Math:
    """
    A basic "math" class to add and subtract
    """

    def __init__(self):
        """
        New object initialization function.
        Params:  NA
        Returns: NA
        """
        pass

    def add(a, b):
        """
        Add a and b together.
        Params:  a   1st number to add
                 b   2nd number to add
        Returns: the sum of a + b
        """
        return a + b

    def subtract(a, b):
        """
        Subtract b from a.
        Params:  a   number to subtract from
                 b   number to subtract
        Returns: the result of a - b
        """
        return a - b

# =================== END OF REQUIRED STUFF FOR THE TESTS BELOW ====================================

# Instead of this (and losing the nice, clean, indentation):

cmd = '''line {0}
line {1}
line {2}'''.format(1,2,3)

print(cmd)
print()

# Do this (and KEEP the nice, clean, indentation)!

cmd = textwrap.dedent('''\
    line {0}
    line {1}
    line {2}''').format(1,2,3)

print(cmd)
print()

# And of course, if it's really long, you can put each `format()` arg on a new line too:

cmd = textwrap.dedent('''\
    line {0}
    line {1}
    line {2}
    line {3}
    line {4}
    line {5}
    line {6}
    line {7}
    line {8}
    line {9}
    line {10}
    line {11}
    line {12}
    line {13}
    line {14}
    line {15}
    line {16}
    line {17}
    line {18}
    line {19}''').format(
        1,
        2,
        3,
        4,
        5,
        6,
        7,
        8,
        9,
        10,
        11,
        12,
        13,
        14,
        15,
        16,
        17,
        18,
        19,
        20,
    )

print(cmd)
print()


# Instead of this:

print("\n\n" +
      "########################\n" +
      "PRINT DOCSTRING DEMO:\n" +
      "########################")


# Do this!
# Note: use the `\` below to prevent the implicit newline right after it from being printed.
print(textwrap.dedent("""

      ########################
      PRINT DOCSTRING DEMO:
      ########################\
      """))


# Instead of this:

def printDocstrings1():
    """
    Print all document strings for this module, then exit.
    Params:  NA
    Returns: NA
    """

    # A LITTLE BIT UGLY, BUT IT WORKS.
    print("""
---------------------
Module Documentation:
---------------------
printDocstrings:{}
myFunc1:{}
class Math:{}
    __init__:{}
    add:{}
    subtract:{}""".format(
        printDocstrings1.__doc__,
        myFunc1.__doc__,
        Math.__doc__,
        Math.__init__.__doc__,
        Math.add.__doc__,
        Math.subtract.__doc__))


# Do this!

def printDocstrings2():
    """
    Print all document strings for this module, then exit.
    Params:  NA
    Returns: NA
    """

    # MUCH CLEANER! Now I can have the proper indentation on the left withOUT
    # it printing that indentation!
    print(textwrap.dedent("""\
    ---------------------
    Module Documentation:
    ---------------------
    printDocstrings:{}
    myFunc1:{}
    class Math:{}
        __init__:{}
        add:{}
        subtract:{}""").format(
            printDocstrings2.__doc__,
            myFunc1.__doc__,
            Math.__doc__,
            Math.__init__.__doc__,
            Math.add.__doc__,
            Math.subtract.__doc__))


printDocstrings1()
printDocstrings2()
