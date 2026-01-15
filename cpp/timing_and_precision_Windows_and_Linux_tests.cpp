///usr/bin/env ccache g++ -Wall -Wextra -Werror -O3 -std=gnu++17 "$0" -o /tmp/a && /tmp/a "$@"; exit
// For the line just above, see my answer here: https://stackoverflow.com/a/75491834/4561887

/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

C++ Windows and Linux cross-platform timing tests.

GS
Jan. 2026

STATUS: Done and works!

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
1. ---
1. See all clock types in the "Clocks" section here at the top of this page:
   https://en.cppreference.com/w/cpp/chrono.html
1. https://en.cppreference.com/w/cpp/thread/sleep_for.html

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

TODO:
1. [x] Print timestamp stats for all 3 major clocks, also indicating if certain clocks are the same
   based on `using` declarations.
1. [x] Use the highest precision clock timestamps to then time sleep calls of various lengths, and
   see how accurate they are. Identify the minimum sleep time that is possible.
   ex: 1ns, 1ms, 2ms, 10ms, 20ms, 50ms, 100ms, 500ms, 1s.
1. [ ] Write standalone mean, median, mode, stddev, etc. stats functions and quit duplicating that
   logic in both `test_and_print_clock_precision()` and `sleep_test()`.

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
#include <thread>  // For `std::this_thread::sleep_for`
#include <type_traits>  // For `std::is_same`
#include <unordered_map>  // For mode calculation
#include <vector>  // For `std::vector`

// Get time stamp in nanoseconds.
// - See my answer: https://stackoverflow.com/a/49066369/4561887
template<typename MeasurementClock = std::chrono::high_resolution_clock>
uint64_t nanos()
{
    uint64_t ns = std::chrono::duration_cast<std::chrono::nanoseconds>(
            MeasurementClock::now().time_since_epoch())
            .count();
    return ns;
}

static constexpr size_t SAMPLE_SIZE = 20'000'000;

// Run clock precision tests for the specified clock type, and print all results.
template<typename MeasurementClock>
void test_and_print_clock_precision()
{
    // NB: use `static` to keep off the stack, as it will overflow the stack if too big.
    // - See stack sizes: https://stackoverflow.com/a/64085509/4561887
    // Alternatively, use heap via `std::vector`.
    static std::array<uint64_t, SAMPLE_SIZE> timestamps_ns;

    // Get timestamps as fast as possible
    for (size_t i = 0; i < timestamps_ns.size(); i++)
    {
        timestamps_ns[i] = nanos<MeasurementClock>();
    }

    // Calculate time deltas between successive timestamps
    constexpr size_t MAX_NUM_DELTAS_POSSIBLE = timestamps_ns.size() - 1;
    std::vector<uint64_t> deltas_ns;
    deltas_ns.reserve(MAX_NUM_DELTAS_POSSIBLE);
    size_t invalid_delta_count = 0; // increment each time an invalid delta of 0 is found
    for (size_t i = 0; i < timestamps_ns.size() - 1; i++)
    {
        uint64_t delta_ns = timestamps_ns[i+1] - timestamps_ns[i];
        if (delta_ns == 0)
        {
            // Invalid deltas of 0 are expected on Windows because the clock precision is so poor
            // (~16 ms) that many timestamps will be identical when taken in rapid succession.
            invalid_delta_count++;
            continue;
        }

        deltas_ns.push_back(delta_ns);
        // printf("%" PRIu64 "\n", deltas_ns.back());  // debugging
    }

    printf("\ninvalid_delta_count = %zu (%.2f%%) (expected 0 sample deltas invalid on Linux, "
        "and the majority invalid on Windows)\n",
        invalid_delta_count,
        (100.0 * invalid_delta_count) / MAX_NUM_DELTAS_POSSIBLE);

    // Calculate stats: mean, median, mode, and stddev of the time differences

    printf("Analyzing %zu (%.2f%% of collected) time delta samples...\n\n",
        deltas_ns.size(),
        (100.0 * deltas_ns.size()) / MAX_NUM_DELTAS_POSSIBLE);

    // 1. Calculate Mean

    uint64_t sum = 0;
    for (size_t i = 0; i < deltas_ns.size(); i++)
    {
        sum += deltas_ns[i];
    }
    double mean = static_cast<double>(sum) / deltas_ns.size();

    // 2. Calculate Median (requires sorting a copy)

    std::vector<uint64_t> sorted_deltas = deltas_ns;
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
    printf("Mode:   %7" PRIu64 "     ns (appears %zu times, %.3f%%)  <=== ESTIMATED "
        "CLOCK PRECISION; MOST RELIABLE ESTIMATE\n",
           mode, max_count, (100.0 * max_count) / deltas_ns.size());
    printf("Stddev: %11.3f ns\n", stddev);

    printf("\nAdditional stats:\n");
    printf("Min:    %7" PRIu64 " ns\n", sorted_deltas.front());
    printf("Max:    %7" PRIu64 " ns\n", sorted_deltas.back());
    printf("Range:  %7" PRIu64 " ns\n", sorted_deltas.back() - sorted_deltas.front());
}

