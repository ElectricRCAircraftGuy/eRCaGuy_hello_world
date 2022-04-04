/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

Try to sleep the SMALLEST time interval possible, and see how it does! How long does it actually
sleep? What's the absolute error, in time? What if I sleep longer times? What's the error?
Test and find out!
---

Answer/result:

If you command it to sleep only **1 ns**, it will sleep on average about **55000 ns**
(**55 us**), with the smallest sleep times being about **10 us** and the largest for this
command being about **500~1000 us**, or **~1 ms**.
This means that about **55000 ns** (**55 us**) is the smallest sleep interval the
system can do! <====== FINAL ANSWER! SMALLEST SLEEP INTERVAL IS ~55 us FOR MY SYSTEM. <======

Commanding sleep times of **100,000 ns** (100 us) results in sleeps of about 157,000 ns (157 us) on
average.

No matter what sleep time you command, sleep time error is consistently around **100,000 ns**
(100 us) on average, and ~500 us worst-case, with ~1000 us (1 ms) being the absolute worst-case.
This is pretty good!

I think getting consistent loop times at 10 Hz (100 ms period) should be super easy, 100 Hz (10 ms
period) easy, and perhaps even 1000 Hz (1 ms period) doable. We shall see. That will be another
test later on.


STATUS: done!

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# 1. In C:
gcc -Wall -Wextra -Werror -O3 -std=c17 sleep_nanosleep_minimum_time_interval.c timinglib.c -o bin/a -lm && time bin/a

# 2. In C++
g++ -Wall -Wextra -Werror -O3 -std=c++17 sleep_nanosleep_minimum_time_interval.c timinglib.c -o bin/a && time bin/a
```

References:
1. *****+https://man7.org/linux/man-pages/man2/clock_nanosleep.2.html
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
// `<time.h>`! See: https://man7.org/linux/man-pages/man2/clock_nanosleep.2.html
#define _POSIX_C_SOURCE 200112L

// Local includes
#include "timinglib.h"

// Linux includes

// C includes
#include <errno.h>   // `errno`
#include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`
#include <stdlib.h>  // `exit()`
#include <string.h>  // `strerror(errno)`
#include <time.h>    // `nanosleep()`, `clock_nanosleep()`, etc.


/// Run `NUM_MEASUREMENTS` sleep tests, attempting to sleep `sleep_time_ns` nanoseconds per
/// sleep test. This also prints the results when done.
void run_sleep_tests(uint64_t sleep_time_ns, uint64_t num_measurements)
{
    int retcode;

    // =============================================================================================
    printf("Attempt to sleep %lu ns per `clock_nanosleep()` call, %lu times.\n", sleep_time_ns,
        num_measurements);
    // See: https://man7.org/linux/man-pages/man2/clock_nanosleep.2.html
    // =============================================================================================

    struct timespec ts_requested;
    struct timespec ts_remaining;

    ts_requested.tv_sec = sleep_time_ns / NS_PER_SEC;
    ts_requested.tv_nsec = sleep_time_ns % NS_PER_SEC;
    printf("ts_requested.tv_sec  = %lu\n", ts_requested.tv_sec);
    printf("ts_requested.tv_nsec = %lu\n", ts_requested.tv_nsec);

    // uint64_t time_measurement_array[NUM_MEASUREMENTS];
    uint64_t sum_ns = 0;
    uint64_t min_dt_ns = UINT64_MAX;
    uint64_t max_dt_ns = 0;
    uint64_t failure_cnt = 0;
    for (size_t i = 0; i < num_measurements; i++)
    {
        uint64_t t_start_ns = nanos();
        retcode = clock_nanosleep(CLOCK_MONOTONIC, 0, &ts_requested, &ts_remaining);
        uint64_t t_end_ns = nanos();
        if (retcode != 0)
        {
            failure_cnt++;
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

        uint64_t dt_ns = t_end_ns - t_start_ns; // elapsed time for a single sleep

        // Uncomment to print ALL sleep times!
        // printf("%6lu\n", dt_ns);

        sum_ns += dt_ns;
        if (dt_ns > max_dt_ns)
        {
            max_dt_ns = dt_ns;
        }

        if (dt_ns < min_dt_ns)
        {
            min_dt_ns = dt_ns;
        }
    }

    double avg_dt_ns = (double)sum_ns/num_measurements;
    printf("failure_cnt                                              = %16lu\n", failure_cnt);
    printf("average time required per `clock_nanosleep()` sleep call = %16.3f ns", avg_dt_ns);
    printf(";   error = %9li **us**\n", NS_TO_US((int64_t)sleep_time_ns - (int64_t)avg_dt_ns));
    printf("minimum time for a `clock_nanosleep()` sleep call        = %16lu ns", min_dt_ns);
    printf(";   error = %9li **us**\n", NS_TO_US((int64_t)sleep_time_ns - (int64_t)min_dt_ns));
    printf("maximum time for a `clock_nanosleep()` sleep call        = %16lu ns", max_dt_ns);
    printf(";   error = %9li **us**\n", NS_TO_US((int64_t)sleep_time_ns - (int64_t)max_dt_ns));
    printf("\n");
}

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    uint64_t t_start_ns = nanos();

    // smallest sleep time possible!
    run_sleep_tests(1, 1000);       // 1 ns

    run_sleep_tests(100, 1000);     //       100 ns =    0.100 us
    run_sleep_tests(1000, 1000);    //     1,000 ns =    1     us
    run_sleep_tests(10000, 1000);   //    10,000 ns =   10     us
    run_sleep_tests(100000, 1000);  //   100,000 ns =  100     us = 0.1 ms
    run_sleep_tests(1000000, 1000); // 1,000,000 ns = 1000     us = 1 ms

    run_sleep_tests(1000000003, 2); // 1 second and 3 ns, twice
    run_sleep_tests(100000000, 10); // 0.1 seconds (100 ms), ten times


    uint64_t t_end_ns = nanos();
    printf("Total program run time = %.9f sec.\n", NS_TO_SEC((double)t_end_ns - t_start_ns));

    return 0;
}

