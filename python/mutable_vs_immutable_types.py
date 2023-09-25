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
    print(f"var before modification: {var}")

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

    print(f"var after modification:  {var}\n")


def is_mutable(variable, original_value_literal):
    """
    Returns whether the variable is "mutable" or "immutable".

    This is identified simply by checking if `variable` is the same as
    `original_value_literal`. If it is, then it is immutable, since the update
    above was *not* seen outside the `modify_variable` function. If the two
    values are different, then it *is* mutable.

    Note that the `variable` input can be the variable, but the
    `original_value_literal` must be the original value copied again into the
    call-site of this function. Otherwise, mutable types will be erroneously
    identified as immutable since the "original" variable will just be another
    reference to the same underlying data as the variable.
    """
    # print(f"variable = {variable}")  # debugging
    # print(f"original_value_literal = {original_value_literal}")  # debugging

    if variable == original_value_literal:
        return "immutable"
    else:
        return "mutable"


my_bool = True
my_float = 1.0
my_int = 7
my_str = "some words"
my_list = [7, 8, 9]
my_dict = {"key1": "value1", "key2": "value2"}
my_tuple = (7, 8, 9)

modify_variable(my_bool)
modify_variable(my_float)
modify_variable(my_int)
modify_variable(my_str)
modify_variable(my_list)
modify_variable(my_dict)
modify_variable(my_tuple)

print("is_mutable(my_bool, True)                                    --> ",
       is_mutable(my_bool, True))
print("is_mutable(my_float, 1.0)                                    --> ",
       is_mutable(my_float, 1.0))
print("is_mutable(my_int, 7)                                        --> ",
       is_mutable(my_int, 7))
print('is_mutable(my_str, "some words")                             --> ',
       is_mutable(my_str, "some words"))
print("is_mutable(my_list, [7, 8, 9])                               --> ",
       is_mutable(my_list, [7, 8, 9]))
print('is_mutable(my_dict, {"key1": "value1", "key2": "value2"})    --> ',
       is_mutable(my_dict, {"key1": "value1", "key2": "value2"}))
print("is_mutable(my_tuple, (7, 8, 9))                              --> ",
       is_mutable(my_tuple, (7, 8, 9)))
print()

# ==============================================================================
# - For **mutable** types, setting two variables to the same value gives each
#   variable a **unique underlying object** in memory, since they must have
#   separate memory to be independently mutated.
# - But for **immutable** types, setting two variables to the same value gives
#   each variable the **same underlying object,** since they cannot be mutated.
# ==============================================================================

# MUTABLE TYPES
# **Mutable type:** each variable has an **independent underlying object**
my_dict1 = {"key": "value"}
my_dict2 = {"key": "value"}
my_dict3 = {"key": "value"}
# Therefore, each of these is False because the underlying objects differ.
print(my_dict3 is my_dict2)    # False
print(my_dict2 is my_dict1)    # False
print(my_dict3 is my_dict1)    # False
# But, each of these is True because all variables have the same value.
print(my_dict3 == my_dict2)    # True
print(my_dict2 == my_dict1)    # True
print(my_dict3 == my_dict1)    # True
print()

# IMMUTABLE TYPES
## **Immutable type:** each variable has the **same underlying object**
my_int1 = 7
my_int2 = 7
my_int3 = 7
# Therefore, each of these is True because the underlying objects are the same.
print(my_int3 is my_int2)      # True
print(my_int2 is my_int1)      # True
print(my_int3 is my_int1)      # True
# And, each of these is also True because all variables have the same value.
print(my_int3 == my_int2)      # True
print(my_int2 == my_int1)      # True
print(my_int3 == my_int1)      # True
print()



# # For mutable types, changing one of these variables changes all of them. But
# # for immutable types, it does not (more on this below).
# my_dict3 = my_dict2 = my_dict1 = {"key": "value"}   # by reference (has side
#                                                     #   effects)
# my_int3 = my_int2 = my_int1 = 7                     # by copy (no side effects)

# # Each of these is True because all variables have the same value.
# print(my_dict3 == my_dict2)    # True
# print(my_dict2 == my_dict1)    # True
# print(my_dict3 == my_dict1)    # True
# # Each of these is True because all variables point to the same underlying
# # object, since a dict is **mutable** and thus passed **by reference.**
# # Therefore, the underlying object being pointed to by each of these variables
# # **is** the same underlying object!
# print(my_dict3 is my_dict2)    # True
# print(my_dict2 is my_dict1)    # True
# print(my_dict3 is my_dict1)    # True
# print()

# # Each of these is True because all variables have the same value.
# print(my_int3 == my_int2)      # True
# print(my_int2 == my_int1)      # True
# print(my_int3 == my_int1)      # True
# # Each of these is False because all variables point to different underlying
# # object, since the underlying object (int) is **immutable** and thus passed
# # **by copy.**
# print(my_int3 is my_int2)      # False
# print(my_int2 is my_int1)      # False
# print(my_int3 is my_int1)      # False
# print()



# pylint: disable-next=pointless-string-statement
"""
SAMPLE OUTPUT:

    eRCaGuy_hello_world/python$ ./mutable_and_immutable_types.py
    Hello world!

"""
