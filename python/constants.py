#!/usr/bin/env python3

"""
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
13 May 2023

Practice making this module with just a few constants in it.

Status: done and works!

keywords: (keywords)

Check this script with `pylint` v2.0.0 or later. See "eRCaGuy_hello_world/python/README.md" for
installation instructions to install the latest version from GitHub.
For a list of all error codes, such as `C0301`, `C0116`, `W0105`, etc., see here:
https://pylint.pycqa.org/en/latest/messages/messages_list.html
```bash
pylint constants.py
```

Run command:
```bash
./constants.py
# OR
python3 constants.py
```

References:
1.

"""


import textwrap

SOME_VALUE1 = 700
SOME_VALUE2 = 800
SOME_STRING1 = "hello world"

def main():
    """
    The main function of this program.
    """
    print(textwrap.dedent(f"""\
        SOME_VALUE1  = {SOME_VALUE1}
        SOME_VALUE2  = {SOME_VALUE2}
        SOME_STRING1 = {SOME_STRING1}\
    """))


# Only run `main()` if this script is **run**, NOT imported
if __name__ == '__main__':
    main()



# pylint: disable-next=pointless-string-statement
"""
SAMPLE OUTPUT:

    eRCaGuy_hello_world$ python/constants.py
    SOME_VALUE1  = 700
    SOME_VALUE2  = 800
    SOME_STRING1 = hello world

"""
