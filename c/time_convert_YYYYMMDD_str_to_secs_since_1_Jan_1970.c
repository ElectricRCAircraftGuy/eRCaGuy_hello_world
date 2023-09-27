///usr/bin/env ccache gcc -Wall -Wextra -Werror -O3 -std=gnu17 "$0" -o /tmp/a -lm && /tmp/a "$@"; exit
// For the line just above, see my answer here: https://stackoverflow.com/a/75491834/4561887

/*
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
Sept. 2023

Convert a "YYYY.MM.DD" string to seconds since 1 Jan 1970, in C.

In Python it looks like this:
See: "eRCaGuy_hello_world/python/time_convert_utc_timestamps_to_unix_sec.py":
```py
import datetime
date_local_time = datetime.datetime.strptime("2023.09.23", "%Y.%m.%d")
date_utc_time = date_local_time.replace(tzinfo=datetime.timezone.utc)
date_utc_sec = date_utc_time.timestamp()
print(f"date_utc_time = {date_utc_time}\ndate_utc_sec = {date_utc_sec}")
```
Output:
```
date_utc_time = 2023-09-23 00:00:00+00:00
date_utc_sec = 1695427200.0
```

STATUS: Done and works!

keywords to easily grep or ripgrep in this repo for this program and what it teaches
KEYWORDS:

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# Why `-std=gnu17` vs `-std=c17`, and `-std=gnu++17` vs `-std=c++17`?
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# [run once ever] install ccache
sudo apt update && sudo apt install ccache

# 1. In C:
./time_convert_YYYYMMDD_str_to_secs_since_1_Jan_1970.c
# or:
gcc -Wall -Wextra -Werror -O3 -std=gnu17 time_convert_YYYYMMDD_str_to_secs_since_1_Jan_1970.c -o
bin/a -lm && bin/a

# 2. In C++
g++ -Wall -Wextra -Werror -O3 -std=gnu++17 time_convert_YYYYMMDD_str_to_secs_since_1_Jan_1970.c -o
bin/a && bin/a
```

References:
1. GitHub CoPilot
1. string parse time - https://man7.org/linux/man-pages/man3/strptime.3.html
1. make seconds timestamp from `struct tm` - https://man7.org/linux/man-pages/man3/mktime.3p.html
1. `struct tm` - https://man7.org/linux/man-pages/man3/tm.3type.html
1. `strftime()` string format time -https://man7.org/linux/man-pages/man3/strftime.3.html


*/

#define _DEFAULT_SOURCE  // For `tm.tm_gmtoff` (seconds East of UTC) in `struct tm` in C.
                         // See: 1. https://man7.org/linux/man-pages/man7/feature_test_macros.7.html
                         //      2. https://man7.org/linux/man-pages/man3/tm.3type.html
#define _XOPEN_SOURCE  // For `strptime()`; this MUST be before all includes below; see example
                       // here: https://man7.org/linux/man-pages/man3/strptime.3.html

#include <errno.h>    // For `errno` (error numbers)
#include <stdbool.h>  // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>   // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>    // For `printf()`
#include <stdlib.h>   // For `EXIT_FAILURE` and `EXIT_SUCCESS`
#include <string.h>   // For `strerror()`
#include <time.h>     // For `strptime()` (string parse time) and `mktime()` (make seconds timestamp)

