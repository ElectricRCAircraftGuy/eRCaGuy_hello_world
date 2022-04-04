/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

See the .h file for details.

References:
1. <time.h> header: https://en.cppreference.com/w/c/chrono
1. https://en.cppreference.com/w/c/chrono/timespec_get

*/

// Local includes
#include "timinglib.h"

// Linux includes

// C includes
#include <stdint.h>
#include <stdio.h>   // For `printf()`
#include <time.h>


uint64_t millis()
{
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    uint64_t ms = SEC_TO_MS((uint64_t)ts.tv_sec) + NS_TO_MS((uint64_t)ts.tv_nsec);
    return ms;
}

uint64_t micros()
{
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    uint64_t us = SEC_TO_US((uint64_t)ts.tv_sec) + NS_TO_US((uint64_t)ts.tv_nsec);
    return us;
}

uint64_t nanos()
{
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    uint64_t ns = SEC_TO_NS((uint64_t)ts.tv_sec) + (uint64_t)ts.tv_nsec;
    return ns;
}

uint64_t get_resolution()
{
    // Obtain a bunch of measurements as fast as possible, then let's see the gap between them.

    // Note: for a large linux computer, 10000 produces really consistent results. To be fast,
    // however, even **10** produces fine results.
    #define NUM_MEASUREMENTS 10
    // statically allocate this array to keep this memory off both the stack and the heap, so that
    // it can be HUGE if I want (ex: 100 Million elements--which takes about 2 seconds)! Otherwise,
    // I'm limited to ~8 MB on the stack--see my answer here:
    // https://stackoverflow.com/a/64085509/4561887
    static struct timespec ts_array[NUM_MEASUREMENTS];

    // rapidly obtain back-to-back timestamps
    for (size_t i = 0; i < ARRAY_LEN(ts_array); i++)
    {
        timespec_get(&ts_array[i], TIME_UTC);
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
