/*

This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
22 Apr. 2021

Show various ways of type punning (reinterpreting multi-byte values as byte arrays) in C and C++.

To compile and run (assuming you've already `cd`ed into this dir):
1. In C:
    mkdir -p bin && gcc -Wall -Wextra -Werror -O3 -std=c11 -save-temps=obj type_punning.c \
    -o bin/type_punning && bin/type_punning
2. In C++
    mkdir -p bin && g++ -Wall -Wextra -Werror -O3 -std=c++17 -save-temps=obj type_punning.c \
    -o bin/type_punning && bin/type_punning

References:
1. [my answer--READ THIS FOR A DETAILED EXPLANATION OF THE BELOW CODE!]
   https://stackoverflow.com/questions/67206482/portability-of-using-union-for-conversion/67206563#67206563

*/

#include <stdint.h>
#include <stdio.h>

typedef union my_union_u
{
    uint32_t value;
    /// A byte array large enough to hold the largest of any value in the union.
    uint8_t bytes[sizeof(uint32_t)];
} my_union_t;

int main()
{
    printf("Type punning and ptr-based serialization demo\n");

    // -------------------------------------------------------------------------

    printf("TECHNIQUE 1: union-based type punning:\n");
    {
        my_union_t u;

        // write to uint32_t value
        u.value = 1234;

        // read & print individual bytes from uint32_t value
        printf("1st byte = 0x%02X\n", (u.bytes)[0]);
        printf("2nd byte = 0x%02X\n", (u.bytes)[1]);
        printf("3rd byte = 0x%02X\n", (u.bytes)[2]);
        printf("4th byte = 0x%02X\n", (u.bytes)[3]);
    }

    // -------------------------------------------------------------------------

    printf("TECHNIQUE 2: reading through raw pointers:\n");
    {
        uint32_t value = 1234;
        uint8_t *bytes = (uint8_t *)&value;

        // read & print individual bytes from uint32_t value
        printf("1st byte = 0x%02X\n", bytes[0]);
        printf("2nd byte = 0x%02X\n", bytes[1]);
        printf("3rd byte = 0x%02X\n", bytes[2]);
        printf("4th byte = 0x%02X\n", bytes[3]);
    }

    // -------------------------------------------------------------------------

    printf("TECHNIQUE 3.1: use bit-masks and bit shifting:\n");
    {
        uint32_t value = 1234;

        // read individual bytes from uint32_t value
        uint8_t byte0 = (value >> 0)  & 0xff;
        uint8_t byte1 = (value >> 8)  & 0xff;
        uint8_t byte2 = (value >> 16) & 0xff;
        uint8_t byte3 = (value >> 24) & 0xff;

        // Print the bytes
        printf("1st byte = 0x%02X\n", byte0);
        printf("2nd byte = 0x%02X\n", byte1);
        printf("3rd byte = 0x%02X\n", byte2);
        printf("4th byte = 0x%02X\n", byte3);
    }

    // -------------------------------------------------------------------------

    printf("TECHNIQUE 3.2: use a convenience macro to do bit-masks and "
           "bit shifting:\n");
    {
        #define BYTE(value, byte_num) ((uint8_t)(((value) >> (8*(byte_num))) & 0xff))

        uint32_t value = 1234;

        // read individual bytes from uint32_t value

        uint8_t byte0 = BYTE(value, 0);
        uint8_t byte1 = BYTE(value, 1);
        uint8_t byte2 = BYTE(value, 2);
        uint8_t byte3 = BYTE(value, 3);

        // OR

        uint8_t bytes[] = {
            BYTE(value, 0),
            BYTE(value, 1),
            BYTE(value, 2),
            BYTE(value, 3),
        };

        // Print the bytes

        printf("1st byte = 0x%02X\n", byte0);
        printf("2nd byte = 0x%02X\n", byte1);
        printf("3rd byte = 0x%02X\n", byte2);
        printf("4th byte = 0x%02X\n", byte3);
        printf("---------------\n");
        printf("1st byte = 0x%02X\n", bytes[0]);
        printf("2nd byte = 0x%02X\n", bytes[1]);
        printf("3rd byte = 0x%02X\n", bytes[2]);
        printf("4th byte = 0x%02X\n", bytes[3]);
    }


    return 0;
}

/*
SAMPLE OUTPUT (ran on an x86-64 **little endian** Ubuntu 20.04 machine):

    eRCaGuy_hello_world/c$ mkdir -p bin && gcc -Wall -Wextra -Werror -O3 -std=c11 -save-temps=obj type_punning.c     -o bin/type_punning && bin/type_punning
    Type punning and ptr-based serialization demo
    TECHNIQUE 1: union-based type punning:
    1st byte = 0xD2
    2nd byte = 0x04
    3rd byte = 0x00
    4th byte = 0x00
    TECHNIQUE 2: reading through raw pointers:
    1st byte = 0xD2
    2nd byte = 0x04
    3rd byte = 0x00
    4th byte = 0x00
    TECHNIQUE 3.1: use bit-masks and bit shifting:
    1st byte = 0xD2
    2nd byte = 0x04
    3rd byte = 0x00
    4th byte = 0x00
    TECHNIQUE 3.2: use a convenience macro to do bit-masks and bit shifting:
    1st byte = 0xD2
    2nd byte = 0x04
    3rd byte = 0x00
    4th byte = 0x00
    ---------------
    1st byte = 0xD2
    2nd byte = 0x04
    3rd byte = 0x00
    4th byte = 0x00

*/
