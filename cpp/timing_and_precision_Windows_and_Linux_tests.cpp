///usr/bin/env ccache g++ -Wall -Wextra -Werror -O3 -std=gnu++17 "$0" -o /tmp/a && /tmp/a "$@"; exit
// For the line just above, see my answer here: https://stackoverflow.com/a/75491834/4561887

/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

C++ Windows and Linux cross-platform timing tests.

GS
Jan. 2026

STATUS: wip

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# NB: you may need to use `-std=gnu++17` instead of `-std=c++17` in order to obtain extra GNU
# gcc features, including gcc extensions, POSIX cmds, and Linux sytem cmds.
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# [run once ever] install ccache
sudo apt update && sudo apt install ccache

# 1. In C++
time g++ -Wall -Wextra -Werror -O3 -std=gnu++17 timing_and_precision_Windows_and_Linux_tests.cpp -o bin/a && bin/a

# OR (just call this file as an exectuable directly)
time ./timing_and_precision_Windows_and_Linux_tests.cpp
```

References:
1. "eRCaGuy_hello_world/c/timinglib.h"/.c.
1. For high-precision timing in Python: https://stackoverflow.com/a/73482099/4561887 - shows the
   language-agnostic OS-based timing precisions for various clocks.
1. Here is how to get simple C-like millisecond, microsecond, and nanosecond timestamps in C++
   https://stackoverflow.com/a/49066369/4561887

See also:
1. *****+[MY ANSWER] Get a timestamp in C in microseconds? - https://stackoverflow.com/a/67731965/4561887
1. Example "delay until" timing code to look at: https://www.freertos.org/vtaskdelayuntil.html
1. See also my answers here regarding Linux nanosleep functions and soft
real-time schedulers, such as the `SCHED_RR` soft real-time round-robin
scheduler:
    1. [my ans] How to run a high-resolution, high-precision periodic loop in
    Linux easily, at any frequency (ex: 10 KHz) using a soft real-time
    scheduler and nanosecond delays:
    https://stackoverflow.com/a/71790209/4561887
    1. [my ans] pthread_create not working properly with
    pthread_attr_setschedparam: https://stackoverflow.com/a/71789490/4561887
    1. [my ans] How to configure the Linux SCHED_RR soft real-time round-robin
    scheduler so that clock_nanosleep() can have improved resolution of ~4 us
    down from ~ 55 us: https://stackoverflow.com/a/71757858/4561887

*/


// C++ (incl. C) includes
#include <array>
#include <chrono>
#include <cinttypes>  // For `PRIu64`
#include <cstdint>  // For `uint8_t`, `int8_t`, etc.
#include <cstdio>   // For `printf()`
#include <iostream>  // For `std::cin`, `std::cout`, `std::endl`, etc.

// Get time stamp in nanoseconds.
// - See my answer: https://stackoverflow.com/a/49066369/4561887
uint64_t nanos()
{
    uint64_t ns = std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::high_resolution_clock::now().time_since_epoch())
            .count();
    return ns;
}

static constexpr size_t SAMPLE_SIZE = 20'000'000;

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Hello ");
    std::cout << "world!\n\n";

    // NB: use `static` to keep off the stack, as it will overflow the stack if too big.
    // See stack sizes: https://stackoverflow.com/a/64085509/4561887
    static std::array<uint64_t, SAMPLE_SIZE> timestamps_ns;

    // Get timestamps as fast as possible
    for (size_t i = 0; i < timestamps_ns.size(); i++)
    {
        timestamps_ns[i] = nanos();
    }

    // NB: use `static` to keep off the stack, as it will overflow the stack if too big.
    // See stack sizes: https://stackoverflow.com/a/64085509/4561887
    static std::array<uint64_t, SAMPLE_SIZE - 1> deltas_ns;
    for (size_t i = 0; i < deltas_ns.size(); i++)
    {
        deltas_ns[i] = timestamps_ns[i+1] - timestamps_ns[i];
        // printf("%" PRIu64 "\n", deltas_ns[i]);  // debugging
    }

    // Calculate mean, median, mode, and stddev of the time differences


    return 0;
}