/*
SAMPLE OUTPUT:

In C:

    eRCaGuy_hello_world/c$ gcc -Wall -Wextra -Werror -O3 -std=c17 sleep_nanosleep_minimum_time_interval.c timinglib.c -o bin/a -lm && time bin/a
    Attempt to sleep 1 ns per `clock_nanosleep()` call, 1000 times.
    ts_requested.tv_sec  = 0
    ts_requested.tv_nsec = 1
    failure_cnt                                              =                0
    average time required per `clock_nanosleep()` sleep call =        53675.742 ns;   error =       -53 **us**
    minimum time for a `clock_nanosleep()` sleep call        =            12963 ns;   error =       -12 **us**
    maximum time for a `clock_nanosleep()` sleep call        =            93691 ns;   error =       -93 **us**

    Attempt to sleep 100 ns per `clock_nanosleep()` call, 1000 times.
    ts_requested.tv_sec  = 0
    ts_requested.tv_nsec = 100
    failure_cnt                                              =                0
    average time required per `clock_nanosleep()` sleep call =        57645.493 ns;   error =       -57 **us**
    minimum time for a `clock_nanosleep()` sleep call        =            28682 ns;   error =       -28 **us**
    maximum time for a `clock_nanosleep()` sleep call        =           157062 ns;   error =      -156 **us**

    Attempt to sleep 1000 ns per `clock_nanosleep()` call, 1000 times.
    ts_requested.tv_sec  = 0
    ts_requested.tv_nsec = 1000
    failure_cnt                                              =                0
    average time required per `clock_nanosleep()` sleep call =        61224.712 ns;   error =       -60 **us**
    minimum time for a `clock_nanosleep()` sleep call        =            17492 ns;   error =       -16 **us**
    maximum time for a `clock_nanosleep()` sleep call        =           560359 ns;   error =      -559 **us**

    Attempt to sleep 10000 ns per `clock_nanosleep()` call, 1000 times.
    ts_requested.tv_sec  = 0
    ts_requested.tv_nsec = 10000
    failure_cnt                                              =                0
    average time required per `clock_nanosleep()` sleep call =        72386.553 ns;   error =       -62 **us**
    minimum time for a `clock_nanosleep()` sleep call        =            22643 ns;   error =       -12 **us**
    maximum time for a `clock_nanosleep()` sleep call        =           988789 ns;   error =      -978 **us**

    Attempt to sleep 100000 ns per `clock_nanosleep()` call, 1000 times.
    ts_requested.tv_sec  = 0
    ts_requested.tv_nsec = 100000
    failure_cnt                                              =                0
    average time required per `clock_nanosleep()` sleep call =       163173.417 ns;   error =       -63 **us**
    minimum time for a `clock_nanosleep()` sleep call        =           130761 ns;   error =       -30 **us**
    maximum time for a `clock_nanosleep()` sleep call        =           296215 ns;   error =      -196 **us**

    Attempt to sleep 1000000 ns per `clock_nanosleep()` call, 1000 times.
    ts_requested.tv_sec  = 0
    ts_requested.tv_nsec = 1000000
    failure_cnt                                              =                0
    average time required per `clock_nanosleep()` sleep call =      1124105.694 ns;   error =      -124 **us**
    minimum time for a `clock_nanosleep()` sleep call        =          1037005 ns;   error =       -37 **us**
    maximum time for a `clock_nanosleep()` sleep call        =          1273952 ns;   error =      -273 **us**

    Attempt to sleep 1000000003 ns per `clock_nanosleep()` call, 2 times.
    ts_requested.tv_sec  = 1
    ts_requested.tv_nsec = 3
    failure_cnt                                              =                0
    average time required per `clock_nanosleep()` sleep call =   1000224763.500 ns;   error =      -224 **us**
    minimum time for a `clock_nanosleep()` sleep call        =       1000166579 ns;   error =      -166 **us**
    maximum time for a `clock_nanosleep()` sleep call        =       1000282948 ns;   error =      -282 **us**

    Attempt to sleep 100000000 ns per `clock_nanosleep()` call, 10 times.
    ts_requested.tv_sec  = 0
    ts_requested.tv_nsec = 100000000
    failure_cnt                                              =                0
    average time required per `clock_nanosleep()` sleep call =    100182029.500 ns;   error =      -182 **us**
    minimum time for a `clock_nanosleep()` sleep call        =        100082942 ns;   error =       -82 **us**
    maximum time for a `clock_nanosleep()` sleep call        =        100375405 ns;   error =      -375 **us**

    Total program run time = 4.536036879 sec.

    real    0m4.537s
    user    0m0.010s
    sys 0m0.049s




OR, in C++:




*/
