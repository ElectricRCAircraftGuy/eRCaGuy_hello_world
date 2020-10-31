
// This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

/*

floating_point_and_double_resolution_test.cpp

- Find out when float += 1 ns (in decimal form, assuming the whole units are seconds) no longer
equals uint64_t += 1 ns, and so on, printing each time another ns of resolution is lost!
- Do the same for += 1.0 sec!

GS
30 Oct. 2020

References:
1. Optimization levels: https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html

Build and run command:
Note: use optimization level `-O3` for normal use, and `-O0` for debugging with gdb.

  Normal:

    mkdir -p bin && g++ -Wall -Wextra -Werror -ggdb -O3 -std=c++17 -o ./bin/tmp \
    floating_point_and_double_resolution_test.cpp && ./bin/tmp

  Debugging:

    mkdir -p bin && g++ -Wall -Wextra -Werror -ggdb -O0 -std=c++17 -o ./bin/tmp \
    floating_point_and_double_resolution_test.cpp && ./bin/tmp

*/

#include <cmath>
#include <cstdio>
#include <iostream>

int main()
{
    printf("Hello World\n\n");

    constexpr double NS_PER_SEC = 1e9;
    constexpr double SEC_PER_NS = 1.0/NS_PER_SEC;

    printf("NS_PER_SEC = %f\n"
           "SEC_PER_NS = %3.12f\n",
           NS_PER_SEC,
           SEC_PER_NS);

    double time_sec = 0.0;
    uint64_t time_ns = 0;

    while (true)
    {
        static uint64_t loop_cnt = 0;
        loop_cnt++;

        // Add 1 ns to each
        time_sec += SEC_PER_NS;
        time_ns += 1;

        // accumulated floating point error
        double accumulated_error_ns = time_sec*NS_PER_SEC - time_ns;
        static uint64_t ns_error_bound = 1;
        if (std::abs(accumulated_error_ns) > (double)ns_error_bound)
        {
            ns_error_bound += 1;

            printf("loop_cnt = %lu\n", loop_cnt);

            printf("time_ns = %lu\n"
                   "accumulated_error_ns = %f\n"
                   "time_ns in seconds = %3.9f\n\n",
                   time_ns, accumulated_error_ns, (double)time_ns/NS_PER_SEC);
        }
    }

    return 0;
}


