/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

See the .h file for details.

References:
1. MY ANSWER WITH THIS CODE: Get a timestamp in C in microseconds? -
   https://stackoverflow.com/a/67731965/4561887
1. <time.h> header: https://en.cppreference.com/w/c/chrono
1. https://en.cppreference.com/w/c/chrono/timespec_get
1. https://linux.die.net/man/3/clock_gettime
1. *****+https://man7.org/linux/man-pages/man3/clock_gettime.3.html
    1. Shows the requirement for "_POSIX_C_SOURCE >= 199309L" in order to obtain
       access to these functions!: `clock_getres()`, `clock_gettime()`, `clock_settime()`.
    1. See definitions for all of the clock types here, too, such as `CLOCK_REALTIME`,
       `CLOCK_MONOTONIC`, `CLOCK_MONOTONIC_RAW`, etc.

*/


/// Comment this define out to use the C `timespec_get()` instead of the better Linux and POSIX
/// `clock_gettime()`.
/// Note: `clock_gettime()` (see references above) is better that `timespec_get()`. However,
/// `clock_gettime()` is only available on Linux and POSIX systems, whereas `timespec_get()` is a
/// generic C function.
#define USE_CLOCK_GETTIME

/// The clock to use for underlying timing functions. I recommend `CLOCK_MONOTONIC` or
/// `CLOCK_MONOTONIC_RAW`. For details on the various clock types, see:
/// https://man7.org/linux/man-pages/man3/clock_gettime.3.html.
/// Note that `CLOCK_MONOTONIC_RAW` does NOT work with `clock_nanosleep()`, or else I'd prefer the
/// `CLOCK_MONOTONIC_RAW` clock over the `CLOCK_MONOTONIC` clock.
#define CLOCK_TYPE CLOCK_MONOTONIC

#ifdef USE_CLOCK_GETTIME
    // This line **must** come **before** including <time.h> in order to bring in
    // the POSIX functions such as `clock_gettime()`, `nanosleep()`, etc., from
    // `<time.h>`! See: https://man7.org/linux/man-pages/man2/clock_nanosleep.2.html
    #define _POSIX_C_SOURCE 200112L

    #define GET_TIME(timespec_ptr) clock_gettime(CLOCK_TYPE, (timespec_ptr))
#else
    #define GET_TIME(timespec_ptr) timespec_get((timespec_ptr), TIME_UTC)
#endif

// Local includes
#include "timinglib.h"

// Linux includes

// C includes
#include <errno.h>  // `errno`
#include <stdint.h> // `UINT64_MAX`
#include <stdio.h>  // `printf()`
#include <string.h> // `strerror(errno)`
#include <time.h>   // `clock_gettime()` and `timespec_get()`


uint64_t millis()
{
    struct timespec ts;
    GET_TIME(&ts);
    uint64_t ms = SEC_TO_MS((uint64_t)ts.tv_sec) + NS_TO_MS((uint64_t)ts.tv_nsec);
    return ms;
}

uint64_t micros()
{
    struct timespec ts;
    GET_TIME(&ts);
    uint64_t us = SEC_TO_US((uint64_t)ts.tv_sec) + NS_TO_US((uint64_t)ts.tv_nsec);
    return us;
}

uint64_t nanos()
{
    struct timespec ts;
    GET_TIME(&ts);
    uint64_t ns = SEC_TO_NS((uint64_t)ts.tv_sec) + (uint64_t)ts.tv_nsec;
    return ns;
}

uint64_t get_estimated_resolution()
{
    // Obtain a bunch of measurements as fast as possible, then let's see the gap between them.

    // Note: for a large linux computer, 10000 produces really consistent results. To be fast,
    // however, even **10** produces fine results. So, use whatever number you want here between
    // about 10 and 1 Million.
    #define NUM_MEASUREMENTS 1000
    // statically allocate this array to keep this memory off both the stack and the heap, so that
    // it can be HUGE if I want (ex: 100 Million elements--which takes about 2 seconds)! Otherwise,
    // I'm limited to ~8 MB on the stack--see my answer here:
    // https://stackoverflow.com/a/64085509/4561887
    static struct timespec ts_array[NUM_MEASUREMENTS];

    // rapidly obtain back-to-back timestamps
    for (size_t i = 0; i < ARRAY_LEN(ts_array); i++)
    {
        GET_TIME(&ts_array[i]);
    }

    // Obtain an array of all of the time differences: delta time array, in nanosecond time deltas
    // uint64_t dt_array_ns[NUM_MEASUREMENTS];
    uint64_t t_old_ns = SEC_TO_NS((uint64_t)ts_array[0].tv_sec) + (uint64_t)ts_array[0].tv_nsec;
    uint64_t min_dt_ns = UINT64_MAX;
    for (size_t i = 0; i < ARRAY_LEN(ts_array); i++)
    {
        uint64_t t_new_ns = SEC_TO_NS((uint64_t)ts_array[i].tv_sec) + (uint64_t)ts_array[i].tv_nsec;
        // dt = delta time
        uint64_t dt_ns = t_new_ns - t_old_ns;
        t_old_ns = t_new_ns;
        // dt_array_ns[i] = dt_ns;

        // debugging; result: mostly ~23~24 ns; occasionally ~1000 ns (1 us)
        // printf("%lu ns\n", dt_ns);

        if (dt_ns > 0 && dt_ns < min_dt_ns)
        {
            min_dt_ns = dt_ns;
        }
    }

    return min_dt_ns;
}

