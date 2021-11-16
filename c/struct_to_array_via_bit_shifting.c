/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
15 Nov. 2021

Answer 2/3: convert a struct to an array of bytes via manual bit-shifting

Convert a struct to an array in C via bit shifting, which unlike the union technique, does NOT have
architecture-based endianness concerns or differences which can vary from hardware architecture to
architecture! Rather, the manual bit-shifting *removes* endianness concerns at the expense of
manually copying the bytes from the struct into an array!

To compile and run (assuming you've already `cd`ed into this dir):
1. In C:
    mkdir -p bin && gcc -Wall -Wextra -Werror -O3 -std=c11 -save-temps=obj struct_to_array_via_bit_shifting.c \
    -o bin/struct_to_array_via_bit_shifting && bin/struct_to_array_via_bit_shifting
2. In C++
    mkdir -p bin && g++ -Wall -Wextra -Werror -O3 -std=c++17 -save-temps=obj struct_to_array_via_bit_shifting.c \
    -o bin/struct_to_array_via_bit_shifting && bin/struct_to_array_via_bit_shifting

References:
1. [my answer with this code!] https://stackoverflow.com/a/69984464/4561887
1. [my answer] https://stackoverflow.com/a/69984037/4561887
1. [another answer of mine] https://stackoverflow.com/a/67206563/4561887

*/

// #include <assert.h>  // For `assert()` and `static_assert()` macro wrappers in C11
#include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`

// Read a single byte at index `byte_num` from any multi-byte variable.
#define BYTE(value, byte_num) ((uint8_t)(((value) >> (8*(byte_num))) & 0xff))

// Notice with this technique the struct does NOT need to be packed! This is contrary to the
// union technique.
typedef struct message_s
{
    uint16_t time;
    uint16_t lat;
    uint8_t ns;
    uint16_t lon;
    uint8_t ew;
} message_t;

void message_struct_to_array(const message_t* message, uint8_t* bytes)
{
    bytes[0] = BYTE(message->time, 0);
    bytes[1] = BYTE(message->time, 1);

    bytes[2] = BYTE(message->lat, 0);
    bytes[3] = BYTE(message->lat, 1);

    bytes[4] = BYTE(message->ns, 0);

    bytes[5] = BYTE(message->lon, 0);
    bytes[6] = BYTE(message->lon, 1);

    bytes[7] = BYTE(message->ew, 0);
}

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Answer 2/3: convert a struct to an array of bytes via manual bit-shifting.\n");

    message_t message =
    {
        .time = 0x1234,
        .lat = 0x2122,
        .ns = 'n',  // 0x6E
        .lon = 0x1834,
        .ew = 'e', // 0x65
    };

    // NB: this is NOT the same thing as `sizeof(message_t)` due to padding bytes which are in the
    // `message_t` struct!
    const size_t MESSAGE_NUM_BYTES = sizeof(message.time) + sizeof(message.lat) +
        sizeof(message.ns) + sizeof(message.lon) + sizeof(message.ew);

    uint8_t bytes[MESSAGE_NUM_BYTES];
    message_struct_to_array(&message, bytes);

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

    eRCaGuy_hello_world/c$ mkdir -p bin && gcc -Wall -Wextra -Werror -O3 -std=c11 -save-temps=obj struct_to_array_via_bit_shifting.c \
    >     -o bin/struct_to_array_via_bit_shifting && bin/struct_to_array_via_bit_shifting
    Answer 2/3: convert a struct to an array of bytes via manual bit-shifting.
    bytes = [0x34, 0x12, 0x22, 0x21, 0x6E, 0x34, 0x18, 0x65]

*/
