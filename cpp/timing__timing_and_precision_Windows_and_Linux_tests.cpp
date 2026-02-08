///usr/bin/env ccache g++ -Wall -Wextra -Werror -O3 -std=gnu++20 "$0" -o bin/a_hashbang && bin/a_hashbang "$@"; exit
// For the line just above, see my answer here: https://stackoverflow.com/a/75491834/4561887

/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

C++ Windows and Linux cross-platform timing tests.

GS
Jan. 2026

STATUS: Done and works!

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# NB: you may need to use `-std=gnu++20` instead of `-std=c++20` in order to obtain extra GNU
# gcc features, including gcc extensions, POSIX cmds, and Linux sytem cmds.
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# [run once ever] install ccache
sudo apt update && sudo apt install ccache

# In C++:

# 1. For Linux
time g++ -Wall -Wextra -Werror -O3 -std=gnu++20 timing__timing_and_precision_Windows_and_Linux_tests.cpp -o bin/a && bin/a

# OR (just call this file as an exectuable directly)
# - This run technique works on Linux only right now because it's missing the required
#   `-lwinmm` Windows Multimedia Library (WinMM) linker flag for Windows.
time ./timing__timing_and_precision_Windows_and_Linux_tests.cpp

# 2. Cross-compiling from Linux for Windows via mingw-w64: https://www.mingw-w64.org/
sudo apt update
sudo apt install mingw-w64
# Then build only (don't run):
# - Requires the Windows Multimedia Library (WinMM) linker flag option via `-lwinmm`.
time x86_64-w64-mingw32-g++ -Wall -Wextra -Werror -O3 -std=gnu++20 timing__timing_and_precision_Windows_and_Linux_tests.cpp -o bin/a.exe -lwinmm

# 3. Building on Windows for Windows
# - Requires:
#   1. The MSYS2 ucrt64 environment with g++ installed (see my instructions here:
#      https://stackoverflow.com/a/77407282/4561887) and
#   2. The Windows Multimedia Library (WinMM) linker flag option via `-lwinmm`.
cd path/to/eRCaGuy_hello_world/cpp
#
# Then:
#
# Option 1: Run from the MSYS2 ucrt64 bash shell in Windows:
time g++ -Wall -Wextra -Werror -O3 -std=gnu++20 timing__timing_and_precision_Windows_and_Linux_tests.cpp -o bin/a -lwinmm && bin/a
#
# Option 2: Run from Powershell in Windows, accessing the MSYS2 ucrt64 bash shell automatically:
# - See my answer here under the section titled "When running from a Windows PowerShell":
#   https://stackoverflow.com/a/79201770/4561887
C:\msys64\msys2_shell.cmd -defterm -here -no-start -ucrt64 -shell bash -c 'time g++ -Wall -Wextra -Werror -O3 -std=gnu++20 timing__timing_and_precision_Windows_and_Linux_tests.cpp -o bin/a -lwinmm && bin/a'
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
1. https://learn.microsoft.com/en-us/windows/win32/api/timeapi/nf-timeapi-timebeginperiod:
   `timeBeginPeriod(1)` - to get higher-resolution and precision sleeps and timestamps and
   clocks in Windows!
1. GS NOTES: experimentation and research tells me that this `timeBeginPeriod(1)` call affects
   only the Windows `Sleep()` call, not the C++ `std::this_thread::sleep_for()` call. It is also
   expected to affect and improve the timeout precisions of the Windows `WSAPoll()` socket
   call.
   - Each call to `timeBeginPeriod()`/`timeEndPeriod()`, however: 1) affects the ENTIRE SYSTEM,
     not just your program, 2) increases power consumption system-wide, and 3) is inefficient,
    taking ~200 us each call (range: 2~500us per call).

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
(newest on BOTTOM)
[x] Print timestamp stats for all 3 major clocks, also indicating if certain clocks are the same
   based on `using` declarations.
[x] Use the highest precision clock timestamps to then time sleep calls of various lengths, and
   see how accurate they are. Identify the minimum sleep time that is possible.
   ex: 1ns, 1ms, 2ms, 10ms, 20ms, 50ms, 100ms, 500ms, 1s.
[x] Write standalone mean, median, mode, stddev, etc. stats functions and quit duplicating that
   logic in both `test_and_print_clock_precision()` and `sleep_test()`.
[ ] Finish sleep tests; [x] collect all stats; [ ] print results
[ ] Tabulate the results nicely. Reading them in paragraph type form is tedious.
[ ] Do the todos here too: "eRCaGuy_hello_world/TODO2.txt"

*/


// C++ (incl. C) includes
#include <algorithm>  // For `std::sort`
#include <array>
#include <chrono>
#include <cinttypes>  // For `PRIu64`
#include <cmath>  // For `sqrt`
#include <cstdint>  // For `uint8_t`, `int8_t`, etc.
#include <cstdio>   // For `printf()`
#include <format>   // For `std::format`
#include <fstream>  // For file I/O
#include <iostream>  // For `std::cin`, `std::cout`, `std::endl`, etc.
#include <string>
#include <thread>  // For `std::this_thread::sleep_for`
#include <type_traits>  // For `std::is_same`
#include <unordered_map>  // For mode calculation
#include <vector>  // For `std::vector`

