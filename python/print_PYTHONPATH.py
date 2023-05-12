#!/usr/bin/env python3

"""
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
11 May 2023

Print the environment variable `PYTHONPATH`, and the `sys.path` list, to see how they differ.

Status: done and works!

keywords: read or print system environment variables

Check this script with `pylint` v2.0.0 or later. See "eRCaGuy_hello_world/python/README.md" for
installation instructions to install the latest version from GitHub.
For a list of all error codes, such as `C0301`, `C0116`, `W0105`, etc., see here:
https://pylint.pycqa.org/en/latest/messages/messages_list.html
```bash
pylint print_PYTHONPATH.py
```

Run command:
```bash
./print_PYTHONPATH.py
# OR
python3 print_PYTHONPATH.py

# to set the PYTHONPATH environment variable at the same time, do this:
PYTHONPATH="$HOME/my/new/path:$PYTHONPATH" ./print_PYTHONPATH.py
```

References:
1. This answer, and my comments underneath it: Permanently add a directory to PYTHONPATH? -
https://stackoverflow.com/a/3402176/4561887
1. This answer, and the usage of `sys.path.append()` within it:
https://stackoverflow.com/a/16985066/4561887
1. ***** [official documentation] https://docs.python.org/3/using/cmdline.html#envvar-PYTHONPATH
1. ***** [official documentation] https://docs.python.org/3/library/sys.html#sys.path
1. How can I access environment variables in Python? - https://stackoverflow.com/a/11447648/4561887

"""

import os
import sys

# pretty print; see: https://stackoverflow.com/a/1523664/4561887
from pprint import pprint


def main():
    """
    The main function of this program.
    """

    # Read the `PYTHONPATH` system environment variable. Note: to see if this variable exists, run
    # this in your terminal:
    #
    # ```bash
    # env | grep PYTHONPATH
    # ```
    #
    # See: https://stackoverflow.com/a/11447648/4561887
    PYTHONPATH = os.environ.get("PYTHONPATH", "")
    print(f"PYTHONPATH = {PYTHONPATH}\n")

    print("sys.path = ")
    pprint(sys.path)


# Only run `main()` if this script is **run**, NOT imported
if __name__ == '__main__':
    main()



# pylint: disable-next=pointless-string-statement
"""
SAMPLE OUTPUT:

Run 1:

    eRCaGuy_hello_world/python$ ./print_PYTHONPATH.py
    PYTHONPATH =

    sys.path =
    ['/home/gabriel/GS/dev/eRCaGuy_hello_world/python',
    '/usr/lib/python38.zip',
    '/usr/lib/python3.8',
    '/usr/lib/python3.8/lib-dynload',
    '/home/gabriel/.local/lib/python3.8/site-packages',
    '/usr/local/lib/python3.8/dist-packages',
    '/usr/lib/python3/dist-packages',
    '/usr/lib/python3.8/dist-packages']

Run 2:

    eRCaGuy_hello_world$ python/print_PYTHONPATH.py
    PYTHONPATH =

    sys.path =
    ['/home/gabriel/GS/dev/eRCaGuy_hello_world/python',
    '/usr/lib/python38.zip',
    '/usr/lib/python3.8',
    '/usr/lib/python3.8/lib-dynload',
    '/home/gabriel/.local/lib/python3.8/site-packages',
    '/usr/local/lib/python3.8/dist-packages',
    '/usr/lib/python3/dist-packages',
    '/usr/lib/python3.8/dist-packages']

Run 3 [manually setting `PYTHONPATH` in the call]:

    eRCaGuy_hello_world/python$ PYTHONPATH="$HOME/my/new/path:$PYTHONPATH" ./print_PYTHONPATH.py
    PYTHONPATH = /home/gabriel/my/new/path:

    sys.path =
    ['/home/gabriel/GS/dev/eRCaGuy_hello_world/python',
    '/home/gabriel/my/new/path',
    '/home/gabriel/GS/dev/eRCaGuy_hello_world/python',
    '/usr/lib/python38.zip',
    '/usr/lib/python3.8',
    '/usr/lib/python3.8/lib-dynload',
    '/home/gabriel/.local/lib/python3.8/site-packages',
    '/usr/local/lib/python3.8/dist-packages',
    '/usr/lib/python3/dist-packages',
    '/usr/lib/python3.8/dist-packages']


"""
