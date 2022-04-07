/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

This is a basic timing and timestamp library for Linux / POSIX systems.

TODO: add:
1. [x] sleep_ms(), sleep_us(), sleep_ns()
1. [x] sleep_until_ms(), sleep_until_us(), sleep_until_ns()
    1. Similar to: https://www.freertos.org/vtaskdelayuntil.html

STATUS: works!

To compile and run:
- See a file which includes this header file, as an example.

References:
1. *****+[MY ANSWER] Get a timestamp in C in microseconds? - https://stackoverflow.com/a/67731965/4561887
1. Example "delay until" timing code to look at: https://www.freertos.org/vtaskdelayuntil.html

*/

#pragma once

#include <assert.h>
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.


/// Get the number of elements in any C array
/// - Usage example: [my own answer]:
///   https://arduino.stackexchange.com/questions/80236/initializing-array-of-structs/80289#80289
#define ARRAY_LEN(array) (sizeof(array) / sizeof(array[0]))

static_assert(sizeof(long) == sizeof(int64_t), "`L` should indicate `long` and "
    "be equal to `int64_t` for your system. If not, update the `L`s below to `LL` or whatever "
    "you need so that those constants are the same type and size as `int64_t`, as I want them "
    "to be.");

#define MS_PER_SEC (1000L)
#define US_PER_SEC (1000000L)
#define NS_PER_SEC (1000000000L)

#define NS_PER_MS (1000000L)
#define NS_PER_US (1000L)

/// Convert seconds to milliseconds
#define SEC_TO_MS(sec) ((sec)*MS_PER_SEC)
/// Convert seconds to microseconds
#define SEC_TO_US(sec) ((sec)*US_PER_SEC)
/// Convert seconds to nanoseconds
#define SEC_TO_NS(sec) ((sec)*NS_PER_SEC)

/// Convert nanoseconds to seconds
#define NS_TO_SEC(ns)   ((ns)/NS_PER_SEC)
/// Convert nanoseconds to milliseconds
#define NS_TO_MS(ns)    ((ns)/NS_PER_MS)
/// Convert nanoseconds to microseconds
#define NS_TO_US(ns)    ((ns)/NS_PER_US)

/// Convert milliseconds to nanoseconds
#define MS_TO_NS(ms)    ((ms)*NS_PER_MS)
/// Convert microseconds to nanoseconds
#define US_TO_NS(us)    ((us)*NS_PER_US)

/// Convert microseconds to seconds
#define US_TO_SEC(us)   ((us)/US_PER_SEC)
/// Convert milliseconds to seconds
#define MS_TO_SEC(ms)   ((ms)/MS_PER_SEC)


/// Get a monotonic time stamp in milliseconds.
uint64_t millis();

/// Get a monotonic time stamp in microseconds.
uint64_t micros();

/// Get a monotonic time stamp in nanoseconds.
uint64_t nanos();

/// Obtain an estimate, in nanoseconds, of the resolution of the underlying clock used to obtain all
/// of the timestamps above. This estimate is determined empirically through testing.
/// - Testing on my x86-64 Linux Ubuntu system shows my estimated timestamp resolution to be
///   ~15~30 ns. Run your own tests via "timinglib_get_resolution.c".
uint64_t get_estimated_resolution();

/// Obtain the specified resolution, as returned by `clock_getres()`. See:
/// https://linux.die.net/man/3/clock_gettime. Works properly only if `USE_CLOCK_GETTIME` is
/// defined in the .c file.
/// - Testing on my x86-64 Linux Ubuntu system returns 1 ns. Run you rown tests via
///   "timinglib_get_resolution.c".
uint64_t get_specified_resolution();


/// Sleep for `sleep_time_ms` milliseconds.
/// - Testing on my x86-64 Linux Ubuntu system via "sleep_nanosleep_minimum_time_interval.c"
///   shows that my system has a minimum sleep resolution of ~55000 ns (< 1 ms), so any ms sleep
///   value is acceptable.
void sleep_ms(uint64_t sleep_time_ms);

