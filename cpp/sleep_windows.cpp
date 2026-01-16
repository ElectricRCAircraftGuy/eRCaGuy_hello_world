///usr/bin/env ccache g++ -Wall -Wextra -Werror -O3 -std=gnu++20 "$0" -o /tmp/a && /tmp/a "$@"; exit
// For the line just above, see my answer here: https://stackoverflow.com/a/75491834/4561887

/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
Jan. 2026

(description)
STATUS: wip

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
1. https://share.google/aimode/riWp4tozmA3ArN1IQ

*/

// C++ (incl. C) includes
#include <chrono>
#include <cstdint>  // For `uint8_t`, `int8_t`, etc.
#include <cstdio>   // For `printf()`
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

int main() {
    // 1. Create the high-resolution waitable timer
    // This provides ~0.5ms resolution without changing the global interrupt frequency.
    HANDLE hTimer = CreateWaitableTimerEx(
        NULL,
        NULL,
        CREATE_WAITABLE_TIMER_HIGH_RESOLUTION,
        TIMER_ALL_ACCESS
    );

    if (hTimer == NULL) {
        std::cerr << "Failed to create timer. Error: " << GetLastError() << std::endl;
        return 1;
    }

    // 2. Configure the sleep duration (in 100-nanosecond intervals)
    // Negative values indicate relative time. -10,000 = 1ms.
    LARGE_INTEGER dueTime;
    dueTime.QuadPart = -10000LL;

    // 3. Set the timer
    if (!SetWaitableTimer(hTimer, &dueTime, 0, NULL, NULL, FALSE)) {
        std::cerr << "SetWaitableTimer failed. Error: " << GetLastError() << std::endl;
        CloseHandle(hTimer);
        return 1;
    }

    // 4. Wait for the timer to be signaled (this is your high-res sleep)
    uint64_t t_start_ns = nanos();
    WaitForSingleObject(hTimer, INFINITE);
    uint64_t t_end_ns = nanos();
    double sleep_duration_ms = (t_end_ns - t_start_ns) / 1e6;
    std::cout << "Slept for " << sleep_duration_ms << " ms." << std::endl;

    std::cout << "Successfully slept for 1ms with high precision." << std::endl;

    // 5. Clean up
    CloseHandle(hTimer);
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