// Sample size for testing clock precision.
static constexpr size_t SAMPLE_SIZE = 20'000'000;

/// Get the number of elements in any C array.
/// - Usage example: [my own answer]:
///   https://arduino.stackexchange.com/a/80289/7727
#define ARRAY_LEN(array) (sizeof(array) / sizeof((array)[0]))

// Get time stamp in nanoseconds.
// - See my answer: https://stackoverflow.com/a/49066369/4561887
template<typename MeasurementClock = std::chrono::steady_clock>
uint64_t nanos()
{
    uint64_t ns = std::chrono::duration_cast<std::chrono::nanoseconds>(
            MeasurementClock::now().time_since_epoch())
            .count();
    return ns;
}

// 1. Calculate mean
template <typename SampleType>
double calculate_mean(const std::vector<SampleType>& data)
{
    SampleType sum = 0;
    for (size_t i = 0; i < data.size(); i++)
    {
        sum += data[i];
    }
    double mean = static_cast<double>(sum) / data.size();
    return mean;
}

// 2. Calculate median (requires that this function make a copy of the data and then sort it).
// To receive back the sorted data, pass in a non-null pointer to a vector via `data_sorted`.
template <typename SampleType>
double calculate_median(const std::vector<SampleType>& data,
    std::vector<SampleType>* data_sorted = nullptr)
{
    std::vector<SampleType> data_sorted_ = data;
    std::sort(data_sorted_.begin(), data_sorted_.end());
    if (data_sorted != nullptr)
    {
        // Pass back the sorted data to the user, if requested
        *data_sorted = data_sorted_;
    }

    double median;
    size_t i_mid = data_sorted_.size() / 2;
    if (data_sorted_.size() % 2 == 0)
    {
        // There are an even number of elements
        median = (data_sorted_[i_mid - 1] + data_sorted_[i_mid]) / 2.0;
    }
    else
    {
        // There are an odd number of elements
        median = data_sorted_[i_mid];
    }
    return median;
}

// 3. Calculate min.
// - You must pass in a sorted data vector--ex: received from `calculate_median()`.
template <typename SampleType>
SampleType calculate_min(const std::vector<SampleType>& data_sorted)
{
    return data_sorted.front();
}

// 4. Calculate max.
// - You must pass in a sorted data vector--ex: received from `calculate_median()`.
template <typename SampleType>
SampleType calculate_max(const std::vector<SampleType>& data_sorted)
{
    return data_sorted.back();
}

// 5. Calculate mode (most frequent value)
// - Optionally receive back the mode's max count too via the `mode_count` pointer.
template <typename SampleType>
SampleType calculate_mode(const std::vector<SampleType>& data, size_t *mode_count = nullptr)
{
    std::unordered_map<SampleType, size_t> frequency_map;
    for (size_t i = 0; i < data.size(); i++)
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
        frequency_map[data[i]]++;
    }

    // Find the value with the highest frequency
    SampleType mode = 0;
    size_t max_count = 0;
    for (const std::pair<const SampleType, size_t>& pair : frequency_map)
    {
        SampleType number = pair.first; // key
        size_t count = pair.second;   // value

        if (count > max_count)
        {
            max_count = count;
            mode = number;
        }
    }

    if (mode_count != nullptr)
    {
        *mode_count = max_count;
    }

    return mode;
}

// 6. Calculate Standard Deviation
// - This is the spread of the data around the mean.
// - It is calculated as the square root of the variance, where the variance is the average
//   of the squared differences from the mean.
template <typename SampleType>
double calculate_stddev(const std::vector<SampleType>& data, double mean)
{
    // sum of the squared differences from the mean
    double variance_sum = 0;

    for (size_t i = 0; i < data.size(); i++)
    {
        double difference = data[i] - mean;
        double difference_squared = difference * difference;
        variance_sum += difference_squared;
    }

    // avg of the squared differences
    double variance = variance_sum / data.size();

    // sqrt of the variance
    double stddev = std::sqrt(variance);

    return stddev;
}

template <typename SampleType>
struct Stats
{
    double mean;
    double median;
    SampleType min;
    SampleType max;
    SampleType range;         // max - min
    SampleType mode;          // the most frequently occurring value
    size_t mode_count;  // the number of times the mode value appears
    double mode_pct;        // the percentage of times the mode value appears
    double stddev;

    // Pointer to the original data vector; NOT owned by this struct
    const std::vector<SampleType>* data;
    // Copy of the original data vector, sorted; IS owned by this struct
    std::vector<SampleType> data_sorted;
};

