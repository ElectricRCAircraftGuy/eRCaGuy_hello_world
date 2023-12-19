///usr/bin/env ccache gcc -Wall -Wextra -Werror -O3 -std=gnu17 "$0" -o /tmp/a -lm && /tmp/a "$@"; exit
// For the line just above, see my answer here: https://stackoverflow.com/a/75491834/4561887

/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
Dec. 2023

Learn to print macro `#define` values at compile time in C and C++.
See: https://stackoverflow.com/a/10227059/4561887

RESULTS:
- All of the `#pragma message PRINT_MACRO_AT_COMPILE_TIME()` calls work perfectly in both C and C++!

STATUS: Done and works!

keywords to easily grep or ripgrep in this repo for this program and what it teaches
KEYWORDS:

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# Why `-std=gnu17` vs `-std=c17`, and `-std=gnu++17` vs `-std=c++17`?
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# [run once ever] install ccache
sudo apt update && sudo apt install ccache

# 1. In C:
./macro_print_macro_values_at_compile_time.c
# or:
gcc -Wall -Wextra -Werror -O3 -std=gnu17 macro_print_macro_values_at_compile_time.c -o bin/a -lm && bin/a

# 2. In C++
g++ -Wall -Wextra -Werror -O3 -std=gnu++17 macro_print_macro_values_at_compile_time.c -o bin/a && bin/a
```

References:
1. How do I show the value of a #define at compile-time? -
   https://stackoverflow.com/a/10227059/4561887
1.

*/


#include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`

// Various macro definitions to test
#define DEFINED_BUT_NO_VALUE
#define MY_INT 3
#define MY_STR "ABC"
#define MY_CODE_BLOCK           \
    do                          \
    {                           \
        printf("Hi.\n");        \
    } while (0)
//
// NB: the `#pragma message` output of the above macro is substantially different if I define it as
// `MY_CODE_BLOCK()` instead, and call it as such inside `main()`! Try it out and you'll see.

// Helper macros to print the value of a macro at compile-time
#define VALUE_TO_STRING(x) #x
#define VALUE(x) VALUE_TO_STRING(x)
#define PRINT_MACRO_AT_COMPILE_TIME(var) #var "=`" VALUE(var) "`"

// Example prints at compile-time
#pragma message PRINT_MACRO_AT_COMPILE_TIME(NOT_DEFINED)
#pragma message PRINT_MACRO_AT_COMPILE_TIME(DEFINED_BUT_NO_VALUE)
#pragma message PRINT_MACRO_AT_COMPILE_TIME(MY_INT)
#pragma message PRINT_MACRO_AT_COMPILE_TIME(MY_STR)
#pragma message PRINT_MACRO_AT_COMPILE_TIME(MY_CODE_BLOCK)


// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    MY_CODE_BLOCK;
    printf("Hello World.\n\n");

    return 0;
}


