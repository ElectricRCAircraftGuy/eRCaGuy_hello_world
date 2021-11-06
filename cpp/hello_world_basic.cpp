/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
1 Nov 2021

Make a basic demo I can easily copy-paste whenever I need a simple program.

To compile and run (assuming you've already `cd`ed into this dir):
1. In C++
    mkdir -p bin && g++ -Wall -Wextra -Werror -O3 -std=c++17 -save-temps=obj hello_world_basic.cpp \
    -o bin/hello_world_basic && bin/hello_world_basic

References:
1. eRCaGuy_hello_world/c/hello_world_basic.c
1. https://en.cppreference.com/w/cpp/header/iostream

*/

// C++ includes
#include <iostream>  // For `std::cin`, `std::cout`, `std::endl`, etc.

// C includes
#include <cstdint>  // For `uint8_t`, `int8_t`, etc.
#include <cstdio>   // For `printf()`

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("This is the start of `main()`.\n");
    printf("  Hello world.\n");
    printf("This is the end of `main()`.\n");

    static_assert(1 == true, "1 must equal true");
    std::cout << "the static_assert passed" << std::endl;

    return 0;
}

/*
SAMPLE OUTPUT:

In C++:

    eRCaGuy_hello_world/cpp$ mkdir -p bin && g++ -Wall -Wextra -Werror -O3 -std=c++17 -save-temps=obj hello_world_basic.cpp \
    >     -o bin/hello_world_basic && bin/hello_world_basic
    This is the start of `main()`.
      Hello world.
    This is the end of `main()`.
    the static_assert passed

*/
