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

TODO:
1. [x] Experiment by commenting out code to see what is making the new_thread
run fast. Which code is making that happen? Demo 5 should be, but appears to
not be working as expected.
    1. Answer: the problem was I needed to call
    `pthread_attr_setinheritsched(&pthread_attr, PTHREAD_EXPLICIT_SCHED);` to
    tell `pthread_create()` to use the scheduler policy and priority set inside
    of `pthread_attr` instead of inheriting those scheduling parameters from the
    calling thread!

To compile and run (assuming you've already `cd`ed into this dir). See:
1. Linux scheduler descriptions: https://man7.org/linux/man-pages/man7/sched.7.html
1. Command-line method for how to set which Linux **policy** (scheduler) and **priority** to use for
   a given command or process: https://askubuntu.com/a/51285/327339

```bash
# 1. In C:

# ALTERNATIVELY, you may change the scheduler which runs this Linux code in the source code below,
# rather than using the `chrt` "change real-time" command at call-time at the command-line.

# With the **regular** `SCHED_OTHER`/`SCHED_NORMAL` "Default Linux time-sharing" scheduler:
# (see: https://man7.org/linux/man-pages/man7/sched.7.html and https://askubuntu.com/a/51285/327339)
gcc -Wall -Wextra -Werror -O3 -std=c17 sleep_nanosleep_minimum_time_interval.c timinglib.c -o bin/a -lm -pthread && time bin/a

# GOOD VERSION TO USE:
# With whatever scheduler is **manually set in the code below** in the function `set_scheduler()`!
# (running the program with `sudo` is required to set the scheduler in the code)
gcc -Wall -Wextra -Werror -O3 -std=c17 sleep_nanosleep_minimum_time_interval.c timinglib.c -o bin/a -lm -pthread && time sudo bin/a

# EASIEST VERSION TO USE:
# With the **soft real-time** `SCHED_RR` "round-robin" scheduler at the **lowest** priority of 1:
# (see: https://man7.org/linux/man-pages/man7/sched.7.html and https://askubuntu.com/a/51285/327339)
# Note: see `chrt` priority ranges for each scheduler with `chrt --max`.
gcc -Wall -Wextra -Werror -O3 -std=c17 sleep_nanosleep_minimum_time_interval.c timinglib.c -o bin/a -lm -pthread && time sudo chrt --rr 1 bin/a

# With the **soft real-time** `SCHED_RR` "round-robin" scheduler at the **highest** priority of 99:
# (see: https://man7.org/linux/man-pages/man7/sched.7.html and https://askubuntu.com/a/51285/327339)
# Note: see `chrt` priority ranges for each scheduler with `chrt --max`.
gcc -Wall -Wextra -Werror -O3 -std=c17 sleep_nanosleep_minimum_time_interval.c timinglib.c -o bin/a -lm -pthread && time sudo chrt --rr 99 bin/a

# With the **soft real-time** `SCHED_FIFO` "first-in first-out" scheduler at the **lowest**
# priority of 1:
# (see: https://man7.org/linux/man-pages/man7/sched.7.html and https://askubuntu.com/a/51285/327339)
# Note: see `chrt` priority ranges for each scheduler with `chrt --max`.
gcc -Wall -Wextra -Werror -O3 -std=c17 sleep_nanosleep_minimum_time_interval.c timinglib.c -o bin/a -lm -pthread && time sudo chrt --fifo 1 bin/a

# With the **soft real-time** `SCHED_FIFO` "first-in first-out" scheduler at the **highest**
# priority of 99:
# (see: https://man7.org/linux/man-pages/man7/sched.7.html and https://askubuntu.com/a/51285/327339)
# Note: see `chrt` priority ranges for each scheduler with `chrt --max`.
gcc -Wall -Wextra -Werror -O3 -std=c17 sleep_nanosleep_minimum_time_interval.c timinglib.c -o bin/a -lm -pthread && time sudo chrt --fifo 99 bin/a


# 2. In C++
# With the **regular** `SCHED_OTHER`/`SCHED_NORMAL` "Default Linux time-sharing" scheduler
g++ -Wall -Wextra -Werror -O3 -std=c++17 sleep_nanosleep_minimum_time_interval.c timinglib.c -o bin/a -pthread && time bin/a
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
1. Linux real-time scheduler options:
    1. Linux scheduler descriptions: https://man7.org/linux/man-pages/man7/sched.7.html
    1. Command-line method for how to set which Linux **policy** (scheduler) and **priority** to use
    for a given command or process: https://askubuntu.com/a/51285/327339
    1. *****https://www.drdobbs.com/soft-real-time-programming-with-linux/184402031?pgno=1
    1. https://man7.org/linux/man-pages/man2/sched_setparam.2.html
1. List of all possible `errno` errors, such as `EPERM`: "error, operation not permitted":
   https://man7.org/linux/man-pages/man3/errno.3.html

*/


// This line **must** come **before** including <time.h> in order to bring in
// the POSIX functions such as `clock_gettime()`, `nanosleep()`, etc., from
// `<time.h>`! See: https://man7.org/linux/man-pages/man2/clock_nanosleep.2.html
#define _POSIX_C_SOURCE 200112L

// Local includes
#include "timinglib.h"

// Linux includes
#include <pthread.h>
#include <sched.h>    // https://man7.org/linux/man-pages/man2/sched_setscheduler.2.html
#include <sys/mman.h> // `mlockall()` https://man7.org/linux/man-pages/man2/mlock.2.html

// C includes
#include <errno.h>   // `errno`
#include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`
#include <stdlib.h>  // `exit()`, `malloc()`
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
    printf("average time required per `clock_nanosleep()` sleep call = %16.0f ns", avg_dt_ns);
    printf(";   error = %9.0f **us**\n", NS_TO_US((double)sleep_time_ns - (double)avg_dt_ns));
    printf("minimum time for a `clock_nanosleep()` sleep call        = %16lu ns", min_dt_ns);
    printf(";   error = %9.0f **us**\n", NS_TO_US((double)sleep_time_ns - (double)min_dt_ns));
    printf("maximum time for a `clock_nanosleep()` sleep call        = %16lu ns", max_dt_ns);
    printf(";   error = %9.0f **us**\n", NS_TO_US((double)sleep_time_ns - (double)max_dt_ns));
    printf("\n");
}

