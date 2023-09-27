#!/usr/bin/env python3

"""
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
Sept. 2023

Write a nested function closure in Python. This is a function that returns a function, and the
returned function has access to the variables in the scope of the outer function.

Status: Done and works!

keywords: (keywords)

Check this script with `pylint` v2.0.0 or later. See "eRCaGuy_hello_world/python/README.md" for
installation instructions to install the latest version from GitHub.
For a list of all error codes, such as `C0301`, `C0116`, `W0105`, etc., see here:
https://pylint.pycqa.org/en/latest/messages/messages_list.html
```bash
pylint nested_function_closure.py
```

Run command:
```bash
./nested_function_closure.py
# OR
python3 nested_function_closure.py
```

References:
1. GitHub Copilot. It wrote most of this code for me, including the definition of a "closure" above.
1.

"""


def outer_function():
    x = 1

    def inner_function():
        print(f"x = {x}")

    return inner_function

my_func_closure = outer_function()
my_func_closure()  # Output: 1



# pylint: disable-next=pointless-string-statement
"""
SAMPLE OUTPUT:

    eRCaGuy_hello_world$ python/nested_function_closure.py
    x = 1

"""
