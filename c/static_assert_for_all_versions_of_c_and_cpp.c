/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
First Written: 4 Mar. 2019
Updated: 16 Apr. 2022

Demonstrate a universal static assert macro which works and can be used
in **all** versions of C and C++ (at least: so long as the gcc or clang
compilers are used), if possible.

See my answer with this code here: https://stackoverflow.com/a/54993033/4561887.

Note: we must use C-style comments instead of C++ //-style comments, in order to
compile this code in ISO C90. Otherwise , you'll see:
> error: C++ style comments are not allowed in ISO C90

STATUS: done and works! I now have a `STATIC_ASSERT()` macro below which handles ALL versions of C
and C++, and gnu C and gnu C++! The only caveats are that ISO C versions < C11 do NOT support
static assertions inside structs or unions. ie: `-std=c90` and `-std=c99` do NOT allow static
assertions in structs and unions, but `-std=gnu90` and `-std=gnu99`, and **all** other versions of
C, C++, gnu C, and gnu C++, **do**!

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# Why `-std=gnu17` vs `-std=c17`, and `-std=gnu++17` vs `-std=c++17`?
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# 1. In C:
gcc -Wall -Wextra -Werror -O3 -std=c90 static_assert_for_all_versions_of_c_and_cpp.c -o bin/a -lm && bin/a
gcc -Wall -Wextra -Werror -O3 -std=c99 static_assert_for_all_versions_of_c_and_cpp.c -o bin/a -lm && bin/a
gcc -Wall -Wextra -Werror -O3 -std=c11 static_assert_for_all_versions_of_c_and_cpp.c -o bin/a -lm && bin/a
gcc -Wall -Wextra -Werror -O3 -std=c17 static_assert_for_all_versions_of_c_and_cpp.c -o bin/a -lm && bin/a
# gnu C
gcc -Wall -Wextra -Werror -O3 -std=gnu90 static_assert_for_all_versions_of_c_and_cpp.c -o bin/a -lm && bin/a
gcc -Wall -Wextra -Werror -O3 -std=gnu99 static_assert_for_all_versions_of_c_and_cpp.c -o bin/a -lm && bin/a
gcc -Wall -Wextra -Werror -O3 -std=gnu11 static_assert_for_all_versions_of_c_and_cpp.c -o bin/a -lm && bin/a
gcc -Wall -Wextra -Werror -O3 -std=gnu17 static_assert_for_all_versions_of_c_and_cpp.c -o bin/a -lm && bin/a  # my default C build cmd


# 2. In C++
g++ -Wall -Wextra -Werror -O3 -std=c++98 static_assert_for_all_versions_of_c_and_cpp.c -o bin/a && bin/a
g++ -Wall -Wextra -Werror -O3 -std=c++03 static_assert_for_all_versions_of_c_and_cpp.c -o bin/a && bin/a
g++ -Wall -Wextra -Werror -O3 -std=c++11 static_assert_for_all_versions_of_c_and_cpp.c -o bin/a && bin/a
g++ -Wall -Wextra -Werror -O3 -std=c++17 static_assert_for_all_versions_of_c_and_cpp.c -o bin/a && bin/a
# gnu++
g++ -Wall -Wextra -Werror -O3 -std=gnu++98 static_assert_for_all_versions_of_c_and_cpp.c -o bin/a && bin/a
g++ -Wall -Wextra -Werror -O3 -std=gnu++03 static_assert_for_all_versions_of_c_and_cpp.c -o bin/a && bin/a
g++ -Wall -Wextra -Werror -O3 -std=gnu++11 static_assert_for_all_versions_of_c_and_cpp.c -o bin/a && bin/a
g++ -Wall -Wextra -Werror -O3 -std=gnu++17 static_assert_for_all_versions_of_c_and_cpp.c -o bin/a && bin/a  # my default C++ build cmd