int main()
{
    // 1. Convert the date string to a `struct tm` object

    struct tm time_struct;
    memset(&time_struct, 0, sizeof(time_struct)); // REQUIRED: initialize to all zeros!

    const char* DATE_STR = "2023.09.23";
    const char* FORMAT_STR = "%Y.%m.%d";

    // Parse the date string according to the format string
    // See: https://man7.org/linux/man-pages/man3/strptime.3.html
    //
    // See: "eRCaGuy_hello_world/python/time_convert_utc_timestamps_to_unix_sec.py":
    // Note: since the date_str does not contain any time zone info, `strptime()` assumes local
    // time, and applies the current local time offset to the year.month.day time string provided.
    char* return_val = strptime(DATE_STR, FORMAT_STR, &time_struct);
    if (return_val == NULL)
    {
        printf("ERROR: strptime() failed to parse date string!\n");
        return EXIT_FAILURE;
    }
    else if (*return_val == '\0')
    {
        printf("Whole date string parsed correctly.\n");
    }
    else
    {
        printf("Date string parsed correctly up to: %s\n", return_val);
    }

    // debugging; will be 123 for the year 2023, since 1900 + 123 = 2023
    // printf("time_struct.tm_year = %i\n", time_struct.tm_year);
    // printf("time_struct.tm_gmtoff seconds East of UTC = %li\n", time_struct.tm_gmtoff);

    // See contents of this struct: https://man7.org/linux/man-pages/man3/tm.3type.html
    printf("time_struct contains:\n"
           "  sec   = %i\n"   // Seconds (0-60)
           "  min   = %i\n"   // Minutes (0-59)
           "  hour  = %i\n"   // Hours (0-23)
           "  mday  = %i\n"   // Day of the month (1-31)
           "  mon   = %i\n"   // Month (0-11)
           "  year  = %i\n"   // Year - 1900
           "  wday  = %i\n"   // Day of the week (0-6, Sunday = 0)
           "  yday  = %i\n"   // Day in the year (0-365, 1 Jan = 0)
           "  isdst = %i\n"   // Daylight saving time
           "  tm_gmtoff = %li\n" // Seconds East of UTC
           "  tm_zone   = %s\n"  // Timezone abbreviation
           "\n",
           time_struct.tm_sec, time_struct.tm_min, time_struct.tm_hour,
           time_struct.tm_mday, time_struct.tm_mon, time_struct.tm_year,
           time_struct.tm_wday, time_struct.tm_yday, time_struct.tm_isdst,
           time_struct.tm_gmtoff, time_struct.tm_zone);

    // 1.5. Figure out the timezone offset from UTC in seconds, by getting a current timestamp

    // TODO: add error handling later
    time_t time_now_sec = time(NULL);
    struct tm* time_now_struct = localtime(&time_now_sec);

    printf("time_now_struct (not re-entrant) contains:\n"
           "  sec   = %i\n"       // Seconds (0-60)
           "  min   = %i\n"       // Minutes (0-59)
           "  hour  = %i\n"       // Hours (0-23)
           "  mday  = %i\n"       // Day of the month (1-31)
           "  mon   = %i\n"       // Month (0-11)
           "  year  = %i\n"       // Year - 1900
           "  wday  = %i\n"       // Day of the week (0-6, Sunday = 0)
           "  yday  = %i\n"       // Day in the year (0-365, 1 Jan = 0)
           "  isdst = %i\n"       // Daylight saving time
           "  tm_gmtoff = %li\n"  // Seconds East of UTC
           "  tm_zone   = %s\n"   // Timezone abbreviation
           "\n",
           time_now_struct->tm_sec, time_now_struct->tm_min, time_now_struct->tm_hour,
           time_now_struct->tm_mday, time_now_struct->tm_mon, time_now_struct->tm_year,
           time_now_struct->tm_wday, time_now_struct->tm_yday, time_now_struct->tm_isdst,
           time_now_struct->tm_gmtoff, time_now_struct->tm_zone);

    long int local_time_zone_offset_sec = time_now_struct->tm_gmtoff;

    // 2. Convert the struct tm object to a `time_t` number of seconds since 1 Jan 1970

    time_t timestamp_sec = mktime(&time_struct);
    if (timestamp_sec == -1)
    {
        printf("ERROR: mktime() failed to convert `struct tm` to `time_t`! errno = %d (%s)\n",
            errno, strerror(errno));
        return EXIT_FAILURE;
    }

    // 2.5. Add the timezone offset back to the timestamp to convert from local time back to UTC
    // time

    timestamp_sec += local_time_zone_offset_sec;

    // 3. Print the date and timestamp

    char time_str[20];
    size_t num_chars_written = strftime(
        time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", &time_struct);
    if (num_chars_written == 0)
    {
        printf("ERROR: `time_str` buffer is probably too small!\n");
    }

    printf("date (UTC) = %s\ndate_sec = %ld\n", time_str, timestamp_sec);

    return EXIT_SUCCESS;
}

/*
SAMPLE OUTPUT:

In C:

    eRCaGuy_hello_world$ c/time_convert_YYYYMMDD_str_to_secs_since_1_Jan_1970.c
    Whole date string parsed correctly.
    time_struct contains:
    sec   = 0
    min   = 0
    hour  = 0
    mday  = 23
    mon   = 8
    year  = 123
    wday  = 6
    yday  = 265
    isdst = 0
    tm_gmtoff = 0
    tm_zone   = (null)

    time_now_struct (not re-entrant) contains:
    sec   = 12
    min   = 17
    hour  = 0
    mday  = 27
    mon   = 8
    year  = 123
    wday  = 3
    yday  = 269
    isdst = 0
    tm_gmtoff = -25200
    tm_zone   = MST

    date (UTC) = 2023-09-23 00:00:00
    date_sec = 1695427200


OR, in C++:

[same as above]

*/
