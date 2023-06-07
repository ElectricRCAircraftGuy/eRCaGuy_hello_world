///usr/bin/env ccache gcc -Wall -Wextra -Werror -O3 -std=gnu17 "$0" -o /tmp/a -lm && /tmp/a "$@"; exit
// For the line just above, see my answer here: https://stackoverflow.com/a/75491834/4561887

/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
6 June 2023

Practice finding the absolute value of (num1 - num2). ie: `abs(num1 - num2)`.
See this question here, which I'm attempting to answer:
https://stackoverflow.com/q/76419734/4561887

STATUS: done and works!

keywords to easily grep or ripgrep in this repo for this program and what it teaches
KEYWORDS:

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# Why `-std=gnu17` vs `-std=c17`, and `-std=gnu++17` vs `-std=c++17`?
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# [run once ever] install ccache
sudo apt update && sudo apt install ccache

# 1. In C:
./absolute_value_of_num1_minus_num2.c
# or:
gcc -Wall -Wextra -Werror -O3 -std=gnu17 absolute_value_of_num1_minus_num2.c -o bin/a -lm && bin/a

# 2. In C++
g++ -Wall -Wextra -Werror -O3 -std=gnu++17 absolute_value_of_num1_minus_num2.c -o bin/a && bin/a
```

References:
1. ***** See my answer with this code here: How to safely and efficiently find
   `abs((int)num1 - (int)num2)` - https://stackoverflow.com/a/76420269/4561887
1.

*/


#include <limits.h>
#include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`


#define TEST_EQ(func, num1, num2, equals) \
    printf("%s\n", func((num1), (num2)) == (equals) ? "Passed" : "FAILED")

/// Safely and efficiently return `abs((int8_t)num1 - (int8_t)num2)`
uint8_t abs_num1_minus_num2_int8(int8_t num1, int8_t num2)
{
    uint8_t abs_diff = num1 > num2 ?
        (uint8_t)num1 - (uint8_t)num2 :
        (uint8_t)num2 - (uint8_t)num1;

    // debugging
    printf("num1 = %4i (%3u); num2 = %4i (%3u); num1-num2=%3u;  ",
        num1, (uint8_t)num1, num2, (uint8_t)num2, abs_diff);

    return abs_diff;
}

/// Safely and efficiently return `abs((int)num1 - (int)num2)`
unsigned int abs_num1_minus_num2_int(int num1, int num2)
{
    unsigned int abs_diff = num1 > num2 ?
        (unsigned int)num1 - (unsigned int)num2 :
        (unsigned int)num2 - (unsigned int)num1;

    // debugging
    printf("num1 = %11i (%10u); num2 = %11i (%10u); num1-num2=%10u;  ",
        num1, (unsigned int)num1, num2, (unsigned int)num2, abs_diff);

    return abs_diff;
}