template <typename SampleType>
Stats<SampleType> calculate_stats(const std::vector<SampleType>& data)
{
    Stats<SampleType> stats;

    stats.data = &data;
    stats.mean = calculate_mean(data);
    stats.median = calculate_median(data, &stats.data_sorted);
    stats.min = calculate_min(stats.data_sorted);
    stats.max = calculate_max(stats.data_sorted);
    stats.range = stats.max - stats.min;
    stats.mode = calculate_mode(data, &stats.mode_count);
    stats.mode_pct = (100.0 * stats.mode_count) / data.size();
    stats.stddev = calculate_stddev(data, stats.mean);

    return stats;
}

// Run clock precision tests for the specified clock type, and print all results.
template<typename MeasurementClock>
void test_and_print_clock_precision(std::vector<Stats<uint64_t>>* all_clock_stats)
{
    if (all_clock_stats == nullptr)
    {
        std::cout << "Error: all_clock_stats pointer is null!\n";
        return;
    }

    // NB: use `static` to keep off the stack, as it will overflow the stack if too big.
    // - See stack sizes: https://stackoverflow.com/a/64085509/4561887
    // Even better, use dynamic memory allocation via `std::vector` instead, as `static`
    // variables get placed into the Windows executable, making it huge (~300 MB).
    std::vector<uint64_t> timestamps_ns;
    // resize to allocate and initialize elements (use resize here, not reserve, since I'm using the
    // size() and indices below!)
    timestamps_ns.resize(SAMPLE_SIZE);

    // Get timestamps as fast as possible
    for (size_t i = 0; i < timestamps_ns.size(); i++)
    {
        timestamps_ns[i] = nanos<MeasurementClock>();
    }

    // Calculate time deltas between successive timestamps
    const size_t MAX_NUM_DELTAS_POSSIBLE = timestamps_ns.size() - 1;
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

    printf("\ninvalid_delta_count = %zu (%.2f%%) (it is expected that there will be "
        "0 invalid sample deltas on Linux, and tons [the majority] to be invalid on Windows)\n\n",
        invalid_delta_count,
        (100.0 * invalid_delta_count) / MAX_NUM_DELTAS_POSSIBLE);

    // Calculate stats: mean, median, mode, and stddev of the time differences
    Stats stats = calculate_stats(deltas_ns);
    all_clock_stats->push_back(stats);

    // Print results

    printf("Estimation of your clock precision:\n\n");
    printf("Mean:   %11.3f ns\n", stats.mean);
    printf("Median: %11.3f ns\n", stats.median);
    printf("Mode:   %7" PRIu64 "     ns (appears %zu times, %.3f%%)  <=== ESTIMATED "
        "CLOCK PRECISION; MOST RELIABLE ESTIMATE\n",
           stats.mode, stats.mode_count, stats.mode_pct);
    printf("Stddev: %11.3f ns\n", stats.stddev);

    printf("\nAdditional stats:\n");
    printf("Min:    %7" PRIu64 " ns\n", stats.min);
    printf("Max:    %7" PRIu64 " ns\n", stats.max);
    printf("Range:  %7" PRIu64 " ns\n", stats.range);
}

enum class SleepType
{
    // ------------------------------------------
    // Windows and Linux
    // ------------------------------------------

    // C++ `std::this_thread::sleep_for()`.
    STD_THISTHREAD_SLEEPFOR = 0,

    // ------------------------------------------
    // Windows only
    // ------------------------------------------

    // C++ `std::this_thread::sleep_for()` on Windows with `timeBeginPeriod(minimum)` called first.
    WINDOWS__STD_THISTHREAD_SLEEPFOR_WITH_TIMEBEGINPERIOD_EVERY_CALL,

    // LEGACY DEFAULT: Windows `Sleep()` withOUT `timeBeginPeriod(minimum)` called first.
    // - Legacy ~15.6 ms precision on Windows.
    WINDOWS_LEGACY_DEFAULT__SLEEP_WITHOUT_TIMEBEGINPERIOD,

    // LEGACY BETTER: Windows `Sleep()` WITH `timeBeginPeriod(minimum)` called first every sleep
    // call.
    // - Legacy ~1ms precision on Windows.
    // - System-wide impact.
    // - NB: it is inefficient to call `timeBeginPeriod(minimum)` and `timeEndPeriod(minimum)` every
    //   sleep call since it takes ~200 us avg. per begin or end call. The approximate time range is
    //   2~500us per call.
    WINDOWS_LEGACY_BETTER__SLEEP_WITH_TIMEBEGINPERIOD_EVERY_CALL,

    // LEGACY BEST: Windows `Sleep()` WITH `timeBeginPeriod(minimum)` called once at the start of
    // the program.
    // - Legacy ~1ms precision on Windows.
    // - System-wide impact.
    // - Most efficient way to use `timeBeginPeriod(minimum)`/`timeEndPeriod(minimum)`: calling it
    //   only once each per program run.
    WINDOWS_LEGACY_BEST__SLEEP_WITH_TIMEBEGINPERIOD_SINGLE_CALL,

    // MODERN BEST: Windows waitable timers via `CreateWaitableTimerEx()`.
    // - Modern single-process impact.
    // - Modern ~0.5ms~1ms precision on Windows.
    WINDOWS_MODERN_BEST__WAITABLE_TIMER,

