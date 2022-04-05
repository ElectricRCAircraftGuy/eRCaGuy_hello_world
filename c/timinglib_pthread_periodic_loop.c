/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

Show how to use the timinglib "sleep until" functions in a pthread (POSIX thread) thread. Let's run
the loop really fast (ex: 100 Hz ~ 1000 Hz), and analyze the time errors!

STATUS: works!

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# 1. In C:
gcc -Wall -Wextra -Werror -O3 -std=c17 timinglib_pthread_periodic_loop.c timinglib.c -o bin/a -pthread && time bin/a

# 2. In C++
g++ -Wall -Wextra -Werror -O3 -std=c++17 timinglib_pthread_periodic_loop.c timinglib.c -o bin/a -pthread && time bin/a
```

References:
1. https://linux.die.net/man/3/pthread_create
1. https://man7.org/linux/man-pages/man3/pthread_create.3.html
1. https://linux.die.net/man/3/pthread_join

*/


// Local includes
#include "timinglib.h"

// Linux includes
#include <pthread.h>

// C includes
#include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`

#define NUM_ITERATIONS 100

// TODO: consider passing in the period to the `pthread_task()` function, and spawning multiple
// threads at once.

// Perform an action at the period specified by `PERIOD_MS` below.
// - Start `pthread_task` as its own thread, using a library such as
//   `pthread` (POSIX threads).
void * pthread_task(void * argument)
{
    const char* thread_name = (const char*)argument;
    printf("thread_name = %s\n", thread_name);

    const uint64_t PERIOD_MS = 10; // 10 ms --> 100 Hz; 1 ms --> 1000 Hz
    // Seed the last wake time with the current time.
    uint64_t last_wake_time_ms = millis();

    // while (true)
    uint64_t t_start_ns = nanos();
    int64_t time_error_sum_us = 0;
    int64_t time_error_min_us = INT64_MAX;
    int64_t time_error_max_us = INT64_MIN;
    for (size_t i = 0; i < NUM_ITERATIONS; i++)
    {
        // Wait for the next cycle.
        sleep_until_ms(&last_wake_time_ms, PERIOD_MS);

        // -----------------------------------------------------------------------------------------
        // Perform whatever action you want here at this fixed interval.
        // -----------------------------------------------------------------------------------------

        uint64_t t_end_ns = nanos();
        uint64_t dt_ns = t_end_ns - t_start_ns;
        t_start_ns = t_end_ns;

        int64_t time_period_error_us = NS_TO_US(MS_TO_NS((int64_t)PERIOD_MS) - (int64_t)dt_ns);
        printf("%4zu: dt_ns = %9lu ns;  error = %6li **us**\n", i, dt_ns, time_period_error_us);

        // gather statistics on the time interval error;

        // // reject the first iteration from the stats, however, since it has extra error!
        // if (i == 0)
        // {
        //     continue;
        // }

        time_error_sum_us += time_period_error_us;

        if (time_period_error_us > time_error_max_us)
        {
            time_error_max_us = time_period_error_us;
        }

        if (time_period_error_us < time_error_min_us)
        {
            time_error_min_us = time_period_error_us;
        }
    }

    printf("\n");
    double time_error_avg_us = (double)time_error_sum_us/(NUM_ITERATIONS);
    printf("average time error per iteration = %8.3f us\n", time_error_avg_us);
    printf("minimum time error per iteration = %4li us\n", time_error_min_us);
    printf("maximum time error per iteration = %4li us\n", time_error_max_us);

    return (void*)"Done!";
}

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Starting pthread at fixed interval using `sleep_until_ms()`.\n\n");

    pthread_t thread;
    const char thread_name[] = "some thread name"; // this can really be ANY argument
    int retcode = pthread_create(&thread, NULL, pthread_task, (void*)thread_name);
    if (retcode != 0)
    {
        printf("Failed to create pthread. retcode = %i\n", retcode);
    }

    const char * return_message;
    retcode = pthread_join(thread, (void**)&return_message);
    if (retcode != 0)
    {
        printf("Failed to join (terminate) pthread. retcode = %i\n", retcode);
    }

    printf("\nFinal message from thread = %s\n", return_message);

    return 0;
}

