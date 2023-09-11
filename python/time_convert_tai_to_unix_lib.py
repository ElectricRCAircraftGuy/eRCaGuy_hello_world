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

    > tai is, very simply, the actual number of elapsed seconds since the epoch.
    >
    > tai10 provides TAI-10 seconds, which is how TAI time has traditionally
      been most commonly used, because when leapseconds were introduced in
      1972, UTC was TAI minus 10 seconds.
      ...
      **When most people use TAI time, it is usually TAI-10.**

"""


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
- Column 1 = TAI Time in seconds since 1 Jan. 1900.
- Column 2 = Seconds to add to Unix time to get TAI time for any TAI timestamp on or after the
  value in column 1. ie:
  TAI_on_or_after_the_value_in_column1 = Unix + column2, so
  Unix = TAI_on_or_after_the_value_in_column1 - column2   <========= key equation! ==========

To see if your version of the leap-seconds.list file is up-to-date, look for these lines near the
end of the comments in the file, just before the table begins:

> #   Updated through IERS Bulletin C65
> #   File expires on:  28 December 2023
"""
LEAP_SECONDS_TABLE = [
    # See column descriptions just above.
    (2272060800 10, "1 Jan 1972"),
    (2287785600 11, "1 Jul 1972"),
    (2303683200 12, "1 Jan 1973"),
    (2335219200 13, "1 Jan 1974"),
    (2366755200 14, "1 Jan 1975"),
    (2398291200 15, "1 Jan 1976"),
    (2429913600 16, "1 Jan 1977"),
    (2461449600 17, "1 Jan 1978"),
    (2492985600 18, "1 Jan 1979"),
    (2524521600 19, "1 Jan 1980"),
    (2571782400 20, "1 Jul 1981"),
    (2603318400 21, "1 Jul 1982"),
    (2634854400 22, "1 Jul 1983"),
    (2698012800 23, "1 Jul 1985"),
    (2776982400 24, "1 Jan 1988"),
    (2840140800 25, "1 Jan 1990"),
    (2871676800 26, "1 Jan 1991"),
    (2918937600 27, "1 Jul 1992"),
    (2950473600 28, "1 Jul 1993"),
    (2982009600 29, "1 Jul 1994"),
    (3029443200 30, "1 Jan 1996"),
    (3076704000 31, "1 Jul 1997"),
    (3124137600 32, "1 Jan 1999"),
    (3345062400 33, "1 Jan 2006"),
    (3439756800 34, "1 Jan 2009"),
    (3550089600 35, "1 Jul 2012"),
    (3644697600 36, "1 Jul 2015"),
    (3692217600 37, "1 Jan 2017"),
]

def get_leap_seconds(tai_time_ns):
    """
    Get the number of leap seconds to subtract from TAI time to get Unix time.
    """
    # binary search
    i = len(LEAP_SECONDS_TABLE) // 2
    while True:
        leap_time_ns = sec_to_ns(LEAP_SECONDS_TABLE[i][0])
        if tai_time_ns

    for leap_seconds in LEAP_SECONDS_TABLE:
        if tai_time_ns >= leap_seconds[0]:
            return leap_seconds[1]


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

def time_tai10_to_tai(timestamp_tai10_ns):
    """
    Convert TAI-10 ("TAI minus 10 seconds") Time in nanoseconds to TAI Time in nanoseconds.
    See some definitions: https://metacpan.org/pod/Time::TAI::Simple#ABOUT-TAI,-TAI10,-TAI35
        "When most people use TAI time, it is usually TAI-10.
    TAI-10 is TAI time minus 10 seconds.
        TAI10 = TAI - 10
        so TAI = TAI10 + 10
    """
    timestamp_tai_ns = timestamp_tai10_ns + sec_to_ns(10)
    return timestamp_tai_ns

def time_tai_to_tai10(timestamp_tai_ns):
    """
    Convert TAI Time in nanoseconds to TAI-10 ("TAI minus 10 seconds") Time in nanoseconds.
    See notes in the `time_tai10_to_tai()` function above.
    """
    timestamp_tai10_ns = timestamp_tai_ns - sec_to_ns(10)
    return timestamp_tai10_ns

def time_tai_to_unix(timestamp_tai_ns):
    """
    Convert TAI Time in nanoseconds to Unix Time in nanoseconds.
    """


def time_unix_to_tai(timestamp_unix_ns):
    """
    Convert Unix Time in nanoseconds to TAI Time in nanoseconds.
    """

def time_tai10_to_unix(timestamp_tai10_ns):
    """
    Convert TAI-10 ("TAI minus 10 seconds") Time in nanoseconds to Unix Time in nanoseconds.
    """
    timestamp_unix_ns = time_tai_to_unix(time_tai10_to_tai(timestamp_tai10_ns))
    return timestamp_unix_ns

def time_unix_to_tai10(timestamp_unix_ns):
    """
    Convert Unix Time in nanoseconds to TAI-10 ("TAI minus 10 seconds") Time in nanoseconds.
    """
    timestamp_tai10_ns = time_tai_to_tai10(time_unix_to_tai(timestamp_unix_ns))
    return timestamp_tai10_ns

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