// Test sleep precision by sleeping multiple times and measuring actual sleep duration using
// `MeasurementClock`.
template<typename MeasurementClock, typename SleepDuration>
void sleep_test(SleepDuration sleep_duration, size_t num_iterations)
{
    // Convert duration to nanoseconds for display
    uint64_t requested_ns =
        std::chrono::duration_cast<std::chrono::nanoseconds>(sleep_duration).count();

    printf("\n----------------------------------------------------------\n");
    printf("Sleep test: requested duration = **%" PRIu64 " ns**", requested_ns);

    // Also show in more readable units if appropriate: sec, ms, us
    if (requested_ns >= 1'000'000'000)
    {
        printf(" (**%.3f s**)", requested_ns / 1e9);
    }
    else if (requested_ns >= 1'000'000)
    {
        printf(" (**%.3f ms**)", requested_ns / 1e6);
    }
    else if (requested_ns >= 1'000)
    {
        printf(" (**%.3f us**)", requested_ns / 1e3);
    }
    printf(", iterations = %zu\n", num_iterations);
    printf("----------------------------------------------------------\n");

    // Store actual sleep durations
    std::vector<uint64_t> actual_durations_ns;
    // Pre-allocate dynamic memory (heap) for speed
    actual_durations_ns.reserve(num_iterations);

    // Perform sleep tests
    size_t num_successful_sleeps = 0;
    size_t num_failed_sleeps = 0;
    while (num_successful_sleeps < num_iterations)
    {
        uint64_t start_ns = nanos<MeasurementClock>();
        // See: https://en.cppreference.com/w/cpp/thread/sleep_for.html
        std::this_thread::sleep_for(sleep_duration);
        uint64_t end_ns = nanos<MeasurementClock>();

        uint64_t actual_ns = end_ns - start_ns;
        if (actual_ns == 0)
        {
            // This should never happen unless the clock precision is very poor
            // (ex: Windows system_clock with ~16 ms precision, and on ultra-short sleeps)
            num_failed_sleeps++;
            continue;
        }

        num_successful_sleeps++;
        actual_durations_ns.push_back(actual_ns);
    }

    // Calculate statistics

    // mean
    uint64_t sum = 0;
    for (uint64_t duration : actual_durations_ns)
    {
        sum += duration;
    }
    double mean = static_cast<double>(sum) / actual_durations_ns.size();

    // median
    std::vector<uint64_t> sorted_durations = actual_durations_ns;
    std::sort(sorted_durations.begin(), sorted_durations.end());

    double median;
    size_t mid = sorted_durations.size() / 2;
    if (sorted_durations.size() % 2 == 0)
    {
        // even number of elements
        median = (sorted_durations[mid - 1] + sorted_durations[mid]) / 2.0;
    }
    else
    {
        // odd number of elements
        median = sorted_durations[mid];
    }

    // min and max
    uint64_t min = sorted_durations.front();
    uint64_t max = sorted_durations.back();

    // standard deviation
    double variance_sum = 0;
    for (uint64_t duration : actual_durations_ns)
    {
        double diff = duration - mean;
        variance_sum += diff * diff;
    }
    double variance = variance_sum / actual_durations_ns.size();
    double stddev = std::sqrt(variance);

    // Print results

    if (num_failed_sleeps > 0)
    {
        printf("WARNING: %zu failed sleeps due to clock precision being too poor to measure such\n"
            "a short duration. Probably no sleep took place at all, but a yield may have occurred\n"
            "in which the OS's scheduler ran for a duration <= the clock's minimum resolution.\n"
            "- This is expected on Windows, not on Linux.\n"
            "- Probable yield duration: < %" PRIu64 " ns\n",
            num_failed_sleeps, min);
    }

#define PRINT_HUMAN_READABLE(ns_value)                                           \
    if ((ns_value) >= 1e9) printf(" (%8.3f s)", (double)(ns_value) / 1e9);       \
    else if ((ns_value) >= 1e6) printf(" (%8.3f ms)", (double)(ns_value) / 1e6); \
    else if ((ns_value) >= 1e3) printf(" (%8.3f us)", (double)(ns_value) / 1e3);

#define PRINT_HUMAN_READABLE_ABS(ns_value)                                                 \
    if (std::abs((ns_value)) >= 1e9) printf(" (%8.3f s)", (double)(ns_value) / 1e9);       \
    else if (std::abs((ns_value)) >= 1e6) printf(" (%8.3f ms)", (double)(ns_value) / 1e6); \
    else if (std::abs((ns_value)) >= 1e3) printf(" (%8.3f us)", (double)(ns_value) / 1e3);

    printf("\nActual sleep duration statistics:\n");

    printf("  Mean:     %16.3f ns", mean);
    PRINT_HUMAN_READABLE(mean);
    printf("\n");

    printf("  Median:   %16.3f ns", median);
    PRINT_HUMAN_READABLE(median);
    printf("  <=== MEDIAN ACTUAL SLEEP\n");

    printf("  Stddev:   %16.3f ns", stddev);
    PRINT_HUMAN_READABLE(stddev);
    printf("\n");

    printf("  Min:      %12" PRIu64 "     ns", min);
    PRINT_HUMAN_READABLE(min);
    printf("\n");

    printf("  Max:      %12" PRIu64 "     ns", max);
    PRINT_HUMAN_READABLE(max);
    printf("\n");

    printf("  Range:    %12" PRIu64 "     ns", max - min);
    PRINT_HUMAN_READABLE(max - min);
    printf("\n");

    // Calculate error
    double error_ns = mean - requested_ns;
    double error_percent = (error_ns / requested_ns) * 100.0;
    printf("\nError (mean - requested):\n");
    printf("  Absolute: %16.3f ns", error_ns);
    PRINT_HUMAN_READABLE_ABS(error_ns);
    printf("  <=== WHAT I CARE ABOUT THE MOST\n");
    printf("  Relative: %16.3f %%\n", error_percent);
}

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

    printf("\n");
    printf("===================================================================================\n");
    printf("1. Timestamp precision tests\n");
    printf("===================================================================================\n");

    printf("\nDefinition reminders:\n"
        "  See my answer here: https://stackoverflow.com/a/73482099/4561887. \n"
        "  - Resolution = the smallest time difference the units can represent. Ex: 1 ns.\n"
        "  - Precision  = the repeatability of the measurement. This is the smallest time\n"
        "    difference the clock can repeatedly measure, and is usually much larger than the\n"
        "    resolution. Ex: 20 ns.\n"
        "  - Accuracy   = how close a given clock measurement (whether an absolute timestamp,\n"
        "    or an interval measurement) is to the true time or value. This has to do with how\n"
        "    accurate your hardware clock's quartz crystal (or equivalent RC, ceramic, or PLL)\n"
        "    oscillator is, and how well it's calibrated. Ex: +/- 60 us when measuring a\n"
        "    1 minute time interval, for a clock which drifts 30 seconds per year.\n"
        "    (30 sec/year drift / 31557600 sec/year * 60 sec measured time interval =\n"
        "    0.000057039 sec = 57.039 us drift over that 60 seconds).\n"
        "\n"
        "This program estimates the PRECISION of each clock type below.\n");

    // See all clock types in the "Clocks" section here at the top of this page:
    // https://en.cppreference.com/w/cpp/chrono.html

    // Check if certain clock types are the same
    printf("\nClock type comparisons:\n");
    printf("  std::chrono::high_resolution_clock == std::chrono::system_clock: %s\n",
           std::is_same<std::chrono::high_resolution_clock, std::chrono::system_clock>::value
           ? "true" : "false");
    printf("  std::chrono::high_resolution_clock == std::chrono::steady_clock: %s\n",
           std::is_same<std::chrono::high_resolution_clock, std::chrono::steady_clock>::value
           ? "true" : "false");
    printf("  std::chrono::system_clock          == std::chrono::steady_clock: %s\n",
           std::is_same<std::chrono::system_clock, std::chrono::steady_clock>::value
           ? "true" : "false");

    printf("\n");
    printf("std::chrono::system_clock.is_steady:           %s\n",
           std::chrono::system_clock::is_steady ? "true" : "false");
    printf("std::chrono::steady_clock.is_steady:           %s\n",
           std::chrono::steady_clock::is_steady ? "true" : "false");
    printf("std::chrono::high_resolution_clock.is_steady:  %s\n",
           std::chrono::high_resolution_clock::is_steady ? "true" : "false");

    printf("\n"
        "----------------------------------------------------------\n"
        "Testing std::chrono::system_clock precision:\n"
        "----------------------------------------------------------\n");
    test_and_print_clock_precision<std::chrono::system_clock>();

    printf("\n"
        "----------------------------------------------------------\n"
        "Testing std::chrono::steady_clock precision:\n"
        "----------------------------------------------------------\n");
    test_and_print_clock_precision<std::chrono::steady_clock>();

    printf("\n"
        "----------------------------------------------------------\n"
        "Testing std::chrono::high_resolution_clock precision:\n"
        "----------------------------------------------------------\n");
    test_and_print_clock_precision<std::chrono::high_resolution_clock>();

    printf("\n");
    printf("===================================================================================\n");
    printf("2. Sleep precision tests\n");
    printf("===================================================================================\n");

    // Allow for a different selection of clock type for measurements just in case we need to
    // for Windows (in case its steady clock is very poor resolution).
#if defined(_WIN32)
    // Windows
    using measurement_clock_type = std::chrono::steady_clock;
#elif defined (__linux__)
    // Linux
    using measurement_clock_type = std::chrono::steady_clock;
#endif

    using namespace std::chrono_literals;

    sleep_test<measurement_clock_type>(1ns, 1);  // sanity check to compare to the next line to
                                                 // see if 1 ulta-short sleep iteration works ok
    sleep_test<measurement_clock_type>(1ns, 100);
    sleep_test<measurement_clock_type>(1us, 50);
    sleep_test<measurement_clock_type>(10us, 50);
    sleep_test<measurement_clock_type>(20us, 50);
    sleep_test<measurement_clock_type>(30us, 50);
    sleep_test<measurement_clock_type>(50us, 50);
    sleep_test<measurement_clock_type>(100us, 50);
    sleep_test<measurement_clock_type>(200us, 50);
    sleep_test<measurement_clock_type>(500us, 50);
    sleep_test<measurement_clock_type>(1ms, 50);
    sleep_test<measurement_clock_type>(2ms, 50);
    sleep_test<measurement_clock_type>(10ms, 10);
    sleep_test<measurement_clock_type>(20ms, 10);
    sleep_test<measurement_clock_type>(50ms, 10);
    sleep_test<measurement_clock_type>(100ms, 10);
    sleep_test<measurement_clock_type>(500ms, 1);
    sleep_test<measurement_clock_type>(1s, 1);

    return 0;
}


/*
EXAMPLE RUN ON LINUX:

eRCaGuy_hello_world$ time cpp/timing_and_precision_Windows_and_Linux_tests.cpp
cpp/timing_and_precision_Windows_and_Linux_tests.cpp running...
Operating System: Linux

===================================================================================
1. Timestamp precision tests
===================================================================================

Definition reminders:
  See my answer here: https://stackoverflow.com/a/73482099/4561887.
  - Resolution = the smallest time difference the units can represent. Ex: 1 ns.
  - Precision  = the repeatability of the measurement. This is the smallest time
    difference the clock can repeatedly measure, and is usually much larger than the
    resolution. Ex: 20 ns.
  - Accuracy   = how close a given clock measurement (whether an absolute timestamp,
    or an interval measurement) is to the true time or value. This has to do with how
    accurate your hardware clock's quartz crystal (or equivalent RC, ceramic, or PLL)
    oscillator is, and how well it's calibrated. Ex: +/- 60 us when measuring a
    1 minute time interval, for a clock which drifts 30 seconds per year.
    (30 sec/year drift / 31557600 sec/year * 60 sec measured time interval =
    0.000057039 sec = 57.039 us drift over that 60 seconds).

This program estimates the PRECISION of each clock type below.

Clock type comparisons:
  std::chrono::high_resolution_clock == std::chrono::system_clock: true
  std::chrono::high_resolution_clock == std::chrono::steady_clock: false
  std::chrono::system_clock          == std::chrono::steady_clock: false

std::chrono::system_clock.is_steady:           false
std::chrono::steady_clock.is_steady:           true
std::chrono::high_resolution_clock.is_steady:  false

----------------------------------------------------------
Testing std::chrono::system_clock precision:
----------------------------------------------------------

Analyzing 19999999 time delta samples...

Estimation of your clock precision:

Mean:        21.254 ns
Median:      19.000 ns
Mode:        19     ns (appears 7415654 times, 37.078%)  <== USE THIS; MOST RELIABLE ESTIMATE
Stddev:     225.159 ns

Additional stats:
Min:         13 ns
Max:     249736 ns
Range:   249723 ns

----------------------------------------------------------
Testing std::chrono::steady_clock precision:
----------------------------------------------------------

Analyzing 19999999 time delta samples...

Estimation of your clock precision:

Mean:        21.401 ns
Median:      19.000 ns
Mode:        19     ns (appears 7488461 times, 37.442%)  <== USE THIS; MOST RELIABLE ESTIMATE
Stddev:      94.773 ns

Additional stats:
Min:         15 ns
Max:     224804 ns
Range:   224789 ns

----------------------------------------------------------
Testing std::chrono::high_resolution_clock precision:
----------------------------------------------------------

Analyzing 19999999 time delta samples...

Estimation of your clock precision:

Mean:        18.679 ns
Median:      19.000 ns
Mode:        19     ns (appears 7855362 times, 39.277%)  <== USE THIS; MOST RELIABLE ESTIMATE
Stddev:      23.646 ns

Additional stats:
Min:         13 ns
Max:     249736 ns
Range:   249723 ns

===================================================================================
2. Sleep precision tests
===================================================================================

----------------------------------------------------------
Sleep test: requested duration = 1 ns, iterations = 1
----------------------------------------------------------

Actual sleep duration statistics:
  Mean:            55211.000 ns (  55.211 us)
  Median:          55211.000 ns (  55.211 us)
  Stddev:              0.000 ns
  Min:             55211     ns (  55.211 us)
  Max:             55211     ns (  55.211 us)
  Range:               0     ns

Error (mean - requested):
  Absolute:        55210.000 ns (  55.210 us)  <=== WHAT I CARE ABOUT THE MOST
  Relative:      5521000.000 %

----------------------------------------------------------
Sleep test: requested duration = 1 ns, iterations = 100
----------------------------------------------------------

Actual sleep duration statistics:
  Mean:            51558.650 ns (  51.559 us)
  Median:          52372.500 ns (  52.373 us)
  Stddev:           7925.843 ns (   7.926 us)
  Min:              5138     ns (   5.138 us)
  Max:             61980     ns (  61.980 us)
  Range:           56842     ns

Error (mean - requested):
  Absolute:        51557.650 ns (  51.558 us)  <=== WHAT I CARE ABOUT THE MOST
  Relative:      5155765.000 %

----------------------------------------------------------
Sleep test: requested duration = 1000000 ns (1.000 ms), iterations = 50
----------------------------------------------------------

Actual sleep duration statistics:
  Mean:          1060626.980 ns (   1.061 ms)
  Median:        1060087.500 ns (   1.060 ms)
  Stddev:           5347.188 ns (   5.347 us)
  Min:           1040862     ns (   1.041 ms)
  Max:           1079697     ns (   1.080 ms)
  Range:           38835     ns

Error (mean - requested):
  Absolute:        60626.980 ns (  60.627 us)  <=== WHAT I CARE ABOUT THE MOST
  Relative:            6.063 %

----------------------------------------------------------
Sleep test: requested duration = 2000000 ns (2.000 ms), iterations = 50
----------------------------------------------------------

Actual sleep duration statistics:
  Mean:          2070531.680 ns (   2.071 ms)
  Median:        2063482.000 ns (   2.063 ms)
  Stddev:          22918.334 ns (  22.918 us)
  Min:           2025927     ns (   2.026 ms)
  Max:           2188693     ns (   2.189 ms)
  Range:          162766     ns

Error (mean - requested):
  Absolute:        70531.680 ns (  70.532 us)  <=== WHAT I CARE ABOUT THE MOST
  Relative:            3.527 %

----------------------------------------------------------
Sleep test: requested duration = 10000000 ns (10.000 ms), iterations = 10
----------------------------------------------------------

Actual sleep duration statistics:
  Mean:         10087397.200 ns (  10.087 ms)
  Median:       10066011.000 ns (  10.066 ms)
  Stddev:          37349.955 ns (  37.350 us)
  Min:          10062112     ns (  10.062 ms)
  Max:          10181911     ns (  10.182 ms)
  Range:          119799     ns

Error (mean - requested):
  Absolute:        87397.200 ns (  87.397 us)  <=== WHAT I CARE ABOUT THE MOST
  Relative:            0.874 %

----------------------------------------------------------
Sleep test: requested duration = 20000000 ns (20.000 ms), iterations = 10
----------------------------------------------------------

Actual sleep duration statistics:
  Mean:         20101051.700 ns (  20.101 ms)
  Median:       20101640.000 ns (  20.102 ms)
  Stddev:          28222.627 ns (  28.223 us)
  Min:          20061646     ns (  20.062 ms)
  Max:          20166213     ns (  20.166 ms)
  Range:          104567     ns

Error (mean - requested):
  Absolute:       101051.700 ns ( 101.052 us)  <=== WHAT I CARE ABOUT THE MOST
  Relative:            0.505 %

----------------------------------------------------------
Sleep test: requested duration = 50000000 ns (50.000 ms), iterations = 10
----------------------------------------------------------

Actual sleep duration statistics:
  Mean:         50126353.700 ns (  50.126 ms)
  Median:       50109866.000 ns (  50.110 ms)
  Stddev:          54203.778 ns (  54.204 us)
  Min:          50066144     ns (  50.066 ms)
  Max:          50209016     ns (  50.209 ms)
  Range:          142872     ns

Error (mean - requested):
  Absolute:       126353.700 ns ( 126.354 us)  <=== WHAT I CARE ABOUT THE MOST
  Relative:            0.253 %

----------------------------------------------------------
Sleep test: requested duration = 100000000 ns (100.000 ms), iterations = 10
----------------------------------------------------------

Actual sleep duration statistics:
  Mean:        100084364.300 ns ( 100.084 ms)
  Median:      100068178.000 ns ( 100.068 ms)
  Stddev:          50602.555 ns (  50.603 us)
  Min:         100034244     ns ( 100.034 ms)
  Max:         100229060     ns ( 100.229 ms)
  Range:          194816     ns

Error (mean - requested):
  Absolute:        84364.300 ns (  84.364 us)  <=== WHAT I CARE ABOUT THE MOST
  Relative:            0.084 %

----------------------------------------------------------
Sleep test: requested duration = 500000000 ns (500.000 ms), iterations = 1
----------------------------------------------------------

Actual sleep duration statistics:
  Mean:        500091156.000 ns ( 500.091 ms)
  Median:      500091156.000 ns ( 500.091 ms)
  Stddev:              0.000 ns
  Min:         500091156     ns ( 500.091 ms)
  Max:         500091156     ns ( 500.091 ms)
  Range:               0     ns

Error (mean - requested):
  Absolute:        91156.000 ns (  91.156 us)  <=== WHAT I CARE ABOUT THE MOST
  Relative:            0.018 %

----------------------------------------------------------
Sleep test: requested duration = 1000000000 ns (1.000 s), iterations = 1
----------------------------------------------------------

Actual sleep duration statistics:
  Mean:       1000204313.000 ns (   1.000 s)
  Median:     1000204313.000 ns (   1.000 s)
  Stddev:              0.000 ns
  Min:        1000204313     ns (   1.000 s)
  Max:        1000204313     ns (   1.000 s)
  Range:               0     ns

Error (mean - requested):
  Absolute:       204313.000 ns ( 204.313 us)  <=== WHAT I CARE ABOUT THE MOST
  Relative:            0.020 %

real	0m7.647s
user	0m3.794s
sys	0m0.385s
*/



/*
EXAMPLE RUN ON WINDOWS:
Run inside of MSYS2 ucrt64 terminal. See my setup instructions here:
https://stackoverflow.com/a/77407282/4561887

tbd

*/
