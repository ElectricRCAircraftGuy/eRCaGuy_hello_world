/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

This file is "included" (used) by `static_extern_function_include__main.c`. Run that file instead.

*/

#pragma once

#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.

void print_incrementing_number_wrapper();
void set_counter(uint32_t new_counter);
uint32_t get_counter();

// Also fine, but for **functions**, `extern` is automatically implicitly applied and does NOT have
// to be explicitly written! 
// - See my answer here: https://stackoverflow.com/a/77527374/4561887
// 
// extern void print_incrementing_number_wrapper();
// extern void set_counter(uint32_t new_counter);
// extern uint32_t get_counter();
