/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

This file is "included" (used) by `static_extern_function_include__main.c`. Run that file instead.

*/

#include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`

// =============================================================================
// Original code: linker error
// =============================================================================

// // ------- their original code left as-is -------

// static uint32_t counter = 0;

// static void print_incrementing_number()
// {
//     printf("counter = %u\n", counter);
//     counter++;
// }

// void foo()
// {
//     print_incrementing_number();
//     // a bunch of other library code here
// }

// =============================================================================
// Remove `static`: works!
// =============================================================================

// // ------- NO `static`! -------

// uint32_t counter = 0;

// void print_incrementing_number()
// {
//     printf("counter = %u\n", counter);
//     counter++;
// }

// void foo()
// {
//     print_incrementing_number();
//     // a bunch of other library code here
// }

// =============================================================================
// Original code + custom wrappers and setters/getters at bottom
// =============================================================================

// // ------- their original code left as-is -------

// static uint32_t counter = 0;

// static void print_incrementing_number()
// {
//     printf("counter = %u\n", counter);
//     counter++;
// }

// void foo()
// {
//     print_incrementing_number();
//     // a bunch of other library code here
// }

// // ------- custom wrappers and setters/getters -------

// void print_incrementing_number_wrapper()
// {
//     print_incrementing_number();
// }

// void set_counter(uint32_t new_counter)
// {
//     counter = new_counter;
// }

// uint32_t get_counter()
// {
//     return counter;
// }

// =============================================================================
// Original code + ptrs at bottom
// =============================================================================

// // ------- their original code left as-is -------

// static uint32_t counter = 0;

// static void print_incrementing_number()
// {
//     printf("counter = %u\n", counter);
//     counter++;
// }

// void foo()
// {
//     print_incrementing_number();
//     // a bunch of other library code here
// }

// // ------- your custom, non-static pointer variables -------

// typedef void (*void_void_func_ptr_t)(void);

// void_void_func_ptr_t print_incrementing_number_ptr = 
//     print_incrementing_number;

// uint32_t* counter_ptr = &counter;

// =============================================================================
// Original code + custom include (getting the wrapper code in my case) at
// bottom
// =============================================================================

// ------- their original code left as-is -------

static uint32_t counter = 0;

static void print_incrementing_number()
{
    printf("counter = %u\n", counter);
    counter++;
}

void foo()
{
    print_incrementing_number();
    // a bunch of other library code here
}

// ------- your custom include line at the very bottom -------
#include "static_extern_function_include__module_extensions.c"