    // Hybrid approach: to use a sophisticated modern hybrid approach which allows loop iteration
    // times < 1ms on Windows, you must use a 100%-CPU-usage busy-wait loop with Windows' 100 ns
    // clock, such as `std::chrono::steady_clock`.
    // - This is best done with a hybrid approach where you first use my
    //   `WINDOWS_MODERN_BEST__WAITABLE_TIMER` approach to sleep for the desired time less ~2ms,
    //   then use a busy-wait loop via `nanos<std::chrono::steady_clock>()` timestamp calls for the
    //   last ~2ms to hit your desired time precisely.
    // - Uses busy-wait.
    // - Has 100% CPU usage for any sleeps < ~2ms.
    WINDOWS_HYBRID__SLEEP_PLUS_BUSY_WAIT,

    // ------------------------------------------
    // Linux only
    // ------------------------------------------

    // Linux `clock_nanosleep()` via my "c/timinglib.h/.c" library `sleep_ns()` call.
    LINUX__CLOCK_NANOSLEEP,

    // Linux `clock_nanosleep()` via my "c/timinglib.h/.c" library `use_realtime_scheduler()`
    // and then `sleep_ns()` calls.
    // - Uses the Linux `SCHED_RR` soft real-time round-robin scheduler to improve sleep precision.
    LINUX__CLOCK_NANOSLEEP_WITH_SOFT_REALTIME_SCHEDULER,

    // Linux `std::this_thread::sleep_for()` with `use_realtime_scheduler()` called first.
    // - Uses the Linux `SCHED_RR` soft real-time round-robin scheduler to improve sleep precision.
    LINUX__STD_THISTHREAD_SLEEPFOR_WITH_SOFT_REALTIME_SCHEDULER,

    // ------------------------------------------
    // NA; enum helpers
    // ------------------------------------------

    // Not a sleep type; used to count the number of sleep types.
    count,
};

// Array of strings to map enum error types to printable strings.
// - See my answer: https://stackoverflow.com/a/59221452/4561887
const char* const SLEEP_TYPE_STRS[] =
{
    "STD_THISTHREAD_SLEEPFOR",
    "WINDOWS__STD_THISTHREAD_SLEEPFOR_WITH_TIMEBEGINPERIOD_EVERY_CALL",
    "WINDOWS_LEGACY_DEFAULT__SLEEP_WITHOUT_TIMEBEGINPERIOD",
    "WINDOWS_LEGACY_BETTER__SLEEP_WITH_TIMEBEGINPERIOD_EVERY_CALL",
    "WINDOWS_LEGACY_BEST__SLEEP_WITH_TIMEBEGINPERIOD_SINGLE_CALL",
    "WINDOWS_MODERN_BEST__WAITABLE_TIMER",
    "WINDOWS_HYBRID__SLEEP_PLUS_BUSY_WAIT",
    "LINUX__CLOCK_NANOSLEEP",
    "LINUX__CLOCK_NANOSLEEP_WITH_SOFT_REALTIME_SCHEDULER",
    "LINUX__STD_THISTHREAD_SLEEPFOR_WITH_SOFT_REALTIME_SCHEDULER",
};
static_assert(ARRAY_LEN(SLEEP_TYPE_STRS) == static_cast<size_t>(SleepType::count),
    "You must keep your `SleepType` enum and your `SLEEP_TYPE_STRS` array in-sync!");

// To get a printable error string
const char* sleep_type_to_str(SleepType sleep_type)
{
    const char* str = "Invalid";
    size_t i = static_cast<size_t>(sleep_type);

    if (i >= ARRAY_LEN(SLEEP_TYPE_STRS))
    {
        return str;
    }

    str = SLEEP_TYPE_STRS[i];
    return str;
}

// Function pointer to the sleep setup and teardown functions.
using VoidVoidFuncPtr = void (*)();

// Function pointer to sleep functions.
// Parameters:
//   [in]  uint64_t sleep_time_ns,
//   [out] uint64_t *actual_sleep_time_ns = nullptr,
//   [out] uint64_t *non_sleep_time_ns = nullptr
using SleepFuncPtr = void (*)(uint64_t, uint64_t*, uint64_t*);

// STD_THISTHREAD_SLEEPFOR
// - See the description for this in the `enum class SleepType`.
// Args:
// - sleep_time_ns: desired sleep time in nanoseconds.
// - actual_sleep_time_ns: if not nullptr, the actual sleep time will be written here.
// - non_sleep_time_ns: if not nullptr, the time spent outside the sleep call will be written here.
//      ie: this is "overhead", or wasted time just to set up the sleep call.
template<typename MeasurementClock>
void sleep_ns__STD_THISTHREAD_SLEEPFOR(
    uint64_t sleep_time_ns,
    uint64_t *actual_sleep_time_ns = nullptr,
    uint64_t *non_sleep_time_ns = nullptr)
{
    // For both Windows and Linux

    uint64_t t_start_ns = nanos<MeasurementClock>();
    std::this_thread::sleep_for(std::chrono::nanoseconds(sleep_time_ns));
    uint64_t t_end_ns = nanos<MeasurementClock>();

    if (actual_sleep_time_ns != nullptr)
    {
        *actual_sleep_time_ns = t_end_ns - t_start_ns;
    }

    if (non_sleep_time_ns != nullptr)
    {
        uint64_t t_now_ns = nanos<MeasurementClock>();
        *non_sleep_time_ns = t_now_ns - t_end_ns;
    }
}

