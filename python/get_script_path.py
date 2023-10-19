#!/usr/bin/env python3

"""
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
Sept. 2023

Get the path to the current script, in Python.

Status: Done and works!

keywords: (keywords)

Check this script with `pylint` v2.0.0 or later. See "eRCaGuy_hello_world/python/README.md" for
installation instructions to install the latest version from GitHub.
For a list of all error codes, such as `C0301`, `C0116`, `W0105`, etc., see here:
https://pylint.pycqa.org/en/latest/messages/messages_list.html
```bash
pylint get_script_path.py
```

Run command:
```bash
./get_script_path.py
# OR
python3 get_script_path.py
```

References:
1. My previous research. Ex:
    1. "eRCaGuy_hello_world/python/import_helper.py"
    1. ***** "eRCaGuy_hello_world/python/pandas_dataframe_iteration_vs_vectorization_vs_list_comprehension_speed_tests.py"
1. My answer to this in Bash: https://stackoverflow.com/a/60157372/4561887
1. *****+ GitHub CoPilot (was very helpful)
1. *****+++ My answer, with this code:
   https://stackoverflow.com/a/74800814/4561887
1.

"""


import os
import sys


FULL_PATH_TO_SCRIPT = os.path.abspath(__file__)
SCRIPT_DIRECTORY = str(os.path.dirname(FULL_PATH_TO_SCRIPT))
SCRIPT_PARENT_DIRECTORY = str(os.path.dirname(SCRIPT_DIRECTORY))
# this also works, but its output will have the two dots (`/..`) in it.
SCRIPT_PARENT_DIRECTORY2 = f"{SCRIPT_DIRECTORY}/.."
FILENAME = str(os.path.basename(FULL_PATH_TO_SCRIPT))
FILENAME_NO_EXTENSION = os.path.splitext(FILENAME)[0]
FILENAME_EXTENSION = os.path.splitext(FILENAME)[1]

# Other useful paths:

# home directory of the current, running user
HOME_DIR_USER = os.path.expanduser("~")
# Obtain the home dir of the user in whose home directory this script resides,
# which may *not* be the home dir of the current user! Ex: run this script
# as root, via `sudo`, and you'll see that `HOME_DIR_USER` != `HOME_DIR_SCRIPT`.
script_path_list = os.path.normpath(FULL_PATH_TO_SCRIPT).split(os.sep)
HOME_DIR_SCRIPT = os.path.join("/", script_path_list[1], script_path_list[2])

# Bonus: add the parent directory to the start of the system PATH variable so
# that you can import modules directly in that directory above this script!
sys.path.insert(0, SCRIPT_PARENT_DIRECTORY)
# Now, assuming there is a `config.py`` file in the `SCRIPT_PARENT_DIRECTORY`,
# you can import it directly, like this:
#
# import config.py
#

# Print results
print(f"__file__:                  {__file__}")
print(f"FULL_PATH_TO_SCRIPT:       {FULL_PATH_TO_SCRIPT}")
print(f"SCRIPT_DIRECTORY:          {SCRIPT_DIRECTORY}")
print(f"SCRIPT_PARENT_DIRECTORY:   {SCRIPT_PARENT_DIRECTORY}")
print(f"SCRIPT_PARENT_DIRECTORY2:  {SCRIPT_PARENT_DIRECTORY2}")
print(f"FILENAME:                  {FILENAME}")
print(f"FILENAME_NO_EXTENSION:     {FILENAME_NO_EXTENSION}")
print(f"FILENAME_EXTENSION:        {FILENAME_EXTENSION}")
print("---")
print(f"HOME_DIR_USER:             {HOME_DIR_USER}")
print(f"script_path_list:          {script_path_list}")
print(f"HOME_DIR_SCRIPT:           {HOME_DIR_SCRIPT}")


# pylint: disable-next=pointless-string-statement
"""
SAMPLE OUTPUT:

    eRCaGuy_hello_world$ python/get_script_path.py
    __file__:                  python/get_script_path.py
    FULL_PATH_TO_SCRIPT:       /home/gabriel/GS/dev/eRCaGuy_hello_world/python/get_script_path.py
    SCRIPT_DIRECTORY:          /home/gabriel/GS/dev/eRCaGuy_hello_world/python
    SCRIPT_PARENT_DIRECTORY:   /home/gabriel/GS/dev/eRCaGuy_hello_world
    SCRIPT_PARENT_DIRECTORY2:  /home/gabriel/GS/dev/eRCaGuy_hello_world/python/..
    FILENAME:                  get_script_path.py
    FILENAME_NO_EXTENSION:     get_script_path
    FILENAME_EXTENSION:        .py
    ---
    HOME_DIR_USER:             /home/gabriel
    script_path_list:          ['', 'home', 'gabriel', 'GS', 'dev', 'eRCaGuy_hello_world', 'python', 'get_script_path.py']
    HOME_DIR_SCRIPT:           /home/gabriel

When run as root:

    eRCaGuy_hello_world$ sudo python/get_script_path.py
    [sudo] password for gabriel:
    __file__:                  python/get_script_path.py
    FULL_PATH_TO_SCRIPT:       /home/gabriel/GS/dev/eRCaGuy_hello_world/python/get_script_path.py
    SCRIPT_DIRECTORY:          /home/gabriel/GS/dev/eRCaGuy_hello_world/python
    SCRIPT_PARENT_DIRECTORY:   /home/gabriel/GS/dev/eRCaGuy_hello_world
    SCRIPT_PARENT_DIRECTORY2:  /home/gabriel/GS/dev/eRCaGuy_hello_world/python/..
    FILENAME:                  get_script_path.py
    FILENAME_NO_EXTENSION:     get_script_path
    FILENAME_EXTENSION:        .py
    ---
    HOME_DIR_USER:             /root
    script_path_list:          ['', 'home', 'gabriel', 'GS', 'dev', 'eRCaGuy_hello_world', 'python', 'get_script_path.py']
    HOME_DIR_SCRIPT:           /home/gabriel

"""
