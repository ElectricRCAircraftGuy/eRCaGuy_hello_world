#!/usr/bin/env python3

"""
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
Sept. 2023

Test which types are mutable and which are immutable.

Status: (status)

keywords: (keywords)

Check this script with `pylint` v2.0.0 or later. See "eRCaGuy_hello_world/python/README.md" for
installation instructions to install the latest version from GitHub.
For a list of all error codes, such as `C0301`, `C0116`, `W0105`, etc., see here:
https://pylint.pycqa.org/en/latest/messages/messages_list.html
```bash
pylint mutable_and_immutable_types.py
```

Run command:
```bash
./mutable_and_immutable_types.py
# OR
python3 mutable_and_immutable_types.py
```

References:
1. This question and the answer I'm about to add there:
   https://stackoverflow.com/q/8056130/4561887
1. GitHub Copilot (very minor assistance in this case)


"""


def modify_variable(var):
    """
    Modifies the variable passed to it so that we can see later if the change to
    this variable can be seen outside the function.
    """
    print(f"var before modification = {var}")

    if type(var) is bool:
        print("var is a bool")
        var = not var  # flip it
    elif type(var) is float:
        print("var is a float")
        var += 1.0  # increment it
    elif type(var) is int:
        print("var is an int")
        var += 1  # increment it
    elif type(var) is str:
        print("var is a str (string)")
        var += "; some more words" # append some new words to it
    elif type(var) is list:
        print("var is a list")
        var.append(1)  # append a 1 to it
    elif type(var) is dict:
        print("var is a dict")
        var["new_key"] = "new_value"  # add a new key-value pair to it
    elif type(var) is tuple:
        print("var is a tuple")
        var = (1, 2, 3)  # reassign it to a new tuple

    print(f"var after modification = {var}\n")


def is_mutable(value_new, value_old):
    """
    Returns whether the variable is "mutable" or "immutable".

    This is identified simply by checking if `value_new` is the same as
    `value_old`. If it is, then it is immutable, since the update above
    was *not* seen outside the `modify_variable` function. If the two values
    are different, then it *is* mutable.
    """
    print(f"value_new = {value_new}")  # debugging
    print(f"value_old = {value_old}")  # debugging

    if value_new == value_old:
        return "immutable"
    else:
        return "mutable"


#############
INITIAL_VALUE_BOOL = True
INITIAL_VALUE_FLOAT = 1.0
INITIAL_VALUE_INT = 7
INITIAL_VALUE_STR = "some words"
INITIAL_VALUE_LIST = [7, 8, 9]
INITIAL_VALUE_DICT = {"key1": "value1", "key2": "value2"}
INITIAL_VALUE_TUPLE = (7, 8, 9)

my_bool = INITIAL_VALUE_BOOL
my_float = INITIAL_VALUE_FLOAT
my_int = INITIAL_VALUE_INT
my_str = INITIAL_VALUE_STR
my_list = INITIAL_VALUE_LIST
my_dict = INITIAL_VALUE_DICT
my_tuple = INITIAL_VALUE_TUPLE

modify_variable(my_bool)
modify_variable(my_float)
modify_variable(my_int)
modify_variable(my_str)
modify_variable(my_list)
modify_variable(my_dict)
modify_variable(my_tuple)

print("is_mutable(my_bool, INITIAL_VALUE_BOOL)      --> ",
       is_mutable(my_bool, INITIAL_VALUE_BOOL), "\n")
print("is_mutable(my_float, INITIAL_VALUE_FLOAT)    --> ",
       is_mutable(my_float, INITIAL_VALUE_FLOAT), "\n")
print("is_mutable(my_int, INITIAL_VALUE_INT)        --> ",
       is_mutable(my_int, INITIAL_VALUE_INT), "\n")
print("is_mutable(my_str, INITIAL_VALUE_STR)        --> ",
       is_mutable(my_str, INITIAL_VALUE_STR), "\n")
print("is_mutable(my_list, INITIAL_VALUE_LIST)      --> ",
       is_mutable(my_list, INITIAL_VALUE_LIST), "\n")
print("is_mutable(my_dict, INITIAL_VALUE_DICT)      --> ",
       is_mutable(my_dict, INITIAL_VALUE_DICT), "\n")
print("is_mutable(my_tuple, INITIAL_VALUE_TUPLE)    --> ",
       is_mutable(my_tuple, INITIAL_VALUE_TUPLE), "\n")


########## also show triple assignment:
# no side effects
# a = b = c = 1  # by copy
# a = 7  # b and c are NOT updated too
#
# side effects
# mydict3 = mydict2 = mydict1 = {"key": "value"}  # by reference
# mydict3["new_key"] = "new_value"  # mydict2 and mydict1 are both updated too!

# pylint: disable-next=pointless-string-statement
"""
SAMPLE OUTPUT:

    eRCaGuy_hello_world/python$ ./mutable_and_immutable_types.py
    Hello world!

"""
