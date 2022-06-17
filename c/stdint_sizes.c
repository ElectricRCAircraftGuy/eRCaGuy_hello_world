/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
June 2022

Check the sizes of all types on my 64-bit Linux machine with the gcc/c++ compiler in C and C++.

STATUS: done!

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# Why `-std=gnu17` vs `-std=c17`, and `-std=gnu++17` vs `-std=c++17`?
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# 1. In C:
gcc -Wall -Wextra -Werror -O3 -std=gnu17 stdint_sizes.c -o bin/a -lm && bin/a

# 2. In C++
g++ -Wall -Wextra -Werror -O3 -std=gnu++17 stdint_sizes.c -o bin/a && bin/a
```

References:
1. ***** https://en.cppreference.com/w/c/types/integer - fixed-width integer types
1. https://www.cs.yale.edu/homes/aspnes/pinewiki/C(2f)IntegerTypes.html
1. ***** https://www.ibm.com/docs/en/ibm-mq/7.5?topic=platforms-standard-data-types
1. [my answer] Integer and floating point rank and promotion rules in C and C++:
   https://stackoverflow.com/a/72654668/4561887

*/

#include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("----------------------\n"
           "Integer types:\n"
           "----------------------\n");
    printf("sizeof(bool)                = %zu\n", sizeof(bool));
    printf("sizeof(_Bool)               = %zu\n", sizeof(_Bool));
    printf("sizeof(char)                = %zu\n", sizeof(char));
    printf("sizeof(unsigned char)       = %zu\n", sizeof(unsigned char));
    printf("sizeof(short)               = %zu\n", sizeof(short));
    printf("sizeof(unsigned short)      = %zu\n", sizeof(unsigned short));
    printf("sizeof(int)                 = %zu\n", sizeof(int));
    printf("sizeof(unsigned int)        = %zu\n", sizeof(unsigned int));
    printf("sizeof(long)                = %zu\n", sizeof(long));
    printf("sizeof(unsigned long)       = %zu\n", sizeof(unsigned long));
    printf("sizeof(long long)           = %zu\n", sizeof(long long));
    printf("sizeof(unsigned long long)  = %zu\n", sizeof(unsigned long long));
    printf("\n\n");

    printf("----------------------\n"
           "Special integer types:\n"
           "----------------------\n");
    printf("sizeof(void *)              = %zu\n", sizeof(void *));
    printf("sizeof(size_t)              = %zu\n", sizeof(size_t));
    printf("\n\n");

    printf("----------------------\n"
           "Floating point types:\n"
           "----------------------\n");
    printf("sizeof(float)               = %zu\n", sizeof(float));
    printf("sizeof(double)              = %zu\n", sizeof(double));
    printf("sizeof(long double)         = %zu\n", sizeof(long double));
    printf("\n\n");


    return 0;
}

/*
SAMPLE OUTPUT:

In C:
- On my 64-bit Linux Ubuntu machine with the gcc compiler:

    eRCaGuy_hello_world/c$ gcc -Wall -Wextra -Werror -O3 -std=gnu17 stdint_sizes.c -o bin/a -lm && bin/a
    ----------------------
    Integer types:
    ----------------------
    sizeof(bool)                = 1
    sizeof(_Bool)               = 1
    sizeof(char)                = 1
    sizeof(unsigned char)       = 1
    sizeof(short)               = 2
    sizeof(unsigned short)      = 2
    sizeof(int)                 = 4
    sizeof(unsigned int)        = 4
    sizeof(long)                = 8
    sizeof(unsigned long)       = 8
    sizeof(long long)           = 8
    sizeof(unsigned long long)  = 8


    ----------------------
    Special integer types:
    ----------------------
    sizeof(void *)              = 8
    sizeof(size_t)              = 8


    ----------------------
    Floating point types:
    ----------------------
    sizeof(float)               = 4
    sizeof(double)              = 8
    sizeof(long double)         = 16



OR, in C++:

(exact same as in C)


*/
