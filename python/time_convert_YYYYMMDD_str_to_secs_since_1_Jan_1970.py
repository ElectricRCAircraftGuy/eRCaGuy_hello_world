#!/usr/bin/env python3

"""
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
Sept. 2023

Convert a "YYYY.MM.DD" string to UTC (local time zone offset removed) seconds since 1 Jan 1970, in
Python.
See also: "eRCaGuy_hello_world/c/time_convert_YYYYMMDD_str_to_secs_since_1_Jan_1970.c".

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
1. "eRCaGuy_hello_world/python/time_convert_utc_timestamps_to_unix_sec.py"


"""


import datetime

# See: "eRCaGuy_hello_world/python/time_convert_utc_timestamps_to_unix_sec.py":
# Note: since the date_str does not contain any time zone info, `strptime()` assumes local time,
# and applies the current local time offset to the year.month.day time string provided.
date_local_time = datetime.datetime.strptime("2023.09.23", "%Y.%m.%d")
# See: "eRCaGuy_hello_world/python/time_convert_utc_timestamps_to_unix_sec.py":
# Use the `replace()` function to convert the local time to UTC time by setting the time zone to
# UTC, thereby removing our local time zone offset from what `strptime()` just applied.
date_utc_time = date_local_time.replace(tzinfo=datetime.timezone.utc)

# See: "eRCaGuy_hello_world/python/time_convert_utc_timestamps_to_unix_sec.py":
# Note: `date_utc_sec` can easily be calculated in an Excel or Calc spreadsheet too: just input
# 1/1/1970 in once cell, the current date in another and subtract the two to get the number of
# days since then. Then, multiply that number of days by 24*60*60 to get the number of seconds
# since 1 Jan. 1970. That number of seconds will exactly equal this `date_utc_sec` value.
date_utc_sec = date_utc_time.timestamp()

print(f"date_utc_time = {date_utc_time}\ndate_utc_sec = {date_utc_sec}")



# pylint: disable-next=pointless-string-statement
"""
SAMPLE OUTPUT:

    eRCaGuy_hello_world$ python/time_convert_YYYYMMDD_str_to_secs_since_1_Jan_1970.py
    date_utc_time = 2023-09-23 00:00:00+00:00
    date_utc_sec = 1695427200.0

"""
