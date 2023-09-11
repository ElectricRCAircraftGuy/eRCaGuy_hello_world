#!/usr/bin/env python3

"""
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
2023

Library to convert TAI Time (International Atomic Time) to Unix Time, and back. See the references
below.
- Beware that what many sources may call "TAI Time" is actually "TAI-10 Time", which is TAI time
minus 10 seconds. See some definitions:
https://metacpan.org/pod/Time::TAI::Simple#ABOUT-TAI,-TAI10,-TAI35
> When most people use TAI time, it is usually TAI-10.
- Note that Unix time is NOT UTC time. Unix time takes into account leap seconds via pausing or
  skipping a second periodically, I believe, whereas UTC time may explicitly count leap seconds. I'm
  still confused about some of these details. Also, not everyone and not every library does this the
  same.

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
1. Bing AI chat help (view in Edge browser only): https://sl.bing.net/b2tanuWQXtY
1. Some definitions: TAI time vs TAI-10:
   https://metacpan.org/pod/Time::TAI::Simple#ABOUT-TAI,-TAI10,-TAI35

    > **tai** is, very simply, the actual number of elapsed seconds since the epoch.
    >
    > **tai10** provides TAI-10 seconds, which is how TAI time has traditionally
      been most commonly used, because when leapseconds were introduced in
      1972, UTC was TAI minus 10 seconds.
      ...
      **When most people use TAI time, it is usually TAI-10.**

1. Definition of **Unix time** [GS: this is very misleading, as it apparently actually *does* take
   into account leap seconds!--just via a **discontinuity** (time jump at the leap second) is all]:

    1. https://docs.python.org/3/library/time.html#time.time (`time.time()`):

        > Return the time in seconds since the epoch as a floating point number. The handling of
        leap seconds is platform dependent. On Windows and most Unix systems, the leap seconds are
        not counted towards the time in seconds since the epoch. This is commonly referred to as
        **Unix time.**

    1. From Bing AI (open in the Edge browser only): https://sl.bing.net/jBrkYHIb64q

    1. From Wikipedia: https://en.wikipedia.org/wiki/Unix_time

        > [Unix time] measures time by the number of seconds that have elapsed since 00:00:00 UTC on
        1 January 1970, the Unix epoch, **without** adjustments made due to leap seconds.

        > Every day in Unix time consists of exactly 86400 seconds. [3600 sec/hr x 24 hrs/day =
        86400 seconds].

        ***** > When a leap second occurs, the UTC day is not exactly 86400 seconds long and the
        Unix time number (which always increases by exactly 86400 each day) experiences a
        discontinuity.

        I left a comment on the talk page (search for "ERCaGuy"):
        https://en.wikipedia.org/wiki/Talk:Unix_time

1. *****+ [BEST CODE AND ANSWER YET!] More help and code from Chat GPT:
   https://chat.openai.com/share/078bbab0-16a7-404c-9f02-48f57a4a92c0


SCRATCH:
```python
import datetime
import time

timestamp_unix_sec = time.time()
timestamp_utc_object = datetime.datetime.fromtimestamp(timestamp_unix_sec, tz=datetime.timezone.utc)
```
"""


import pprint