/*
SAMPLE OUTPUT:

In C:

    eRCaGuy_hello_world/c$ ./macro_print_macro_values_at_compile_time.c
    ./macro_print_macro_values_at_compile_time.c:66:9: note: ‘#pragma message: NOT_DEFINED=`NOT_DEFINED`’
       66 | #pragma message PRINT_MACRO_AT_COMPILE_TIME(NOT_DEFINED)
          |         ^~~~~~~
    ./macro_print_macro_values_at_compile_time.c:67:9: note: ‘#pragma message: DEFINED_BUT_NO_VALUE=``’
       67 | #pragma message PRINT_MACRO_AT_COMPILE_TIME(DEFINED_BUT_NO_VALUE)
          |         ^~~~~~~
    ./macro_print_macro_values_at_compile_time.c:68:9: note: ‘#pragma message: MY_INT=`3`’
       68 | #pragma message PRINT_MACRO_AT_COMPILE_TIME(MY_INT)
          |         ^~~~~~~
    ./macro_print_macro_values_at_compile_time.c:69:9: note: ‘#pragma message: MY_STR=`"ABC"`’
       69 | #pragma message PRINT_MACRO_AT_COMPILE_TIME(MY_STR)
          |         ^~~~~~~
    ./macro_print_macro_values_at_compile_time.c:70:9: note: ‘#pragma message: MY_CODE_BLOCK=`do { printf("Hi.\n"); } while (0)`’
       70 | #pragma message PRINT_MACRO_AT_COMPILE_TIME(MY_CODE_BLOCK)
          |         ^~~~~~~
    Hi.
    Hello World.


OR, in C++:

    eRCaGuy_hello_world/c$ g++ -Wall -Wextra -Werror -O3 -std=gnu++17 macro_print_macro_values_at_compile_time.c -o bin/a && bin/a
    macro_print_macro_values_at_compile_time.c:63:63: note: ‘#pragma message: NOT_DEFINED=`NOT_DEFINED`’
       63 | #define PRINT_MACRO_AT_COMPILE_TIME(var) #var "=`" VALUE(var) "`"
          |                                                               ^~~
    macro_print_macro_values_at_compile_time.c:66:17: note: in expansion of macro ‘PRINT_MACRO_AT_COMPILE_TIME’
       66 | #pragma message PRINT_MACRO_AT_COMPILE_TIME(NOT_DEFINED)
          |                 ^~~~~~~~~~~~~~~~~~~~~~~~~~~
    macro_print_macro_values_at_compile_time.c:63:63: note: ‘#pragma message: DEFINED_BUT_NO_VALUE=``’
       63 | #define PRINT_MACRO_AT_COMPILE_TIME(var) #var "=`" VALUE(var) "`"
          |                                                               ^~~
    macro_print_macro_values_at_compile_time.c:67:17: note: in expansion of macro ‘PRINT_MACRO_AT_COMPILE_TIME’
       67 | #pragma message PRINT_MACRO_AT_COMPILE_TIME(DEFINED_BUT_NO_VALUE)
          |                 ^~~~~~~~~~~~~~~~~~~~~~~~~~~
    macro_print_macro_values_at_compile_time.c:63:63: note: ‘#pragma message: MY_INT=`3`’
       63 | #define PRINT_MACRO_AT_COMPILE_TIME(var) #var "=`" VALUE(var) "`"
          |                                                               ^~~
    macro_print_macro_values_at_compile_time.c:68:17: note: in expansion of macro ‘PRINT_MACRO_AT_COMPILE_TIME’
       68 | #pragma message PRINT_MACRO_AT_COMPILE_TIME(MY_INT)
          |                 ^~~~~~~~~~~~~~~~~~~~~~~~~~~
    macro_print_macro_values_at_compile_time.c:63:63: note: ‘#pragma message: MY_STR=`"ABC"`’
       63 | #define PRINT_MACRO_AT_COMPILE_TIME(var) #var "=`" VALUE(var) "`"
          |                                                               ^~~
    macro_print_macro_values_at_compile_time.c:69:17: note: in expansion of macro ‘PRINT_MACRO_AT_COMPILE_TIME’
       69 | #pragma message PRINT_MACRO_AT_COMPILE_TIME(MY_STR)
          |                 ^~~~~~~~~~~~~~~~~~~~~~~~~~~
    macro_print_macro_values_at_compile_time.c:63:63: note: ‘#pragma message: MY_CODE_BLOCK=`do { printf("Hi.\n"); } while (0)`’
       63 | #define PRINT_MACRO_AT_COMPILE_TIME(var) #var "=`" VALUE(var) "`"
          |                                                               ^~~
    macro_print_macro_values_at_compile_time.c:70:17: note: in expansion of macro ‘PRINT_MACRO_AT_COMPILE_TIME’
       70 | #pragma message PRINT_MACRO_AT_COMPILE_TIME(MY_CODE_BLOCK)
          |                 ^~~~~~~~~~~~~~~~~~~~~~~~~~~
    Hi.
    Hello World.


*/
