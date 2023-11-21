/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

This file is "included" (used) by `static_extern_function_include__main.c`. Run that file instead.

*/

#include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`

static uint32_t counter = 0;

static void print_incrementing_number()
{
    printf("counter = %u\n", counter);
    counter++;
}

void foo()
{
    print_incrementing_number();
}
