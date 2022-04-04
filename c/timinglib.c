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
