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
pylint config2.py
```

Run command:
```bash
./config2.py
# OR
python3 config2.py
```

References:
1.

"""

import textwrap

# Constants to be used by the whole package, from within ANY module (file) within the package!
MY_CONSTANT1 = 44
MY_CONSTANT2 = 55
MY_CONSTANT3 = 66

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

    eRCaGuy_config2/python/package_and_module_practice_with_config_file$ ./config.py
    MY_CONSTANT1 = 7
    MY_CONSTANT2 = 8
    MY_CONSTANT3 = 9


"""
