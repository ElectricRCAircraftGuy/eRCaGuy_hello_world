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
#include <algorithm>  // For `std::sort`
#include <array>
#include <chrono>
#include <cinttypes>  // For `PRIu64`
#include <cmath>  // For `sqrt`
#include <cstdint>  // For `uint8_t`, `int8_t`, etc.
#include <cstdio>   // For `printf()`
#include <iostream>  // For `std::cin`, `std::cout`, `std::endl`, etc.
#include <unordered_map>  // For mode calculation

// Get time stamp in nanoseconds.
// - See my answer: https://stackoverflow.com/a/49066369/4561887
template<typename Clock = std::chrono::high_resolution_clock>
uint64_t nanos()
{
    uint64_t ns = std::chrono::duration_cast<std::chrono::nanoseconds>(
            Clock::now().time_since_epoch())
            .count();
    return ns;
}

static constexpr size_t SAMPLE_SIZE = 20'000'000;

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("%s running...\n", __FILE__);

    // Print the operating system
    // - See my answer: https://stackoverflow.com/a/79228659/4561887
#if defined(_WIN32)
    printf("Operating System: Windows (32-bit or 64-bit)\n");
#elif defined (__linux__)
    printf("Operating System: Linux\n");
#endif

    // NB: use `static` to keep off the stack, as it will overflow the stack if too big.
    // See stack sizes: https://stackoverflow.com/a/64085509/4561887
    static std::array<uint64_t, SAMPLE_SIZE> timestamps_ns;

    // Get timestamps as fast as possible
    for (size_t i = 0; i < timestamps_ns.size(); i++)
    {
        timestamps_ns[i] = nanos<std::chrono::high_resolution_clock>();
    }

    // NB: use `static` to keep off the stack, as it will overflow the stack if too big.
    // See stack sizes: https://stackoverflow.com/a/64085509/4561887
    static std::array<uint64_t, SAMPLE_SIZE - 1> deltas_ns;
    for (size_t i = 0; i < deltas_ns.size(); i++)
    {
        deltas_ns[i] = timestamps_ns[i+1] - timestamps_ns[i];
        // printf("%" PRIu64 "\n", deltas_ns[i]);  // debugging
    }

    // Calculate stats: mean, median, mode, and stddev of the time differences

    printf("\nAnalyzing %zu time delta samples...\n\n", deltas_ns.size());

    // 1. Calculate Mean

    uint64_t sum = 0;
    for (size_t i = 0; i < deltas_ns.size(); i++)
    {
        sum += deltas_ns[i];
    }
    double mean = static_cast<double>(sum) / deltas_ns.size();

    // 2. Calculate Median (requires sorting a copy)

    static std::array<uint64_t, SAMPLE_SIZE - 1> sorted_deltas = deltas_ns;
    std::sort(sorted_deltas.begin(), sorted_deltas.end());

    double median;
    size_t i_mid = sorted_deltas.size() / 2;
    if (sorted_deltas.size() % 2 == 0)
    {
        // There are an even number of elements
        median = (sorted_deltas[i_mid - 1] + sorted_deltas[i_mid]) / 2.0;
    }
    else
    {
        // There are an odd number of elements
        median = sorted_deltas[i_mid];
    }

    // 3. Calculate Mode (most frequent value)

    std::unordered_map<uint64_t, size_t> frequency_map;
    for (size_t i = 0; i < deltas_ns.size(); i++)
    {
        // NB: When you use `operator[]` on a `std::unordered_map` with a key that doesn't
        // exist yet, it automatically:
        //
        // 1. Creates a new entry with that key
        // 2. Value-initializes the value (for size_t, this means it's initialized to 0)
        // 3. Returns a reference to that value
        //
        // So if the key exists, this line increments its count, and if the key does not yet
        // exist, it creates an entry with value 0, then increments it to 1.
        //
        frequency_map[deltas_ns[i]]++;
    }

    uint64_t mode = 0;
    size_t max_count = 0;
    for (const std::pair<const uint64_t, size_t>& pair : frequency_map)
    {
        uint64_t number = pair.first;
        size_t count = pair.second;

        if (count > max_count)
        {
            max_count = count;
            mode = number;
        }
    }

    // 4. Calculate Standard Deviation
    // - This is the spread of the data around the mean.
    // - It is calculated as the square root of the variance, where the variance is the average
    //   of the squared differences from the mean.

    double variance_sum = 0;
    for (size_t i = 0; i < deltas_ns.size(); i++)
    {
        double diff = deltas_ns[i] - mean;
        double diff_squared = diff * diff;
        variance_sum += diff_squared;
    }
    // avg of the squared differences
    double variance = variance_sum / deltas_ns.size();
    // sqrt of the variance
    double stddev = std::sqrt(variance);

    // Print results

    printf("Estimation of your clock precision:\n\n");
    printf("Mean:   %11.3f ns\n", mean);
    printf("Median: %11.3f ns\n", median);
    printf("Mode:   %7" PRIu64 "     ns (appears %zu times, %.3f%%)  <== USE THIS; MOST RELIABLE "
           "ESTIMATE\n",
           mode, max_count, (100.0 * max_count) / deltas_ns.size());
    printf("Stddev: %11.3f ns\n", stddev);

    printf("\nAdditional stats:\n");
    printf("Min:    %7" PRIu64 " ns\n", sorted_deltas.front());
    printf("Max:    %7" PRIu64 " ns\n", sorted_deltas.back());
    printf("Range:  %7" PRIu64 " ns\n", sorted_deltas.back() - sorted_deltas.front());

    return 0;
}


/*
EXAMPLE RUN ON LINUX:

eRCaGuy_hello_world$ time cpp/timing_and_precision_Windows_and_Linux_tests.cpp
cpp/timing_and_precision_Windows_and_Linux_tests.cpp running...
Operating System: Linux

Analyzing 19999999 time delta samples...

Mean:   28.463 ns
Median: 24.000 ns
Mode:   24 ns (appears 6536745 times, 32.684%)
Stddev: 242.249 ns

Additional Statistics:
Min:    19 ns
Max:    264029 ns
Range:  264010 ns

real	0m2.269s
user	0m1.958s
sys	0m0.302s



EXAMPLE RUN ON WINDOWS:

tbd

*/
