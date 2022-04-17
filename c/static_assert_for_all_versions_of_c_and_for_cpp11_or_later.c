/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
First Written: 4 Mar. 2019
Updated: 16 Apr. 2022

Demonstrate a universal static assert macro which works and can be used
in **all** versions of C and C++ (at least: so long as the gcc or clang
compilers are used), if possible.

Note: we must use C-style comments instead of C++ //-style comments, in order to
compile this code in ISO C90.

STATUS: wip

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# Why `-std=gnu17` vs `-std=c17`, and `-std=gnu++17` vs `-std=c++17`?
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# 1. In C:
gcc -Wall -Wextra -Werror -O3 -std=c90 static_assert_for_all_versions_of_c_and_for_cpp11_or_later.c -o bin/a -lm && bin/a
gcc -Wall -Wextra -Werror -O3 -std=c99 static_assert_for_all_versions_of_c_and_for_cpp11_or_later.c -o bin/a -lm && bin/a
gcc -Wall -Wextra -Werror -O3 -std=c11 static_assert_for_all_versions_of_c_and_for_cpp11_or_later.c -o bin/a -lm && bin/a
gcc -Wall -Wextra -Werror -O3 -std=c17 static_assert_for_all_versions_of_c_and_for_cpp11_or_later.c -o bin/a -lm && bin/a
# gnu C
gcc -Wall -Wextra -Werror -O3 -std=gnu90 static_assert_for_all_versions_of_c_and_for_cpp11_or_later.c -o bin/a -lm && bin/a
gcc -Wall -Wextra -Werror -O3 -std=gnu99 static_assert_for_all_versions_of_c_and_for_cpp11_or_later.c -o bin/a -lm && bin/a
gcc -Wall -Wextra -Werror -O3 -std=gnu11 static_assert_for_all_versions_of_c_and_for_cpp11_or_later.c -o bin/a -lm && bin/a
gcc -Wall -Wextra -Werror -O3 -std=gnu17 static_assert_for_all_versions_of_c_and_for_cpp11_or_later.c -o bin/a -lm && bin/a  # my default C build cmd


# 2. In C++
g++ -Wall -Wextra -Werror -O3 -std=c++98 static_assert_for_all_versions_of_c_and_for_cpp11_or_later.c -o bin/a && bin/a
g++ -Wall -Wextra -Werror -O3 -std=c++03 static_assert_for_all_versions_of_c_and_for_cpp11_or_later.c -o bin/a && bin/a
g++ -Wall -Wextra -Werror -O3 -std=c++11 static_assert_for_all_versions_of_c_and_for_cpp11_or_later.c -o bin/a && bin/a
g++ -Wall -Wextra -Werror -O3 -std=c++17 static_assert_for_all_versions_of_c_and_for_cpp11_or_later.c -o bin/a && bin/a
# gnu++
g++ -Wall -Wextra -Werror -O3 -std=gnu++98 static_assert_for_all_versions_of_c_and_for_cpp11_or_later.c -o bin/a && bin/a
g++ -Wall -Wextra -Werror -O3 -std=gnu++03 static_assert_for_all_versions_of_c_and_for_cpp11_or_later.c -o bin/a && bin/a
g++ -Wall -Wextra -Werror -O3 -std=gnu++11 static_assert_for_all_versions_of_c_and_for_cpp11_or_later.c -o bin/a && bin/a
g++ -Wall -Wextra -Werror -O3 -std=gnu++17 static_assert_for_all_versions_of_c_and_for_cpp11_or_later.c -o bin/a && bin/a  # my default C++ build cmd