/// A dummy function to be called and run by a new pthread.
void * dummy_pthread_action(void * argument)
{
    const char* thread_name = (const char*)argument;

    printf("===== dummy_pthread_action(): pthread function started "
           "(name = \"%s\"). =====\n", thread_name);

    // Now do a nanosleep just to prove which scheduler is running in this
    // thread. A low average sleep time of ~4 us indicates the soft real-time
    // SCHED_RR round robin scheduler, and a high average sleep time of ~55 us
    // indicates SCHED_OTHER, which is the default **non-real-time**
    // round-robin scheduler!
    run_sleep_tests(1, 10000);

    printf("===== dummy_pthread_action(): pthread function ended. =====\n");

    // Generate a message to return, just for fun.
    const size_t MAX_STR_SIZE = 1024;
    char* return_message = (char*)malloc(MAX_STR_SIZE);
    snprintf(return_message, MAX_STR_SIZE,
        "Thread named \"%s\" completed successfully!", thread_name);
    return (void*)return_message;
}

/// Set the real-time Linux scheduler _policy_ and _priority_ you'd like to use.
// Comment out any demos or code below you don't want to test or use.
void set_scheduler()
{
    int retcode; // return code to check for errors from function calls

    // -------------------------------------------------------------------------
    // Demo 1: use `sched_setscheduler()` to change the current process's
    // scheduler "policy" **and** "priority".
    // See:
    // 1. https://man7.org/linux/man-pages/man2/sched_setscheduler.2.html
    // 1. All `errno` errors: https://man7.org/linux/man-pages/man3/errno.3.html
    // 1. `mlockall()`: https://man7.org/linux/man-pages/man2/mlock.2.html
    // 1. *****https://www.drdobbs.com/soft-real-time-programming-with-linux/184402031?pgno=1
    // -------------------------------------------------------------------------
    {
        const struct sched_param priority_param =
        {
            // the priority must be from 1 (lowest priority) to 99
            // (highest priority) for the `SCHED_FIFO` AND `SCHED_RR`
            // (round robin) scheduler policies; see:
            // https://man7.org/linux/man-pages/man7/sched.7.html
            .sched_priority = 1,
        };

        // Note: use `0` as the `pid` (1st param) to indicate the PID of this
        // running process
        retcode = sched_setscheduler(0, SCHED_RR, &priority_param);
        if (retcode == -1)
        {
            printf("ERROR: in file %s: %i: Failed to set scheduler. "
                   "errno = %i: %s.\n",
                __FILE__, __LINE__, errno, strerror(errno));
            if (errno == EPERM)  // Error: Permissions
            {
                printf("  You must use `sudo` or run this program as root to "
                       "have proper privileges!\n");
            }
        }
        else
        {
            printf("`sched_setscheduler()` successful.\n");
        }

        // Memory lock: also lock the memory into RAM so that the kernel is NOT
        // allowed to move it into the swap space, which would otherwise be a
        // slow operation and break the "real-time" characteristics of this
        // process.
        // See:
        // 1. https://man7.org/linux/man-pages/man2/mlock.2.html
        // 1. This tutorial/blog post:
        //    https://www.drdobbs.com/soft-real-time-programming-with-linux/184402031?pgno=1
        retcode = mlockall(MCL_CURRENT | MCL_FUTURE | MCL_ONFAULT);
        if (retcode == -1)
        {
            printf("ERROR: in file %s: %i: Failed to lock memory into RAM. "
                   "errno = %i: %s.\n",
                __FILE__, __LINE__, errno, strerror(errno));
            if (errno == EPERM)  // Error: Permissions
            {
                printf("  You must use `sudo` or run this program as root to "
                       "have proper privileges!\n");
            }
        }
        else
        {
            printf("`mlockall()` successful.\n");
        }
    } // end of Demo 1

    // -------------------------------------------------------------------------
    // Demo 2: use `sched_setparam()` to change **only** the "priority" of the
    // running process.
    // See:
    // 1. https://man7.org/linux/man-pages/man2/sched_setparam.2.html
    // 1. https://www.drdobbs.com/soft-real-time-programming-with-linux/184402031?pgno=1
    //      1. "Listing 1" demo code: this code shows how to raise a child
    //      priority, lower a child priority, and raise a priority in order to
    //      obtain a mutex lock which otherwise it would never be able to
    //      obtain if a higher-priority process has it:
    //      https://www.drdobbs.com/soft-real-time-programming-with-linux/184402031?pgno=2
    // -------------------------------------------------------------------------
    {
        const int new_priority = 2;
        const struct sched_param priority_param =
        {
            // the priority must be from 1 (lowest priority) to 99
            // (highest priority) for the `SCHED_FIFO` AND `SCHED_RR`
            // (round robin) scheduler policies; see:
            // https://man7.org/linux/man-pages/man7/sched.7.html
            .sched_priority = new_priority,
        };
        // Note: use `0` as the `pid` (1st param) to indicate the PID of this
        // running process
        retcode = sched_setparam(0, &priority_param);
        if (retcode == -1)
        {
            printf("ERROR: in file %s: %i: Failed to set priority. "
                   "errno = %i: %s.\n",
                __FILE__, __LINE__, errno, strerror(errno));
            // NB: through testing, it seems that `errno` gets set to 22
            // (EINVAL), if `sudo` is not used to run this code. That seems
            // like a compiler bug, because it should be `EPERM`, but let's
            // just handle it as though it was `EPERM`.
            if (errno == EPERM || errno == EINVAL)  // Error: Permissions
            {
                printf("  You must use `sudo` or run this program as root to "
                       "have proper privileges!\n");
            }
        }
        else
        {
            printf("`sched_setparam()` successful.\n");
        }
    } // end of Demo 2

    // -------------------------------------------------------------------------
    // [THIS IS MY PREFERRED TECHNIQUE FOR GENERAL USE]  <==================
    // Demo 3 (the pthread version of Demo 1): if using pthreads: use
    // `pthread_setschedparam()` to change the current thread's scheduler
    // "policy" and "priority".
    // See:
    // 1. https://man7.org/linux/man-pages/man3/pthread_setschedparam.3.html
    // 1. https://man7.org/linux/man-pages/man3/pthread_self.3.html
    // 1. https://www.drdobbs.com/soft-real-time-programming-with-linux/184402031?pgno=1
    // 1. https://askubuntu.com/a/1129915/327339
    // -------------------------------------------------------------------------
    {
        pthread_t this_thread = pthread_self();
        const struct sched_param priority_param =
        {
            // the priority must be from 1 (lowest priority) to 99
            // (highest priority) for the `SCHED_FIFO` AND `SCHED_RR`
            // (round robin) scheduler policies; see:
            // https://man7.org/linux/man-pages/man7/sched.7.html
            .sched_priority = 1,
        };
        retcode = pthread_setschedparam(this_thread, SCHED_RR, &priority_param);
        if (retcode != 0)
        {
            printf("ERROR: in file %s: %i: Failed to set pthread scheduler. "
                   "retcode = %i: %s.\n",
                    __FILE__, __LINE__, retcode, strerror(retcode));
            if (retcode == EPERM)  // Error: Permissions
            {
                printf("  You must use `sudo` or run this program as root to "
                       "have proper privileges!\n");
            }
        }
        else
        {
            printf("`pthread_setschedparam()` successful.\n");
        }

        // Memory lock: also lock the memory into RAM to prevent slow operations
        // where the kernel puts it into swap space. See notes above.
        retcode = mlockall(MCL_CURRENT | MCL_FUTURE | MCL_ONFAULT);
        if (retcode == -1)
        {
            printf("ERROR: in file %s: %i: Failed to lock memory into RAM. "
                   "errno = %i: %s.\n",
                __FILE__, __LINE__, errno, strerror(errno));
            if (errno == EPERM)  // Error: Permissions
            {
                printf("  You must use `sudo` or run this program as root to "
                       "have proper privileges!\n");
            }
        }
        else
        {
            printf("`mlockall()` successful.\n");
        }
    } // end of Demo 3

    // -------------------------------------------------------------------------
    // Demo 4 (the pthread version of Demo 2): if using pthreads: use
    // `pthread_setschedprio()` to change only the current thread's "priority".
    // See:
    // 1. https://man7.org/linux/man-pages/man3/pthread_setschedprio.3.html
    // -------------------------------------------------------------------------
    {
        pthread_t this_thread = pthread_self();

        // the priority must be from 1 (lowest priority) to 99
        // (highest priority) for the `SCHED_FIFO` AND `SCHED_RR`(round robin)
        // scheduler policies; see:
        // https://man7.org/linux/man-pages/man7/sched.7.html
        const int priority = 3;
        retcode = pthread_setschedprio(this_thread, priority);
        if (retcode != 0)
        {
            printf("ERROR: in file %s: %i: Failed to set pthread priority. "
                   "retcode = %i: %s.\n",
                    __FILE__, __LINE__, retcode, strerror(retcode));
            // NB: through testing, it seems that `pthread_setschedprio
            // ()` returns 22(EINVAL), if `sudo` is not used to run this code.
            // That seems like a compiler bug, because it should be `EPERM`,
            // but let's just handle it as though it was `EPERM`.
            if (retcode == EPERM || retcode == EINVAL)  // Error: Permissions
            {
                printf("  You must use `sudo` or run this program as root to "
                       "have proper privileges!\n");
            }
        }
        else
        {
            printf("`pthread_setschedprio()` successful.\n");
        }
    } // end of Demo 4

    // -------------------------------------------------------------------------
    // Demo 5 (create a pthread with the desired scheduler **policy**
    // and **priority** at creation time): if using pthreads: use
    // `pthread_attr_setschedpolicy()` and `pthread_attr_setschedparam()` to
    // set an initial scheduler **policy** and **priority** at the time of
    // thread creation via `pthread_create()`. Don't forget to use
    // `pthread_attr_setinheritsched()` to force `pthread_create()` to use our
    // new settings instead of inheriting scheduler settings from the calling
    // thread! You should use `pthread_attr_init()` and `pthread_attr_destroy()`
    // as well to initialize and destroy the attributes object.
    // See:
    // 1. https://man7.org/linux/man-pages/man3/pthread_attr_init.3.html
    // 1. https://man7.org/linux/man-pages/man3/pthread_attr_setschedpolicy.3.html
    // 1. https://man7.org/linux/man-pages/man3/pthread_attr_setschedparam.3.html
    // 1. https://man7.org/linux/man-pages/man3/pthread_attr_setinheritsched.3.html
    // 1. https://man7.org/linux/man-pages/man3/pthread_create.3.html
    // 1. https://man7.org/linux/man-pages/man3/pthread_join.3.html
    // 1. https://www.drdobbs.com/soft-real-time-programming-with-linux/184402031?pgno=1
    //      1. "Listing 2" code which demonstrates some of this code below:
    //         https://www.drdobbs.com/soft-real-time-programming-with-linux/184402031?pgno=3
    // -------------------------------------------------------------------------
    {
        // 0. Memory lock: also lock the memory into RAM to prevent slow operations
        // where the kernel puts it into swap space. See notes above.
        retcode = mlockall(MCL_CURRENT | MCL_FUTURE | MCL_ONFAULT);
        if (retcode == -1)
        {
            printf("ERROR: in file %s: %i: Failed to lock memory into RAM. "
                   "errno = %i: %s.\n",
                __FILE__, __LINE__, errno, strerror(errno));
            if (errno == EPERM)  // Error: Permissions
            {
                printf("  You must use `sudo` or run this program as root to "
                       "have proper privileges!\n");
            }
        }
        else
        {
            printf("`mlockall()` successful.\n");
        }

        // 1. Create and initialize a pthread attribute object.

        pthread_attr_t pthread_attr;
        retcode = pthread_attr_init(&pthread_attr);
        if (retcode != 0)
        {
            printf("ERROR: `pthread_attr_init()` failed. "
                   "retcode = %i: %s.\n",
                   retcode, strerror(retcode));
        }

        // 2. Set the scheduler **policy** (scheduler type) for the next thread
        // to be created.

        // Set to RR (round robin) soft real-time scheduler.
        int scheduler_policy = SCHED_RR;
        retcode = pthread_attr_setschedpolicy(&pthread_attr, scheduler_policy);
        if (retcode != 0)
        {
            printf("ERROR: `pthread_attr_setschedpolicy()` failed. "
                   "retcode = %i: %s.\n",
                   retcode, strerror(retcode));
        }

        // 3. Set the scheduler **priority** for the next thread to be created.

        const struct sched_param priority_param =
        {
            // the priority must be from 1 (lowest priority) to 99
            // (highest priority) for the `SCHED_FIFO` AND `SCHED_RR`
            // (round robin) scheduler policies; see:
            // https://man7.org/linux/man-pages/man7/sched.7.html
            .sched_priority = 1,
        };
        retcode = pthread_attr_setschedparam(&pthread_attr, &priority_param);
        if (retcode != 0)
        {
            printf("ERROR: `pthread_attr_setschedparam()` failed. "
                   "retcode = %i: %s.\n",
                   retcode, strerror(retcode));
        }

        // 4. Set the scheduler inheritance attribute so that `pthread_create()`
        // will use the scheduler settings set above inside the `pthread_attr`
        // object rather than inheriting scheduler attributes from the calling
        // thread! If you don't call this function, the default behavior is for
        // `pthread_create()` to IGNORE your scheduler policy and priority
        // settings inside the `pthread_attr` object, and use the calling
        // threads scheduler policy and priority instead!
        retcode = pthread_attr_setinheritsched(&pthread_attr,
            PTHREAD_EXPLICIT_SCHED);
        if (retcode != 0)
        {
            printf("ERROR: `pthread_attr_setinheritsched()` failed. "
                   "retcode = %i: %s.\n",
                   retcode, strerror(retcode));
        }

        // 5. Create any number of new pthread (POSIX thread) threads with this
        // scheduler policy and priority set at thread creation time. Here is
        // a demo creating just one pthread.

        pthread_t new_thread;
        retcode = pthread_create(&new_thread, &pthread_attr,
            dummy_pthread_action, "new_thread");
        if (retcode != 0)
        {
            printf("ERROR: `pthread_create()` failed. "
                   "retcode = %i: %s.\n",
                   retcode, strerror(retcode));
            if (retcode == EPERM)  // Error: Permissions
            {
                printf("  You must use `sudo` or run this program as root to "
                       "have proper privileges!\n");
            }
        }

        // 6. Destroy the thread attribute object. When done using the
        // `pthread_attr_t` attribute object above to create any number of
        // pthreads you desire, destroy it, presumably to free up dynamic
        // memory and prevent memory leaks.

        retcode = pthread_attr_destroy(&pthread_attr);
        if (retcode != 0)
        {
            printf("ERROR: `pthread_attr_destroy()` failed. "
                   "retcode = %i: %s.\n",
                   retcode, strerror(retcode));
        }

        // 7. thread cleanup: wait for the `new_thread` to finish with its
        // task by joining with it to wait and then clean it up.
        // See: https://man7.org/linux/man-pages/man3/pthread_join.3.html
        const char* return_message;
        retcode = pthread_join(new_thread, (void**)&return_message);
        if (retcode != 0)
        {
            printf("ERROR: `pthread_join()` failed. "
                   "retcode = %i: %s.\n",
                   retcode, strerror(retcode));
        }
        else
        {
            printf("`pthread_join()` successful: return_message = \"%s\"\n",
                return_message);
        }
    } // end of Demo 5

    printf("End of `set_scheduler()`.\n\n");
}

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    uint64_t t_start_ns = nanos();

    // set_scheduler(); // comment this in or out for testing
    use_realtime_scheduler();

    // smallest sleep time possible!
    run_sleep_tests(1, 100000);    // 1 ns

    run_sleep_tests(100, 100000);   //       100 ns =    0.100 us
    run_sleep_tests(1000, 100000);  //     1,000 ns =    1     us
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

