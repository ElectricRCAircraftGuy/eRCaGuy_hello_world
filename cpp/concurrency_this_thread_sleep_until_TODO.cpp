/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
30 Aug. 2022

Practice running something at a fixed loop interval by sleeping until a certain point in time in the
future. Compare its resolution and effectiveness to my own timinglib.c's implementation of
`sleep_until_ns()`! See link to it below.

See:
1. https://en.cppreference.com/w/cpp/thread/sleep_until
1. https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world/blob/master/c/timinglib.c

STATUS: todo

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# NB: you may need to use `-std=gnu++17` instead of `-std=c++17` in order to obtain extra GNU
# gcc features, including gcc extensions, POSIX cmds, and Linux sytem cmds.
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# 1. In C++
time g++ -Wall -Wextra -Werror -O3 -std=c++17 hello_world_extra_basic.cpp -o bin/a && bin/a
```

References:
1. https://en.cppreference.com/w/cpp/thread - Concurrency support library
1. https://en.cppreference.com/w/cpp/thread/sleep_until
1. https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world/blob/master/c/timinglib.c

*/

// C++ includes
#include <iostream>  // For `std::cin`, `std::cout`, `std::endl`, etc.

// C includes
#include <cstdint>  // For `uint8_t`, `int8_t`, etc.
#include <cstdio>   // For `printf()`

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Hello ");
    std::cout << "world!\n\n";

    return 0;
}



/*
SAMPLE OUTPUT:

    eRCaGuy_hello_world/cpp$ time g++ -Wall -Wextra -Werror -O3 -std=c++17 hello_world_extra_basic.cpp -o bin/a && bin/a

    real    0m2.079s
    user    0m0.775s
    sys 0m0.087s
    Hello world!

*/