"""
Leap seconds table:

From the "/usr/share/zoneinfo/leap-seconds.list" file on Ubuntu 22.04. I found this file on Ubuntu
by searching for one of the leap seconds values in the file, using ripgrep (`rg`), like this:

        time rg --hidden 3124137600 /usr 2>/dev/null  # takes about 7 seconds

Find it online here, for example: https://www.ietf.org/timezones/data/leap-seconds.list

As explained in the comments at the top of the "leap-seconds.list" file, the official reference is
IERS Bulletin C:

> Leap seconds are announced by the IERS in its Bulletin C.
>
> See www.iers.org for more details.

- The latest version is here: https://datacenter.iers.org/data/latestVersion/bulletinC.txt
- Other versions are here: https://www.iers.org/IERS/EN/Publications/Bulletins/bulletins.html
- All IERS Bulletin C files are here:
  https://www.iers.org/IERS/EN/Publications/Bulletins/bulletins.html

In "/usr/share/zoneinfo/leap-seconds.list":

> The following table shows the corrections that must be applied to compute International Atomic
Time (TAI) from the Coordinated Universal Time (UTC) values that are transmitted by almost all time
services.

- Column 1 = UTC Time??? (I think--as transmitted by a time service), but converted to be in seconds
  since 1 Jan. 1900. GS: just use Unix time here, I think, but with a fixed epoch of 1 Jan. 1900.
    - GS NB: watch out! The Unix time epoch is 1 Jan. 1970, so this is 70 years earlier!
      See: https://en.wikipedia.org/wiki/Unix_time
- Column 2 = Seconds to add to Unix or UTC time to get TAI time for any TAI timestamp on or after
  the value in column 1. ie:
  TAI = Unix_on_or_after_the_value_in_column1 + column2, so
  Unix_on_or_after_the_value_in_column1 = TAI - column2   <========= key equation! ==========

- GS Note: UTC time takes into account your time zone. Unix time does NOT. So, Unix time is absolute
  throughout the world, whereas UTC time varies based on your time zone. BOTH take into account leap
  seconds: UTC explicitly I believe, and Unix time implicitly by counting the same second twice to
  account for the leap second.

To see if your version of the leap-seconds.list file is up-to-date, look for these lines near the
end of the comments in the file, just before the table begins:

> #   Updated through IERS Bulletin C65
> #   File expires on:  28 December 2023
"""
LEAP_SECONDS_TABLE = [
    # See column descriptions just above.
    #
    # UTC time (sec) as broadcasted by a time service?, but in seconds since 1 Jan. 1900
    # GS: just use Unix time here, I think, but with a fixed epoch of 1 Jan. 1900.
    #  |       leap seconds to add to Unix or UTC time to get TAI time
    #  |         |
    (2272060800, 10, "1 Jan 1972"), # GS note: 2272060800/(3600×24×365.25) = 71.997 years, so
                                    # this number of seconds clearly accounts for leap seconds
    (2287785600, 11, "1 Jul 1972"),
    (2303683200, 12, "1 Jan 1973"),
    (2335219200, 13, "1 Jan 1974"),
    (2366755200, 14, "1 Jan 1975"),
    (2398291200, 15, "1 Jan 1976"),
    (2429913600, 16, "1 Jan 1977"),
    (2461449600, 17, "1 Jan 1978"),
    (2492985600, 18, "1 Jan 1979"),
    (2524521600, 19, "1 Jan 1980"),
    (2571782400, 20, "1 Jul 1981"),
    (2603318400, 21, "1 Jul 1982"),
    (2634854400, 22, "1 Jul 1983"),
    (2698012800, 23, "1 Jul 1985"),
    (2776982400, 24, "1 Jan 1988"),
    (2840140800, 25, "1 Jan 1990"),
    (2871676800, 26, "1 Jan 1991"),
    (2918937600, 27, "1 Jul 1992"),
    (2950473600, 28, "1 Jul 1993"),
    (2982009600, 29, "1 Jul 1994"),
    (3029443200, 30, "1 Jan 1996"),
    (3076704000, 31, "1 Jul 1997"),
    (3124137600, 32, "1 Jan 1999"),
    (3345062400, 33, "1 Jan 2006"),
    (3439756800, 34, "1 Jan 2009"),
    (3550089600, 35, "1 Jul 2012"),
    (3644697600, 36, "1 Jul 2015"),
    (3692217600, 37, "1 Jan 2017"),
]

def ns_to_sec(ns):
    """
    Convert nanoseconds to seconds.
    """
    return ns / 1e9

def sec_to_ns(sec):
    """
    Convert seconds to nanoseconds.
    """
    return sec * 1e9

# Convert the leap seconds table to nanoseconds, and use a Unix-like epoch of 1 Jan. 1970

LEAP_SECONDS_TABLE_NEW = [None]*len(LEAP_SECONDS_TABLE)
TWO_UNIX_YEARS_SEC = 3600*24*365*2
# UTC offset - two Unix-time years
EPOCH_OFFSET_SEC = LEAP_SECONDS_TABLE[0][0] - TWO_UNIX_YEARS_SEC
for i, row in enumerate(LEAP_SECONDS_TABLE):
    # col0 = Unix time (ns), with its defined epoch of **1 Jan. 1970**
    # col1 = TAI time (ns), with an altered epoch of **1 Jan. 1970** (to be Unix-like),
    #        assuming the offset at this row applies
    # col2 = leap seconds (sec)
    # col3 = human-readable date string

    col0 = int(sec_to_ns(LEAP_SECONDS_TABLE[i][0] - EPOCH_OFFSET_SEC))
    col1 = col0 + int(sec_to_ns(LEAP_SECONDS_TABLE[i][1]))
    col2 = LEAP_SECONDS_TABLE[i][1]
    col3 = LEAP_SECONDS_TABLE[i][2]
    LEAP_SECONDS_TABLE_NEW[i] = (col0, col1, col2, col3)

