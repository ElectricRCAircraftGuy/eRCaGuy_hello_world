///usr/bin/env ccache gcc -Wall -Wextra -Werror -O3 -std=gnu17 "$0" "$(dirname "$0")/typedef_handle_h__test_const_module.c" -o /tmp/a -lm && /tmp/a "$@"; exit
// For the line just above, see my answer here: https://stackoverflow.com/a/75491834/4561887

/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
Nov. 2023

Check if `const my_module_h` makes the pointer constant or the struct it points to. 

Fix my answer here: https://stackoverflow.com/a/54488289/4561887. 

If you have `typedef struct my_module_s *my_module_h;`, and then do `void doStuff2(const my_module_h
my_module);`, does that `const` make the pointer itself `const`, or the struct it points to `const`?
I think it's the former, but when I wrote this answer (https://stackoverflow.com/a/54488289/4561887)
I thought at the time it was the latter. Let's find out!

STATUS: done and works! I've fixed it now! 

CONCLUSION:
`const my_module_h` makes the pointer itself `const`, NOT the struct it points to!
To make the struct itself `const` instead, use 
`typedef const struct my_module_s *const_my_module_h;`, as I have it now in the .h file.


keywords to easily grep or ripgrep in this repo for this program and what it teaches
KEYWORDS: opaque ptr opaque pointer opaque struct

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# Why `-std=gnu17` vs `-std=c17`, and `-std=gnu++17` vs `-std=c++17`?
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# [run once ever] install ccache
sudo apt update && sudo apt install ccache

# 1. In C:
./typedef_handle_h__test_const.c
# or:
gcc -Wall -Wextra -Werror -O3 -std=gnu17 typedef_handle_h__test_const.c typedef_handle_h__test_const_module.c -o bin/a -lm && bin/a

# 2. In C++
g++ -Wall -Wextra -Werror -O3 -std=gnu++17 typedef_handle_h__test_const.c typedef_handle_h__test_const_module.c -o bin/a && bin/a
```

References:
1. My answer: https://stackoverflow.com/a/54488289/4561887
1.

*/

// local includes
#include "typedef_handle_h__test_const_module.h"

// 3rd party includes
// NA

// C library includes
#include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Hello World\n");

    bool exit_now = false;

    // setup/initialization
    my_module_h my_module = NULL;
    // For safety-critical and real-time embedded systems, it is **critical**
    // that you ONLY call the `_open()` functions during **initialization**, but
    // NOT during normal run-time, so that once the system is initialized and
    // up-and-running, you can safely know that no more dynamic-memory
    // allocation, which is non-deterministic and can lead to crashes, will
    // occur.
    my_module_open(&my_module);
    // Ensure initialization was successful and `my_module` is no longer NULL.
    if (!my_module)
    {
        // await connection of debugger, or automatic system power reset by
        // watchdog
        printf("ERROR: my_module_open() failed!\n");
        // log_errors_and_enter_infinite_loop(); 
    }

    // run the program in this infinite main loop
    while (exit_now == false)
    {
        static size_t counter = 0;

        my_module_do_stuff1(my_module);
        my_module_do_stuff2(my_module);

        counter++;
        if (counter >= 2)
        {
            exit_now = true;
        }
    }

    // program clean-up; will only be reached in this case in the event of a
    // major system problem, which triggers the infinite main loop above to
    // `break` or exit via the `exit_now` variable
    my_module_close(my_module);

    // for microcontrollers or other low-level embedded systems, we can never
    // return, so enter infinite loop instead
    // while (true) {}; // await reset by watchdog

    return 0;
}


/*
SAMPLE OUTPUT:

In C:

    eRCaGuy_hello_world$ c/typedef_handle_h__test_const.c 
    Hello World
    my_module_open() done
    my_module->my_private_int1 = 0
    my_module_do_stuff1() done
    my_module_do_stuff2() done
    my_module->my_private_int1 = 7
    my_module_do_stuff1() done
    my_module_do_stuff2() done
    my_module_close() done


OR, in C++:

    eRCaGuy_hello_world/c$ g++ -Wall -Wextra -Werror -O3 -std=gnu++17 typedef_handle_h__test_const.c typedef_handle_h__test_const_module.c -o bin/a && bin/a
    Hello World
    my_module_open() done
    my_module->my_private_int1 = 0
    my_module_do_stuff1() done
    my_module_do_stuff2() done
    my_module->my_private_int1 = 7
    my_module_do_stuff1() done
    my_module_do_stuff2() done
    my_module_close() done


*/
