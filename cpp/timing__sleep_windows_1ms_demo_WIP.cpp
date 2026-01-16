///usr/bin/env echo "This file is for Windows only. Compile on Windows with: cl windows_1ms_sleep_demo.cpp /link winmm.lib"; exit
// Or with MinGW: g++ -Wall -Wextra -O3 -std=c++17 windows_1ms_sleep_demo.cpp -o windows_1ms_sleep_demo.exe -lwinmm

/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

Windows 1ms Sleep Resolution Demo

Demonstrates how to achieve 1ms resolution sleep timing in Windows by using the
timeBeginPeriod/timeEndPeriod API from the Windows Multimedia library.

GS
Jan. 2026

Assisted by AI, NOT tested yet.
STATUS: wip

To compile and run on Windows:
```bash
# Using Visual Studio compiler
cl windows_1ms_sleep_demo.cpp /link winmm.lib
windows_1ms_sleep_demo.exe

# OR using MinGW
g++ -Wall -Wextra -O3 -std=c++17 windows_1ms_sleep_demo.cpp -o windows_1ms_sleep_demo.exe -lwinmm
./windows_1ms_sleep_demo.exe
```

Key Points:
1. Without timeBeginPeriod(1), Windows sleep has ~15.6ms resolution
2. With timeBeginPeriod(1), you can achieve ~1ms resolution
3. Always call timeEndPeriod() to restore the default timer resolution
4. This affects the entire system, not just your application
5. Use sparingly as it increases power consumption

References:
1. https://learn.microsoft.com/en-us/windows/win32/api/timeapi/nf-timeapi-timebeginperiod
2. https://learn.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-sleep
3. https://randomascii.wordpress.com/2020/10/04/windows-timer-resolution-the-great-rule-change/
*/

#ifdef _WIN32

#include <windows.h>    // For Sleep()
#include <timeapi.h>    // For timeBeginPeriod/timeEndPeriod
#include <chrono>
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>    // For std::sort
#include <cmath>        // For std::sqrt

// Pragma to link winmm.lib automatically with MSVC
#pragma comment(lib, "winmm.lib")

// Get high-resolution timestamp in nanoseconds
uint64_t nanos()
{
    return std::chrono::duration_cast<std::chrono::nanoseconds>(
        std::chrono::high_resolution_clock::now().time_since_epoch()).count();
}

// Test sleep accuracy with specified number of iterations
void test_sleep_accuracy(uint32_t sleep_ms, size_t iterations, bool use_high_resolution)
{
    printf("\n========================================\n");
    printf("Testing %u ms sleep (%zu iterations)\n", sleep_ms, iterations);
    printf("High resolution timer: %s\n", use_high_resolution ? "ENABLED" : "DISABLED");
    printf("========================================\n");

    std::vector<double> actual_sleep_times_ms;
    actual_sleep_times_ms.reserve(iterations);

    // Set timer resolution if requested
    if (use_high_resolution)
    {
        TIMECAPS tc;
        if (timeGetDevCaps(&tc, sizeof(TIMECAPS)) == TIMERR_NOERROR)
        {
            printf("Timer capabilities: min=%u ms, max=%u ms\n", tc.wPeriodMin, tc.wPeriodMax);
            // Request 1ms resolution (or minimum supported)
            timeBeginPeriod(tc.wPeriodMin);
        }
        else
        {
            printf("Warning: Could not get timer capabilities\n");
            timeBeginPeriod(1);
        }
    }

    // Perform sleep tests
    for (size_t i = 0; i < iterations; i++)
    {
        uint64_t start_ns = nanos();

        // Method 1: Using Windows Sleep() API
        Sleep(sleep_ms);

        // Method 2: Using C++ standard library (uncomment to compare)
        // std::this_thread::sleep_for(std::chrono::milliseconds(sleep_ms));

        uint64_t end_ns = nanos();

        double actual_ms = (end_ns - start_ns) / 1e6;
        actual_sleep_times_ms.push_back(actual_ms);
    }

    // Restore timer resolution if we changed it
    if (use_high_resolution)
    {
        timeEndPeriod(1);
    }

    // Calculate statistics
    double sum = 0;
    for (double time_ms : actual_sleep_times_ms)
    {
        sum += time_ms;
    }
    double mean = sum / actual_sleep_times_ms.size();

    // Calculate median
    std::vector<double> sorted_times = actual_sleep_times_ms;
    std::sort(sorted_times.begin(), sorted_times.end());
    double median;
    size_t mid = sorted_times.size() / 2;
    if (sorted_times.size() % 2 == 0)
    {
        median = (sorted_times[mid - 1] + sorted_times[mid]) / 2.0;
    }
    else
    {
        median = sorted_times[mid];
    }

    // Calculate standard deviation
    double variance_sum = 0;
    for (double time_ms : actual_sleep_times_ms)
    {
        double diff = time_ms - mean;
        variance_sum += diff * diff;
    }
    double stddev = std::sqrt(variance_sum / actual_sleep_times_ms.size());

    // Calculate error
    double error_ms = mean - sleep_ms;
    double error_percent = (error_ms / sleep_ms) * 100.0;

    // Print results
    printf("\nResults:\n");
    printf("  Requested:     %u ms\n", sleep_ms);
    printf("  Mean:          %.3f ms\n", mean);
    printf("  Median:        %.3f ms\n", median);
    printf("  Stddev:        %.3f ms\n", stddev);
    printf("  Min:           %.3f ms\n", sorted_times.front());
    printf("  Max:           %.3f ms\n", sorted_times.back());
    printf("  Error (mean):  %.3f ms (%.2f%%)\n", error_ms, error_percent);
}

