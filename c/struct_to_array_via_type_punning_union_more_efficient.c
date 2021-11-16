/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
15 Nov. 2021

Answer 1/3 [better]: use a union and a packed struct

Convert a struct to an array in C via a union without doing the unnecessary copy from a struct to a
union.

To compile and run (assuming you've already `cd`ed into this dir):
1. In C:
    mkdir -p bin && gcc -Wall -Wextra -Werror -O3 -std=c11 -save-temps=obj struct_to_array_via_type_punning_union_more_efficient.c \
    -o bin/struct_to_array_via_type_punning_union_more_efficient && bin/struct_to_array_via_type_punning_union_more_efficient
2. In C++
    mkdir -p bin && g++ -Wall -Wextra -Werror -O3 -std=c++17 -save-temps=obj struct_to_array_via_type_punning_union_more_efficient.c \
    -o bin/struct_to_array_via_type_punning_union_more_efficient && bin/struct_to_array_via_type_punning_union_more_efficient

References:
1. [my answer with this code below] https://stackoverflow.com/a/69984037/4561887
1. [another answer of mine] https://stackoverflow.com/a/67206563/4561887

*/

// #include <assert.h>  // For `assert()` and `static_assert()` macro wrappers in C11
#include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`

typedef struct message_data_unpacked_s
{
    uint16_t time;
    uint16_t lat;
    uint8_t ns;
    uint16_t lon;
    uint8_t ew;
} message_data_unpacked_t;

typedef struct __attribute__ ((__packed__)) message_data_s
{
    uint16_t time;
    uint16_t lat;
    uint8_t ns;
    uint16_t lon;
    uint8_t ew;
} message_data_t;

typedef union message_u
{
    message_data_t data;
    uint8_t bytes[sizeof(message_data_t)];
} message_t;

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("This is the start of `main()`.\n");

    printf("sizeof(message_data_unpacked_t) = %zu bytes\n", sizeof(message_data_unpacked_t)); // 10 bytes due to padding
    printf("sizeof(message_data_t) = %zu bytes\n", sizeof(message_data_t)); // 8 bytes

    message_t message =
    {
        .data =
        {
            .time = 0x1234,
            .lat = 0x2122,
            .ns = 'n',  // 0x6E
            .lon = 0x1834,
            .ew = 'e', // 0x65
        },
    };

    // Print the bytes
    printf("bytes = [");
    for (size_t i = 0; i < sizeof(message.bytes); i++)
    {
        printf("0x%02X", message.bytes[i]);
        if (i < sizeof(message.bytes) - 1)
        {
            printf(", ");
        }
    }
    printf("]\n");

    return 0;
}

/*
SAMPLE OUTPUT:

    eRCaGuy_hello_world/c$ mkdir -p bin && gcc -Wall -Wextra -Werror -O3 -std=c11 -save-temps=obj struct_to_array_via_type_punning_union_more_efficient.c \
    >     -o bin/struct_to_array_via_type_punning_union_more_efficient && bin/struct_to_array_via_type_punning_union_more_efficient
    This is the start of `main()`.
    sizeof(message_data_unpacked_t) = 10 bytes
    sizeof(message_data_t) = 8 bytes
    bytes = [0x34, 0x12, 0x22, 0x21, 0x6E, 0x34, 0x18, 0x65]

*/
