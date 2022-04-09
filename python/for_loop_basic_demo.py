#!/usr/bin/env python3

"""
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
7 March 2022

Demonstrate a basic range-based for loop in Python, as well as the 3 main ways to do formatted
printing, in order of newest first to oldest last:
1. [newest] formatted string literals (f-strings)
2. `str.format()` method
3. [oldest] C-like "printf"-style `%` operator

Status: done!

keywords: for loop; print strings; formatted strings; format strings

Check this script with `pylint` v2.0.0 or later. See "eRCaGuy_hello_world/python/README.md" for
installation instructions to install the latest version from GitHub.
For a list of all error codes, such as `C0301`, `C0116`, `W0105`, etc., see here:
https://pylint.pycqa.org/en/latest/messages/messages_list.html
```bash
pylint for_loop_basic_demo.py
```

Run command:
```bash
./for_loop_basic_demo.py
# OR
python3 for_loop_basic_demo.py
```

References:
1. [MY ANSWER with this code] How to type "line1", "line2", "line3".... using a for loop in python:
   https://stackoverflow.com/a/71376781/4561887
1. f-strings / "format strings": https://realpython.com/python-f-strings/

"""


END_NUM = 7
for i in range(1, END_NUM + 1):
    # 3 techniques to print:

    # 1. newest technique: formatted string literals; AKA: "f-strings" or "format strings"; see:
    # https://realpython.com/python-f-strings/
    print(f"line{i}")

    # 2. newer technique: `str.format()` method
    # pylint: disable-next=consider-using-f-string
    print("line{}".format(i))

    # 3. oldest, C-like "printf"-style `%` operator print method
    # (sometimes is still the best method, however, as it provides lots of versatility and control!)
    # pylint: disable-next=consider-using-f-string
    print("line%i" % i)

    print() # newline



# pylint: disable-next=pointless-string-statement
"""
SAMPLE OUTPUT:

    eRCaGuy_hello_world/python$ ./for_loop_basic_demo.py
    line1
    line1
    line1

    line2
    line2
    line2

    line3
    line3
    line3

    line4
    line4
    line4

    line5
    line5
    line5

    line6
    line6
    line6

    line7
    line7
    line7



"""
