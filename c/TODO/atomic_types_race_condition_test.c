/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
13 Apr. 2022

Verify which types are atomic in gcc/on Linux x86-64 or similar.

See my Q, and the answers, here: https://stackoverflow.com/q/71866535/4561887

STATUS: wip


TODO design notes:

Make this program spawn 16 new pthreads, each of which tries to write to a 128-bit integer
(see: https://stackoverflow.com/a/34588884/4561887), withOUT a mutex! Leave all 16 of those threads
on the default `SCHED_OTHER` Linux scheduler. As those 16 threads write to the same variable at the
same time, the main thread will use the `SCHED_RR` soft real-time Linux scheduler with a priority
of 1 (lowest priority, so as to not preempt other real-time threads) (see here for how:
`use_realtime_scheduler()` in timinglib.c) to **read** the variable.

Each of those 16 threads is trying to write a fixed constant for its index from an array of 16
pre-defined constants, so the reader knows that ONE of those 16 predefined constants should be what
is in the variable. If any other number is in the variable, it means that a race condition
occurred, meaning the writes into that variable are NOT atomic! Print out a timestamp of elapsed
program runtime (using `nanos()` from timinglib.h converted to double sec), and move on to the next
smallest type to test!

The main thread will perform each read withOUT a mutex, using my `doAtomicRead()` function here
(https://stackoverflow.com/a/71625693/4561887), and keep trying until it successfully reads. Then,
it will sleep for a tiny time (ex: 1 ns), and then read again. If the value isn't changed for 2/4
reads, it means that likely the sleep was too short to let the other threads write again, so it
will double the sleep time, print the new sleep value, and sleep again.

Making the main thread higher priority will ensure it can read at the interval it wants, and
doubling the sleep time if the value isn't changing 2/4 times ensures the main reader thread's
sleep time is long enough to let the 16 writer threads contend with each other to write.

Every 10 seconds, the main thread will print out the elapsed time, the variable size the system is
working on, and the number of collisions detected. The important information like collisions
detected and timestamps of collisions will also be written to a log file for later review.

Here are the variables the system will test, in this order:

#define NUM_WRITER_THREADS 16

const uint128_t vals_to_write[NUM_WRITER_THREADS] = {fill in with random numbers from LibreOffice Calc};
const uint64_t vals_to_write[NUM_WRITER_THREADS] = {fill in with random numbers from LibreOffice Calc};
const uint32_t vals_to_write[NUM_WRITER_THREADS] = {fill in with random numbers from LibreOffice Calc};
const uint16_t vals_to_write[NUM_WRITER_THREADS] = {fill in with random numbers from LibreOffice Calc};
const uint8_t vals_to_write[NUM_WRITER_THREADS] = {fill in with random numbers from LibreOffice Calc};

I suspect at either 64-bit or 32-bits the system will be able to run all night with no collisions.
Once that happens, test other types of that size to ensure I get the same results. I could have it
automatically try the other ones once it runs for 1 hr or something on a given one.



To compile and run (assuming you've already `cd`ed into this dir):
```bash
# Why `-std=gnu17` vs `-std=c17`, and `-std=gnu++17` vs `-std=c++17`?
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# 1. In C:
gcc -Wall -Wextra -Werror -O3 -std=gnu17 atomic_types_race_condition_test.c -o bin/a -lm && bin/a

# 2. In C++
g++ -Wall -Wextra -Werror -O3 -std=gnu++17 atomic_types_race_condition_test.c -o bin/a && bin/a
```

References:
1. [My Q] *****Which types on a 64-bit computer are naturally atomic in C and
C++?--meaning they have atomic reads, and atomic writes -
https://stackoverflow.com/q/71866535/4561887
    1. C `_Atomic` types:
        1. *****https://en.cppreference.com/w/c/thread
        1. *****https://en.cppreference.com/w/c/language/atomic
    1. C++ `std::atomic<>` types:
        1. *****https://en.cppreference.com/w/cpp/atomic/atomic

1. "/usr/include/x86_64-linux-gnu/c++/8/bits/atomic_word.h"
1. https://gcc.gnu.org/onlinedocs/libstdc++/manual/ext_concurrency.html
1. https://gcc.gnu.org/onlinedocs/gcc-4.6.2/libstdc++/api/a00760_source.html - atomicity.h


*/



// Linux & GNU extensions includes
// #include <ext/atomicity.h> // gnu++ only
// #include <bits/atomic_word.h> // gnu++ only

// C includes
#include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Hello World. Todo.\n\n");

    return 0;
}

/*
SAMPLE OUTPUT:

In C:

    eRCaGuy_hello_world/c$ gcc -Wall -Wextra -Werror -O3 -std=c17 atomic_types_race_condition_test.c -o bin/a -lm && bin/a
    Hello World.


OR, in C++:

    eRCaGuy_hello_world/c$ g++ -Wall -Wextra -Werror -O3 -std=c++17 atomic_types_race_condition_test.c -o bin/a && bin/a
    Hello World.


*/
