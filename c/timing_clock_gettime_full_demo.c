/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
15 Apr. 2022

Do a basic demo of how to use the POSIX/Linux function `clock_gettime()` to obtain an NTP-adjusted
RTC (Real-Time Clock) timestamp, with full error-checking, and printed in various output formats.

STATUS: works!

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# Why `-std=gnu17` vs `-std=c17`, and `-std=gnu++17` vs `-std=c++17`?
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# 1. In C:
gcc -Wall -Wextra -Werror -O3 -std=gnu17 timing_clock_gettime_full_demo.c -o bin/a && bin/a

# 2. In C++
g++ -Wall -Wextra -Werror -O3 -std=gnu++17 timing_clock_gettime_full_demo.c -o bin/a && bin/a
```

References:
1. [I'm answering this question]: https://stackoverflow.com/q/51550722/4561887
    1. *****+ [MY ANSWER with this code!] How to read an NTP-adjusted RTC
    (Real-time clock) timestamp on Linux:
    https://stackoverflow.com/a/71889029/4561887
1. [my answer--another one with this code]
   Retrieve Linux Time using struct timespec:
   https://stackoverflow.com/a/71889097/4561887
1. *****https://man7.org/linux/man-pages/man3/clock_gettime.3.html
1. RTC: https://en.wikipedia.org/wiki/Real-time_clock
1. NTP: https://en.wikipedia.org/wiki/Network_Time_Protocol
1. https://man7.org/linux/man-pages/man3/localtime.3p.html - contains a great
   example of `strftime()` at the bottom too!
1. `struct tm`: https://man7.org/linux/man-pages/man3/ctime.3.html
1. https://man7.org/linux/man-pages/man3/strftime.3p.html

*/

// This define is required to bring in some of the extra POSIX features defined
// in `<time.h>`. Depending on your compiler settings, it may be required to
// get access to `clock_gettime()`. Using `-std=gnu17`, however, brings it in
// automatically since the compiler then uses the "gnu c" language instead of
// the standard "c" language.
//
// #define _POSIX_C_SOURCE 200112L

// Linux includes
// NA

// C includes
#include <errno.h>   // `errno`
#include <inttypes.h> // `PRIu64`
#include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`
#include <string.h>  // `strerror(errno)`
#include <time.h>    // Includes `clock_gettime()` on Linux


#define NS_PER_SEC (1000000000L)
/// Convert seconds to nanoseconds
#define SEC_TO_NS(sec) ((sec)*NS_PER_SEC)


// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Obtain an NTP-adjusted Real-time Clock timestamp on Linux.\n\n");

    // Obtain a timestamp
    struct timespec ts;
    int retcode = clock_gettime(CLOCK_REALTIME, &ts);
    if (retcode == -1)
    {
        printf("Failed to get a timestamp. errno = %i: %s\n",
            errno, strerror(errno));
    }

    // Print seconds.nanoseconds
    printf("timestamp = %li.%09li sec.\n\n", ts.tv_sec, ts.tv_nsec);

    // Convert it to just `uint64_t` nanoseconds
    // See: eRCaGuy_hello_world/c/timinglib.c
    uint64_t ns = SEC_TO_NS((uint64_t)ts.tv_sec) + (uint64_t)ts.tv_nsec;
    printf("timestamp = %" PRIu64 " nanoseconds.\n\n", ns);

    // Convert it to a local time stored in `struct tm`. Use the re-entrant
    // (thread-safe) version of the function, called `localtime_r()`. See:
    // 1. https://man7.org/linux/man-pages/man3/localtime.3p.html
    // 1. https://stackoverflow.com/a/47532938/4561887
    // 1. `struct tm`: https://man7.org/linux/man-pages/man3/ctime.3.html
    struct tm localtime_struct;
    // Note: retptr means "return pointer"
    struct tm * retptr = localtime_r(&ts.tv_sec, &localtime_struct);
    if (retptr == NULL)
    {
        printf("Failed to convert to localtime. errno = %i: %s\n",
            errno, strerror(errno));
    }
    printf("localtime_struct contains:\n"
           "  ns    = %li\n" // Nanoseconds (0-999999999); NOT FROM THIS STRUCT
           "  sec   = %i\n"  // Seconds (0-60)
           "  min   = %i\n"  // Minutes (0-59)
           "  hour  = %i\n"  // Hours (0-23)
           "  mday  = %i\n"  // Day of the month (1-31)
           "  mon   = %i\n"  // Month (0-11)
           "  year  = %i\n"  // Year - 1900
           "  wday  = %i\n"  // Day of the week (0-6, Sunday = 0)
           "  yday  = %i\n"  // Day in the year (0-365, 1 Jan = 0)
           "  isdst = %i\n"  // Daylight saving time
           "\n",
           ts.tv_nsec,
           localtime_struct.tm_sec,
           localtime_struct.tm_min,
           localtime_struct.tm_hour,
           localtime_struct.tm_mday,
           localtime_struct.tm_mon,
           localtime_struct.tm_year,
           localtime_struct.tm_wday,
           localtime_struct.tm_yday,
           localtime_struct.tm_isdst);

    // Convert the `struct tm` localtime struct to a human-readable string in
    // normal human time units of Day, Month, Year, etc.
    // - This is the format string required to output timestamps in the exact
    //   same format as `git` uses when you `git commit`.
    const char * time_format_str = "%a %b %-d %H:%M:%S %Y %z";
    char time_str[100];
    size_t bytes_written = strftime(time_str, sizeof(time_str),
        time_format_str, &localtime_struct);
    if (bytes_written == 0)
    {
        printf("Failed to convert `struct tm` to a human-readable "
               "time string.\n");
    }
    printf("Formatted local time string = %s\n\n", time_str);


    return 0;
}


/*
SAMPLE OUTPUT:

In C:

    eRCaGuy_hello_world/c$ gcc -Wall -Wextra -Werror -O3 -std=gnu17 timing_clock_gettime_full_demo.c -o bin/a && bin/a
    Obtain an NTP-adjusted Real-time Clock timestamp on Linux.

    timestamp = 1650056712.080211270 sec.

    timestamp = 1650056712080211270 nanoseconds.

    localtime_struct contains:
      ns    = 80211270
      sec   = 12
      min   = 5
      hour  = 14
      mday  = 15
      mon   = 3
      year  = 122
      wday  = 5
      yday  = 104
      isdst = 0

    Formatted local time string = Fri Apr 15 14:05:12 2022 -0700




OR, in C++:

(same as in C)


*/
