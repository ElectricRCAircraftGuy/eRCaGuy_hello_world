/*

This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
29 June 2021

Make a basic demo I can easily copy-paste whenever I need a simple program.

To compile and run (assuming you've already `cd`ed into this dir):
1. In C:
    mkdir -p bin && gcc -Wall -Wextra -Werror -O3 -std=c11 -save-temps=obj hello_world_basic.c \
    -o bin/hello_world_basic && bin/hello_world_basic
2. In C++
    mkdir -p bin && g++ -Wall -Wextra -Werror -O3 -std=c++17 -save-temps=obj hello_world_basic.c \
    -o bin/hello_world_basic && bin/hello_world_basic

References:
1. None.

*/

#include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Hello world.\n");

    return 0;
}

/*
SAMPLE OUTPUT:

In C:

    eRCaGuy_hello_world/c$ mkdir -p bin && gcc -Wall -Wextra -Werror -O3 -std=c11 -save-temps=obj hello_world_basic.c     -o bin/hello_world_basic && bin/hello_world_basic
    Hello world.

OR, in C++:

    eRCaGuy_hello_world/c$ mkdir -p bin && g++ -Wall -Wextra -Werror -O3 -std=c++17 -save-temps=obj hello_world_basic.c     -o bin/hello_world_basic && bin/hello_world_basic
    Hello world.

*/
