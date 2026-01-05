#!/usr/bin/env python3

"""
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
Jan. 2026

Practice using dataclasses as C-style structs in Python!
See my answer: https://stackoverflow.com/a/77161026/4561887

Status: Done and works!

keywords: (keywords)

Check this script with `pylint` v2.0.0 or later. See "eRCaGuy_hello_world/python/README.md" for
installation instructions to install the latest version from GitHub.
For a list of all error codes, such as `C0301`, `C0116`, `W0105`, etc., see here:
https://pylint.pycqa.org/en/latest/messages/messages_list.html
```bash
pylint dataclass_example.py
```

Run command:
```bash
./dataclass_example.py
# OR
python3 dataclass_example.py
```

References:
1. My answer: https://stackoverflow.com/a/77161026/4561887
1. Official Python documentation on dataclasses: https://docs.python.org/3/library/dataclasses.html
1. eRCaGuy_hello_world/python/struct_c_like.py

"""


from dataclasses import dataclass

@dataclass
class MyStruct:
    """
    A simple struct-like dataclass with some fields of various types.
    2 fields have default values.
    """
    name: str
    x: int
    y: int
    z: float = 0.0  # default value
    is_ready: bool = False  # default value

# Create an instance of MyStruct
my_data = MyStruct(name="My struct", x=123, y=456)
my_data.z = 789.001 # set z later if desired
my_data.x = 999     # modify x later if desired

my_data2 = MyStruct(
    name="Another struct",
    x=10,
    y=20,
    z=30.0,
    is_ready=True
)

print(my_data)
print(my_data2)

# ---------------------
# Illegal operations:
# ---------------------

# TypeError: MyStruct.__init__() missing 1 required positional argument: 'y'
# my_data = MyStruct(name="Some useful name of this data", x=123)

# ---------------------
# Adding new fields on the fly
# - kind of works, but is not recommended
# ---------------------

# Adding a new member `w` at run-time is allowed, but not recommended
my_data.w = 7
# will NOT print the newly-added `w` member; prints only:
# `MyStruct(name='My struct', x=123, y=456, z=789.001, is_ready=False)`
print(my_data)
# will print `7`
print(my_data.w)


# pylint: disable-next=pointless-string-statement
"""
SAMPLE OUTPUT:

MyStruct(name='My struct', x=999, y=456, z=789.001, is_ready=False)
MyStruct(name='Another struct', x=10, y=20, z=30.0, is_ready=True)
MyStruct(name='My struct', x=999, y=456, z=789.001, is_ready=False)
7

"""
