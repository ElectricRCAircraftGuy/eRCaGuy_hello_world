#!/usr/bin/env python3

"""
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

Status: wip

keywords: (keywords)

Check this script with `pylint` v2.0.0 or later. See "eRCaGuy_hello_world/python/README.md" for
installation instructions to install the latest version from GitHub.
For a list of all error codes, such as `C0301`, `C0116`, `W0105`, etc., see here:
https://pylint.pycqa.org/en/latest/messages/messages_list.html
```bash
pylint config1.py
```

Run command:
```bash
./config1.py
# OR
python3 config1.py
```

References:
1.

"""

# import sys
# import os
# SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
# print(f"SCRIPT_DIR = {SCRIPT_DIR}\n")
# print(f"sys.path = {sys.path}\n")
# sys.path.append(os.path.dirname(SCRIPT_DIR))
# print(f"sys.path = {sys.path}\n")

# # -------------------------- allow higher-up package imports START ---------------------------------
# # Allow module importing in Python similar to what I can do in Bash. See my Bash
# # answer here: https://stackoverflow.com/a/60157372/4561887
# import os
# import sys
# FULL_PATH_TO_SCRIPT = os.path.abspath(__file__)
# SCRIPT_DIRECTORY = os.path.dirname(FULL_PATH_TO_SCRIPT)
# SCRIPT_FILENAME = os.path.basename(FULL_PATH_TO_SCRIPT)
# # the number of levels deep from this file's directory up to the root dir
# # containing the package; update this value appropriately
# NUM_LEVELS_DEEP = 1
# ROOT_DIR_CONTAINING_PACKAGE = SCRIPT_DIRECTORY
# for i in range(NUM_LEVELS_DEEP):
#     ROOT_DIR_CONTAINING_PACKAGE = os.path.dirname(ROOT_DIR_CONTAINING_PACKAGE)
# sys.path.append(ROOT_DIR_CONTAINING_PACKAGE)
# # -------------------------- allow higher-up package imports END -----------------------------------
# print(f"ROOT_DIR_CONTAINING_PACKAGE = {ROOT_DIR_CONTAINING_PACKAGE}") # debugging

# import sys
# print(f"sys.path = {sys.path}\n")
# sys.path.append("/home/gabriel/GS/dev/eRCaGuy_hello_world/python/package_import_down")
# sys.path.append("package_import_down")
# print(f"sys.path = {sys.path}\n")

# from .mypackage.mysubpackage import config2
import mypackage.mysubpackage.config2

# exit()

import textwrap

# Constants to be used by the whole package, from within ANY module (file) within the package!
MY_CONSTANT1 = 11
MY_CONSTANT2 = 22
MY_CONSTANT3 = 33

def _test():
    print(textwrap.dedent(f"""\
        MY_CONSTANT1 = {MY_CONSTANT1}
        MY_CONSTANT2 = {MY_CONSTANT2}
        MY_CONSTANT3 = {MY_CONSTANT3}\
    """))
    print()

    print(textwrap.dedent(f"""\
        mypackage.mysubpackage.config2.MY_CONSTANT1 = {mypackage.mysubpackage.config2.MY_CONSTANT1}
        mypackage.mysubpackage.config2.MY_CONSTANT2 = {mypackage.mysubpackage.config2.MY_CONSTANT2}
        mypackage.mysubpackage.config2.MY_CONSTANT3 = {mypackage.mysubpackage.config2.MY_CONSTANT3}\
    """))
    print()

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