Linux default scheduler:

    eRCaGuy_hello_world/c$ gcc -Wall -Wextra -Werror -O3 -std=c17 sleep_nanosleep_minimum_time_interval.c timinglib.c -o bin/a -lm -pthread && time bin/a
    Attempt to sleep 1 ns per `clock_nanosleep()` call, 100000 times.
    ts_requested.tv_sec  = 0
    ts_requested.tv_nsec = 1
    failure_cnt                                              =                0
    average time required per `clock_nanosleep()` sleep call =        54471.927 ns;   error =       -54 **us**
    minimum time for a `clock_nanosleep()` sleep call        =             3671 ns;   error =        -3 **us**
    maximum time for a `clock_nanosleep()` sleep call        =          6601283 ns;   error =     -6601 **us**

    Attempt to sleep 100 ns per `clock_nanosleep()` call, 100000 times.
    ts_requested.tv_sec  = 0
    ts_requested.tv_nsec = 100
    failure_cnt                                              =                0
    average time required per `clock_nanosleep()` sleep call =        56702.391 ns;   error =       -56 **us**
    minimum time for a `clock_nanosleep()` sleep call        =             3901 ns;   error =        -3 **us**
    maximum time for a `clock_nanosleep()` sleep call        =          6108997 ns;   error =     -6108 **us**

    Attempt to sleep 1000 ns per `clock_nanosleep()` call, 100000 times.
    ts_requested.tv_sec  = 0
    ts_requested.tv_nsec = 1000
    failure_cnt                                              =                0
    average time required per `clock_nanosleep()` sleep call =        55908.875 ns;   error =       -54 **us**
    minimum time for a `clock_nanosleep()` sleep call        =             4458 ns;   error =        -3 **us**
    maximum time for a `clock_nanosleep()` sleep call        =          4740096 ns;   error =     -4739 **us**

    Attempt to sleep 10000 ns per `clock_nanosleep()` call, 1000 times.
    ts_requested.tv_sec  = 0
    ts_requested.tv_nsec = 10000
    failure_cnt                                              =                0
    average time required per `clock_nanosleep()` sleep call =        68783.728 ns;   error =       -58 **us**
    minimum time for a `clock_nanosleep()` sleep call        =            17810 ns;   error =        -7 **us**
    maximum time for a `clock_nanosleep()` sleep call        =          1891034 ns;   error =     -1881 **us**

    Attempt to sleep 100000 ns per `clock_nanosleep()` call, 1000 times.
    ts_requested.tv_sec  = 0
    ts_requested.tv_nsec = 100000
    failure_cnt                                              =                0
    average time required per `clock_nanosleep()` sleep call =       156984.599 ns;   error =       -56 **us**
    minimum time for a `clock_nanosleep()` sleep call        =           110281 ns;   error =       -10 **us**
    maximum time for a `clock_nanosleep()` sleep call        =          1072336 ns;   error =      -972 **us**

    Attempt to sleep 1000000 ns per `clock_nanosleep()` call, 1000 times.
    ts_requested.tv_sec  = 0
    ts_requested.tv_nsec = 1000000
    failure_cnt                                              =                0
    average time required per `clock_nanosleep()` sleep call =      1069170.389 ns;   error =       -69 **us**
    minimum time for a `clock_nanosleep()` sleep call        =          1008534 ns;   error =        -8 **us**
    maximum time for a `clock_nanosleep()` sleep call        =          4357027 ns;   error =     -3357 **us**

    Attempt to sleep 1000000003 ns per `clock_nanosleep()` call, 2 times.
    ts_requested.tv_sec  = 1
    ts_requested.tv_nsec = 3
    failure_cnt                                              =                0
    average time required per `clock_nanosleep()` sleep call =   1000060659.000 ns;   error =       -60 **us**
    minimum time for a `clock_nanosleep()` sleep call        =       1000059084 ns;   error =       -59 **us**
    maximum time for a `clock_nanosleep()` sleep call        =       1000062234 ns;   error =       -62 **us**

    Attempt to sleep 100000000 ns per `clock_nanosleep()` call, 10 times.
    ts_requested.tv_sec  = 0
    ts_requested.tv_nsec = 100000000
    failure_cnt                                              =                0
    average time required per `clock_nanosleep()` sleep call =    100081604.600 ns;   error =       -81 **us**
    minimum time for a `clock_nanosleep()` sleep call        =        100058123 ns;   error =       -58 **us**
    maximum time for a `clock_nanosleep()` sleep call        =        100130465 ns;   error =      -130 **us**

    Total program run time = 21.016586607 sec.

    real    0m21.018s
    user    0m0.123s
    sys 0m0.698s


