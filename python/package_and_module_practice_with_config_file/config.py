#!/usr/bin/env python3

"""
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

By Gabriel Staples
7 May 2023

Practice setting constants and configuration data in a "config.py" file at the package root, where
this information might need to be imported by *any* module/file within this whole package!
It turns out this is actually quite a non-trivial, and tricky, thing to do!

Status: wip

keywords: (keywords)

Check this script with `pylint` v2.0.0 or later. See "eRCaGuy_hello_world/python/README.md" for
installation instructions to install the latest version from GitHub.
For a list of all error codes, such as `C0301`, `C0116`, `W0105`, etc., see here:
https://pylint.pycqa.org/en/latest/messages/messages_list.html
```bash
pylint hello_world.py
```

Run command:
```bash
./hello_world.py
# OR
python3 hello_world.py
```

References:
1. These links do NOT solve this problem--my code here does. Rather, they just provide some *hints*
   to help me!:
    1. https://stackoverflow.com/a/16985066/4561887
    1. https://docs.python.org/3/reference/import.html#namespace-packages

"""

import textwrap

# Constants to be used by the whole package, from within ANY module (file) within the package!
MY_CONSTANT1 = 7
MY_CONSTANT2 = 8
MY_CONSTANT3 = 9

def _test():
    print(textwrap.dedent(f"""\
        MY_CONSTANT1 = {MY_CONSTANT1}
        MY_CONSTANT2 = {MY_CONSTANT2}
        MY_CONSTANT3 = {MY_CONSTANT3}\
    """))

if __name__ == '__main__':
    _test()


# pylint: disable-next=pointless-string-statement
"""
SAMPLE OUTPUT:

    eRCaGuy_hello_world/python/package_and_module_practice_with_config_file$ ./config.py
    MY_CONSTANT1 = 7
    MY_CONSTANT2 = 8
    MY_CONSTANT3 = 9


"""
