
// This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

/*

floating_point_and_double_resolution_test.cpp

- Find out when float += 1 ns (in decimal form, assuming the whole units are seconds) no longer
equals uint64_t += 1 ns, and so on, printing each time another ns of resolution is lost!
- Do the same for += 1.0 sec!

GS
30 Oct. 2020

References:
1.

Build and run command:

    mkdir -p bin && g++ -Wall -Wextra -Werror -ggdb -std=c++17 -o ./bin/tmp \
    floating_point_and_double_resolution_test.cpp && ./bin/tmp

*/

#include <cstdio>
#include <iostream>

int main()
{
    printf("Hello World\n\n");

    double time_sec = 0.0;
    constexpr double NS_PER_SEC = 1e9;
    // constexpr double NS_PER_SEC = 1e-9;

    uint64_t time_ns = 0;

    printf("NS_PER_SEC = %3.12f\n", NS_PER_SEC);

    while (true)
    {
        time_sec += NS_PER_SEC;
        time_ns += 1;

        if (time_sec * 1e9)
    }

    return 0;
}


