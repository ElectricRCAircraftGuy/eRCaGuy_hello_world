/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

This file is "included" (used) by `static_extern_function_include__main.c`. Run that file instead.

*/

void print_incrementing_number_wrapper()
{
    print_incrementing_number();
}

void set_counter(uint32_t new_counter)
{
    counter = new_counter;
}

uint32_t get_counter()
{
    return counter;
}