#ifdef _WIN64
// Windows only

// WINDOWS__STD_THISTHREAD_SLEEPFOR_WITH_TIMEBEGINPERIOD_EVERY_CALL
template<typename MeasurementClock>
void sleep_ns__WINDOWS__STD_THISTHREAD_SLEEPFOR_WITH_TIMEBEGINPERIOD_EVERY_CALL(
    uint64_t sleep_time_ns,
    uint64_t *actual_sleep_time_ns = nullptr,
    uint64_t *non_sleep_time_ns = nullptr)
{

}
#endif // _WIN64

// Sleep once using the specified sleep type and duration, timing how long it takes and
// calculating the CPU usage percentage during the sleep call.
void sleep_once(
    SleepFuncPtr sleep_ns_func,
    uint64_t requested_sleep_time_ns,
    uint64_t *actual_sleep_time_ns = nullptr,
    uint64_t *non_sleep_time_ns = nullptr,
    double *cpu_usage_pct = nullptr)
{
    if (sleep_ns_func == nullptr)
    {
        std::cout << "Error: sleep function pointer is null!\n";
        return;
    }

    // Call the sleep function
    sleep_ns_func(requested_sleep_time_ns, actual_sleep_time_ns, non_sleep_time_ns);

    // Calculate and pass out CPU usage percentage during the sleep call, since parts of the
    // sleep call may be setup code that uses CPU time.
    if (actual_sleep_time_ns != nullptr && non_sleep_time_ns != nullptr && cpu_usage_pct != nullptr)
    {
        // Calculate CPU usage percentage during the sleep call
        uint64_t total_time_ns = *actual_sleep_time_ns + *non_sleep_time_ns;
        *cpu_usage_pct = static_cast<double>(*non_sleep_time_ns) / total_time_ns * 100.0;
    }
}

struct SleepStat
{
    // --------------------------------------
    // One-time sleep setup, if applicable
    // --------------------------------------

    // Function intended to be run once at the start of the program before any sleeps.
    VoidVoidFuncPtr sleep_setup_func = nullptr;
    std::string sleep_setup_name = "NA";
    uint64_t sleep_setup_time_ns = 0;

    // --------------------------------------
    // Sleep call itself
    // --------------------------------------

    SleepType sleep_type;
    std::string sleep_type_name;
    uint64_t requested_sleep_time_ns;
    uint64_t num_iterations; // number of times to test the sleep call duration

    // The sleep call itself to sleep a certain number of nanoseconds.
    SleepFuncPtr sleep_func = nullptr;
    std::string sleep_func_name;

    std::vector<uint64_t> actual_sleep_times_ns;
    Stats<uint64_t> sleep_stats;
    double sleep_error_ns; // `sleep_stats.mean - requested_sleep_time_ns`
    double sleep_error_pct; // `100.0 * sleep_error_ns / requested_sleep_time_ns`

    std::vector<uint64_t> non_sleep_times_ns;
    Stats<uint64_t> non_sleep_stats;

    // From the user's perspective, the "sleep time" is the total time spent in the sleep call,
    // which includes both the actual sleep time and the non-sleep time (setup overhead, etc.).
    //////////
    std::vector<uint64_t> user_sleep_times_ns;
    Stats<uint64_t> user_sleep_stats;
    ////////
    double sleep_error_user_ns; // `user_sleep_stats.mean - requested_sleep_time_ns`
    double sleep_error_user_pct; // `100.0 * sleep_error_user_ns / requested_sleep_time_ns`

    std::vector<double> cpu_usages_pct;
    Stats<double> cpu_usage_stats;

    // --------------------------------------
    // One-time sleep teardown, if applicable
    // --------------------------------------

    // Function intended to be run once at the end of the program after all sleeps.
    VoidVoidFuncPtr sleep_teardown_func = nullptr;
    std::string sleep_teardown_name = "NA";
    uint64_t sleep_teardown_time_ns = 0;
};

