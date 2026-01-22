///usr/bin/env ccache g++ -Wall -Wextra -Werror -O3 -std=gnu++20 "$0" -o /tmp/a && /tmp/a "$@"; exit
// For the line just above, see my answer here: https://stackoverflow.com/a/75491834/4561887

/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

(description)
STATUS: (status)

keywords to easily grep or ripgrep in this repo for this program and what it teaches
KEYWORDS:

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# NB: you may need to use `-std=gnu++20` instead of `-std=c++20` in order to obtain extra GNU
# gcc features, including gcc extensions, POSIX cmds, and Linux sytem cmds.
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# [run once ever] install ccache
sudo apt update && sudo apt install ccache

# 1. In C++
time g++ -Wall -Wextra -Werror -O3 -std=gnu++20 hello_world_extra_basic.cpp -o bin/a && bin/a

# OR (just call this file as an exectuable directly)
time ./hello_world_extra_basic.cpp
```

References:
1.

*/

// Primary include
#include "timinglib.hpp"

// Local includes
// NA

// 3rd-party includes
// NA

// Platform-specific includes
// clang-format off
#ifdef _WIN64
    // Windows
    #include <windows.h> // NB: MUST come before `timeapi.h` below
    #include <timeapi.h> // for `timeBeginPeriod()`, `timeEndPeriod()`
#else
    // Linux
    // NA
#endif
// clang-format on

// C and C++ includes
#include <chrono>
#include <format>
#include <iostream>  // For `std::cin`, `std::cout`, `std::endl`, etc.
#include <thread>


namespace timing
{

using measurement_clock = std::chrono::steady_clock;

// Get time stamp in milliseconds.
uint64_t millis()
{
    uint64_t ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                      measurement_clock::now().time_since_epoch())
                      .count();
    return ms;
}

// Get time stamp in microseconds.
uint64_t micros()
{
    uint64_t us = std::chrono::duration_cast<std::chrono::microseconds>(
                      measurement_clock::now().time_since_epoch())
                      .count();
    return us;
}

// Get time stamp in nanoseconds.
uint64_t nanos()
{
    uint64_t ns = std::chrono::duration_cast<std::chrono::nanoseconds>(
                      measurement_clock::now().time_since_epoch())
                      .count();
    return ns;
}

#ifdef _WIN64
// Windows

// Use Windows high-resolution waitable timer to sleep for `sleep_time_ms`.
static void windows_sleep_ms(uint64_t sleep_time_ms)
{
    if (sleep_time_ms == 0)
    {
        std::cout << "sleep_time_ms is 0; not sleeping.\n";
        return;
    }

    // Create high-resolution waitable timer

    HANDLE timer = CreateWaitableTimerEx(
        nullptr, // No security attributes
        nullptr, // Anonymous, unnamed timer
        // High-resolution timer for sub-ms precision (Windows 10 v1803+)
        CREATE_WAITABLE_TIMER_HIGH_RESOLUTION,
        // Required access rights to function properly
        SYNCHRONIZE | TIMER_MODIFY_STATE | TIMER_QUERY_STATE);
    if (timer == nullptr)
    {
        std::cout << std::format("Failed to create timer. Error: {}\n", GetLastError());
        return;
    }

    // Set the timer's wakeup time

    LARGE_INTEGER dueTime;
    // Convert to 100-ns tick intervals; do + 50 first to do rounding integer division
    uint64_t sleep_ticks = (MS_TO_NS(sleep_time_ms) + 50) / 100;
    dueTime.QuadPart = -static_cast<LONGLONG>(sleep_ticks); // negative for relative time

    // See:
    // https://learn.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-setwaitabletimerex
    bool success = SetWaitableTimerEx(
        timer,
        &dueTime, // When to wake up
        0,        // No period; fire once
        nullptr,  // No timer callback func
        nullptr,  // No arg to timer callback func
        nullptr,  // No wake context
        // TolerableDelay of 0 ms: request no timer wake-up coalescing, for optimal precision:
        //
        // 0 (recommended for precision): No tolerance allowed. The system attempts to fire the
        // timer as close as possible to the exact requested time. This maximizes accuracy and is
        // essential for sub-millisecond resolution, especially when using
        // CREATE_WAITABLE_TIMER_HIGH_RESOLUTION.
        //
        // Non-zero value (e.g., 1 ms, 10 ms, etc.): Allows the OS to delay firing the timer by up
        // to that many milliseconds. This enables timer coalescing, where the system batches
        // multiple timers together to reduce CPU wake-ups, improving power efficiency (useful on
        // laptops or battery-powered devices). However, it can introduce additional latency.
        0 // TolerableDelay in ms
    );
    if (!success)
    {
        std::cout << std::format("Failed to set timer. Error: {}\n", GetLastError());
        goto cleanup;
    }

    // Sleep: wait for the timer to expire
    WaitForSingleObject(timer, INFINITE);

cleanup:

    // Close/kill the timer

    success = CloseHandle(timer);
    if (!success)
    {
        std::cout << std::format("CloseHandle failed. Error: {}\n", GetLastError());
    }
}
#endif

// Sleep until the next time interval which is `period_ms` milliseconds after the
// `previous_wake_time_ms`.
void sleep_until_ms(uint64_t* previous_wake_time_ms, uint64_t period_ms)
{
    if (previous_wake_time_ms == nullptr || period_ms == 0)
    {
        std::cout << std::format("sleep_until_ms: invalid arguments: {}, {}\n",
            static_cast<void*>(previous_wake_time_ms), period_ms));
        return;
    }

    uint64_t next_wake_time_ms = *previous_wake_time_ms + period_ms;
    *previous_wake_time_ms = next_wake_time_ms;

    uint64_t t_now_ms = millis();
    int64_t sleep_time_ms = next_wake_time_ms - t_now_ms;
    if (sleep_time_ms <= 0)
    {
        // We're behind schedule; do not sleep
        std::cout << std::format("Behind schedule by {} ms; not sleeping\n", -sleep_time_ms);

        // Adjust `previous_wake_time_ms` to not let it fall more than 2 periods behind, while
        // allowing it to use 100% of the CPU and catch up to stay on schedule if possible.
        // - Do the `(2*period_ms <= t_now_ms)` check to avoid underflow during the subtraction
        //   when `t_now_ms` is very small (near 0) or `period_ms` is very large.
        if ((2*period_ms <= t_now_ms) && (*previous_wake_time_ms < t_now_ms - 2*period_ms))
        {
            *previous_wake_time_ms = t_now_ms - 2*period_ms;
        }

        return;
    }

    // TODO: change this to not use #ifdefs here. Instead, use a sleep function wrapper and
    // use ifdefs in it if needed, but call that wrapper directly here.
#ifdef _WIN64
    windows_sleep_ms(static_cast<uint64_t>(sleep_time_ms));
#else
    // Linux: sleep resolution is already ~50 us. No special handling needed.
    std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time_ms));
#endif
}

} // namespace timing
