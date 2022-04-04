/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

Practice using `nanosleep()` and `clock_nanosleep()`--which is even better since it allows you to
specify the clock to use, AND it allows you to sleep until **absolute** timestamps rather than
only doing **relative** sleeps!

Do a general `nanosleep()` and `clock_nanosleep()` demo on Linux!

STATUS: WORKS!

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# 1. In C:
gcc -Wall -Wextra -Werror -O3 -std=c17 sleep_nanosleep.c -o bin/a -lm && time bin/a

# 2. In C++
g++ -Wall -Wextra -Werror -O3 -std=c++17 sleep_nanosleep.c -o bin/a && time bin/a
```

References:
1. *****+https://man7.org/linux/man-pages/man2/clock_nanosleep.2.html
1. https://man7.org/linux/man-pages/man2/nanosleep.2.html
1. *****[MY ANSWER] sleep in nanoseconds - https://stackoverflow.com/a/55860234/4561887
1. [MY ANSWER] Get a timestamp in C in microseconds? - https://stackoverflow.com/a/67731965/4561887
1. *****https://man7.org/linux/man-pages/man2/clock_nanosleep.2.html
1. timinglib_get_resolution.c
    1. timinglib.h
    1. timinglib.c
1. https://en.cppreference.com/w/c/program/exit

*/


// This line **must** come **before** including <time.h> in order to bring in
// the POSIX functions such as `clock_gettime()`, `nanosleep()`, etc., from
// `<time.h>`!
#define _POSIX_C_SOURCE 200112L

// Local includes

// Linux includes

// C includes
#include <errno.h>   // `errno`
#include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`
#include <stdlib.h>  // `exit()`
#include <string.h>  // `strerror(errno)`
#include <time.h>    // `nanosleep()`, `clock_nanosleep()`, etc.


// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    int retcode;

    printf("Practice sleeping!\n\n");

    // =============================================================================================
    printf("Sleeping 1 second using `nanosleep()` (relative sleep).\n");
    // See: https://man7.org/linux/man-pages/man2/nanosleep.2.html
    // =============================================================================================

    // 1 second
    struct timespec ts_requested =
    {
        .tv_sec = 1,
        .tv_nsec = 0,
    };

    struct timespec ts_remaining;
    retcode = -1; // force to run once
    while (retcode == -1)
    {
        retcode = nanosleep(&ts_requested, &ts_remaining);
        if (retcode == -1)
        {
            printf("Failed to sleep the full amount of time. The sleep call was either "
                   "interrupted by a signal handler OR encountered an error. errno = %i: %s\n",
                   errno, strerror(errno));
            ts_requested = ts_remaining; // prepare for the next loop iteration
        }
    }

    // =============================================================================================
    printf("Sleeping 1 second using `clock_nanosleep()` (relative sleep).\n");
    // See: https://man7.org/linux/man-pages/man2/clock_nanosleep.2.html
    // =============================================================================================

    ts_requested.tv_sec = 1;
    ts_requested.tv_nsec = 0;
    retcode = EINTR; // force to run once
    while (retcode == EINTR)
    {
        retcode = clock_nanosleep(CLOCK_MONOTONIC, 0, &ts_requested, &ts_remaining);
        if (retcode != 0)
        {
            printf("`clock_nanosleep()` failed! retcode = %i: ", retcode);
            // See all error codes here: https://man7.org/linux/man-pages/man2/clock_nanosleep.2.html
            switch (retcode)
            {
            case EFAULT:
                printf("EFAULT: `request` or `remain` specified an invalid address.\n");
                break;
            case EINTR:
                printf("EINTR: The sleep was interrupted by a signal handler.\n");
                break;
            case EINVAL:
                printf("EINVAL: The value in the `tv_nsec` field was not in the range 0 to "
                       "999999999 or `tv_sec` was negative.\n");
                break;
            case ENOTSUP:
                printf("ENOTSUP: The kernel does not support sleeping against this `clockid`.\n");
                break;
            }

            ts_requested = ts_remaining; // prepare for the next loop iteration
        }
    }

    // =============================================================================================
    printf("Sleeping 1 second using `clock_nanosleep()` with the `TIMER_ABSTIME` flag for "
           "absolute time (sleep until)!\n");
    // See: https://man7.org/linux/man-pages/man2/clock_nanosleep.2.html
    // Using this function with flag `TIMER_ABSTIME` has similarities to `vTaskDelayUntil()` in
    // FreeRTOS!: `https://www.freertos.org/vtaskdelayuntil.html`
    // =============================================================================================
    // > Using an absolute timer is useful for preventing timer drift
    // > problems of the type described in nanosleep(2).  (Such problems
    // > are exacerbated in programs that try to restart a relative sleep
    // > that is repeatedly interrupted by signals.)  To perform a
    // > relative sleep that avoids these problems, call clock_gettime(2)
    // > for the desired clock, add the desired interval to the returned
    // > time value, and then call clock_nanosleep() with the
    // > TIMER_ABSTIME flag.

    // 1. Get the timestamp now, since we will be sleeping with absolute time!
    struct timespec ts_now;
    // See my ans: https://stackoverflow.com/a/67731965/4561887
    retcode = clock_gettime(CLOCK_MONOTONIC, &ts_now);
    if (retcode == -1)
    {
        printf("Failed to obtain timestamp. errno = %i: %s\n", errno,
            strerror(errno));
        exit(EXIT_FAILURE);
    }

    // 2. Add the desired sleep time to the timestamp we just got
    ts_requested.tv_sec = ts_now.tv_sec + 1; // sleep 1 second
    ts_requested.tv_nsec = ts_now.tv_nsec;
    retcode = EINTR; // force to run once
    while (retcode == EINTR)
    {
        retcode = clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &ts_requested, NULL);
        if (retcode != 0)
        {
            printf("`clock_nanosleep()` failed! retcode = %i: ", retcode);
            // See all error codes here: https://man7.org/linux/man-pages/man2/clock_nanosleep.2.html
            switch (retcode)
            {
            case EFAULT:
                printf("EFAULT: `request` or `remain` specified an invalid address.\n");
                break;
            case EINTR:
                printf("EINTR: The sleep was interrupted by a signal handler.\n");
                break;
            case EINVAL:
                printf("EINVAL: The value in the `tv_nsec` field was not in the range 0 to "
                       "999999999 or `tv_sec` was negative.\n");
                break;
            case ENOTSUP:
                printf("ENOTSUP: The kernel does not support sleeping against this `clockid`.\n");
                break;
            }
        }
    }


    return 0;
}

/*
SAMPLE OUTPUT:

In C:

    eRCaGuy_hello_world/c$ gcc -Wall -Wextra -Werror -O3 -std=c17 sleep_nanosleep.c -o bin/a -lm && time bin/a
    Practice sleeping!

    Sleeping 1 second using `nanosleep()` (relative sleep).
    Sleeping 1 second using `clock_nanosleep()` (relative sleep).
    Sleeping 1 second using `clock_nanosleep()` with the `TIMER_ABSTIME` flag for absolute time (sleep until)!

    real    0m3.002s
    user    0m0.000s
    sys 0m0.001s




OR, in C++:




*/
