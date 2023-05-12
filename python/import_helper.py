#!/usr/bin/env python3

"""
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
11 May 2023

Come up with a "package import helper" designed to allow you to import nearby packages and modules
easier, in particular those which are in directories **up** from, or **up and over** from the script
being run, both of which are *not* normally supported by Python. This is somewhat related to my Bash
answer and style here:
  https://stackoverflow.com/a/60157372/4561887
- And it is related to the `sys.path.append()` part at the bottom of this answer here: Relative
  imports in Python 3 - https://stackoverflow.com/a/16985066/4561887

Status: wip

keywords: (keywords)

Check this script with `pylint` v2.0.0 or later. See "eRCaGuy_hello_world/python/README.md" for
installation instructions to install the latest version from GitHub.
For a list of all error codes, such as `C0301`, `C0116`, `W0105`, etc., see here:
https://pylint.pycqa.org/en/latest/messages/messages_list.html
```bash
pylint import_helper.py
```

Run command:
```bash
./import_helper.py
# OR
python3 import_helper.py
```

References:
1. *****+ See the links in my description above.
1. beyond top level package error in relative import - https://stackoverflow.com/q/30669474/4561887
1. Relative imports for the billionth time - https://stackoverflow.com/a/14132912/4561887

"""


# -------------------------- allow higher-up package imports START ---------------------------------
# Allow module importing in Python at higher-up directory levels, similar to what I can do in Bash.
# See my Bash answer here: https://stackoverflow.com/a/60157372/4561887
import os
import sys
FULL_PATH_TO_SCRIPT = os.path.abspath(__file__)
SCRIPT_DIRECTORY = os.path.dirname(FULL_PATH_TO_SCRIPT)
SCRIPT_FILENAME = os.path.basename(FULL_PATH_TO_SCRIPT)
# the number of levels deep from this file's directory up to the root dir
# containing the package; update this value appropriately
NUM_LEVELS_DEEP = 1
ROOT_DIR_CONTAINING_PACKAGE = SCRIPT_DIRECTORY
for i in range(NUM_LEVELS_DEEP):
    ROOT_DIR_CONTAINING_PACKAGE = os.path.dirname(ROOT_DIR_CONTAINING_PACKAGE)
sys.path.append(ROOT_DIR_CONTAINING_PACKAGE)
# -------------------------- allow higher-up package imports END -----------------------------------

def do_debug_prints():
    printf(f"__file__ = {__file__}")

    print(f"ROOT_DIR_CONTAINING_PACKAGE = {ROOT_DIR_CONTAINING_PACKAGE}") ######


def _test():
    """
    Run some basic demos/tests and print the results.
    """
    print("import_helper demo/tests:")


# Only run `main()` if this script is **run**, NOT imported
if __name__ == '__main__':
    _test()



# pylint: disable-next=pointless-string-statement
"""
SAMPLE OUTPUT:

    eRCaGuy_hello_world/python$ ./import_helper.py
    Hello world!

"""
