/*

This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

Gabriel Staples
26 Sept. 2020

regular_func.cpp
- See the readme in this folder for a description.

To compile and run:

    g++ -Wall -Werror -g3 -O3 -std=c++17 -o regular_func \
    regular_func.cpp && ./regular_func

*/

#include <cstdint>
#include <cstdio>
#include <iostream>

inline void print_array_size(uint8_t * byte_array, size_t len)
{
    printf("sizeof(byte_array) = %lu\n", len);
}

int main()
{
    printf("Hello World\n");

    for (size_t i = 1; i <= 10; i++)
    {
        uint8_t byte_array[i];
        print_array_size(byte_array, sizeof(byte_array));
    }

    return 0;
}


/*
Size (`size <executable>`):

WITH*OUT* `inline`ing the func:
`void print_array_size(uint8_t * byte_array, size_t len) {...}`

1. for i <= 10:

        $ size regular_func
           text    data     bss     dec     hex filename
           2103     648       8    2759     ac7 regular_func

2. for i <= 100000 (it is exactly the same!):

        $ size regular_func
           text    data     bss     dec     hex filename
           2103     648       8    2759     ac7 regular_func


*WITH* `inline`ing the func:
`inline void print_array_size(uint8_t * byte_array, size_t len) {...}`

1. for i <= 10:

        $ size regular_func
           text    data     bss     dec     hex filename
           2039     648       8    2695     a87 regular_func


2. for i <= 100000 (it is exactly the same!):

        $ size regular_func
           text    data     bss     dec     hex filename
           2039     648       8    2695     a87 regular_func



Sample Output:

    $ g++ -Wall -Werror -g3 -O3 -std=c++17 -o regular_func     regular_func.cpp && ./regular_func
    Hello World
    sizeof(byte_array) = 1
    sizeof(byte_array) = 2
    sizeof(byte_array) = 3
    sizeof(byte_array) = 4
    sizeof(byte_array) = 5
    sizeof(byte_array) = 6
    sizeof(byte_array) = 7
    sizeof(byte_array) = 8
    sizeof(byte_array) = 9
    sizeof(byte_array) = 10

*/





