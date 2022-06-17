/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
1 July 2021

- Following this answer here (https://stackoverflow.com/a/68171817/4561887) and the comment
  underneath it, practice **dynamically injecting function calls** into another program before and
  after main. Yeah, pretty cool, huh!? :)
- This program will have no `main()` itself. It will simply be the part to dynamically inject itself
  into another program as it loads that program's object file.

To compile and run (assuming you've already `cd`ed into this dir):
1. In C: BUILD A DYNAMIC (SHARED OBJECT `lib*.so`) library file and use it in another program to
   dynamically inject my function calls below **before AND after** their `main()` function!:
        ./dynamic_func_call_before_and_after_main__build_and_run.sh

References:
1. [my Q, and the ans. here] https://stackoverflow.com/questions/68171246/in-gcc-is-there-any-way-to-dynamically-add-a-function-call-to-the-start-of-main
    - see also my links at the bottom of my Q!
1. See also my own "build_all.sh" script in my `fast_malloc` repo to see how I make a *.so dynamic
   library. I learned that originally here: https://www.cprogramming.com/tutorial/shared-libraries-linux-gcc.html
1. [gcc `constructor` and `destructor` function attributes!]
   https://gcc.gnu.org/onlinedocs/gcc/Common-Function-Attributes.html#Common-Function-Attributes
1. [c `atexit()` func to register functions to be called AFTER `main()` returns or exits!]
   https://en.cppreference.com/w/c/program/atexit


*/

#include <assert.h>
#include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`
#include <stdlib.h>  // For `atexit()`

/// 3. This function gets attached as a post-main() callback (a sort of program "destructor")
/// via the C <stdlib.h> `atexit()` call below
void also_called_after_main()
{
    printf("`atexit()`-registered callback functions are also called AFTER `main()`.\n");
}

/// 1. Functions with gcc function attribute, `constructor`, get automatically called **before**
/// `main()`; see:
/// https://gcc.gnu.org/onlinedocs/gcc/Common-Function-Attributes.html#Common-Function-Attributes
__attribute__((__constructor__))
void called_before_main()
{
    printf("gcc constructors are called BEFORE `main()`.\n");

    // 3. Optional way to register a function call for AFTER main(), although
    // I prefer the simpler gcc `destructor` attribute technique below, instead.
    int retcode = atexit(also_called_after_main);
    assert(retcode == 0); // ensure the `atexit()` call to register the callback function succeeds
}

/// 2. Functions with gcc function attribute, `destructor`, get automatically called **after**
/// `main()`; see:
/// https://gcc.gnu.org/onlinedocs/gcc/Common-Function-Attributes.html#Common-Function-Attributes
__attribute__((__destructor__))
void called_after_main()
{
    printf("gcc destructors are called AFTER `main()`.\n");
}


/*
SAMPLE OUTPUT:

    eRCaGuy_hello_world/c$ ./dynamic_func_call_before_and_after_main__build_and_run.sh
    gcc constructors are called BEFORE `main()`.
    This is the start of `main()`.
      Hello world.
    This is the end of `main()`.
    gcc destructors are called AFTER `main()`.
    `atexit()`-registered callback functions are also called AFTER `main()`.

*/
