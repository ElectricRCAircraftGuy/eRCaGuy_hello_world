#!/usr/bin/env python3

"""
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
Sept. 2023

Test which types are **mutable** (have side effects, and are passed **by
reference**) vs which are **immutable** (do NOT have side effects, and are
passed **by value**).

Status: Done and works!
TODO:
1. [ ] Add `id()` checks to show that the underlying object is the same or not.
    See:
    1. https://docs.python.org/3/reference/expressions.html#is-not
    1. https://docs.python.org/3/library/functions.html#id

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
1. ***** This question and the answer I'm about to add there:
   https://stackoverflow.com/q/8056130/4561887
    1. *****+++ My answer which references and uses this code below:
       https://stackoverflow.com/a/77177223/4561887
1. GitHub Copilot (minor assistance in this case)
    1. I got started on the topic, however, with this chat with GitHub
       Copilot here:
       "eRCaGuy_hello_world/python/mutable_vs_immutable_types_initial_GitHub_Copilot_chat.md"
1.


"""


def modify_variable(var):
    """
    Modifies the variable passed to it so that we can see later if the change to
    this variable can be seen outside the function (as a "side effect").
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
    reference to the same underlying data (object) as the variable.
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

# Here's another way to test if a type is mutable:
# 1. Set 3 variables to the same value.
# 2. Modify one of them.
# 3. If the other two are also modified, then the type is mutable.

my_int3 = my_int2 = my_int1 = 7
my_int3 += 1
if my_int3 == my_int2 == my_int1:
    # side effects occurred (modifying one variable modified another)
    print("int is mutable")
else:
    # side effects did not occur (modifying one variable did not modify another)
    print("int is immutable")  # <== this is the result

my_list3 = my_list2 = my_list1 = [7, 8, 9]
my_list3.append(1)
if my_list3 == my_list2 == my_list1:
    # side effects occurred (modifying one variable modified another)
    print("list is mutable")   # <== this is the result
else:
    # side effects did not occur (modifying one variable did not modify another)
    print("list is immutable")
print()

# ==============================================================================
# - For **mutable** types, setting two variables to the same value gives each
#   variable a **unique underlying object** in memory, since they must have
#   separate memory to be independently mutated.
# - But for **immutable** types, setting two variables to the same value gives
#   each variable the **same underlying object,** since they cannot be mutated.
# ==============================================================================

print("MUTABLE TYPES")
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

print("IMMUTABLE TYPES")
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
#
# Try the test again, this time like this
print("integer types again")
my_int1 = 7
my_int2 = my_int1
my_int3 = my_int2
# Same as above: same underlying object, so each of these is True
print(my_int3 is my_int2)      # True
print(my_int2 is my_int1)      # True
print(my_int3 is my_int1)      # True
# Same as above: same value, so each of these is True
print(my_int3 == my_int2)      # True
print(my_int2 == my_int1)      # True
print(my_int3 == my_int1)      # True
print()


# To force a **mutable** type to be copied instead of passed by reference, you
# must call the `.copy()` method on it.

# Copy **by reference**, so all variables point to the same underlying object.
my_dict3 = my_dict2 = my_dict1 = {"key": "value"}
# Could also be written as:
my_dict1 = {"key": "value"}
my_dict2 = my_dict1
my_dict3 = my_dict2
# Therefore, each of these is True because the underlying object is the same
# blob of memory.
print(my_dict3 is my_dict2)    # True
print(my_dict2 is my_dict1)    # True
print(my_dict3 is my_dict1)    # True
# And each of these is True because all variables have the same value.
print(my_dict3 == my_dict2)    # True
print(my_dict2 == my_dict1)    # True
print(my_dict3 == my_dict1)    # True
print()

# Force-copy **by value**, so each variable has its own underlying object.
# The `.copy()` method makes an entirely new copy of the underlying object.
my_dict1 = {"key": "value"}
my_dict2 = my_dict1.copy()
my_dict3 = my_dict2.copy()
# Therefore, each of these is False because the underlying objects differ.
print(my_dict3 is my_dict2)    # False
print(my_dict2 is my_dict1)    # False
print(my_dict3 is my_dict1)    # False
# But, each of these is True because all variables have the same value.
print(my_dict3 == my_dict2)    # True
print(my_dict2 == my_dict1)    # True
print(my_dict3 == my_dict1)    # True
print()


# ==============================================================================
print("How to update immutable vs mutable variables in a function:\n")
# ==============================================================================

def modify_immutable_type(var_immutable):
    var_immutable += 1  # increment
    return var_immutable

my_int = 7
print(my_int)  # 7
# For immutable types, you must reassign the variable to the function's return
my_int = modify_immutable_type(my_int)
print(my_int)  # 8
print()


def modify_mutable_type(var_mutable):
    var_mutable.append(1)  # append to a list

my_list = [7, 8, 9]
print(my_list)  # [7, 8, 9]
# For mutable types, you do not need to reassign the variable to the function's
# return
modify_mutable_type(my_list)
print(my_list)  # [7, 8, 9, 1]
print()


def modify_immutable_type_hack(var_list):
    var_list[0] += 1  # increment

my_int = 10
my_int_list = [my_int]
print(my_int_list[0])  # 10
# Force an immutable type to act mutable by passing it inside a list, which is a
# mutable type, into a function. This way, the "side effect" of the change to
# the list being visible outside the function is still seen. This is because the
# list gets passed **by reference** instead of **by value.**
modify_immutable_type_hack(my_int_list)
print(my_int_list[0])  # 11
print(my_int)          # 10
print()



# pylint: disable-next=pointless-string-statement
"""
SAMPLE OUTPUT:

    eRCaGuy_hello_world$ python/mutable_vs_immutable_types.py
    var before modification: True
    var is a bool
    var after modification:  False

    var before modification: 1.0
    var is a float
    var after modification:  2.0

    var before modification: 7
    var is an int
    var after modification:  8

    var before modification: some words
    var is a str (string)
    var after modification:  some words; some more words

    var before modification: [7, 8, 9]
    var is a list
    var after modification:  [7, 8, 9, 1]

    var before modification: {'key1': 'value1', 'key2': 'value2'}
    var is a dict
    var after modification:  {'key1': 'value1', 'key2': 'value2', 'new_key': 'new_value'}

    var before modification: (7, 8, 9)
    var is a tuple
    var after modification:  (1, 2, 3)

    is_mutable(my_bool, True)                                    -->  immutable
    is_mutable(my_float, 1.0)                                    -->  immutable
    is_mutable(my_int, 7)                                        -->  immutable
    is_mutable(my_str, "some words")                             -->  immutable
    is_mutable(my_list, [7, 8, 9])                               -->  mutable
    is_mutable(my_dict, {"key1": "value1", "key2": "value2"})    -->  mutable
    is_mutable(my_tuple, (7, 8, 9))                              -->  immutable

    int is immutable
    list is mutable

    MUTABLE TYPES
    False
    False
    False
    True
    True
    True

    IMMUTABLE TYPES
    True
    True
    True
    True
    True
    True

    integer types again
    True
    True
    True
    True
    True
    True

    True
    True
    True
    True
    True
    True

    False
    False
    False
    True
    True
    True

    How to update immutable vs mutable variables in a function:

    7
    8

    [7, 8, 9]
    [7, 8, 9, 1]

    10
    11
    10

"""
