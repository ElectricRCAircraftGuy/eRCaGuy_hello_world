#!/usr/bin/env python3

"""
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
2023

Library to convert TAI Time (International Atomic Time) to Unix Time, and back.
See the references below.

Status: WIP

keywords: (keywords)

Check this script with `pylint` v2.0.0 or later. See "eRCaGuy_hello_world/python/README.md" for
installation instructions to install the latest version from GitHub.
For a list of all error codes, such as `C0301`, `C0116`, `W0105`, etc., see here:
https://pylint.pycqa.org/en/latest/messages/messages_list.html
```bash
pylint time_convert_tai_to_unix_lib.py
```

Run command:
```bash
./time_convert_tai_to_unix_lib.py
# OR
python3 time_convert_tai_to_unix_lib.py
```

References:
1. TAI Time (International Atomic Time): https://en.wikipedia.org/wiki/International_Atomic_Time
1. Unix Time: https://en.wikipedia.org/wiki/Unix_time
    1. Also described by Python's `time.time()`:
       https://docs.python.org/3/library/time.html#time.time

Bing AI chat help:





"""

def time_tai_to_unix(timestamp_tai_ns):
    """
    Convert TAI Time in nanoseconds to Unix Time in nanoseconds.
    """


def time_unix_to_tai(timestamp_unix_ns):
    """
    Convert Unix Time in nanoseconds to TAI Time in nanoseconds.
    """
    pass

def run_unit_tests():
    print("Running unit tests.")




def main():
    """
    The main function of this program.
    """
    run_unit_tests()


# Only run `main()` if this script is **run**, NOT imported
if __name__ == '__main__':
    main()



# pylint: disable-next=pointless-string-statement
"""
SAMPLE OUTPUT:

    eRCaGuy_hello_world/python$ ./time_convert_tai_to_unix_lib
.py
    Hello world!

"""
