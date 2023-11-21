///usr/bin/env ccache gcc -Wall -Wextra -Werror -O3 -std=gnu17 "$0" -o /tmp/a -lm && /tmp/a "$@"; exit
// For the line just above, see my answer here: https://stackoverflow.com/a/75491834/4561887

/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
Nov. 2023

This is the private ("opaque") file for "opaque_pointer_demo_main.c". See that file for more
info.

References:
1. My answer: https://stackoverflow.com/a/54488289/4561887
1.

*/

#include "opaque_pointer_demo_module.h"

#include <stdio.h>   // For `printf()`
#include <stdlib.h>  // For malloc() and free()
#include <string.h>  // For memset()


// Definition of the opaque struct "object" of C-style "class" "my_module".
// - NB: Since this is an opaque struct (declared in the header but not defined
//   until the source file), it has the following 2 important properties:
// 1) It permits data hiding, wherein you end up with the equivalent of a C++
//    "class" with only *private* member variables.
// 2) Objects of this "class" can only be dynamically allocated. No static
//    allocation is possible since any module including the header file does not
//    know the contents of **nor the size of** (this is the critical part) this
//    "class" (ie: C struct).
struct my_module_s
{
    int my_private_int1;
    int my_private_int2;
    float my_private_float;
    // etc. etc--add more "private" member variables as you see fit
};

void my_module_open(my_module_h * my_module_h_p)
{
    // Ensure the passed-in pointer is not NULL (since it is a core
    // dump/segmentation fault to try to dereference a NULL pointer)
    if (!my_module_h_p)
    {
        // Print some error or store some error code here, and return it at the
        // end of the function instead of returning void.
        goto done;
    }

    // Now allocate the actual memory for a new my_module C object from the
    // heap, thereby dynamically creating this C-style "object".
    my_module_h my_module; // Create a local object handle (pointer to a struct)
    // Dynamically allocate memory for the full contents of the struct "object"
    my_module = (my_module_h)malloc(sizeof(*my_module)); 
    if (!my_module) 
    {
        // Malloc failed due to out-of-memory. Print some error or store some
        // error code here, and return it at the end of the function instead of
        // returning void.   
        goto done;
    }

    // Initialize all memory to zero (OR just use `calloc()` instead of
    // `malloc()` above!)
    memset(my_module, 0, sizeof(*my_module));

    // Now pass out this object to the user, and exit.
    *my_module_h_p = my_module;

done:
    printf("my_module_open() done\n"); // for demo purposes only
}

void my_module_do_stuff1(const_my_module_h my_module)
{
    // Ensure my_module is not a NULL pointer.
    if (!my_module)
    {
        goto done;
    }

    // Do stuff where you use my_module private "member" variables. Ex: use
    // `my_module->my_private_int1` here, or `my_module->my_private_float`, etc. 
    printf("my_module->my_private_int1 = %i\n", my_module->my_private_int1);

    // Now try to modify the variable. This results in the following compile-time
    // error since this function takes `const_my_module_h`:
    //
    // In C:
    // 
    //      eRCaGuy_hello_world/c$ ./opaque_pointer_demo_main.c 
    //      ./opaque_pointer_demo_module.c: In function ‘my_module_do_stuff1’:
    //      ./opaque_pointer_demo_module.c:99:32: error: assignment of member ‘my_private_int1’ in read-only object
    //         99 |     my_module->my_private_int1 = 8;
    //            |                                ^
    //      
    // In C++:
    // 
    //      eRCaGuy_hello_world/c$ g++ -Wall -Wextra -Werror -O3 -std=gnu++17 opaque_pointer_demo_main.c opaque_pointer_demo_module.c -o bin/a && bin/a
    //      opaque_pointer_demo_module.c: In function ‘void my_module_do_stuff1(const_my_module_h)’:
    //      opaque_pointer_demo_module.c:99:32: error: assignment of member ‘my_module_s::my_private_int1’ in read-only object
    //         99 |     my_module->my_private_int1 = 8;
    //            |     ~~~~~~~~~~~~~~~~~~~~~~~~~~~^~~
    //      
    //
    // my_module->my_private_int1 = 8; 

done:
    printf("my_module_do_stuff1() done\n"); // for demo purposes only
}

void my_module_do_stuff2(my_module_h my_module)
{
    // Ensure my_module is not a NULL pointer.
    if (!my_module)
    {
        goto done;
    }

    // Do stuff where you use AND UPDATE my_module private "member" variables.
    // Ex:
    my_module->my_private_int1 = 7;
    my_module->my_private_float = 3.14159;
    // Etc.

done:
    printf("my_module_do_stuff2() done\n"); // for demo purposes only
}

void my_module_close(my_module_h my_module)
{
    // Ensure my_module is not a NULL pointer.
    if (!my_module)
    {
        goto done;
    }

    free(my_module);

done:
    printf("my_module_close() done\n"); // for demo purposes only
}
