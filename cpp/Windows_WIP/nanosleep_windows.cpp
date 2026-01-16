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

// C++ (incl. C) includes
#include <chrono>
#include <cstdint>  // For `uint8_t`, `int8_t`, etc.
#include <cstdio>   // For `printf()`
#include <format>
#include <iostream>  // For `std::cin`, `std::cout`, `std::endl`, etc.

#include <windows.h>
#include <iostream>

// Ensure the flag is defined if using older headers
#ifndef CREATE_WAITABLE_TIMER_HIGH_RESOLUTION
#define CREATE_WAITABLE_TIMER_HIGH_RESOLUTION 0x00000002
#endif

// Get time stamp in nanoseconds.
using measurement_clock = std::chrono::steady_clock;
uint64_t nanos()
{
    uint64_t ns = std::chrono::duration_cast<std::chrono::nanoseconds>(
                      measurement_clock::now().time_since_epoch())
                      .count();
    return ns;
}

// Use Windows high-resolution waitable timer to sleep for `sleep_time_ns`.
void sleep_ns(uint64_t sleep_time_ns)
{
    // Create a high-resolution waitable timer
    // - Use `static` to create only once per program execution, not once per call.
    static HANDLE timer_handle = nullptr;
    if (timer_handle == nullptr)
    {
        timer_handle = CreateWaitableTimerEx(
            nullptr,
            nullptr,
            CREATE_WAITABLE_TIMER_HIGH_RESOLUTION,
            // TIMER_ALL_ACCESS
            TIMER_MODIFY_STATE | TIMER_QUERY_STATE
        );

        if (timer_handle == nullptr) {
            std::cerr << "Failed to create timer. Error: " << GetLastError() << std::endl;
            return;
        }
    }

    // Cancel any previous timer setting to reset it
    // CancelWaitableTimer(timer_handle);

    // Configure the sleep duration (in 100-nanosecond intervals)
    LARGE_INTEGER dueTime;
    // Convert to 100-ns intervals; do + 50 first to do rounding integer division
    dueTime.QuadPart = -static_cast<LONGLONG>((sleep_time_ns + 50) / 100);

    // Set the timer
    bool success = SetWaitableTimer(timer_handle, &dueTime, 0, nullptr, nullptr, false);
    if (!success)
    {
        std::cerr << "SetWaitableTimer failed. Error: " << GetLastError() << std::endl;
        return;
    }

    // Wait for the timer to be signaled (this is your high-res sleep)
    WaitForSingleObject(timer_handle, INFINITE);

    // No clean-up; keep for later use
    // CloseHandle(timer_handle);
}

// Use Windows high-resolution waitable timer to sleep for `sleep_time_ns`.
void sleep_ns2(uint64_t sleep_time_ns)
{
    if (sleep_time_ns == 0) {
        return;
    }

    HANDLE timer = CreateWaitableTimerEx(
        nullptr,  // No security attributes
        nullptr,  // Anonymous timer
        // High-resolution timer for sub-ms precision (Windows 10 1803+)
        CREATE_WAITABLE_TIMER_HIGH_RESOLUTION,
        // NULL // use default security descriptor; see: https://learn.microsoft.com/en-us/windows/win32/sync/synchronization-object-security-and-access-rights
        // TIMER_ALL_ACCESS
        SYNCHRONIZE | TIMER_MODIFY_STATE | TIMER_QUERY_STATE
        // EVENT_ALL_ACCESS//SYNCHRONIZE  // Desired access for waiting
    );

    if (timer == nullptr) {
        std::cerr << "Failed to create timer. Error: " << GetLastError() << std::endl;
        return;
    }

    LARGE_INTEGER dueTime;
    // Convert to 100-ns intervals; do + 50 first to do rounding integer division
    uint64_t sleep_ticks = (sleep_time_ns + 50) / 100;
    dueTime.QuadPart = -static_cast<LONGLONG>(sleep_ticks);  // negative for relative time

    bool success = SetWaitableTimerEx(
        timer,
        &dueTime,
        0,         // No periodic timer
        nullptr,   // No APC routine
        nullptr,   // No arg to APC
        nullptr,   // No resume context
        false          // No wake flags
    );

    if (!success) {
        std::cerr << "SetWaitableTimerEx failed. Error: " << GetLastError() << std::endl;
        bool success = CloseHandle(timer);
        if (!success) {
            std::cerr << "CloseHandle failed 3. Error: " << GetLastError() << std::endl;
        }
        return;
    }

    WaitForSingleObject(timer, INFINITE);  // Wait for timer expiration
    success = CloseHandle(timer);  // Clean up
    if (!success) {
        std::cerr << "CloseHandle failed 4. Error: " << GetLastError() << std::endl;
    }
}

