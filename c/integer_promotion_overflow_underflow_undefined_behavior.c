/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
16 June 2022

I recently took the 15 question (1.5 minutes per question) LinkedIn Skill Assessment badge for C++
(https://www.linkedin.com/skill-assessments/C++/report/?practiceMode=), and although I scored in
the top 5% out of 1.3M people who took it
(screenshot:
https://user-images.githubusercontent.com/6842199/174214260-f11e6b7a-11df-41ae-ac27-026b8dd87edf.png),
I think I missed one of the 15 questions.

I think I missed a question like this regarding underflow and overflow, due to some nuances of the
question I wasn't familiar with, so let's test some things to make sure I understand what the
compiler does when you both:
1. have undefined behavior overflow or underflow in a signed integer type, AND
2. then compare that signed integer against an unsigned integer.

Does the compiler throw any errors with vs withOUT the `-Wall -Wextra -Werror` compiler flags?
Does the compiler automatically to implicit integer promotion of the signed integer to an unsigned
integer when doing the comparison?

NB: **signed** integer overflow and underflow is **undefined behavior** in both C and C++
(see https://stackoverflow.com/a/16188846/4561887), so it is possible that LinkedIn was **relying
on undefined behavior** in their skills assessment on this one particular question--possibly even
having the answer based on what happens during this **undefined behavior** **for a particular
compiler**, such as gcc/g++. If that's the case, I'd say the question should only be considered
legitimate if they specify the compiler or the integer representation scheme, such as "2's
complement." That being said, I still got it wrong! So, let's go refresh my memory on some things!
---
Update: no, if the compiler does the overflow/underflow during preprocessing or copmiling, maybe it
is NOT undefined behavior? Maybe it is only undefined behavior if it happens during run-time? I'm
not sure, but yes, I think this could be the case.


STATUS: done and works!

See my answer related to this: Integer and floating point rank and promotion rules in C and C++:
https://stackoverflow.com/a/72654668/4561887


To compile and run (assuming you've already `cd`ed into this dir):
```bash
# Why `-std=gnu17` vs `-std=c17`, and `-std=gnu++17` vs `-std=c++17`?
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# 1. In C:
gcc -Wall -Wextra -Werror -O3 -std=gnu17 integer_promotion_overflow_underflow_undefined_behavior.c -o bin/a -lm && bin/a

# 2. In C++
g++ -Wall -Wextra -Werror -O3 -std=gnu++17 integer_promotion_overflow_underflow_undefined_behavior.c -o bin/a && bin/a
```

References:
1. Implicit type promotion rules: https://stackoverflow.com/q/46073295/4561887
    1. [my answer] Integer and floating point rank and promotion rules in C and C++:
       https://stackoverflow.com/a/72654668/4561887


------------------------
Integer promotion rules:
------------------------
Source: https://stackoverflow.com/a/46073296/4561887
- any types smaller than an int (ex: int8_t, uint8_t, int16_t, uint16_t) gets promoted to an int    <==================
  (ex: int32_t), unless that's not big enough, in which case it gets promoted to an `unsigned int`
  (ex: uint32_t)
    ...prior to any mathematical or comparison evaluation being performed on the type!
So, with this:
```c
uint8_t x = 0;
uint8_t y = 1;
```
...if you do `x - y`, they first get implicitly promoted to `int` (which is `int32_t` on my 64-bit
   system), and you end up with this: `(int)x - (int)y`, which results in an `int` type with value
   `-1`, rather than a `uint8_t` type of value `255`. To get the desired `255` result, **manually**
   cast the result back to `uint8_t`, by doing this: `(uint8_t)(x - y)`.


*/

#include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Hello World.\n\n");

    // signed integer overflow (undefined behavior): --> 200 - 127 + -(128 - 1) = -56
    // (again, as **undefined behavior**!). Note that the range of int8_t is -(2^8/2) to
    // (2^8/2 - 1), which is -128 to (128-1) or -128 to +127.
    // ---
    // Update: maybe this is NOT considered undefined behavior since it is happening **statically**
    // during **compile-time**, instead of during **run-time**. Maybe only integer
    // overflow/underflow during **runtime** is undefined behavior, but NOT if it is done during
    // compile-time? Yes, I think this is probably the case!
    int8_t a = 200;

    uint8_t b = 100;

    printf("a = %i\n"
           "b = %u\n",
           a, b);

    if (a > b)
    {
        printf("true: a is greater\n");
    }
    else
    {
        printf("false: a is less\n");
    }
    printf("\n");


    // Other examples; from here: https://stackoverflow.com/q/46073295/4561887

    // Example 1
    {
        unsigned char x = 0;
        unsigned char y = 1;

        // print as an unsigned integer type
        printf("%u\n", x - y);                  // Possible output: `4294967295` (2^32 - 1)
        printf("%u\n", (unsigned char)(x - y)); // Output: `255`

        // print as a signed integer type
        printf("%i\n", x - y);                  // Output: `-1`
        printf("%i\n", (unsigned char)(x - y)); // Output: `255`

        printf("\n");
    }

    // Example 2
    {
        unsigned int a = 1;
        signed int b = -2;
        if(a + b > 0)  // is true; see explanation below and "Integer promotion rules" above.
        {
            // This block IS entered, because `a + b` IS > 0, due to integer promotion rules!
            // Variable `b` gets promoted from `signed int` to `unsigned int`, which makes it go
            // from `-2` to 2^32 - 2 = 4294967294. That + b = 4294967295.

            puts("-1 is larger than 0"); // this prints
            printf("a + b = %u\n", a + b);
            printf("a + b = %i\n", a + b);

            printf("\n");
        }
    }

    // Example 3
    {
        unsigned short a = 1;
        // is false, since both types are **small types** so they are promoted to `int`, resulting
        // in a value of a + b = 1 - 2 = -1, which is NOT > 0.
        signed short b = -2;
        if(a + b > 0)
        {
            puts("-1 is larger than 0"); // this does NOT print
        }

        printf("\n");
    }


    return 0;
}

/*
SAMPLE OUTPUT:

In C:

    eRCaGuy_hello_world/c$ gcc -Wall -Wextra -Werror -O3 -std=gnu17 integer_promotion_overflow_underflow_undefined_behavior.c -o bin/a -lm && bin/a
    Hello World.

    a = -56
    b = 100
    false: a is less

    4294967295
    255
    -1
    255

    -1 is larger than 0
    a + b = 4294967295
    a + b = -1


OR, in C++ (exact same):

    eRCaGuy_hello_world/c$ g++ -Wall -Wextra -Werror -O3 -std=gnu++17 integer_promotion_overflow_underflow_undefined_behavior.c -o bin/a && bin/a
    Hello World.

    a = -56
    b = 100
    false: a is less

    4294967295
    255
    -1
    255

    -1 is larger than 0
    a + b = 4294967295
    a + b = -1


*/