def get_leap_seconds_from_tai_time(timestamp_tai_ns):
    """
    Get the number of leap seconds to subtract from TAI time to get Unix time.
    Unix = TAI - leap_seconds
    NB: the TAI timestamp input must use a Unix-like epoch of 1 Jan. 1970 here!
    """

    leap_sec = 0

    # reverse search, since I think it's more likely people are using recent times than old times
    i = len(LEAP_SECONDS_TABLE_NEW) - 1
    while i >= 0:
        if timestamp_tai_ns >= LEAP_SECONDS_TABLE_NEW[i][1]:
            leap_sec = LEAP_SECONDS_TABLE_NEW[i][2]
            break
        i -= 1

    return leap_sec

def get_leap_seconds_from_unix_time(timestamp_unix_ns):
    """
    Get the number of leap seconds to add to Unix time to get TAI time.
    TAI = Unix + leap_seconds
    NB: the TAI timestamp assumes a Unix-like epoch of 1 Jan. 1970 here!
    """

    leap_sec = 0

    # reverse search, since I think it's more likely people are using recent times than old times
    i = len(LEAP_SECONDS_TABLE_NEW) - 1
    while i >= 0:
        if timestamp_unix_ns >= LEAP_SECONDS_TABLE_NEW[i][0]:
            leap_sec = LEAP_SECONDS_TABLE_NEW[i][2]
            break
        i -= 1

    return leap_sec

def time_tai10_to_tai(timestamp_tai10_ns):
    """
    Convert TAI-10 ("TAI minus 10 seconds") Time in nanoseconds to TAI Time in nanoseconds.
    See some definitions: https://metacpan.org/pod/Time::TAI::Simple#ABOUT-TAI,-TAI10,-TAI35
        "When most people use TAI time, it is usually TAI-10.
    TAI-10 is TAI time minus 10 seconds.
        TAI10 = TAI - 10
        so TAI = TAI10 + 10
    NB: the TAI timestamp input must use a Unix-like epoch of 1 Jan. 1970 here!
    """
    timestamp_tai_ns = timestamp_tai10_ns + sec_to_ns(10)
    return timestamp_tai_ns

def time_tai_to_tai10(timestamp_tai_ns):
    """
    Convert TAI Time in nanoseconds to TAI-10 ("TAI minus 10 seconds") Time in nanoseconds.
    See notes in the `time_tai10_to_tai()` function above.
    NB: the TAI timestamp input must use a Unix-like epoch of 1 Jan. 1970 here!
    """
    timestamp_tai10_ns = timestamp_tai_ns - sec_to_ns(10)
    return timestamp_tai10_ns

def time_tai_to_unix(timestamp_tai_ns):
    """
    Convert TAI Time in nanoseconds to Unix Time in nanoseconds.
    Unix = TAI - leap_seconds
    NB: the TAI timestamp input must use a Unix-like epoch of 1 Jan. 1970 here!
    """
    leap_sec = get_leap_seconds_from_tai_time(timestamp_tai_ns)
    leap_ns = sec_to_ns(leap_sec)
    timestamp_unix_ns = timestamp_tai_ns - leap_ns
    return timestamp_unix_ns

def time_unix_to_tai(timestamp_unix_ns):
    """
    Convert Unix Time in nanoseconds to TAI Time in nanoseconds.
    TAI = Unix + leap_seconds
    NB: the TAI timestamp input must use a Unix-like epoch of 1 Jan. 1970 here!
    """
    leap_sec = get_leap_seconds_from_unix_time(timestamp_unix_ns)
    leap_ns = sec_to_ns(leap_sec)
    timestamp_tai_ns = timestamp_unix_ns + leap_ns
    return timestamp_tai_ns

def time_tai10_to_unix(timestamp_tai10_ns):
    """
    Convert TAI-10 ("TAI minus 10 seconds") Time in nanoseconds to Unix Time in nanoseconds.
    NB: the TAI timestamp input must use a Unix-like epoch of 1 Jan. 1970 here!
    """
    timestamp_unix_ns = time_tai_to_unix(time_tai10_to_tai(timestamp_tai10_ns))
    return timestamp_unix_ns

def time_unix_to_tai10(timestamp_unix_ns):
    """
    Convert Unix Time in nanoseconds to TAI-10 ("TAI minus 10 seconds") Time in nanoseconds.
    NB: the TAI timestamp input must use a Unix-like epoch of 1 Jan. 1970 here!
    """
    timestamp_tai10_ns = time_tai_to_tai10(time_unix_to_tai(timestamp_unix_ns))
    return timestamp_tai10_ns

def run_unit_tests():
    print("Running unit tests.")

    print("LEAP_SECONDS_TABLE_NEW:")
    pprint.pprint(LEAP_SECONDS_TABLE_NEW)

    # TODO: add unit tests!


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
