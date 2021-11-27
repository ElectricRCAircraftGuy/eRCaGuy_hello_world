/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
26 Nov. 2021

Demonstrate how preincrement (`++i`) vs postincrement (`i++`) work. Also do the decrements.

vvvvvvvv
In short, the lesson to learn is this:
    * `++i` increments the value first, and THEN reads the value.
    * `i++` reads the value first, and THEN increments it!
The same order goes for prefix and postfix decrements (`--i`, and `i--`, respectively).
That's it!
^^^^^^^^

To compile and run (assuming you've already `cd`ed into this dir):
1. In C:
    mkdir -p bin && gcc -Wall -Wextra -Werror -O3 -std=c11 -save-temps=obj preincrement_and_postincrement_demo.c \
    -o bin/preincrement_and_postincrement_demo && bin/preincrement_and_postincrement_demo
2. In C++
    mkdir -p bin && g++ -Wall -Wextra -Werror -O3 -std=c++17 -save-temps=obj preincrement_and_postincrement_demo.c \
    -o bin/preincrement_and_postincrement_demo && bin/preincrement_and_postincrement_demo

References:

1. I was inspired to write this by this comment by [@Steve Summit]
(https://stackoverflow.com/users/3923896/steve-summit) on this now-deleted question, here:
https://stackoverflow.com/questions/70126466/ambiguity-in-multiplication-of-pre-increment-and-post-increment?noredirect=1#comment123964937_70126466

See Also:
1. https://stackoverflow.com/questions/949433/why-are-these-constructs-using-pre-and-post-increment-undefined-behavior

*/

// #include <assert.h>  // For `assert()` and `static_assert()` macro wrappers in C11
#include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    int i = 4;
    printf("Initial value: %i\n", i);

    printf("\nIncrement tests\n");
    printf("%i\n", ++i);  // 5, because the increment happens FIRST, then the value is read
    printf("%i\n", i);    // 5
    printf("%i\n", i++);  // 5, because the value is read FIRST, then the increment takes place
    printf("%i\n", i);    // 6

    printf("\nDecrement tests\n");
    printf("%i\n", --i);  // 5
    printf("%i\n", i);    // 5
    printf("%i\n", i--);  // 5
    printf("%i\n", i);    // 4

    return 0;
}

/*
SAMPLE OUTPUT:

In C:

    eRCaGuy_hello_world/c$ mkdir -p bin && gcc -Wall -Wextra -Werror -O3 -std=c11 -save-temps=obj preincrement_and_postincrement_demo.c     -o bin/preincrement_and_postincrement_demo && bin/preincrement_and_postincrement_demo
    Initial value: 4

    Increment tests
    5
    5
    5
    6

    Decrement tests
    5
    5
    5
    4


OR, in C++:

    SAME AS IN C

*/
