#!/usr/bin/env python3

"""
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
8 May 2023

Practice importing files/modules **down** from lower directories!

Status: wip

keywords: (keywords)

Check this script with `pylint` v2.0.0 or later. See "eRCaGuy_hello_world/python/README.md" for
installation instructions to install the latest version from GitHub.
For a list of all error codes, such as `C0301`, `C0116`, `W0105`, etc., see here:
https://pylint.pycqa.org/en/latest/messages/messages_list.html
```bash
pylint my_script.py
```

Run command:
```bash
./my_script.py
# OR
python3 my_script.py
```

References:
1.

"""

# My custom modules
import mypackage.config1
import mypackage.mysubpackage.config2

from mypackage.config1 import MY_CONSTANT1
from mypackage.mysubpackage.config2 import MY_CONSTANT2

# Built-in modules
import textwrap


def main():
    """
    The main function of this program.
    """
    print("Hello world!")
    print()

    print(textwrap.dedent(f"""\
        mypackage.config1.MY_CONSTANT1 = {mypackage.config1.MY_CONSTANT1}
        mypackage.config1.MY_CONSTANT2 = {mypackage.config1.MY_CONSTANT2}
        mypackage.config1.MY_CONSTANT3 = {mypackage.config1.MY_CONSTANT3}\
    """))
    print()

    print(textwrap.dedent(f"""\
        mypackage.config1.mypackage.mysubpackage.config2.MY_CONSTANT1 = {mypackage.config1.mypackage.mysubpackage.config2.MY_CONSTANT1}
        mypackage.config1.mypackage.mysubpackage.config2.MY_CONSTANT2 = {mypackage.config1.mypackage.mysubpackage.config2.MY_CONSTANT2}
        mypackage.config1.mypackage.mysubpackage.config2.MY_CONSTANT3 = {mypackage.config1.mypackage.mysubpackage.config2.MY_CONSTANT3}\
    """))
    print()

    print(textwrap.dedent(f"""\
        mypackage.mysubpackage.config2.MY_CONSTANT1 = {mypackage.mysubpackage.config2.MY_CONSTANT1}
        mypackage.mysubpackage.config2.MY_CONSTANT2 = {mypackage.mysubpackage.config2.MY_CONSTANT2}
        mypackage.mysubpackage.config2.MY_CONSTANT3 = {mypackage.mysubpackage.config2.MY_CONSTANT3}\
    """))
    print()

    print(f"MY_CONSTANT1 = {MY_CONSTANT1}")
    print(f"MY_CONSTANT2 = {MY_CONSTANT2}")


# Only run `main()` if this script is **run**, NOT imported
if __name__ == '__main__':
    main()

# pylint: disable-next=pointless-string-statement
"""
SAMPLE OUTPUT:

    eRCaGuy_hello_world/python$ package_import_down/my_script.py
    Hello world!

    mypackage.config1.MY_CONSTANT1 = 11
    mypackage.config1.MY_CONSTANT2 = 22
    mypackage.config1.MY_CONSTANT3 = 33

    mypackage.mysubpackage.config2.MY_CONSTANT1 = 44
    mypackage.mysubpackage.config2.MY_CONSTANT2 = 55
    mypackage.mysubpackage.config2.MY_CONSTANT3 = 66

    MY_CONSTANT1 = 11
    MY_CONSTANT2 = 55


"""

