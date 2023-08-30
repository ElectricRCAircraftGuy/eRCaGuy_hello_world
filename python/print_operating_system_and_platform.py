#!/usr/bin/env python3

"""
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
29 Aug. 2023

Print the operating system and platform: ex: "Windows", "Mac", or "Linux", plus a bigger description
about which platform exactly, such as "Ubuntu 22.04".

I used Bing AI to figure this out.

Me: In Python, show me how to print out the operating system running the program. I'd like something
general like "Windows", "Mac", or "Linux", then something specific like what you might see with
`lsb_release` in Linux too. So, print at least 2 lines total.

Bing AI: https://sl.bing.net/dsoOd8ObxyC

Me: show what output might look like in Windows, in Mac, and in Git Bash on Windows too.

Bing AI: https://sl.bing.net/vbjfx2OGJg

etc.


Status: Done and works!

keywords: (keywords)

Check this script with `pylint` v2.0.0 or later. See "eRCaGuy_hello_world/python/README.md" for
installation instructions to install the latest version from GitHub.
For a list of all error codes, such as `C0301`, `C0116`, `W0105`, etc., see here:
https://pylint.pycqa.org/en/latest/messages/messages_list.html
```bash
pylint print_operating_system_and_platform.py
```

Run command:
```bash
./print_operating_system_and_platform.py
# OR
python3 print_operating_system_and_platform.py
```

References:
1. Bing AI: see links above.

"""


# With the help of Bing AI:


import lsb_release
import platform

# Print the general name of the operating system
print(platform.system())

# Print a more specific name and version of the operating system
print(platform.platform())

# The exact Ubuntu version
print(lsb_release.get_distro_information()["DESCRIPTION"])

# pylint: disable-next=pointless-string-statement
"""
SAMPLE OUTPUT:

On Linux Ubuntu 22.04:
    eRCaGuy_hello_world$ python/print_operating_system_and_platform.py
    Linux
    Linux-6.2.0-26-generic-x86_64-with-glibc2.35
    Ubuntu 22.04.3 LTS

On MacOS:
(TBD)

On Windows in Git Bash:
(TBD)


"""