int main()
{
    printf("Absolute difference tests.\n");

    // ---------------
    // int8_t types
    // ---------------

    int8_t num1_8;
    int8_t num2_8;

    printf("\n");
    printf("INT8_MIN = %i, INT8_MAX = %i\n", INT8_MIN, INT8_MAX); // -128, 127

    num1_8 = -7;
    num2_8 = -4;
    TEST_EQ(abs_num1_minus_num2_int8, num1_8, num2_8, 3);

    num1_8 = INT8_MIN;
    num2_8 = INT8_MAX;
    TEST_EQ(abs_num1_minus_num2_int8, num1_8, num2_8, UINT8_MAX);

    num1_8 = INT8_MAX;
    num2_8 = INT8_MIN;
    TEST_EQ(abs_num1_minus_num2_int8, num1_8, num2_8, UINT8_MAX);

    num1_8 = 100;
    num2_8 = 10;
    TEST_EQ(abs_num1_minus_num2_int8, num1_8, num2_8, 90);

    num1_8 = 10;
    num2_8 = 100;
    TEST_EQ(abs_num1_minus_num2_int8, num1_8, num2_8, 90);

    num1_8 = 10;
    num2_8 = 10;
    TEST_EQ(abs_num1_minus_num2_int8, num1_8, num2_8, 0);

    num1_8 = INT8_MAX;
    num2_8 = 1;
    TEST_EQ(abs_num1_minus_num2_int8, num1_8, num2_8, 126);

    num1_8 = 1;
    num2_8 = INT8_MAX;
    TEST_EQ(abs_num1_minus_num2_int8, num1_8, num2_8, 126);

    // ---------------
    // int types
    // ---------------

    int num1;
    int num2;

    printf("\n");
    printf("INT_MIN = %i, INT_MAX = %i\n", INT_MIN, INT_MAX); // -2147483648, 2147483647

    num1 = -7;
    num2 = -4;
    TEST_EQ(abs_num1_minus_num2_int, num1, num2, 3);

    num1 = INT_MIN;
    num2 = INT_MAX;
    TEST_EQ(abs_num1_minus_num2_int, num1, num2, UINT_MAX);

    num1 = INT_MAX;
    num2 = INT_MIN;
    TEST_EQ(abs_num1_minus_num2_int, num1, num2, UINT_MAX);

    num1 = 100;
    num2 = 10;
    TEST_EQ(abs_num1_minus_num2_int, num1, num2, 90);

    num1 = 10;
    num2 = 100;
    TEST_EQ(abs_num1_minus_num2_int, num1, num2, 90);

    num1 = 10;
    num2 = 10;
    TEST_EQ(abs_num1_minus_num2_int, num1, num2, 0);

    num1 = INT_MAX;
    num2 = 1;
    TEST_EQ(abs_num1_minus_num2_int, num1, num2, 2147483646);

    num1 = 1;
    num2 = INT_MAX;
    TEST_EQ(abs_num1_minus_num2_int, num1, num2, 2147483646);


    return 0;
}


/*
SAMPLE OUTPUT:

In C:

    eRCaGuy_hello_world/c$ ./absolute_value_of_num1_minus_num2.c
    Absolute difference tests.

    INT8_MIN = -128, INT8_MAX = 127
    num1 =   -7 (249); num2 =   -4 (252); num1-num2=  3;  Passed
    num1 = -128 (128); num2 =  127 (127); num1-num2=255;  Passed
    num1 =  127 (127); num2 = -128 (128); num1-num2=255;  Passed
    num1 =  100 (100); num2 =   10 ( 10); num1-num2= 90;  Passed
    num1 =   10 ( 10); num2 =  100 (100); num1-num2= 90;  Passed
    num1 =   10 ( 10); num2 =   10 ( 10); num1-num2=  0;  Passed
    num1 =  127 (127); num2 =    1 (  1); num1-num2=126;  Passed
    num1 =    1 (  1); num2 =  127 (127); num1-num2=126;  Passed

    INT_MIN = -2147483648, INT_MAX = 2147483647
    num1 =          -7 (4294967289); num2 =          -4 (4294967292); num1-num2=         3;  Passed
    num1 = -2147483648 (2147483648); num2 =  2147483647 (2147483647); num1-num2=4294967295;  Passed
    num1 =  2147483647 (2147483647); num2 = -2147483648 (2147483648); num1-num2=4294967295;  Passed
    num1 =         100 (       100); num2 =          10 (        10); num1-num2=        90;  Passed
    num1 =          10 (        10); num2 =         100 (       100); num1-num2=        90;  Passed
    num1 =          10 (        10); num2 =          10 (        10); num1-num2=         0;  Passed
    num1 =  2147483647 (2147483647); num2 =           1 (         1); num1-num2=2147483646;  Passed
    num1 =           1 (         1); num2 =  2147483647 (2147483647); num1-num2=2147483646;  Passed



OR, in C++:
(same as in C)

*/
