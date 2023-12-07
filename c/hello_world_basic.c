/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
29 June 2021

Make a basic demo I can easily copy-paste whenever I need a simple program.

To compile and run (assuming you've already `cd`ed into this dir):
1. In C:
    mkdir -p bin && gcc -Wall -Wextra -Werror -O3 -std=gnu17 -save-temps=obj hello_world_basic.c \
    -o bin/hello_world_basic -lm && bin/hello_world_basic
2. In C++
    mkdir -p bin && g++ -Wall -Wextra -Werror -O3 -std=gnu++17 -save-temps=obj hello_world_basic.c \
    -o bin/hello_world_basic && bin/hello_world_basic

References:
1. [my answer] `-std=c17` vs `-std=gnu17`: https://stackoverflow.com/a/71801111/4561887
1. [my answer on `-save-temps=obj`]: Where do we use .i files and how do we generate them?:
   https://stackoverflow.com/a/56482777/4561887 - ie: how to generate the .i intermediate,
   pre-processed, "single translation unit" file.

*/

// #include <assert.h>  // For `assert()` and `static_assert()` macro wrappers in C11
#include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("This is the start of `main()`.\n");
    printf("  Hello world.\n");
    printf("This is the end of `main()`.\n");

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
