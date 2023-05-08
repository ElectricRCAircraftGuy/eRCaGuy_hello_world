"""
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

By Gabriel Staples
7 May 2023

See the combination of these answers:
1. https://stackoverflow.com/a/16985066/4561887 - where the code below came from
1. https://stackoverflow.com/a/49375740/4561887 - *why* I am putting it in this file
1. https://stackoverflow.com/a/60157372/4561887 - my Bash answer; provides a general format and
   style

To run and test this file manually:
```bash
python3 path/to/__init__.py
```
"""

import os
import sys

FULL_PATH_TO_THIS_FILE = os.path.abspath(__file__)
THIS_FILE_DIR = os.path.dirname(FULL_PATH_TO_THIS_FILE)

# the number of levels deep from this file's directory up to the package root
# - update this for this particular "__init__.py" file
NUM_LEVELS_DEEP = 0 #########

PACKAGE_ROOT_DIR = THIS_FILE_DIR
for i in range(NUM_LEVELS_DEEP):
    PACKAGE_ROOT_DIR = os.path.dirname(PACKAGE_ROOT_DIR)

print(f"PACKAGE_ROOT_DIR = {PACKAGE_ROOT_DIR}")  # debugging

sys.path.append(PACKAGE_ROOT_DIR)

