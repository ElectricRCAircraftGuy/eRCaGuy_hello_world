/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

This is a basic timing and timestamp library.

TODO: add:
1. sleep_ms(), sleep_us(), sleep_ns()
1. sleep_until_ms(), sleep_until_us(), sleep_until_ns()
    1. Similar to: https://www.freertos.org/vtaskdelayuntil.html

STATUS: works!

To compile and run:
- See a file which includes this header file, as an example.

References:
1. *****+[MY ANSWER] Get a timestamp in C in microseconds? - https://stackoverflow.com/a/67731965/4561887
1. Example "delay until" timing code to look at: https://www.freertos.org/vtaskdelayuntil.html

*/

#pragma once

#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.


/// Get the number of elements in any C array
/// - Usage example: [my own answer]:
///   https://arduino.stackexchange.com/questions/80236/initializing-array-of-structs/80289#80289
#define ARRAY_LEN(array) (sizeof(array) / sizeof(array[0]))

/// Convert seconds to milliseconds
#define SEC_TO_MS(sec) ((sec)*1000)
/// Convert seconds to microseconds
#define SEC_TO_US(sec) ((sec)*1000000)
/// Convert seconds to nanoseconds
#define SEC_TO_NS(sec) ((sec)*1000000000)

/// Convert nanoseconds to seconds
#define NS_TO_SEC(ns)   ((ns)/1000000000)
/// Convert nanoseconds to milliseconds
#define NS_TO_MS(ns)    ((ns)/1000000)
/// Convert nanoseconds to microseconds
#define NS_TO_US(ns)    ((ns)/1000)


/// Get a time stamp in milliseconds.
uint64_t millis();

/// Get a time stamp in microseconds.
uint64_t micros();

/// Get a time stamp in nanoseconds.
uint64_t nanos();

/// Obtain an estimate, in nanoseconds, of the resolution of the underlying clock used to obtain all
/// of the timestamps above. This estimate is determined empirically through testing.
uint64_t get_estimated_resolution();

/// Obtain the specified resolution, as returned by `clock_getres()`. See:
/// https://linux.die.net/man/3/clock_gettime. Works properly only if `USE_CLOCK_GETTIME` is
/// defined in the .c file.
uint64_t get_specified_resolution();
