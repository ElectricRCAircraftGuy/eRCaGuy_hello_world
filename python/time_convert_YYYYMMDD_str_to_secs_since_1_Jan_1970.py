#!/usr/bin/env python3

"""
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
Sept. 2023

Convert a "YYYY.MM.DD" string to seconds since 1 Jan 1970, in C.
See: "eRCaGuy_hello_world/c/time_convert_YYYYMMDD_str_to_secs_since_1_Jan_1970.c".

Status: Done and works!

keywords: (keywords)

Check this script with `pylint` v2.0.0 or later. See "eRCaGuy_hello_world/python/README.md" for
installation instructions to install the latest version from GitHub.
For a list of all error codes, such as `C0301`, `C0116`, `W0105`, etc., see here:
https://pylint.pycqa.org/en/latest/messages/messages_list.html
```bash
pylint time_convert_YYYYMMDD_str_to_secs_since_1_Jan_1970.py
```

Run command:
```bash
./time_convert_YYYYMMDD_str_to_secs_since_1_Jan_1970.py
# OR
python3 time_convert_YYYYMMDD_str_to_secs_since_1_Jan_1970.py
```

References:
1. "eRCaGuy_hello_world/c/time_convert_YYYYMMDD_str_to_secs_since_1_Jan_1970.c"
1. GitHub CoPilot
1.


"""


import datetime

date = datetime.datetime.strptime("2023.09.23", "%Y.%m.%d")
date_sec = date.timestamp()
print(f"date (UTC) = {date}\ndate_sec = {date_sec}")



# pylint: disable-next=pointless-string-statement
"""
SAMPLE OUTPUT:

    eRCaGuy_hello_world$ python/time_convert_YYYYMMDD_str_to_secs_since_1_Jan_1970.py
    date (UTC) = 2023-09-23 00:00:00
    date_sec = 1695452400.0


"""