Linux RR (Round robin) soft real-time scheduler, **lowest** priority  of 1:

    eRCaGuy_hello_world/c$ gcc -Wall -Wextra -Werror -O3 -std=c17 sleep_nanosleep_minimum_time_interval.c timinglib.c -o bin/a -lm -pthread && time sudo chrt --rr 1 bin/a
    Attempt to sleep 1 ns per `clock_nanosleep()` call, 100000 times.
    ts_requested.tv_sec  = 0
    ts_requested.tv_nsec = 1
    failure_cnt                                              =                0
    average time required per `clock_nanosleep()` sleep call =         4498.843 ns;   error =        -4 **us**
    minimum time for a `clock_nanosleep()` sleep call        =             2667 ns;   error =        -2 **us**
    maximum time for a `clock_nanosleep()` sleep call        =            40192 ns;   error =       -40 **us**

    Attempt to sleep 100 ns per `clock_nanosleep()` call, 100000 times.
    ts_requested.tv_sec  = 0
    ts_requested.tv_nsec = 100
    failure_cnt                                              =                0
    average time required per `clock_nanosleep()` sleep call =         4156.853 ns;   error =        -4 **us**
    minimum time for a `clock_nanosleep()` sleep call        =             2683 ns;   error =        -2 **us**
    maximum time for a `clock_nanosleep()` sleep call        =            22753 ns;   error =       -22 **us**

    Attempt to sleep 1000 ns per `clock_nanosleep()` call, 100000 times.
    ts_requested.tv_sec  = 0
    ts_requested.tv_nsec = 1000
    failure_cnt                                              =                0
    average time required per `clock_nanosleep()` sleep call =         3894.208 ns;   error =        -2 **us**
    minimum time for a `clock_nanosleep()` sleep call        =             2665 ns;   error =        -1 **us**
    maximum time for a `clock_nanosleep()` sleep call        =            35610 ns;   error =       -34 **us**

    Attempt to sleep 10000 ns per `clock_nanosleep()` call, 1000 times.
    ts_requested.tv_sec  = 0
    ts_requested.tv_nsec = 10000
    failure_cnt                                              =                0
    average time required per `clock_nanosleep()` sleep call =        12694.886 ns;   error =        -2 **us**
    minimum time for a `clock_nanosleep()` sleep call        =            12266 ns;   error =        -2 **us**
    maximum time for a `clock_nanosleep()` sleep call        =            16980 ns;   error =        -6 **us**

    Attempt to sleep 100000 ns per `clock_nanosleep()` call, 1000 times.
    ts_requested.tv_sec  = 0
    ts_requested.tv_nsec = 100000
    failure_cnt                                              =                0
    average time required per `clock_nanosleep()` sleep call =       104684.978 ns;   error =        -4 **us**
    minimum time for a `clock_nanosleep()` sleep call        =           102364 ns;   error =        -2 **us**
    maximum time for a `clock_nanosleep()` sleep call        =           524199 ns;   error =      -424 **us**

    Attempt to sleep 1000000 ns per `clock_nanosleep()` call, 1000 times.
    ts_requested.tv_sec  = 0
    ts_requested.tv_nsec = 1000000
    failure_cnt                                              =                0
    average time required per `clock_nanosleep()` sleep call =      1012720.866 ns;   error =       -12 **us**
    minimum time for a `clock_nanosleep()` sleep call        =          1002401 ns;   error =        -2 **us**
    maximum time for a `clock_nanosleep()` sleep call        =          1102952 ns;   error =      -102 **us**

    Attempt to sleep 1000000003 ns per `clock_nanosleep()` call, 2 times.
    ts_requested.tv_sec  = 1
    ts_requested.tv_nsec = 3
    failure_cnt                                              =                0
    average time required per `clock_nanosleep()` sleep call =   1000045425.000 ns;   error =       -45 **us**
    minimum time for a `clock_nanosleep()` sleep call        =       1000044155 ns;   error =       -44 **us**
    maximum time for a `clock_nanosleep()` sleep call        =       1000046695 ns;   error =       -46 **us**

    Attempt to sleep 100000000 ns per `clock_nanosleep()` call, 10 times.
    ts_requested.tv_sec  = 0
    ts_requested.tv_nsec = 100000000
    failure_cnt                                              =                0
    average time required per `clock_nanosleep()` sleep call =    100035182.600 ns;   error =       -35 **us**
    minimum time for a `clock_nanosleep()` sleep call        =        100008511 ns;   error =        -8 **us**
    maximum time for a `clock_nanosleep()` sleep call        =        100104635 ns;   error =      -104 **us**

    Total program run time = 5.399367936 sec.

    real    0m5.421s
    user    0m0.107s
    sys 0m0.668s


