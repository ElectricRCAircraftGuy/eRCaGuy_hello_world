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


import os
import pathlib
import sys

# pretty print; see: https://stackoverflow.com/a/1523664/4561887
from pprint import pprint


DEFAULT_SYS_PATH = sys.path
HOME = str(pathlib.Path.home())


def add_path_to_dir(path_to_dir):
    """
    Add a path string to the `sys.path` list (which also contains all paths from within the
    `PYTHONPATH` environment variable) so that one can import packages and modules relative to this
    path.

    See:
    1. https://docs.python.org/3/using/cmdline.html#envvar-PYTHONPATH
    1. https://docs.python.org/3/library/sys.html#sys.path
    1. https://stackoverflow.com/a/3402176/4561887

    Parameters:
        path_to_dir (string): the path to the directory to add

    Returns:
        NA
    """
    full_dir_path = os.path.abspath(path_to_dir)
    sys.path.insert(0, full_dir_path)


def add_higher_up_path(starting_path_to_file, num_levels_up=1):
    """
    Add the directory `num_levels_up` from `starting_path` to the `sys.path` list so that one can
    import packages and modules relative to that higher-up path.

    Parameters:
        starting_path_to_file (string): the path to the file from which to start the upwards path
            search; typically you will want to pass in `__file__`
        num_levels_up (int): the number of directories to go up, starting from the directory in
            which the file represented by `starting_path_to_file` resides.

    Returns:
        NA
    """
    full_file_path = os.path.abspath(starting_path_to_file)
    starting_dir = os.path.dirname(full_file_path)

    upper_dir = starting_dir
    for i in range(num_levels_up):
        upper_dir = os.path.dirname(upper_dir)

    sys.path.insert(0, upper_dir)


def _test():
    """
    Run some basic demos/tests and print the results.
    """
    print("import_helper demo/tests:\n")

    print("Before: sys.path = ")
    pprint(sys.path)
    print()

    # ---------------------------------
    # Test `add_path_to_dir()`
    # ---------------------------------

    dir_to_add = f"{HOME}/whatever12345/"
    print(f"Adding {dir_to_add}")
    add_path_to_dir(dir_to_add)
    print("After: sys.path = ")
    pprint(sys.path)
    print()
    assert sys.path[0] == dir_to_add[:-1]  # `-1` since the trailing `/` gets stripped off

    # ---------------------------------
    # Test `add_higher_up_path()`
    # ---------------------------------

    # file_path = __file__  # us this instead for personal, manual checking
    file_path = f"{HOME}/whatever12345/dir1/dir2/dir3/filename"

    print(f"file_path = {file_path}")
    print(f"os.path.abspath(file_path) = {os.path.abspath(file_path)}\n")

    add_higher_up_path(file_path)
    print("with 1 dir up: sys.path = ")
    pprint(sys.path)
    print()
    assert sys.path[0] == f"{HOME}/whatever12345/dir1/dir2"

    # same thing as just above
    add_higher_up_path(file_path, num_levels_up=1)
    print("with 1 dir up: sys.path = ")
    pprint(sys.path)
    print()
    assert sys.path[0] == f"{HOME}/whatever12345/dir1/dir2"

    add_higher_up_path(file_path, 2)
    print("with 2 dirs up: sys.path = ")
    pprint(sys.path)
    print()
    assert sys.path[0] == f"{HOME}/whatever12345/dir1"

    add_higher_up_path(file_path, 3)
    print("with 3 dirs up: sys.path = ")
    pprint(sys.path)
    print()
    assert sys.path[0] == f"{HOME}/whatever12345"

    add_higher_up_path(file_path, 4)
    print("with 4 dirs up: sys.path = ")
    pprint(sys.path)
    print()
    assert sys.path[0] == f"{HOME}"


# Only run `main()` if this script is **run**, NOT imported
if __name__ == '__main__':
    _test()



