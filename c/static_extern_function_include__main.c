///usr/bin/env ccache gcc -Wall -Wextra -Werror -O3 -std=gnu17 "$0" "$(dirname "$0")/static_extern_function_include__module.c" -o /tmp/a -lm && /tmp/a "$@"; exit
// For the line just above, see my answer here: https://stackoverflow.com/a/75491834/4561887

/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
Nov. 2023

Practice force-including `static` functions from other .c source files in C.

`static` functions are internal to the file they are defined in, and are not visible to other
files. However, if you want to force-include them in another file, there are a few hacky ways.
Let's try them out.
See this Q: https://stackoverflow.com/q/35425790/4561887

STATUS: (status)

keywords to easily grep or ripgrep in this repo for this program and what it teaches
KEYWORDS:

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# Why `-std=gnu17` vs `-std=c17`, and `-std=gnu++17` vs `-std=c++17`?
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# [run once ever] install ccache
sudo apt update && sudo apt install ccache

# 1. In C:
./static_extern_function_include__main.c
# or:
gcc -Wall -Wextra -Werror -O3 -std=gnu17 static_extern_function_include__main.c static_extern_function_include__module.c -o bin/a && bin/a

# 2. In C++
g++ -Wall -Wextra -Werror -O3 -std=gnu++17 static_extern_function_include__main.c static_extern_function_include__module.c -o bin/a && bin/a
```

References:
1. https://stackoverflow.com/q/35425790/4561887
    1. *****+ MY ANSWER with this code:
       https://stackoverflow.com/a/77527374/4561887
1.

*/

// #include "static_extern_function_include__module_wrapper.h"
// #include "static_extern_function_include__module_ptrs.h"
#include "static_extern_function_include__module_wrapper.h"  // for _extensions.c wrappers

#include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`

// #include "static_extern_function_include__module.h"
// OR:
// void print_incrementing_number(); // forward function declaration
// extern uint32_t counter;          // forward variable declaration


// int main()
// {
//     printf("Hello World.\n");

//     print_incrementing_number();
//     printf("  counter = %u\n", counter);
//     print_incrementing_number();
//     printf("  counter = %u\n", counter);
//     print_incrementing_number();
//     printf("  counter = %u\n", counter);

//     return 0;
// }


// // Using the wrapper
// int main()
// {
//     printf("Hello World.\n");

//     print_incrementing_number_wrapper();
//     printf("  counter = %u\n", get_counter());
//     print_incrementing_number_wrapper();
//     printf("  counter = %u\n", get_counter());
//     print_incrementing_number_wrapper();
//     printf("  counter = %u\n", get_counter());

//     return 0;
// }


// // Using the pointers
// int main()
// {
//     printf("Hello World.\n");

//     print_incrementing_number_ptr();
//     printf("  counter = %u\n", *counter_ptr);
//     print_incrementing_number_ptr();
//     printf("  counter = %u\n", *counter_ptr);
//     print_incrementing_number_ptr();
//     printf("  counter = %u\n", *counter_ptr);

//     return 0;
// }

// Using the wrappers from the _extensions.c file
int main()
{
    printf("Hello World.\n");

    print_incrementing_number_wrapper();
    printf("  counter = %u\n", get_counter());
    print_incrementing_number_wrapper();
    printf("  counter = %u\n", get_counter());
    print_incrementing_number_wrapper();
    printf("  counter = %u\n", get_counter());

    return 0;
}



/*
SAMPLE OUTPUT:

In C:

    eRCaGuy_hello_world/c$ ./static_extern_function_include__main.c 
    Hello World.
    counter = 0
      counter = 1
    counter = 1
      counter = 2
    counter = 2
      counter = 3


OR, in C++:

    eRCaGuy_hello_world/c$ g++ -Wall -Wextra -Werror -O3 -std=gnu++17 static_extern_function_include__main.c static_extern_function_include__module.c -o bin/a && bin/a
    Hello World.
    counter = 0
      counter = 1
    counter = 1
      counter = 2
    counter = 2
      counter = 3

*/