```

C versions: c90, c99, c11, c17, etc.
C++ versions: c++98, c++03, c++11, c++17, etc.

References:
1. *****+[MY ANSWER] https://stackoverflow.com/a/54993033/4561887
1. https://www.gnu.org/software/gnulib/manual/html_node/assert_002eh.html
1. To be posted in:
    1. https://stackoverflow.com/questions/987684/does-gcc-have-a-built-in-compile-time-assert/987756#987756
    1. https://stackoverflow.com/questions/3385515/static-assert-in-c/7287341#7287341
1. gcc predefined macros:
    1. *****https://gcc.gnu.org/onlinedocs/cpp/Standard-Predefined-Macros.html
    1. *****https://gcc.gnu.org/onlinedocs/cpp/Common-Predefined-Macros.html


*/



#include <stdbool.h>
#include <stdint.h>  /* For `uint8_t`, `int8_t`, etc. */
#include <stdio.h>


/* -------------------------------------------------------------------------- */
/* For **C11 or later _and_ C++11 or later**: */
/*
#include <assert.h>
#define STATIC_ASSERT(test_for_true) \
    static_assert((test_for_true), "(" #test_for_true ") failed")
*/
/* -------------------------------------------------------------------------- */


/* -------------------------------------------------------------------------- */
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
/* -------------------------------------------------------------------------- */



/* --------------------------------- START ---------------------------------- */
/* OR [BEST], for **any version of C OR C++**: */

/* See: https://stackoverflow.com/a/71899854/4561887 */
#define CONCAT_(prefix, suffix) prefix##suffix
/* Concatenate `prefix, suffix` into `prefixsuffix` */
#define CONCAT(prefix, suffix) CONCAT_(prefix, suffix)
/* Make a unique variable name containing the line number at the end of the */
/* name. Ex: `uint64_t MAKE_UNIQUE_VARIABLE_NAME(counter) = 0;` would */
/* produce `uint64_t counter_7 = 0` if the call is on line 7! */
#define MAKE_UNIQUE_VARIABLE_NAME(prefix) CONCAT(prefix##_, __LINE__)

/* Static assert hack required for **pre-C++11**, such as C++98, C++03, etc. */
/* - It works only with C++, NOT with C! */
/* See: */
/* 1. [my ans with this] https://stackoverflow.com/a/54993033/4561887 */
/* 1. Info. on `_Pragma()`: https://stackoverflow.com/a/47518775/4561887 */
/* 1. The inspiration for this `typedef char` array hack as a struct  */
/*    definition: https://stackoverflow.com/a/3385694/4561887 */
/* Discard the `message` portion entirely. */
#define _Static_assert_hack(expression, message) \
    struct MAKE_UNIQUE_VARIABLE_NAME(static_assertion_failed) \
    { \
        _Pragma("GCC diagnostic push") \
        _Pragma("GCC diagnostic ignored \"-Wunused-local-typedefs\"") \
        typedef char static_assertion_failed[(expression) ? 1 : -1]; \
        _Pragma("GCC diagnostic pop") \
    }

/* For C++ only: */
/* See: https://gcc.gnu.org/onlinedocs/cpp/Standard-Predefined-Macros.html */
#ifdef __cplusplus
    #if __cplusplus < 201103L
        /* for pre-C++11 */
        #ifndef _Static_assert
            #define _Static_assert _Static_assert_hack
        #endif
    #else
        /* for C++11 or later */
        #ifndef _Static_assert
            #define _Static_assert static_assert
        #endif
    #endif
#endif

/* For C **and** C++: */
#define STATIC_ASSERT(test_for_true) \
    _Static_assert((test_for_true), "(" #test_for_true ") failed")
/* ---------------------------------- END ----------------------------------- */



STATIC_ASSERT(2 > 1);
STATIC_ASSERT(3 > 1);
STATIC_ASSERT(4 > 1);

typedef struct data_s
{
    int i1;
    int i2;

/* The gcc `_Static_assert()` is incompatible with static asserts inside */
/* structs and unions when compiling with ISO C standards, so remove these */
/* static asserts for C versions < C11. */
/* `-std=c90`, for instance, can NOT handle these, but `-std=gnu90` can. */
/* See: */
/* 1. https://gcc.gnu.org/onlinedocs/cpp/Standard-Predefined-Macros.html */
/* 1. https://gcc.gnu.org/onlinedocs/cpp/Common-Predefined-Macros.html */
/*
#if __STDC_VERSION__  201112L
    STATIC_ASSERT(2 > 1);
    STATIC_ASSERT(3 > 1);
    STATIC_ASSERT(4 > 1);
#endif
*/
} data_t;
STATIC_ASSERT(sizeof(data_t) >= 4);

typedef union data_u
{
    data_t data;
    uint8_t bytes[sizeof(data_t)];


/* See notes above. */
/*
    STATIC_ASSERT(2 > 2);
    STATIC_ASSERT(5 > 5);
    STATIC_ASSERT(2 > 1);
    STATIC_ASSERT(5 > 4);

    _Static_assert(2 > 1, "this should pass");
    _Static_assert(5 > 4, "this should pass");
*/
} data_union_t;
STATIC_ASSERT(sizeof(data_union_t) >= 4);


/* int main(int argc, char *argv[])  // alternative prototype */
int main(void)
{
    printf("Static assert tests in C and C++.\n");

    /* Print C and C++ versions. */

#ifdef __cplusplus
    printf("__cplusplus = %li\n", __cplusplus);
#endif
#ifdef __STDC_VERSION__
    printf("__STDC_VERSION__ = %li\n", __STDC_VERSION__);
#endif
#ifdef __STDC__
    printf("__STDC__ = %i\n", __STDC__);
#endif
#ifdef __STRICT_ANSI__
    printf("__STRICT_ANSI__ = %i\n", __STRICT_ANSI__);
#endif

#if __cplusplus >= 201103L
    printf("__cplusplus >= 201103L\n");
#endif


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
    STATIC_ASSERT(4 > 1);
    STATIC_ASSERT(6 > 1);

    /* this should fail. UNCOMMENT THESE BELOW TO SEE SOME STATIC ASSERTIONS! */
    /*
    STATIC_ASSERT(-5 > 2);
    STATIC_ASSERT(1 > 2);
    STATIC_ASSERT(2 > 2);
    */


    return 0;
}


/*
SAMPLE OUTPUT:

In C:

    eRCaGuy_hello_world/c$ gcc -Wall -Wextra -Werror -O3 -std=c90 static_assert_for_all_versions_of_c_and_cpp.c -o bin/a -lm && bin/a
    Static assert tests in C and C++.
    __STDC__ = 1
    __STRICT_ANSI__ = 1



OR, in C++:

    eRCaGuy_hello_world/c$ g++ -Wall -Wextra -Werror -O3 -std=c++98 static_assert_for_all_versions_of_c_and_cpp.c -o bin/a && bin/a
    Static assert tests in C and C++.
    __cplusplus = 199711
    __STDC__ = 1
    __STRICT_ANSI__ = 1



*/
