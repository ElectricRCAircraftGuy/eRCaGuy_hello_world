/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
29 June 2021

See if I can duplicate a really strange "Segmentation fault" and core dump I get when trying to
override malloc() and free() in my fast_malloc implementation.

To compile and run (assuming you've already `cd`ed into this dir):
1. In C:
    mkdir -p bin && gcc -Wall -Wextra -Werror -O3 -std=c11 -save-temps=obj malloc_override_test.c \
    -o bin/malloc_override_test && bin/malloc_override_test
2. In C++
    mkdir -p bin && g++ -Wall -Wextra -Werror -O3 -std=c++17 -save-temps=obj malloc_override_test.c \
    -o bin/malloc_override_test && bin/malloc_override_test

References:
1. None.


RESULT:

The output looks fine in this case, but these two Stack Overflow questions I asked do indeed seem
to contain and describe the problem as being an infinite recursion between malloc() and printf(),
where I have malloc() call printf(), and printf() in turn sometimes has to malloc() (in my other
code at least, but not this code for some reason):
1. [my Q--THE MAIN ONE] https://stackoverflow.com/questions/68188903/segmentation-fault-core-dumped-for-no-such-file-or-directory-for-libiop-h
1. [my Q--see this too] https://stackoverflow.com/questions/68189631/which-print-calls-in-c-do-not-ever-call-malloc-under-the-hood

*/

#include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`

#ifdef DEBUG
    /// Debug printf function.
    /// See: https://stackoverflow.com/a/1941336/4561887
    #define DEBUG_PRINTF(...) printf("DEBUG: "__VA_ARGS__)
#else
    #define DEBUG_PRINTF(...) \
        do                    \
        {                     \
        } while (0)
#endif

// Override malloc and free

inline void* malloc(size_t num_bytes)
{
    // This is the culprit I think
    DEBUG_PRINTF("%sffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"
                 "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"
                 "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"
                 "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"
                 "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"
                 "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"
                 "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"
                 "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"
                 "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"
                 "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"
                 "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"
                 "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"
                 "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"
                 "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"
                 "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"
                 "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"
                 "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"
                 "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"
                 "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"
                 "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"
                 "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"
                 "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"
                 "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"
                 "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"
                 "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"
                 "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"
                 "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"
                 "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"
                 "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"
                 "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"
                 "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"
                 "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"
                 "():\n", __func__);

    (void)num_bytes;
    return NULL;
}

inline void free(void* ptr)
{
    (void)ptr;
}

int main()
{
    printf("Hello world.\n");

    printf("Hello worldddddddddddddddddddddddddddddddddddddddddddddddddddd.\n"
           "Hello worldddddddddddddddddddddddddddddddddddddddddddddddddddd.\n"
           "Hello worldddddddddddddddddddddddddddddddddddddddddddddddddddd.\n"
           "Hello worldddddddddddddddddddddddddddddddddddddddddddddddddddd.\n"
           "Hello worldddddddddddddddddddddddddddddddddddddddddddddddddddd.\n"
           "Hello worldddddddddddddddddddddddddddddddddddddddddddddddddddd.\n"
           "Hello worldddddddddddddddddddddddddddddddddddddddddddddddddddd.\n"
           "Hello worldddddddddddddddddddddddddddddddddddddddddddddddddddd.\n"
           "Hello worldddddddddddddddddddddddddddddddddddddddddddddddddddd.\n"
           "Hello worldddddddddddddddddddddddddddddddddddddddddddddddddddd.\n"
           "Hello worldddddddddddddddddddddddddddddddddddddddddddddddddddd.\n"
           "Hello worldddddddddddddddddddddddddddddddddddddddddddddddddddd.\n"
           "Hello worldddddddddddddddddddddddddddddddddddddddddddddddddddd.\n"
           "Hello worldddddddddddddddddddddddddddddddddddddddddddddddddddd.\n"
           "Hello worldddddddddddddddddddddddddddddddddddddddddddddddddddd.\n"
           "Hello worldddddddddddddddddddddddddddddddddddddddddddddddddddd.\n"
    );

    return 0;
}

/*
SAMPLE OUTPUT:



*/
