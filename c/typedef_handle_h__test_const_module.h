///usr/bin/env ccache gcc -Wall -Wextra -Werror -O3 -std=gnu17 "$0" -o /tmp/a -lm && /tmp/a "$@"; exit
// For the line just above, see my answer here: https://stackoverflow.com/a/75491834/4561887

/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
Nov. 2023

This is the private ("opaque") file for "typedef_handle_h__test_const.c". See that file for more
info.

References:
1. 

*/

#pragma once

// See my answer: https://stackoverflow.com/a/54488289/4561887

// An opaque pointer (handle) to a C-style "object" of "class" type "my_module"
typedef struct my_module_s *my_module_h;
// Same as above, but an opaque pointer to a const struct instead, so you can't
// modify the contents of the struct. 
typedef const struct my_module_s *const_my_module_h;

// Create a new "object" of "class" "my_module": A function that takes a
// **pointer to** an "object" handle, `malloc`s memory for a new copy of the
// opaque  `struct my_module_s`, then points the user's input handle (via its
// passed-in pointer) to this newly-created  "object" of "class" "my_module".
void my_module_open(my_module_h * my_module_h_p);

// A function that takes this "object" (via its handle) as a read-only object.
void my_module_do_stuff1(const_my_module_h my_module);

// A function that takes this "object" (via its handle) as a read-write object.
void my_module_do_stuff2(my_module_h my_module);

// Destroy the passed-in "object" of "class" type "my_module": A function that
// can close this object by stopping all operations, as required, and `free`ing
// its memory.
void my_module_close(my_module_h my_module);

