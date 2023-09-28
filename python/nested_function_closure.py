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

CHAT WITH GITHUB COPILOT:
-------------------------
ElectricRCAircraftGuy:
What is a closure in Python?

GitHub Copilot:

In Python, a closure is a function object that has access to variables in its enclosing lexical scope, even when the function is called outside of that scope.

A closure is created when a nested function references a value from its enclosing scope. The nested function "closes over" the value, creating a closure that retains access to the value even after the enclosing function has returned.

Here's an example to illustrate this:
```py
def outer_function():
    x = 1

    def inner_function():
        print(x)

    return inner_function

my_func = outer_function()
my_func()  # Output: 1
```

In this example, `inner_function()` is a closure because it references the variable `x` from its enclosing scope (`outer_function()`). When `outer_function()` is called, it returns `inner_function()`, which is then assigned to `my_func`. When `my_func()` is called, it prints the value of `x`, which is defined in `outer_function()`. This works because `inner_function()` is a closure and retains access to the variables in `outer_function()`s scope, even though it is called outside of that scope.
-------------------------

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