/// Sleep for `sleep_time_us` microseconds.
/// - Testing on my x86-64 Linux Ubuntu system via "sleep_nanosleep_minimum_time_interval.c"
///   shows that my system has a minimum sleep resolution of ~55000 ns (55 us), so any us sleep
///   value > 0 and < 55 us will sleep about 55 us.
void sleep_us(uint64_t sleep_time_us);

/// Sleep for `sleep_time_ns` nanoseconds.
/// - Testing on my x86-64 Linux Ubuntu system via "sleep_nanosleep_minimum_time_interval.c"
///   shows that my system has a minimum sleep resolution of ~55000 ns, so any ns sleep
///   value > 0 and < ~55000 ns will sleep about 55000 ns on average.
void sleep_ns(uint64_t sleep_time_ns);


// For precision loop interval timing in order to force a periodic loop or task to run at a desired
// period or frequency, use the following functions. They work just like the FreeRTOS
// function "vTaskDelayUntil()", described here: https://www.freertos.org/vtaskdelayuntil.html.
//
// Example usage:
//
//      // Perform an action at 100 Hz (every 10 ms).
//      // - Start `pthread_task` as its own thread, using a library such as
//      //   `pthread` (POSIX threads).
//      void * pthread_task(void * arguments)
//      {
//          const uint64_t PERIOD_MS = 10; // 100 Hz
//          // Seed the last wake time with the current time.
//          uint64_t last_wake_time_ms = millis();
//
//          while (true)
//          {
//              // Wait for the next cycle.
//              sleep_until_ms(&last_wake_time_ms, PERIOD_MS);
//
//              // Perform whatever action you want here at this fixed interval.
//          }
//      }

/// Sleep (delay) until the absolute timestamp of `previous_wake_time_ms` + `period_ms`, in
/// milliseconds, has been reached.
/// - This works just like FreeRTOS's `vTaskDelayUntil()` function:
///   https://www.freertos.org/vtaskdelayuntil.html
/// - `previous_wake_time_ms` is an in/out parameter, and will be read and then modified by the
///   function.
void sleep_until_ms(uint64_t * previous_wake_time_ms, uint64_t period_ms);

/// Sleep (delay) until the absolute timestamp of `previous_wake_time_us` + `period_us`, in
/// microseconds, has been reached.
/// - This works just like FreeRTOS's `vTaskDelayUntil()` function:
///   https://www.freertos.org/vtaskdelayuntil.html
/// - `previous_wake_time_ms` is an in/out parameter, and will be read and then modified by the
///   function.
void sleep_until_us(uint64_t * previous_wake_time_us, uint64_t period_us);

/// Sleep (delay) until the absolute timestamp of `previous_wake_time_ns` + `period_ns`, in
/// nanoseconds, has been reached.
/// - This works just like FreeRTOS's `vTaskDelayUntil()` function:
///   https://www.freertos.org/vtaskdelayuntil.html
/// - `previous_wake_time_ms` is an in/out parameter, and will be read and then modified by the
///   function.
void sleep_until_ns(uint64_t * previous_wake_time_ns, uint64_t period_ns);


// Real-time scheduler settings
// See `set_scheduler()` in "sleep_nanosleep_minimum_time_interval.c"

/// The lowest soft real-time scheduler priority which can be set.
/// Note: for `SCHED_FIFO` and `SCHED_RR`. See:
/// https://man7.org/linux/man-pages/man7/sched.7.html
#define REALTIME_SCHEDULER_PRIORITY_LOWEST  1
/// The highest soft real-time scheduler priority which can be set.
#define REALTIME_SCHEDULER_PRIORITY_HIGHEST 99

// Call this function to turn ON the Linux soft realtime scheduler for the
// calling thread, in order to get minimum sleep intervals and resolution of
// ~4 us with worst-case results being 100~400 us (0.1~0.4 ms), rather than the
// default minimum sleep time of ~55 us with worst-case results being ~8000 us
// (8 ms)! Calling this function allows for much better sleep resolutions and
// timing accuracies than the default `SCHED_OTHER` scheduler can provide!
void use_realtime_scheduler();
