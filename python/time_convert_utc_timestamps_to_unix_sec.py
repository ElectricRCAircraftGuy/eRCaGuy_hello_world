#!/usr/bin/env python3

"""
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
Sept. 2023

Convert the combination of (
    YYYY.MM.DD string,
    UTC seconds since start of day,
) to Unix time (seconds since 1 Jan 1970).

Status: done and works!

keywords: (keywords)

Check this script with `pylint` v2.0.0 or later. See "eRCaGuy_hello_world/python/README.md" for
installation instructions to install the latest version from GitHub.
For a list of all error codes, such as `C0301`, `C0116`, `W0105`, etc., see here:
https://pylint.pycqa.org/en/latest/messages/messages_list.html
```bash
pylint time_convert_utc_timestamps_to_unix_sec.py
```

Run command:
```bash
./time_convert_utc_timestamps_to_unix_sec.py
# OR
python3 time_convert_utc_timestamps_to_unix_sec.py
```

References:
1. "eRCaGuy_hello_world/c/time_convert_YYYYMMDD_str_to_secs_since_1_Jan_1970.c"
1. GitHub CoPilot
1.


"""


import datetime

def utc_timestamp_to_unix_sec(utc_yyyy_mm_dd_str, utc_time_of_day_sec):
    """
    Convert UTC time to Unix time (seconds since 1 Jan 1970).

    Args:
    utc_yyyy_mm_dd_str (str): UTC date in the format "YYYY.MM.DD"
    utc_time_of_day_sec (float): UTC time of day in seconds since start of day (midnight in UTC+0
    time).

    Returns:
    float: Unix time in seconds since 1 Jan 1970.

    Notes:
    1. From here: https://docs.python.org/3/library/datetime.html#datetime.datetime.timestamp
    > Note There is no method to obtain the POSIX timestamp directly from a
    > naive datetime instance representing UTC time. If your application uses
    > this convention and your system timezone is not set to UTC, you can
    > obtain the POSIX timestamp by supplying tzinfo=timezone.utc:
    >
    >       timestamp = dt.replace(tzinfo=timezone.utc).timestamp()
    >
    > or by calculating the timestamp directly:
    >
    >       timestamp = (dt - datetime(1970, 1, 1)) / timedelta(seconds=1)

    2. IMPORTANT!: since the date string does NOT contain timezone info, `strptime()` (string parse
    time) will assume it is in the local timezone, so it automatically applies the **local** time
    zone offset. So, we must convert it to UTC **afterwards** by using the
    `date.replace(tzinfo=timezone.utc).timestamp()` function to then remove that local time zone
    offset just applied by `strptime()`.

    3. Conversions between UTC and local time:
    Local time = UTC time + UTC time zone offset
    UTC time = Local time - UTC time zone offset
    """

    # Note: since the date_str does not contain any time zone info, `strptime()` assumes local time,
    # and applies the current local time offset to the year.month.day time string provided.
    date_local_time = datetime.datetime.strptime(utc_yyyy_mm_dd_str, "%Y.%m.%d")
    # Use the `replace()` function to convert the local time to UTC time by setting the time zone to
    # UTC, thereby removing our local time zone offset from what `strptime()` just applied.
    date_utc_time = date_local_time.replace(tzinfo=datetime.timezone.utc)

    # Note: `date_utc_sec` can easily be calculated in an Excel or Calc spreadsheet too: just input
    # 1/1/1970 in once cell, the current date in another and subtract the two to get the number of
    # days since then. Then, multiply that number of days by 24*60*60 to get the number of seconds
    # since 1 Jan. 1970. That number of seconds will exactly equal this `date_utc_sec` value.
    date_utc_sec = date_utc_time.timestamp()

    unix_sec = date_utc_sec + utc_time_of_day_sec

    # debugging
    # print(f"date_local_time = {date_local_time}; date_utc_time = {date_utc_time}; " +
    #       f"*local sec** = {date_local_time.timestamp()}; date_utc_sec = {date_utc_sec}")

    return unix_sec


def test_utc_timestamp_to_unix_sec():
    assert utc_timestamp_to_unix_sec("2022.01.01", 0) == 1640995200
    assert utc_timestamp_to_unix_sec("2022.01.01", 3600) == (1640995200 + 3600)
    assert utc_timestamp_to_unix_sec("2023.09.23", 0) == 1695427200
    assert utc_timestamp_to_unix_sec("2023.09.23", 4123) == (1695427200 + 4123)

    print("\033[32mAll unit tests passed!\033[0m") # print in green


def run_unit_tests():
    test_utc_timestamp_to_unix_sec()


if __name__ == '__main__':
    run_unit_tests()



# pylint: disable-next=pointless-string-statement
"""
SAMPLE OUTPUT:

    eRCaGuy_hello_world$ python/time_convert_utc_timestamps_to_unix_sec.py
    All unit tests passed!



"""
