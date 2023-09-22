#!/usr/bin/env python3

"""
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
22 Sept. 2023

Make a super-simple C-like struct in Python.

Status: Done and works! See `class MyData` and `class AnyData` below.

keywords: (keywords)

Check this script with `pylint` v2.0.0 or later. See "eRCaGuy_hello_world/python/README.md" for
installation instructions to install the latest version from GitHub.
For a list of all error codes, such as `C0301`, `C0116`, `W0105`, etc., see here:
https://pylint.pycqa.org/en/latest/messages/messages_list.html
```bash
pylint struct_c_like.py
```

Run command:
```bash
./struct_c_like.py
# OR
python3 struct_c_like.py
```

References:
1. Myself.
1. GitHub CoPilot.
1. This question: C-like structures in Python: https://stackoverflow.com/q/35988/4561887
    1. My answer to it:

"""

import json  # for pretty-printing dicts

class MyData:
    """
    A simple C-like struct with initializer function.
    """
    def __init__(self, x, y, z):
        self.x = x
        self.y = y
        self.z = z

    def print(self):
        """
        Print the values of the struct.
        """
        print(f"x = {self.x}")
        print(f"y = {self.y}")
        print(f"z = {self.z}")
        print()


class AnyData:
    """
    A truly bare-bones struct that the user can put any members into they want.
    """
    pass

# Make a universal print function to print all user-added members of any class like this:
def print_any_class(class_instance):
    """
    Print all members of a class.
    """
    for key, value in class_instance.__dict__.items():
        print(f"{key}: {value}")
    print()


myData = MyData(1, 2, 3)
myData.y = 100
myData.print()


# Classes in Python can have any data arbitrarily added to them at run-time, so this works.
myData2 = AnyData()
myData2.name = "My Data"
myData2.x = 123
myData2.y = 456
myData2.z = 789
print(f"myData2.name = {myData2.name}")
print(f"myData2.x = {myData2.x}")
print(f"myData2.y = {myData2.y}")
print(f"myData2.z = {myData2.z}")
print()

# Data inside a class is accessible via the internal `__dict__` dictionary, which is a dictionary
# of all the class's members. So you can print all user-added members like this too:
print(f"{myData2.__dict__}\n")

# Pretty-print it in JSON format like this:
print(f"{json.dumps(myData2.__dict__, indent=4)}\n")

# Or in key: value format manually like this:
for key, value in myData2.__dict__.items():
    print(f"{key}: {value}")
print()

# Or by calling the universal print function I made above:
print_any_class(myData2)



# pylint: disable-next=pointless-string-statement
"""
SAMPLE OUTPUT:

    eRCaGuy_hello_world$ python/struct_c_like.py
    x = 1
    y = 100
    z = 3

    myData2.name = My Data
    myData2.x = 123
    myData2.y = 456
    myData2.z = 789

    {'name': 'My Data', 'x': 123, 'y': 456, 'z': 789}

    {
        "name": "My Data",
        "x": 123,
        "y": 456,
        "z": 789
    }

    name: My Data
    x: 123
    y: 456
    z: 789

    name: My Data
    x: 123
    y: 456
    z: 789

"""