uint64_t get_specified_resolution()
{
    uint64_t resolution_ns;

#ifndef USE_CLOCK_GETTIME
    resolution_ns = UINT64_MAX - 1;
    return resolution_ns;
#endif

    struct timespec ts;
    int retcode = clock_getres(CLOCK_TYPE, &ts);
    if (retcode == -1)
    {
        printf("Failed to get resolution. errno = %i: %s\n", errno, strerror(errno));
        resolution_ns = UINT64_MAX;
    }
    else
    {
        resolution_ns = SEC_TO_NS((uint64_t)ts.tv_sec) + (uint64_t)ts.tv_nsec;
    }

    return resolution_ns;
}

void sleep_ms(uint64_t sleep_time_ms)
{
    sleep_ns(MS_TO_NS(sleep_time_ms));
}

void sleep_us(uint64_t sleep_time_us)
{
    sleep_ns(US_TO_NS(sleep_time_us));
}

static void print_nanosleep_failed(int return_code)
{
    printf("`clock_nanosleep()` failed! return_code = %i: ", return_code);
    // See all error codes here:
    // https://man7.org/linux/man-pages/man2/clock_nanosleep.2.html
    switch (return_code)
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

void sleep_ns(uint64_t sleep_time_ns)
{
    // See "sleep_nanosleep.c" and "sleep_nanosleep_minimum_time_interval.c" for sleep examples.

    struct timespec ts_requested;
    struct timespec ts_remaining;

    ts_requested.tv_sec = sleep_time_ns / NS_PER_SEC;
    ts_requested.tv_nsec = sleep_time_ns % NS_PER_SEC;

    // If the sleep is interrupted, it may take a couple attempts to sleep the full
    // amount--hence the while loop.
    int retcode = EINTR; // force to run once
    while (retcode == EINTR)
    {
        retcode = clock_nanosleep(CLOCK_TYPE, 0, &ts_requested, &ts_remaining);
        if (retcode != 0)
        {
            print_nanosleep_failed(retcode);
            ts_requested = ts_remaining; // prepare for the next loop iteration
        }
    }
}

void sleep_until_ms(uint64_t * previous_wake_time_ms, uint64_t period_ms)
{
    if (previous_wake_time_ms == NULL)
    {
        printf("ERROR: NULL ptr.\n");
        return;
    }

    uint64_t previous_wake_time_ns = MS_TO_NS(*previous_wake_time_ms);
    uint64_t period_ns = MS_TO_NS(period_ms);

    sleep_until_ns(&previous_wake_time_ns, period_ns);
    *previous_wake_time_ms = NS_TO_MS(previous_wake_time_ns);
}

void sleep_until_us(uint64_t * previous_wake_time_us, uint64_t period_us)
{
    if (previous_wake_time_us == NULL)
    {
        printf("ERROR: NULL ptr.\n");
        return;
    }

    uint64_t previous_wake_time_ns = US_TO_NS(*previous_wake_time_us);
    uint64_t period_ns = US_TO_NS(period_us);

    sleep_until_ns(&previous_wake_time_ns, period_ns);
    *previous_wake_time_us = NS_TO_US(previous_wake_time_ns);
}

void sleep_until_ns(uint64_t * previous_wake_time_ns, uint64_t period_ns)
{
    // See "sleep_nanosleep.c" and "sleep_nanosleep_minimum_time_interval.c" for sleep examples.

    if (previous_wake_time_ns == NULL)
    {
        printf("ERROR: NULL ptr.\n");
        return;
    }

    // Generate an absolute timestamp at a future point in time, at which point we want to
    // wake up after sleeping.
    uint64_t time_wakeup_ns = *previous_wake_time_ns + period_ns;
    *previous_wake_time_ns = time_wakeup_ns; // update the user's input variable
    const struct timespec TS_WAKEUP =
    {
        .tv_sec = (__time_t)(time_wakeup_ns / NS_PER_SEC),
        .tv_nsec = (__syscall_slong_t)(time_wakeup_ns % NS_PER_SEC),
    };

    // If the sleep is interrupted, it may take a couple attempts to sleep the full
    // amount--hence the while loop.
    int retcode = EINTR; // force to run once
    while (retcode == EINTR)
    {
        retcode = clock_nanosleep(CLOCK_TYPE, TIMER_ABSTIME, &TS_WAKEUP, NULL);
        if (retcode != 0)
        {
            print_nanosleep_failed(retcode);
        }
    }
}
