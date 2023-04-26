///usr/bin/env ccache gcc -Wall -Wextra -Werror -O3 -std=gnu17 "$0" -o /tmp/a -lm && /tmp/a "$@"; exit
// For the line just above, see my answer here: https://stackoverflow.com/a/75491834/4561887

/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
26 Apr. 2023

Demonstrate basic function pointers in C and C++ and how to `typedef` them to make them simpler.
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
./func_ptr_typedef.c
# or:
gcc -Wall -Wextra -Werror -O3 -std=gnu17 func_ptr_typedef.c -o bin/a -lm && bin/a

# 2. In C++
g++ -Wall -Wextra -Werror -O3 -std=gnu++17 func_ptr_typedef.c -o bin/a && bin/a
```

References:
1. ***** [very useful!] https://stackoverflow.com/a/4295495/4561887
1. https://www.geeksforgeeks.org/function-pointer-in-c/
1. [my question] https://stackoverflow.com/q/31869026/4561887

*/


#include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`

// typedef of a pointer to a function of type `int(int, int)`--ie: a function which returns `int`
// and accepts two `int`s.
typedef int(*func_t)(int, int);  // <====================

// Pass a function as a parameter withOUT using the typedef above!; notice how ugly this is!
void operate(int(*func)(int, int), int num1, int num2)
{
    int result = func(num1, num2);
    printf("result = %i\n", result);
}

// Now pass a function as a parameter WITH using the typedef above!; notice how beautiful and easy-
// to-read this is!
void operate2(func_t func, int num1, int num2)
{
    int result = func(num1, num2);
    printf("result = %i\n", result);
}

// a couple simple functions to use as function parameters

int add(int num1, int num2)
{
    return num1 + num2;
}

int subtract(int num1, int num2)
{
    return num1 - num2;
}

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Hello World.\n\n");

    operate(add, 5, 7);
    operate2(add, 5, 7);

    operate(subtract, 5, 7);
    operate2(subtract, 5, 7);

    return 0;
}


/*
SAMPLE OUTPUT:

In C:

    eRCaGuy_hello_world/c$ ./func_ptr_typedef.c
    Hello World.

    result = 12
    result = 12
    result = -2
    result = -2



OR, in C++:

    eRCaGuy_hello_world/c$ g++ -Wall -Wextra -Werror -O3 -std=gnu++17 func_ptr_typedef.c -o bin/a && bin/a
    Hello World.

    result = 12
    result = 12
    result = -2
    result = -2


*/