Linux RR (Round robin) soft real-time scheduler, **highest** priority  of 99:

    eRCaGuy_hello_world/c$ gcc -Wall -Wextra -Werror -O3 -std=c17 sleep_nanosleep_minimum_time_interval.c timinglib.c -o bin/a -lm -pthread && time sudo chrt --rr 99 bin/a
    Attempt to sleep 1 ns per `clock_nanosleep()` call, 100000 times.
    ts_requested.tv_sec  = 0
    ts_requested.tv_nsec = 1
    failure_cnt                                              =                0
    average time required per `clock_nanosleep()` sleep call =         4338.589 ns;   error =        -4 **us**
    minimum time for a `clock_nanosleep()` sleep call        =             2713 ns;   error =        -2 **us**
    maximum time for a `clock_nanosleep()` sleep call        =            76852 ns;   error =       -76 **us**

    Attempt to sleep 100 ns per `clock_nanosleep()` call, 100000 times.
    ts_requested.tv_sec  = 0
    ts_requested.tv_nsec = 100
    failure_cnt                                              =                0
    average time required per `clock_nanosleep()` sleep call =         4415.744 ns;   error =        -4 **us**
    minimum time for a `clock_nanosleep()` sleep call        =             2686 ns;   error =        -2 **us**
    maximum time for a `clock_nanosleep()` sleep call        =           106524 ns;   error =      -106 **us**

    Attempt to sleep 1000 ns per `clock_nanosleep()` call, 100000 times.
    ts_requested.tv_sec  = 0
    ts_requested.tv_nsec = 1000
    failure_cnt                                              =                0
    average time required per `clock_nanosleep()` sleep call =         4031.598 ns;   error =        -3 **us**
    minimum time for a `clock_nanosleep()` sleep call        =             2751 ns;   error =        -1 **us**
    maximum time for a `clock_nanosleep()` sleep call        =            81947 ns;   error =       -80 **us**

    Attempt to sleep 10000 ns per `clock_nanosleep()` call, 1000 times.
    ts_requested.tv_sec  = 0
    ts_requested.tv_nsec = 10000
    failure_cnt                                              =                0
    average time required per `clock_nanosleep()` sleep call =        12913.663 ns;   error =        -2 **us**
    minimum time for a `clock_nanosleep()` sleep call        =            12199 ns;   error =        -2 **us**
    maximum time for a `clock_nanosleep()` sleep call        =            71128 ns;   error =       -61 **us**

    Attempt to sleep 100000 ns per `clock_nanosleep()` call, 1000 times.
    ts_requested.tv_sec  = 0
    ts_requested.tv_nsec = 100000
    failure_cnt                                              =                0
    average time required per `clock_nanosleep()` sleep call =       104626.499 ns;   error =        -4 **us**
    minimum time for a `clock_nanosleep()` sleep call        =           102294 ns;   error =        -2 **us**
    maximum time for a `clock_nanosleep()` sleep call        =           176547 ns;   error =       -76 **us**

    Attempt to sleep 1000000 ns per `clock_nanosleep()` call, 1000 times.
    ts_requested.tv_sec  = 0
    ts_requested.tv_nsec = 1000000
    failure_cnt                                              =                0
    average time required per `clock_nanosleep()` sleep call =      1011654.836 ns;   error =       -11 **us**
    minimum time for a `clock_nanosleep()` sleep call        =          1002607 ns;   error =        -2 **us**
    maximum time for a `clock_nanosleep()` sleep call        =          1099322 ns;   error =       -99 **us**

    Attempt to sleep 1000000003 ns per `clock_nanosleep()` call, 2 times.
    ts_requested.tv_sec  = 1
    ts_requested.tv_nsec = 3
    failure_cnt                                              =                0
    average time required per `clock_nanosleep()` sleep call =   1000007763.000 ns;   error =        -7 **us**
    minimum time for a `clock_nanosleep()` sleep call        =       1000007610 ns;   error =        -7 **us**
    maximum time for a `clock_nanosleep()` sleep call        =       1000007916 ns;   error =        -7 **us**

    Attempt to sleep 100000000 ns per `clock_nanosleep()` call, 10 times.
    ts_requested.tv_sec  = 0
    ts_requested.tv_nsec = 100000000
    failure_cnt                                              =                0
    average time required per `clock_nanosleep()` sleep call =    100008057.300 ns;   error =        -8 **us**
    minimum time for a `clock_nanosleep()` sleep call        =        100007330 ns;   error =        -7 **us**
    maximum time for a `clock_nanosleep()` sleep call        =        100009823 ns;   error =        -9 **us**

    Total program run time = 5.422470091 sec.

    real    0m5.446s
    user    0m0.122s
    sys 0m0.673s


Linux FIFO (first-in/first-out) soft real-time scheduler, **lowest** priority  of 1:
    (same as the RR ones above)
Linux FIFO (first-in/first-out) soft real-time scheduler, **highest** priority  of 99:
    (same as the RR ones above)





OR, in C++:




*/
