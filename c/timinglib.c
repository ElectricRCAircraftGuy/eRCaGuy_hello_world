/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

See the .h file for details.

References:
1. <time.h> header: https://en.cppreference.com/w/c/chrono
1. https://en.cppreference.com/w/c/chrono/timespec_get
1. https://linux.die.net/man/3/clock_gettime

*/

// Local includes
#include "timinglib.h"

// Linux includes

// C includes
#include <errno.h>
#include <stdint.h>
#include <stdio.h>   // For `printf()`
#include <string.h>  // `strerror(errno)`
#include <time.h>

/// Comment this define out to use the C `timespec_get()` instead of the better Linux and POSIX
/// `clock_gettime()`.
/// Note: `clock_gettime()` (see references above) is better that `timespec_get()`. However,
/// `clock_gettime()` is only available on Linux and POSIX systems, whereas `timespec_get()` is a
/// generic C function.
#define USE_CLOCK_GETTIME

#ifdef USE_CLOCK_GETTIME
    #define GET_TIME(timespec_ptr) clock_gettime(CLOCK_MONOTONIC, (timespec_ptr))
#else
    #define GET_TIME(timespec_ptr) timespec_get((timespec_ptr), TIME_UTC)
#endif


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
    // however, even **10** produces fine results.
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
    int retcode = clock_getres(CLOCK_MONOTONIC, &ts);
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