# pylint: disable-next=pointless-string-statement
"""
SAMPLE OUTPUT:

    eRCaGuy_hello_world$ python/import_helper.py
    import_helper demo/tests:

    Before: sys.path =
    ['/home/gabriel/GS/dev/eRCaGuy_hello_world/python',
    '/usr/lib/python38.zip',
    '/usr/lib/python3.8',
    '/usr/lib/python3.8/lib-dynload',
    '/home/gabriel/.local/lib/python3.8/site-packages',
    '/usr/local/lib/python3.8/dist-packages',
    '/usr/lib/python3/dist-packages',
    '/usr/lib/python3.8/dist-packages']

    Adding /home/gabriel/whatever12345/
    After: sys.path =
    ['/home/gabriel/whatever12345',
    '/home/gabriel/GS/dev/eRCaGuy_hello_world/python',
    '/usr/lib/python38.zip',
    '/usr/lib/python3.8',
    '/usr/lib/python3.8/lib-dynload',
    '/home/gabriel/.local/lib/python3.8/site-packages',
    '/usr/local/lib/python3.8/dist-packages',
    '/usr/lib/python3/dist-packages',
    '/usr/lib/python3.8/dist-packages']

    file_path = /home/gabriel/whatever12345/dir1/dir2/dir3/filename
    os.path.abspath(file_path) = /home/gabriel/whatever12345/dir1/dir2/dir3/filename

    with 1 dir up: sys.path =
    ['/home/gabriel/whatever12345/dir1/dir2',
    '/home/gabriel/whatever12345',
    '/home/gabriel/GS/dev/eRCaGuy_hello_world/python',
    '/usr/lib/python38.zip',
    '/usr/lib/python3.8',
    '/usr/lib/python3.8/lib-dynload',
    '/home/gabriel/.local/lib/python3.8/site-packages',
    '/usr/local/lib/python3.8/dist-packages',
    '/usr/lib/python3/dist-packages',
    '/usr/lib/python3.8/dist-packages']

    with 2 dirs up: sys.path =
    ['/home/gabriel/whatever12345/dir1',
    '/home/gabriel/whatever12345/dir1/dir2',
    '/home/gabriel/whatever12345',
    '/home/gabriel/GS/dev/eRCaGuy_hello_world/python',
    '/usr/lib/python38.zip',
    '/usr/lib/python3.8',
    '/usr/lib/python3.8/lib-dynload',
    '/home/gabriel/.local/lib/python3.8/site-packages',
    '/usr/local/lib/python3.8/dist-packages',
    '/usr/lib/python3/dist-packages',
    '/usr/lib/python3.8/dist-packages']

    with 3 dirs up: sys.path =
    ['/home/gabriel/whatever12345',
    '/home/gabriel/whatever12345/dir1',
    '/home/gabriel/whatever12345/dir1/dir2',
    '/home/gabriel/whatever12345',
    '/home/gabriel/GS/dev/eRCaGuy_hello_world/python',
    '/usr/lib/python38.zip',
    '/usr/lib/python3.8',
    '/usr/lib/python3.8/lib-dynload',
    '/home/gabriel/.local/lib/python3.8/site-packages',
    '/usr/local/lib/python3.8/dist-packages',
    '/usr/lib/python3/dist-packages',
    '/usr/lib/python3.8/dist-packages']

    with 4 dirs up: sys.path =
    ['/home/gabriel',
    '/home/gabriel/whatever12345',
    '/home/gabriel/whatever12345/dir1',
    '/home/gabriel/whatever12345/dir1/dir2',
    '/home/gabriel/whatever12345',
    '/home/gabriel/GS/dev/eRCaGuy_hello_world/python',
    '/usr/lib/python38.zip',
    '/usr/lib/python3.8',
    '/usr/lib/python3.8/lib-dynload',
    '/home/gabriel/.local/lib/python3.8/site-packages',
    '/usr/local/lib/python3.8/dist-packages',
    '/usr/lib/python3/dist-packages',
    '/usr/lib/python3.8/dist-packages']

"""