// Test sleep precision by sleeping multiple times and measuring actual sleep duration using
// `MeasurementClock`.
// - Return a `SleepStat` struct containing all relevant data and statistics.
template<typename MeasurementClock, typename SleepDuration>
void sleep_test(
    std::array<std::vector<SleepStat>, static_cast<size_t>(SleepType::count)>* sleep_stats_array,
    SleepType sleep_type, SleepDuration sleep_duration, size_t num_iterations)
{
    if (sleep_stats_array == nullptr)
    {
        std::cout << "Error: sleep_stats_array pointer is null!\n";
        return;
    }

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

    SleepStat sleep_stat;
    sleep_stat.sleep_type = sleep_type;
    sleep_stat.sleep_type_name = sleep_type_to_str(sleep_type);
    sleep_stat.requested_sleep_time_ns = requested_ns;
    sleep_stat.num_iterations = num_iterations;

    switch (sleep_type)
    {
        case SleepType::STD_THISTHREAD_SLEEPFOR:
        {
            sleep_stat.sleep_func = &sleep_ns__STD_THISTHREAD_SLEEPFOR<MeasurementClock>;
            sleep_stat.sleep_func_name = "sleep_ns__STD_THISTHREAD_SLEEPFOR()";
            break;
        }
        case SleepType::WINDOWS__STD_THISTHREAD_SLEEPFOR_WITH_TIMEBEGINPERIOD_EVERY_CALL:
        {
            #ifdef _WIN64
            // Windows only
            sleep_stat.sleep_func =
                &sleep_ns__WINDOWS__STD_THISTHREAD_SLEEPFOR_WITH_TIMEBEGINPERIOD_EVERY_CALL<MeasurementClock>;
            sleep_stat.sleep_func_name =
                "sleep_ns__WINDOWS__STD_THISTHREAD_SLEEPFOR_WITH_TIMEBEGINPERIOD_EVERY_CALL()";
            #endif // _WIN64
            break;
        }
        case SleepType::WINDOWS_LEGACY_DEFAULT__SLEEP_WITHOUT_TIMEBEGINPERIOD:
        {
            #ifdef _WIN64
            // Windows only
            #endif // _WIN64
            break;
        }
        case SleepType::WINDOWS_LEGACY_BETTER__SLEEP_WITH_TIMEBEGINPERIOD_EVERY_CALL:
        {
            #ifdef _WIN64
            // Windows only
            #endif // _WIN64
            //////
            break;
        }
        case SleepType::WINDOWS_LEGACY_BEST__SLEEP_WITH_TIMEBEGINPERIOD_SINGLE_CALL:
        {
            #ifdef _WIN64
            // Windows only
            #endif // _WIN64
            //////
            break;
        }
        case SleepType::WINDOWS_MODERN_BEST__WAITABLE_TIMER:
        {
            #ifdef _WIN64
            // Windows only
            #endif // _WIN64
            //////
            break;
        }
        case SleepType::WINDOWS_HYBRID__SLEEP_PLUS_BUSY_WAIT:
        {
            #ifdef _WIN64
            // Windows only
            #endif // _WIN64
            //////
            break;
        }
        case SleepType::LINUX__CLOCK_NANOSLEEP:
        {
            #ifndef _WIN64
            // Linux only
            #endif // not _WIN64
            //////
            break;
        }
        case SleepType::LINUX__CLOCK_NANOSLEEP_WITH_SOFT_REALTIME_SCHEDULER:
        {
            #ifndef _WIN64
            // Linux only
            #endif // not _WIN64
            //////
            break;
        }
        case SleepType::LINUX__STD_THISTHREAD_SLEEPFOR_WITH_SOFT_REALTIME_SCHEDULER:
        {
            #ifndef _WIN64
            // Linux only
            #endif // not _WIN64
            //////
            break;
        }
        case SleepType::count:
        {
            // Invalid
            std::cout << "Error: invalid sleep type: SleepType::count\n";
            return;
        }
    }

    // Prepare to perform sleep tests

    size_t num_successful_sleeps = 0;
    size_t num_failed_sleeps = 0;

    // sleep setup
    if (sleep_stat.sleep_setup_func != nullptr)
    {
        uint64_t t_start_ns = nanos<MeasurementClock>();
        sleep_stat.sleep_setup_func();
        uint64_t t_end_ns = nanos<MeasurementClock>();
        sleep_stat.sleep_setup_time_ns = t_end_ns - t_start_ns;
    }

    if (sleep_stat.sleep_func == nullptr)
    {
        std::cout << "Not sleeping: sleep function not implemented for sleep type: "
            << sleep_type_to_str(sleep_type) << "\n";
        return;
    }

    // Perform sleep tests
    while (num_successful_sleeps < num_iterations)
    {
        // Variables to receive sleep results for this iteration
        uint64_t actual_sleep_time_ns = 0;
        uint64_t non_sleep_time_ns = 0;
        double cpu_usage_pct = 0.0;

        sleep_once(
            sleep_stat.sleep_func,
            sleep_stat.requested_sleep_time_ns,
            &actual_sleep_time_ns,
            &non_sleep_time_ns,
            &cpu_usage_pct);

        if (actual_sleep_time_ns == 0)
        {
            // This should never happen unless the clock precision is very poor, or
            // on ultra-short sleeps which probably just yielded for a moment but didn't sleep.
            // - This is a Windows-only problem not seen on Linux.
            num_failed_sleeps++;
            continue;
        }

        num_successful_sleeps++;

        uint64_t user_sleep_time_ns = actual_sleep_time_ns + non_sleep_time_ns;

        // Store results for this iteration
        sleep_stat.actual_sleep_times_ns.push_back(actual_sleep_time_ns);
        sleep_stat.non_sleep_times_ns.push_back(non_sleep_time_ns);
        sleep_stat.user_sleep_times_ns.push_back(user_sleep_time_ns);
        sleep_stat.cpu_usages_pct.push_back(cpu_usage_pct);
    }

    // Calculate statistics
    sleep_stat.sleep_stats = calculate_stats(sleep_stat.actual_sleep_times_ns);
    sleep_stat.non_sleep_stats = calculate_stats(sleep_stat.non_sleep_times_ns);
    sleep_stat.user_sleep_stats = calculate_stats(sleep_stat.user_sleep_times_ns);
    sleep_stat.cpu_usage_stats = calculate_stats(sleep_stat.cpu_usages_pct);

    // Print results
    // - For now, just print the sleep duration stats.
    const Stats<uint64_t>& stats = sleep_stat.sleep_stats;

    if (num_failed_sleeps > 0)
    {
        printf("\nWARNING: %zu failed sleeps due to clock precision being too poor to measure such\n"
            "a short duration. Probably no sleep took place at all, but a yield may have occurred\n"
            "in which the OS's scheduler ran for a duration <= the clock's minimum resolution.\n"
            "- This is expected on Windows, not on Linux.\n"
            "- Probable yield duration: < %" PRIu64 " ns\n",
            num_failed_sleeps, stats.min);
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

    printf("  Mean:     %16.3f ns", stats.mean);
    PRINT_HUMAN_READABLE(stats.mean);
    printf("\n");

    printf("  Median:   %16.3f ns", stats.median);
    PRINT_HUMAN_READABLE(stats.median);
    printf("  <=== MEDIAN ACTUAL SLEEP\n");

    printf("  Stddev:   %16.3f ns", stats.stddev);
    PRINT_HUMAN_READABLE(stats.stddev);
    printf("\n");

    printf("  Min:      %12" PRIu64 "     ns", stats.min);
    PRINT_HUMAN_READABLE(stats.min);
    printf("\n");

    printf("  Max:      %12" PRIu64 "     ns", stats.max);
    PRINT_HUMAN_READABLE(stats.max);
    printf("\n");

    printf("  Range:    %12" PRIu64 "     ns", stats.range);
    PRINT_HUMAN_READABLE(stats.range);
    printf("\n");

    // Calculate error
    sleep_stat.sleep_error_ns = sleep_stat.sleep_stats.mean - sleep_stat.requested_sleep_time_ns;
    sleep_stat.sleep_error_pct =
        100.0 * sleep_stat.sleep_error_ns / sleep_stat.requested_sleep_time_ns;

    printf("\nError (mean - requested):\n");
    printf("  Absolute: %16.3f ns", sleep_stat.sleep_error_ns);
    PRINT_HUMAN_READABLE_ABS(sleep_stat.sleep_error_ns);
    printf("  <=== WHAT I CARE ABOUT THE MOST\n");
    printf("  Relative: %16.3f %%\n", sleep_stat.sleep_error_pct);

    (*sleep_stats_array)[static_cast<size_t>(sleep_type)].push_back(sleep_stat);
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


    std::vector<Stats<uint64_t>> all_clock_stats; // one Stats struct per clock type

    printf("\n"
        "----------------------------------------------------------\n"
        "Testing `std::chrono::system_clock` precision:\n"
        "----------------------------------------------------------\n");
    test_and_print_clock_precision<std::chrono::system_clock>(&all_clock_stats);

    printf("\n"
        "----------------------------------------------------------\n"
        "Testing `std::chrono::steady_clock` precision:\n"
        "----------------------------------------------------------\n");
    test_and_print_clock_precision<std::chrono::steady_clock>(&all_clock_stats);

    printf("\n"
        "----------------------------------------------------------\n"
        "Testing `std::chrono::high_resolution_clock` precision:\n"
        "----------------------------------------------------------\n");
    test_and_print_clock_precision<std::chrono::high_resolution_clock>(&all_clock_stats);

    // // Print a markdown table of all clock precision stats, writing it to a .md file
    // {
    //     const char* clock_names[] = {
    //         "std::chrono::system_clock",
    //         "std::chrono::steady_clock",
    //         "std::chrono::high_resolution_clock"
    //     };

    //     std::string filename = "timing__timing_and_precision_Windows_and_Linux_tests_RESULTS.md";
    //     // Construct and open the file all at once
    //     std::ofstream outfile(filename);

    //     if (!outfile.is_open())
    //     {
    //         std::cout << "Error: Could not open file " << filename << " for writing\n";
    //     }
    //     else
    //     {
    //         outfile << "# Clock Precision Statistics\n\n";
    //         outfile << "| Clock Type | Mean (ns) | Median (ns) | Mode (ns)* | Mode Count | Mode % | Stddev (ns) | Min (ns) | Max (ns) | Range (ns) |\n";
    //         outfile << "|------------|-----------|-------------|-----------|------------|--------|-------------|----------|----------|------------|\n";

    //         for (size_t i = 0; i < all_clock_stats.size() && i < 3; i++)
    //         {
    //             const Stats<uint64_t>& stats = all_clock_stats[i];
    //             outfile << std::format(
    //                 "| {} | {:.3f} | {:.3f} | {} | {} | {:.2f}% | {:.3f} | {} | {} | {} |\n",
    //                 clock_names[i],
    //                 stats.mean,
    //                 stats.median,
    //                 stats.mode,
    //                 stats.mode_count,
    //                 stats.mode_pct,
    //                 stats.stddev,
    //                 stats.min,
    //                 stats.max,
    //                 stats.range);
    //         }

    //         outfile.close();
    //         std::cout << "\nClock precision statistics written to: " << filename << "\n";
    //     }
    // }

    printf("\n");
    printf("===================================================================================\n");
    printf("2. Sleep precision tests\n");
    printf("===================================================================================\n");

    // Allow for a different selection of clock type for measurements just in case we need to
    // for Windows (in case its steady clock is very poor resolution).
#if defined(_WIN32)
    // Windows: testing shows `std::chrono::steady_clock` to have exactly 100 ns precision
    // on Windows 11 on my hardware
    using measurement_clock_type = std::chrono::steady_clock;
#elif defined (__linux__)
    // Linux: testing shows `std::chrono::steady_clock` to have ~20 ns precision on Linux
    // Ubuntu 22.04 on my hardware
    using measurement_clock_type = std::chrono::steady_clock;
#endif

    using namespace std::chrono_literals;

    printf("IMPORTANT: For Windows, expect that no true sleep will occur for any requested\n"
        "  duration < 1 ms. Rather, it will be at best only a short yield to the OS scheduler.\n"
        "  Deduction indicates that true sleeps don't begin on Windows until >= 1 ms.\n");

    // Iterate over all of the enum sleep types
    // - See my answer: https://stackoverflow.com/a/69762682/4561887
    // Array of vectors of sleep stats, one vector per sleep type
    std::array<std::vector<SleepStat>, static_cast<size_t>(SleepType::count)> all_sleep_stats;
    for (size_t i_sleep_type = 0;
         i_sleep_type < static_cast<size_t>(SleepType::count);
         i_sleep_type++)
    {
        SleepType sleep_type = static_cast<SleepType>(i_sleep_type);

        printf("\n\n"
               "############################################################################\n");
        printf("Sleep Type %zu: %s\n", i_sleep_type, sleep_type_to_str(sleep_type));
        printf("############################################################################\n");

        // Now run all sleep durations for this sleep type

        // sanity check to compare to the next line to see if 1 ulta-short sleep iteration works ok
        sleep_test<measurement_clock_type>(&all_sleep_stats, sleep_type, 1ns, 1);
        sleep_test<measurement_clock_type>(&all_sleep_stats, sleep_type, 1ns, 100);
        sleep_test<measurement_clock_type>(&all_sleep_stats, sleep_type, 1us, 50);
        sleep_test<measurement_clock_type>(&all_sleep_stats, sleep_type, 10us, 50);
        sleep_test<measurement_clock_type>(&all_sleep_stats, sleep_type, 20us, 50);
        sleep_test<measurement_clock_type>(&all_sleep_stats, sleep_type, 30us, 50);
        sleep_test<measurement_clock_type>(&all_sleep_stats, sleep_type, 50us, 50);
        sleep_test<measurement_clock_type>(&all_sleep_stats, sleep_type, 100us, 50);
        sleep_test<measurement_clock_type>(&all_sleep_stats, sleep_type, 200us, 50);
        sleep_test<measurement_clock_type>(&all_sleep_stats, sleep_type, 500us, 50);
        sleep_test<measurement_clock_type>(&all_sleep_stats, sleep_type, 1ms, 50);
        sleep_test<measurement_clock_type>(&all_sleep_stats, sleep_type, 2ms, 50);
        sleep_test<measurement_clock_type>(&all_sleep_stats, sleep_type, 10ms, 10);
        sleep_test<measurement_clock_type>(&all_sleep_stats, sleep_type, 20ms, 10);
        sleep_test<measurement_clock_type>(&all_sleep_stats, sleep_type, 50ms, 10);
        sleep_test<measurement_clock_type>(&all_sleep_stats, sleep_type, 100ms, 10);
        sleep_test<measurement_clock_type>(&all_sleep_stats, sleep_type, 500ms, 1);
        sleep_test<measurement_clock_type>(&all_sleep_stats, sleep_type, 1s, 1);
    }

    //////////////// print markdown tables at end

    return 0;
}


/*
EXAMPLE RUN ON LINUX:

eRCaGuy_hello_world$ time cpp/timing__timing_and_precision_Windows_and_Linux_tests.cpp
cpp/timing__timing_and_precision_Windows_and_Linux_tests.cpp running...
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
