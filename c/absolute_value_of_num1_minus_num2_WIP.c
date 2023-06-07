///usr/bin/env ccache gcc -Wall -Wextra -Werror -O3 -std=gnu17 "$0" -o /tmp/a -lm && /tmp/a "$@"; exit
// For the line just above, see my answer here: https://stackoverflow.com/a/75491834/4561887

/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
6 June 2023

Practice finding the absolute value of (num1 - num2). ie: `abs(num1 - num2)`.
See this question here, which I'm attempting to answer:
https://stackoverflow.com/q/76419734/4561887

STATUS: wip

keywords to easily grep or ripgrep in this repo for this program and what it teaches
KEYWORDS:

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# Why `-std=gnu17` vs `-std=c17`, and `-std=gnu++17` vs `-std=c++17`?
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# [run once ever] install ccache
sudo apt update && sudo apt install ccache

# 1. In C:
./absolute_value_of_num1_minus_num2_WIP.c
# or:
gcc -Wall -Wextra -Werror -O3 -std=gnu17 absolute_value_of_num1_minus_num2_WIP.c -o bin/a -lm && bin/a

# 2. In C++
g++ -Wall -Wextra -Werror -O3 -std=gnu++17 absolute_value_of_num1_minus_num2_WIP.c -o bin/a && bin/a
```

References:
1.
1.

*/


#include <limits.h>
#include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`


#define TEST_EQ(func, num1, num2, equals) \
    printf("%s\n", func((num1), (num2)) == (equals) ? "Passed" : "FAILED")

/// Safely and efficiently return `abs((int8_t)num1 - (int8_t)num2)`
uint8_t absolute_difference_int8(int8_t num1, int8_t num2)
{
    printf("num1 = %i; num2 = %i  ", num1, num2); // debugging
    uint8_t abs_diff = num1 > num2 ?
        (uint8_t)num1 - (uint8_t)num2 : (uint8_t)num2 - (uint8_t)num1;
    return abs_diff;
}

// /// Safely and efficiently return `abs((int)num1 - (int)num2)`
// unsigned int absolute_difference_int(unsigned int num1, unsigned int num2)
// {
//     unsigned int abs_diff = num1 > num2 ? num1 - num2 : num2 - num1;
//     return abs_diff;
// }

int main()
{
    printf("Absolute difference tests.\n");

    int8_t num1_8;
    int8_t num2_8;

    // int num1;
    // int num2;

    printf("INT8_MIN = %i, INT8_MAX = %i\n", INT8_MIN, INT8_MAX); // -128, 127
    printf("\n");

    num1_8 = -7;
    num2_8 = -4;
    TEST_EQ(absolute_difference_int8, num1_8, num2_8, 3);

    num1_8 = INT8_MIN;
    num2_8 = INT8_MAX;
    TEST_EQ(absolute_difference_int8, num1_8, num2_8, 255);

    // printf("%s\n", absolute_difference(INT_MIN, -4) == 3 ? "Passed" : "FAILED");

    return 0;
}


/*
SAMPLE OUTPUT:

In C:

    eRCaGuy_hello_world/c$ gcc -Wall -Wextra -Werror -O3 -std=c17 absolute_value_of_num1_minus_num2_WIP.c -o bin/a -lm && bin/a
    Hello World.


OR, in C++:

    eRCaGuy_hello_world/c$ g++ -Wall -Wextra -Werror -O3 -std=c++17 absolute_value_of_num1_minus_num2_WIP.c -o bin/a && bin/a
    Hello World.

*/