```

C versions: c90, c99, c11, c17, etc.
C++ versions: c++98, c++03, c++11, c++17, etc.

References:
1. *****+[MY ANSWER] https://stackoverflow.com/a/54993033/4561887
1. https://www.gnu.org/software/gnulib/manual/html_node/assert_002eh.html
1. To be posted in:
    1. https://stackoverflow.com/questions/987684/does-gcc-have-a-built-in-compile-time-assert/987756#987756
    1. https://stackoverflow.com/questions/3385515/static-assert-in-c/7287341#7287341


*/



#include <stdbool.h>
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>


/* For **C11 or later _and_ C++11 or later**: */
/*
#include <assert.h>
#define STATIC_ASSERT(test_for_true) \
    static_assert((test_for_true), "(" #test_for_true ") failed")
*/


/* OR [better], for **_any_ version of C (as a gcc extension when using
the gcc compiler), including C90, C99, C11, C17, etc., _and_ for C++11 or
later**: */
/*
#ifdef __cplusplus
    #ifndef _Static_assert
        #define _Static_assert static_assert
    #endif
#endif
#define STATIC_ASSERT(test_for_true) \
    _Static_assert((test_for_true), "(" #test_for_true ") failed")
*/


/* OR [BEST], for **any version of C OR C++**: */
#ifdef __cplusplus
    #if __cplusplus < 201103L
        /* for pre-C++11 */
        #ifndef _Static_assert
            /* This hack is borrowed from the gcc source code here:
            https://github.com/gcc-mirror/gcc/blob/master/libgcc/soft-fp/soft-fp.h#L69-L71
            It works with **C** only, NOT C++! See:
            1. https://unix.stackexchange.com/a/449171/114401
            1. https://stackoverflow.com/q/14087905/4561887
            In C++, you'll get this error:
                error: types may not be defined in ‘sizeof’ expressions
            */
            /*
            #define _Static_assert(expr, msg) \
                extern int (*__Static_assert_function (void)) \
                [!!sizeof (struct { int __error_if_negative: (expr) ? 2 : -1; })]
            */
            #define _Static_assert(expr, msg) typedef char static_assertion_failed[(expr)?1:-1]
                // (void)static_assertion_failed
        #endif

    #else
        /* for C++11 or later */
        #ifndef _Static_assert
            #define _Static_assert static_assert
        #endif
    #endif
#endif
#define STATIC_ASSERT(test_for_true) \
    _Static_assert((test_for_true), "(" #test_for_true ") failed")


// #if sizeof(int) == 4
    // #warning "Hey"
// #endif

#define STATIC_ASSERT2(COND) typedef char static_assertion_failed[(COND)?1:-1]

STATIC_ASSERT2(2 > 1);

typedef struct data_s
{
    int i1;
    int i2;

    STATIC_ASSERT(2 > 2);
    // ((1 ? int i3 : int i4);
    // using i = (1 ? int : long int);

    // STATIC_ASSERT2(2 > 1);
} data_t;
STATIC_ASSERT(sizeof(data_t) >= 4);

typedef union data_u
{
    data_t data;
    uint8_t bytes[sizeof(data_t)];

    STATIC_ASSERT(2 > 1);
} data_union_t;
STATIC_ASSERT(sizeof(data_union_t) >= 4);

/* int main(int argc, char *argv[])  // alternative prototype */
int main(void)
{
    printf("Static assert tests in C and C++.\n");

    /*
    _Static_assert(2 > 1, "this should pass");
    _Static_assert(1 > 2, "this should fail");
    */

    /*
    static_assert(2 > 1, "this should pass");
    static_assert(1 > 2, "this should fail");
    */

    /* this should pass */
    STATIC_ASSERT(2 > 1);
    /*
    */
    /* this should fail */
    /*
    STATIC_ASSERT(1 > 2);
    */


    return 0;
}


/*
SAMPLE OUTPUT:

In C:

    eRCaGuy_hello_world/c$ gcc -Wall -Wextra -Werror -O3 -std=c17 static_assert_for_all_versions_of_c_and_for_cpp11_or_later.c -o bin/a -lm && bin/a
    Hello World.


OR, in C++:

    eRCaGuy_hello_world/c$ g++ -Wall -Wextra -Werror -O3 -std=c++17 static_assert_for_all_versions_of_c_and_for_cpp11_or_later.c -o bin/a && bin/a
    Hello World.


*/