/*
SAMPLE OUTPUT:

In C:

    eRCaGuy_hello_world/c$ gcc -Wall -Wextra -Werror -O3 -std=c17 timinglib_pthread_periodic_loop.c timinglib.c -o bin/a -pthread && time bin/a
    Starting pthread at fixed interval using `sleep_until_ms()`.

    thread_name = some thread name
       0: dt_ns =   9735178 ns;  error =    264 **us**
       1: dt_ns =   9998204 ns;  error =      1 **us**
       2: dt_ns =   9992340 ns;  error =      7 **us**
       3: dt_ns =  10021152 ns;  error =    -21 **us**
       4: dt_ns =   9991807 ns;  error =      8 **us**
       5: dt_ns =   9971915 ns;  error =     28 **us**
       6: dt_ns =  10002417 ns;  error =     -2 **us**
       7: dt_ns =  10039566 ns;  error =    -39 **us**
       8: dt_ns =   9984627 ns;  error =     15 **us**
       9: dt_ns =   9960032 ns;  error =     39 **us**
      10: dt_ns =  10010844 ns;  error =    -10 **us**
      11: dt_ns =  10046415 ns;  error =    -46 **us**
      12: dt_ns =   9994367 ns;  error =      5 **us**
      13: dt_ns =   9954111 ns;  error =     45 **us**
      14: dt_ns =  10193405 ns;  error =   -193 **us**
      15: dt_ns =   9827192 ns;  error =    172 **us**
      16: dt_ns =  10054913 ns;  error =    -54 **us**
      17: dt_ns =   9989492 ns;  error =     10 **us**
      18: dt_ns =   9978018 ns;  error =     21 **us**
      19: dt_ns =   9975802 ns;  error =     24 **us**
      20: dt_ns =   9985199 ns;  error =     14 **us**
      21: dt_ns =  10026753 ns;  error =    -26 **us**
      22: dt_ns =  10011507 ns;  error =    -11 **us**
      23: dt_ns =   9941954 ns;  error =     58 **us**
      24: dt_ns =  10054677 ns;  error =    -54 **us**
      25: dt_ns =   9987750 ns;  error =     12 **us**
      26: dt_ns =   9981280 ns;  error =     18 **us**
      27: dt_ns =   9959769 ns;  error =     40 **us**
      28: dt_ns =  10085370 ns;  error =    -85 **us**
      29: dt_ns =   9941678 ns;  error =     58 **us**
      30: dt_ns =  10018696 ns;  error =    -18 **us**
      31: dt_ns =  10050913 ns;  error =    -50 **us**
      32: dt_ns =   9963577 ns;  error =     36 **us**
      33: dt_ns =   9947881 ns;  error =     52 **us**
      34: dt_ns =  10026641 ns;  error =    -26 **us**
      35: dt_ns =  10015025 ns;  error =    -15 **us**
      36: dt_ns =   9979387 ns;  error =     20 **us**
      37: dt_ns =  10003888 ns;  error =     -3 **us**
      38: dt_ns =  10062648 ns;  error =    -62 **us**
      39: dt_ns =   9937151 ns;  error =     62 **us**
      40: dt_ns =  10003258 ns;  error =     -3 **us**
      41: dt_ns =   9998200 ns;  error =      1 **us**
      42: dt_ns =  10028013 ns;  error =    -28 **us**
      43: dt_ns =  10015356 ns;  error =    -15 **us**
      44: dt_ns =   9951117 ns;  error =     48 **us**
      45: dt_ns =  10004421 ns;  error =     -4 **us**
      46: dt_ns =  10004699 ns;  error =     -4 **us**
      47: dt_ns =  10048501 ns;  error =    -48 **us**
      48: dt_ns =   9996144 ns;  error =      3 **us**
      49: dt_ns =   9971288 ns;  error =     28 **us**
      50: dt_ns =  10046959 ns;  error =    -46 **us**
      51: dt_ns =   9966386 ns;  error =     33 **us**
      52: dt_ns =  10021927 ns;  error =    -21 **us**
      53: dt_ns =   9990311 ns;  error =      9 **us**
      54: dt_ns =  10019170 ns;  error =    -19 **us**
      55: dt_ns =   9967757 ns;  error =     32 **us**
      56: dt_ns =  10019455 ns;  error =    -19 **us**
      57: dt_ns =   9995387 ns;  error =      4 **us**
      58: dt_ns =  10006630 ns;  error =     -6 **us**
      59: dt_ns =   9959851 ns;  error =     40 **us**
      60: dt_ns =  10018525 ns;  error =    -18 **us**
      61: dt_ns =  10014423 ns;  error =    -14 **us**
      62: dt_ns =   9960740 ns;  error =     39 **us**
      63: dt_ns =  10069151 ns;  error =    -69 **us**
      64: dt_ns =   9981962 ns;  error =     18 **us**
      65: dt_ns =  10009861 ns;  error =     -9 **us**
      66: dt_ns =   9981098 ns;  error =     18 **us**
      67: dt_ns =   9973102 ns;  error =     26 **us**
      68: dt_ns =  10026926 ns;  error =    -26 **us**
      69: dt_ns =   9967373 ns;  error =     32 **us**
      70: dt_ns =  10029630 ns;  error =    -29 **us**
      71: dt_ns =  10014935 ns;  error =    -14 **us**
      72: dt_ns =  10001636 ns;  error =     -1 **us**
      73: dt_ns =  10013978 ns;  error =    -13 **us**
      74: dt_ns =   9935977 ns;  error =     64 **us**
      75: dt_ns =  10049426 ns;  error =    -49 **us**
      76: dt_ns =   9973107 ns;  error =     26 **us**
      77: dt_ns =   9996319 ns;  error =      3 **us**
      78: dt_ns =  10002237 ns;  error =     -2 **us**
      79: dt_ns =   9988132 ns;  error =     11 **us**
      80: dt_ns =   9980812 ns;  error =     19 **us**
      81: dt_ns =   9986003 ns;  error =     13 **us**
      82: dt_ns =  10069309 ns;  error =    -69 **us**
      83: dt_ns =   9967841 ns;  error =     32 **us**
      84: dt_ns =   9994342 ns;  error =      5 **us**
      85: dt_ns =  10019304 ns;  error =    -19 **us**
      86: dt_ns =   9996140 ns;  error =      3 **us**
      87: dt_ns =   9992928 ns;  error =      7 **us**
      88: dt_ns =  10068364 ns;  error =    -68 **us**
      89: dt_ns =   9896354 ns;  error =    103 **us**
      90: dt_ns =  10086264 ns;  error =    -86 **us**
      91: dt_ns =   9925043 ns;  error =     74 **us**
      92: dt_ns =  10031766 ns;  error =    -31 **us**
      93: dt_ns =  10006041 ns;  error =     -6 **us**
      94: dt_ns =  10005128 ns;  error =     -5 **us**
      95: dt_ns =   9965488 ns;  error =     34 **us**
      96: dt_ns =  10028760 ns;  error =    -28 **us**
      97: dt_ns =   9964485 ns;  error =     35 **us**
      98: dt_ns =  10040938 ns;  error =    -40 **us**
      99: dt_ns =  10015181 ns;  error =    -15 **us**

    average time error per iteration =    2.300 us
    minimum time error per iteration = -193 us
    maximum time error per iteration =  264 us

    Final message from thread = Done!

    real    0m1.001s
    user    0m0.000s
    sys 0m0.007s


OR, in C++:

(same as in C)


*/
