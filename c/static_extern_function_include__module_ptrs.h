/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

This file is "included" (used) by `static_extern_function_include__main.c`. Run that file instead.

*/

#pragma once

#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.

typedef void (*void_void_func_ptr_t)(void);

// forward pointer variable declarations
extern void_void_func_ptr_t print_incrementing_number_ptr;
extern uint32_t *counter_ptr;
