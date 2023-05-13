#!/usr/bin/env python3

"""
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
13 May 2023

Try to import a higher up Python file, or an "up and over" (higher up and over)
Python file, via the filesystem root, as though all folders from the root down
to it were part of a Python package. This might sound kind of nutty, but I
think I can make it work!

Status: done and works!

keywords: (keywords)

Check this script with `pylint` v2.0.0 or later. See "eRCaGuy_hello_world/python/README.md" for
installation instructions to install the latest version from GitHub.
For a list of all error codes, such as `C0301`, `C0116`, `W0105`, etc., see here:
https://pylint.pycqa.org/en/latest/messages/messages_list.html
```bash
pylint main2_relative_path_import.py
```

Run command:
```bash
./main2_relative_path_import.py
# OR
python3 main2_relative_path_import.py
```

References:
1. eRCaGuy_hello_world/python/import_helper.py

"""

import textwrap
from pprint import pprint

# 1. For **relative path imports**, find the path to the dir containing this script, then go up the
#    correct number of directories to where you need to go!
# 1. Then add _that_ dir to the `sys.path` list.
import os
import sys
FULL_PATH_TO_SCRIPT = os.path.abspath(__file__)
SCRIPT_DIRECTORY = str(os.path.dirname(FULL_PATH_TO_SCRIPT))
sys.path.insert(0, f"{SCRIPT_DIRECTORY}/..")  # up one dir

# 2. Print the `sys.path` now so we can see that `'/'` has been added
# pretty print; see: https://stackoverflow.com/a/1523664/4561887
print("sys.path = ")
pprint(sys.path)
print()

# 3. Now try to import relative to that location.
# - For an alternative technique, see:
#   "eRCaGuy_hello_world/python/package_import_from_file_system_root/main1_absolute_path_import.py"
import constants

# 4. Let's add one more, for fun. We'll import the same constants in a slightly different way still!
sys.path.insert(0, f"{SCRIPT_DIRECTORY}/../../..")  # up three dirs
import eRCaGuy_hello_world.python.constants

# print the `sys.path` list again to see this new addition
print("sys.path = ")
pprint(sys.path)
print()

def main():
    """
    The main function of this program.
    """
    print("Test importing from the filesystem root.\n")

    # 3. Now use the contants we imported.
    print(textwrap.dedent(f"""\
        constants.SOME_VALUE1  = {constants.SOME_VALUE1}
        constants.SOME_VALUE2  = {constants.SOME_VALUE2}
        constants.SOME_STRING1 = {constants.SOME_STRING1}
    """))

    print(textwrap.dedent(f"""\
        eRCaGuy_hello_world.python.constants.SOME_VALUE1  = {eRCaGuy_hello_world.python.constants.SOME_VALUE1}
        eRCaGuy_hello_world.python.constants.SOME_VALUE2  = {eRCaGuy_hello_world.python.constants.SOME_VALUE2}
        eRCaGuy_hello_world.python.constants.SOME_STRING1 = {eRCaGuy_hello_world.python.constants.SOME_STRING1}
    """))

    # Let's check one more thing just for fun. Apparently, importing from the same module in two
    # different ways results in two, unique objects. So, what we write to `constants.SOME_VALUE1`
    # does *not* affect `eRCaGuy_hello_world.python.constants.SOME_VALUE1`. (Also, "constants" in
    # Python aren't really constant).
    print("Calling `constants.SOME_VALUE1 = 999`")
    constants.SOME_VALUE1 = 999
    print("Done")
    print(f"constants.SOME_VALUE1 = {constants.SOME_VALUE1}")
    print(f"eRCaGuy_hello_world.python.constants.SOME_VALUE1 = {eRCaGuy_hello_world.python.constants.SOME_VALUE1}")


# Only run `main()` if this script is **run**, NOT imported
if __name__ == '__main__':
    main()



# pylint: disable-next=pointless-string-statement
"""
SAMPLE OUTPUT:

    eRCaGuy_hello_world$ python/package_import_from_file_system_root/main2_relative_path_import.py
    sys.path =
    ['/',
    '/home/gabriel/GS/dev/eRCaGuy_hello_world/python/package_import_from_file_system_root',
    '/home/gabriel/GS/dev/eRCaGuy_hello_world/python/libraries',
    '/home/gabriel/GS/dev/eRCaGuy_hello_world',
    '/usr/lib/python38.zip',
    '/usr/lib/python3.8',
    '/usr/lib/python3.8/lib-dynload',
    '/home/gabriel/.local/lib/python3.8/site-packages',
    '/usr/local/lib/python3.8/dist-packages',
    '/usr/lib/python3/dist-packages',
    '/usr/lib/python3.8/dist-packages']

    Test importing from the filesystem root.
    constants.SOME_VALUE1  = 700
    constants.SOME_VALUE2  = 800
    constants.SOME_STRING1 = hello world


"""
