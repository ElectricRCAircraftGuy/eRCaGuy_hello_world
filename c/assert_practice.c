/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
29 June 2021

See if `assert()` prints out the file, function, and line, and if not, write a wrapper macro to
force it to do so.

To compile and run (assuming you've already `cd`ed into this dir):
1. In C [THIS IS WHAT I RAN FOR MY TESTING BELOW]:
    mkdir -p bin && gcc -Wall -Wextra -Werror -O3 -std=c11 -save-temps=obj assert_practice.c \
    -o bin/assert_practice && bin/assert_practice
2. In C++
    mkdir -p bin && g++ -Wall -Wextra -Werror -O3 -std=c++17 -save-temps=obj assert_practice.c \
    -o bin/assert_practice && bin/assert_practice

References:
1. https://en.cppreference.com/w/c/error/static_assert
1. https://en.cppreference.com/w/c/error/assert

*/

#include <assert.h>  // For `assert()` and `static_assert()` macro wrappers in C11
#include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`

#define ASSERT_TRUE(condition) \
    do \
    { \
        if (!(condition)) \
        { \
            printf("File: %s, Func: %s(), Line: %i: `" #condition "` expected to be true, " \
                   "but is false.\n", __FILE__, __func__, __LINE__); \
        } \
        assert(condition); \
    } while (0)

int main()
{
    printf("Hello world.\n");

    // Sample output of this static_assert:
    //      assert_practice.c: In function ‘main’:
    //      assert_practice.c:43:4: error: static assertion failed: "Failed; condition must be true to pass\012"
    //         43 |     static_assert(false, "Failed; condition must be true to pass\n");
    //            |    ^~~~~~~~~~~~~~
    // static_assert(false, "Failed; condition must be true to pass\n");

    // Sample output of this assert:
    //      assert_practice: assert_practice.c:43: main: Assertion `false' failed.                        <=== WHAT `assert()` DID AUTOMATICALLY
    //      Aborted (core dumped)
    // assert(false);

    // Sample output of this assert macro:
    //      File: assert_practice.c, Func: main(), Line: 56: `false` expected to be true, but is false.   <=== WHAT I MANUALLY DID
    //      assert_practice: assert_practice.c:56: main: Assertion `0' failed.                            <=== WHAT `assert()` DID AUTOMATICALLY
    //      Aborted (core dumped)
    ASSERT_TRUE(false);

    return 0;
}


/*
SAMPLE OUTPUT:

(see comments above)

*/
