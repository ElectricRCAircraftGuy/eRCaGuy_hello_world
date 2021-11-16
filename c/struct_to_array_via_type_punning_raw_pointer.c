/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
15 Nov. 2021

Answer 3/3: use a packed struct and a raw `uint8_t` pointer to it

Convert a struct to an array in C via a raw pointer without doing the unnecessary copy from a struct to a
union. This also has architecture endianness concerns, just like using a union.

To compile and run (assuming you've already `cd`ed into this dir):
1. In C:
    mkdir -p bin && gcc -Wall -Wextra -Werror -O3 -std=c11 -save-temps=obj struct_to_array_via_type_punning_raw_pointer.c \
    -o bin/struct_to_array_via_type_punning_raw_pointer && bin/struct_to_array_via_type_punning_raw_pointer
2. In C++
    mkdir -p bin && g++ -Wall -Wextra -Werror -O3 -std=c++17 -save-temps=obj struct_to_array_via_type_punning_raw_pointer.c \
    -o bin/struct_to_array_via_type_punning_raw_pointer && bin/struct_to_array_via_type_punning_raw_pointer

References:
1. [my answer with this code below] https://stackoverflow.com/a/69984037/4561887
1. [another answer of mine] https://stackoverflow.com/a/67206563/4561887

*/

// #include <assert.h>  // For `assert()` and `static_assert()` macro wrappers in C11
#include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`

typedef struct message_unpacked_s
{
    uint16_t time;
    uint16_t lat;
    uint8_t ns;
    uint16_t lon;
    uint8_t ew;
} message_unpacked_t;

// This MUST be packed to work properly without having padding bytes in the byte array!
typedef struct __attribute__ ((__packed__)) message_s
{
    uint16_t time;
    uint16_t lat;
    uint8_t ns;
    uint16_t lon;
    uint8_t ew;
} message_t;


// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Answer 3/3: use a packed struct and a raw `uint8_t` pointer to it`.\n");

    // demonstrate that packing the struct matters
    printf("sizeof(message_unpacked_t) = %zu bytes\n", sizeof(message_unpacked_t)); // 10 bytes due to padding
    printf("sizeof(message_t) = %zu bytes\n", sizeof(message_t)); // 8 bytes

    message_t message =
    {
        .time = 0x1234,
        .lat = 0x2122,
        .ns = 'n',  // 0x6E
        .lon = 0x1834,
        .ew = 'e', // 0x65
    };

    // Use a raw pointer
    uint8_t * bytes = (uint8_t*)(&message);

    // Print the bytes
    printf("bytes = [");
    for (size_t i = 0; i < sizeof(bytes); i++)
    {
        printf("0x%02X", bytes[i]);
        if (i < sizeof(bytes) - 1)
        {
            printf(", ");
        }
    }
    printf("]\n");

    return 0;
}

/*
SAMPLE OUTPUT:

    eRCaGuy_hello_world/c$ mkdir -p bin && gcc -Wall -Wextra -Werror -O3 -std=c11 -save-temps=obj struct_to_array_via_type_punning_raw_pointer.c     -o bin/struct_to_array_via_type_punning_raw_pointer && bin/struct_to_array_via_type_punning_raw_pointer
    Answer 3/3: use a packed struct and a raw `uint8_t` pointer to it`.
    sizeof(message_unpacked_t) = 10 bytes
    sizeof(message_t) = 8 bytes
    bytes = [0x34, 0x12, 0x22, 0x21, 0x6E, 0x34, 0x18, 0x65]


*/
