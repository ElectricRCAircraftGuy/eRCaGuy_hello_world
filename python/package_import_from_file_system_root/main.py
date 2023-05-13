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
- Note: this won't run for you unless you have the exact same filesystem layout as I do. Update the
  import path in step 3 below for your filesystem.

keywords: (keywords)

Check this script with `pylint` v2.0.0 or later. See "eRCaGuy_hello_world/python/README.md" for
installation instructions to install the latest version from GitHub.
For a list of all error codes, such as `C0301`, `C0116`, `W0105`, etc., see here:
https://pylint.pycqa.org/en/latest/messages/messages_list.html
```bash
pylint main.py
```

Run command:
```bash
./main.py
# OR
python3 main.py
```

References:
1. eRCaGuy_hello_world/python/import_helper.py

"""

import textwrap

# 1. Add the filesystem root to the `sys.path` list variable
import sys
filesystem_root = "/"  # filesystem root
sys.path.insert(0, filesystem_root)

# 2. Print the `sys.path` now so we can see that `'/'` has been added
# pretty print; see: https://stackoverflow.com/a/1523664/4561887
from pprint import pprint
print("sys.path = ")
pprint(sys.path)
print()

# 3. Now try to import relative to that location.
# - For an alternative technique, see:
#   "eRCaGuy_hello_world/python/package_import_from_file_system_root/main2.py"
# - UPDATE THIS PATH BELOW FOR YOUR SPECIFIC FILESYSTEM PATH!
import home.gabriel.GS.dev.eRCaGuy_hello_world.python.constants as constants

def main():
    """
    The main function of this program.
    """
    print("Test importing from the filesystem root.")

    # 3. Now use the contants we imported.
    print(textwrap.dedent(f"""\
        constants.SOME_VALUE1  = {constants.SOME_VALUE1}
        constants.SOME_VALUE2  = {constants.SOME_VALUE2}
        constants.SOME_STRING1 = {constants.SOME_STRING1}\
    """))


# Only run `main()` if this script is **run**, NOT imported
if __name__ == '__main__':
    main()



# pylint: disable-next=pointless-string-statement
"""
SAMPLE OUTPUT:

    eRCaGuy_hello_world$ python/package_import_from_file_system_root/main.py
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
