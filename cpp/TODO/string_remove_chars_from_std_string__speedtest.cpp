/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
17 Feb. 2022

Q: What's the most efficient way to remove a newline (or any other char) from a C++ std::string? I
don't know! Let's find out!

See this Q here: https://stackoverflow.com/q/1488775/4561887. My goal is to answer it definitively
with real data and timestamps!

TODO: Use my "eRCaGuy_hello_world/c/timinglib.h" library for timestamps!

STATUS: wip: NOT yet functional

To compile and run (assuming you've already `cd`ed into this dir):
1. In C++
```bash
g++ -Wall -Wextra -Werror -O3 -std=c++17 string_remove_chars_from_std_string__speedtest.cpp -o bin/a && bin/a
```

References:
1. The question that inspired me to write this:
   [C++ Remove new line from multiline string](https://stackoverflow.com/q/1488775/4561887)

*/


// C++ includes
#include <chrono>
#include <iostream>  // For `std::cin`, `std::cout`, `std::endl`, etc.
#include <string>

// C includes
#include <cstdint>  // For `uint8_t`, `int8_t`, etc.
#include <cstdio>   // For `printf()`


/// Get time stamp in nanoseconds.
//////////// UPDATE: Use my "eRCaGuy_hello_world/c/timinglib.h" library for timestamps instead!
/// See my answer here: https://stackoverflow.com/a/49066369/4561887
uint64_t nanos()
{
    uint64_t ns = std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::high_resolution_clock::now().time_since_epoch())
            .count();
    return ns;
}

double nsToSec(uint64_t ns)
{
    double sec = ns/1e9;
    return sec;
}

void printTimeElapsed(uint64_t tStartNs, uint64_t tEndNs)
{
    uint64_t tDeltaNs = tEndNs - tStartNs;
    printf("Time elapsed = %lu ns (%.9f sec).\n", tDeltaNs, nsToSec(tDeltaNs));
}

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    uint64_t tStartNs = nanos();
    printf("Hello ");
    std::cout << "world!\n\n";
    uint64_t tEndNs = nanos();
    printTimeElapsed(tStartNs, tEndNs);

    return 0;
}



/*
SAMPLE OUTPUT:

    eRCaGuy_hello_world/cpp/TODO$ g++ -Wall -Wextra -Werror -O3 -std=c++17 string_remove_chars_from_std_string__speedtest.cpp -o bin/a && bin/a
    Hello world!

    Time elapsed = 27570 ns (0.000027570 sec).


*/