int main()
{
    printf("Windows 1ms Sleep Resolution Demo\n");
    printf("==================================\n\n");

    printf("This demo shows the difference between default Windows sleep resolution\n");
    printf("(~15.6ms) and high-resolution sleep (~1ms) using timeBeginPeriod/timeEndPeriod.\n");

    // Test WITHOUT high resolution timer (default ~15.6ms resolution)
    printf("\n\n*** PART 1: Testing WITHOUT high resolution timer ***\n");
    test_sleep_accuracy(1, 20, false);
    test_sleep_accuracy(5, 20, false);
    test_sleep_accuracy(10, 20, false);
    test_sleep_accuracy(20, 20, false);

    // Test WITH high resolution timer (~1ms resolution)
    printf("\n\n*** PART 2: Testing WITH high resolution timer (1ms) ***\n");
    test_sleep_accuracy(1, 20, true);
    test_sleep_accuracy(5, 20, true);
    test_sleep_accuracy(10, 20, true);
    test_sleep_accuracy(20, 20, true);

    printf("\n\n");
    printf("Summary:\n");
    printf("========\n");
    printf("- Without timeBeginPeriod(1): Sleep resolution is ~15.6ms\n");
    printf("  Even Sleep(1) will sleep for ~15-16ms\n");
    printf("- With timeBeginPeriod(1): Sleep resolution is ~1-2ms\n");
    printf("  Sleep(1) will sleep for ~1-2ms as expected\n");
    printf("\n");
    printf("IMPORTANT NOTES:\n");
    printf("- timeBeginPeriod() affects the ENTIRE SYSTEM, not just your app\n");
    printf("- It increases power consumption system-wide\n");
    printf("- Always pair timeBeginPeriod() with timeEndPeriod()\n");
    printf("- Consider using it only when high-precision timing is critical\n");

    return 0;
}

#else
// Non-Windows platforms
#include <cstdio>

int main()
{
    printf("This demo is for Windows only.\n");
    printf("On Linux/Mac, sleep already has sub-millisecond precision.\n");
    printf("Use std::this_thread::sleep_for() or nanosleep() directly.\n");
    return 1;
}

#endif // _WIN32


/*
SAMPLE OUTPUT ON WINDOWS (expected):

Windows 1ms Sleep Resolution Demo
==================================

This demo shows the difference between default Windows sleep resolution
(~15.6ms) and high-resolution sleep (~1ms) using timeBeginPeriod/timeEndPeriod.


*** PART 1: Testing WITHOUT high resolution timer ***

========================================
Testing 1 ms sleep (20 iterations)
High resolution timer: DISABLED
========================================

Results:
  Requested:     1 ms
  Mean:          15.652 ms      <-- ~15.6ms instead of 1ms!
  Median:        15.623 ms
  Stddev:        0.234 ms
  Min:           15.245 ms
  Max:           16.123 ms
  Error (mean):  14.652 ms (1465.20%)

========================================
Testing 10 ms sleep (20 iterations)
High resolution timer: DISABLED
========================================

Results:
  Requested:     10 ms
  Mean:          15.731 ms      <-- Still ~15.6ms, not 10ms!
  Median:        15.689 ms
  Stddev:        0.198 ms
  Min:           15.432 ms
  Max:           16.087 ms
  Error (mean):  5.731 ms (57.31%)


*** PART 2: Testing WITH high resolution timer (1ms) ***

========================================
Testing 1 ms sleep (20 iterations)
High resolution timer: ENABLED
========================================
Timer capabilities: min=1 ms, max=1000000 ms

Results:
  Requested:     1 ms
  Mean:          1.523 ms       <-- Much better! ~1.5ms
  Median:        1.498 ms
  Stddev:        0.156 ms
  Min:           1.234 ms
  Max:           1.876 ms
  Error (mean):  0.523 ms (52.30%)

========================================
Testing 10 ms sleep (20 iterations)
High resolution timer: ENABLED
========================================

Results:
  Requested:     10 ms
  Mean:          10.234 ms      <-- Very accurate now!
  Median:        10.198 ms
  Stddev:        0.287 ms
  Min:           9.876 ms
  Max:           10.765 ms
  Error (mean):  0.234 ms (2.34%)
*/
