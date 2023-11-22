/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

This file is "included" (used) by `static_extern_function_include__main.c`. Run that file instead.

*/

#pragma once

#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.

void print_incrementing_number_wrapper();
void set_counter(uint32_t new_counter);
uint32_t get_counter();