int main() {
    // 1. Create the high-resolution waitable timer
    // This provides ~0.5ms resolution without changing the global interrupt frequency.

    uint64_t t_start_ns;
    uint64_t t_end_ns;
    uint64_t dt_ns;
    double dt_ms;

    t_start_ns = nanos();
    HANDLE hTimer = CreateWaitableTimerEx(
        NULL,
        NULL,
        CREATE_WAITABLE_TIMER_HIGH_RESOLUTION,
        TIMER_ALL_ACCESS
        // EVENT_ALL_ACCESS//TIMER_MODIFY_STATE | TIMER_QUERY_STATE
    );
    t_end_ns = nanos();
    uint64_t dt_creation_ns = t_end_ns - t_start_ns;

    if (hTimer == NULL) {
        std::cerr << "Failed to create timer. Error: " << GetLastError() << std::endl;
        return 1;
    }

    // 2. Configure the sleep duration (in 100-nanosecond intervals)
    // Negative values indicate relative time. -10,000 = 1ms.
    LARGE_INTEGER dueTime;
    dueTime.QuadPart = -10000LL;

    // 3. Set the timer
    t_start_ns = nanos();
    if (!SetWaitableTimer(hTimer, &dueTime, 0, NULL, NULL, FALSE)) {
        std::cerr << "SetWaitableTimer failed. Error: " << GetLastError() << std::endl;
        bool success = CloseHandle(hTimer);
        if (!success)
        {
            std::cerr << "CloseHandle failed 1. Error: " << GetLastError() << std::endl;
        }
        return 1;
    }
    t_end_ns = nanos();
    uint64_t dt_set_timer_ns = t_end_ns - t_start_ns;

    // 4. Wait for the timer to be signaled (this is your high-res sleep)
    t_start_ns = nanos();
    WaitForSingleObject(hTimer, INFINITE);
    t_end_ns = nanos();
    dt_ns = t_end_ns - t_start_ns;
    dt_ms = dt_ns / 1e6;

    printf("Timer creation took %llu ns\n", dt_creation_ns);
    printf("SetWaitableTimer took %llu ns\n", dt_set_timer_ns);
    std::cout << std::format("Slept for {:.9f} ms.\n", dt_ms);

    // std::cout << "Successfully slept for 1ms with high precision." << std::endl;

    // 5. Clean up
    bool success = CloseHandle(hTimer);
    if (!success) {
        std::cerr << "CloseHandle failed 2. Error: " << GetLastError() << std::endl;
    }

    sleep_ns2(100);

    t_start_ns = nanos();
    sleep_ns2(1'000);     // 1 us
    t_end_ns = nanos();
    uint64_t dt_1_ns = t_end_ns - t_start_ns;

    t_start_ns = nanos();
    sleep_ns2(100'000);     // 100 us
    t_end_ns = nanos();
    uint64_t dt_2_ns = t_end_ns - t_start_ns;

    t_start_ns = nanos();
    sleep_ns2(500'000);     // 500 us
    t_end_ns = nanos();
    uint64_t dt_3_ns = t_end_ns - t_start_ns;

    t_start_ns = nanos();
    sleep_ns2(1'000'000); // 1 ms
    t_end_ns = nanos();
    uint64_t dt_4_ns = t_end_ns - t_start_ns;

    // 1.5 MS
    t_start_ns = nanos();
    sleep_ns2(1'500'000);
    t_end_ns = nanos();
    uint64_t dt_5_ns = t_end_ns - t_start_ns;

    // 2.0 MS
    t_start_ns = nanos();
    sleep_ns2(2'000'000);
    t_end_ns = nanos();
    uint64_t dt_6_ns = t_end_ns - t_start_ns;

    std::cout << std::format("Slept for {} us (target: 1 us).\n", (double)dt_1_ns / 1e3);
    std::cout << std::format("Slept for {} ms (target: 100 us).\n", (double)dt_2_ns / 1e3);
    std::cout << std::format("Slept for {} ms (target: 500 us).\n", (double)dt_3_ns / 1e3);
    std::cout << std::format("Slept for {} ms (target: 1 ms).\n", (double)dt_4_ns / 1e6);
    std::cout << std::format("Slept for {} ms (target: 1.5 ms).\n", (double)dt_5_ns / 1e6);
    std::cout << std::format("Slept for {} ms (target: 2.0 ms).\n", (double)dt_6_ns / 1e6);

    return 0;
}



/*
SAMPLE OUTPUT:

    eRCaGuy_hello_world/cpp$ time g++ -Wall -Wextra -Werror -O3 -std=c++20 hello_world_extra_basic.cpp -o bin/a && bin/a

    real    0m2.079s
    user    0m0.775s
    sys 0m0.087s
    Hello world!


You can also run this file as an executable directly!:

    eRCaGuy_hello_world/cpp$ ./hello_world_extra_basic.cpp
    Hello world!


*/
