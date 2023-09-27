///usr/bin/env ccache gcc -Wall -Wextra -Werror -O3 -std=gnu17 "$0" -o /tmp/a -lm && /tmp/a "$@"; exit
// For the line just above, see my answer here: https://stackoverflow.com/a/75491834/4561887

/*
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
Sept. 2023

Convert a "YYYY.MM.DD" string to seconds since 1 Jan 1970, in C.

In Python it looks like this:
```py
import datetime
date = datetime.datetime.strptime("2023.09.23", "%Y.%m.%d")
date_sec = date.timestamp()
print(f"date (UTC) = {date}\ndate_sec = {date_sec}")
```
Output:
```
date = 2023-09-23 00:00:00
date_sec = 1695452400.0
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

    // 2. Convert the struct tm object to a `time_t` number of seconds since 1 Jan 1970

    time_t timestamp_sec = mktime(&time_struct);
    if (timestamp_sec == -1)
    {
        printf("ERROR: mktime() failed to convert `struct tm` to `time_t`! errno = %d (%s)\n",
            errno, strerror(errno));
        return EXIT_FAILURE;
    }

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
    date (UTC) = 2023-09-23 00:00:00
    date_sec = 1695452400

OR, in C++:

[same as above]

*/
