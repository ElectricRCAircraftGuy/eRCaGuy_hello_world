/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
22 Mar. 2022

This tutorial (https://learnxinyminutes.com/docs/c++/) says that in C a char is the sizeof an int,
but in C++ it is 1 byte. Let's check that! Check the size of all C and C++ types while we are at it!
Here is the quote from the link just above:

> // In C++, character literals are chars
> sizeof('c') == sizeof(char) == 1
>
> // In C, character literals are ints
> sizeof('c') == sizeof(int)

STATUS: done; it works!

To compile and run (assuming you've already `cd`ed into this dir):
1. In C:
```bash
gcc -Wall -Wextra -Werror -O3 -std=c17 sizeof_types.c -o bin/a -lm && bin/a
```
2. In C++
```bash
g++ -Wall -Wextra -Werror -O3 -std=c++17 sizeof_types.c -o bin/a && bin/a
```

References:
1. https://learnxinyminutes.com/docs/c++/

*/

#include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    // original C integer types                                                         // NB: these sizes are implementation and hardware-specific!
    //                                                                                  // Your compiler, hardware, or architecture may produce
    //                                                                                  // different results!
    //                                                                                  // -----------------------------
    printf("sizeof('c')                     = %zu\n", sizeof('c'));                     // 4 in C, but 1 in C++!
    printf("sizeof(char)                    = %zu\n", sizeof(char));                    // 1
    printf("sizeof(unsigned char)           = %zu\n", sizeof(unsigned char));           // 1
    printf("sizeof(short)                   = %zu\n", sizeof(short));                   // 2
    printf("sizeof(unsigned short)          = %zu\n", sizeof(unsigned short));          // 2
    printf("sizeof(int)                     = %zu\n", sizeof(int));                     // 4
    printf("sizeof(unsigned int)            = %zu\n", sizeof(unsigned int));            // 4
    printf("sizeof(long int)                = %zu\n", sizeof(long int));                // 8
    printf("sizeof(unsigned long int)       = %zu\n", sizeof(unsigned long int));       // 8
    printf("sizeof(long long int)           = %zu\n", sizeof(long long int));           // 8
    printf("sizeof(unsigned long long int)  = %zu\n", sizeof(unsigned long long int));  // 8
    printf("\n");

    // floating point types
    printf("sizeof(float)                   = %zu\n", sizeof(float));                   // 4
    printf("sizeof(double)                  = %zu\n", sizeof(double));                  // 8
    printf("sizeof(long double)             = %zu\n", sizeof(long double));             // 16
    // printf("sizeof(long long double)        = %zu\n", sizeof(long long double)); // does not exist
    printf("\n");

    // stdint types
    printf("sizeof(int8_t)                  = %zu\n", sizeof(int8_t));                  // 1
    printf("sizeof(uint8_t)                 = %zu\n", sizeof(uint8_t));                 // 1
    printf("sizeof(int16_t)                 = %zu\n", sizeof(int16_t));                 // 2
    printf("sizeof(uint16_t)                = %zu\n", sizeof(uint16_t));                // 2
    printf("sizeof(int32_t)                 = %zu\n", sizeof(int32_t));                 // 4
    printf("sizeof(uint32_t)                = %zu\n", sizeof(uint32_t));                // 4
    printf("sizeof(int64_t)                 = %zu\n", sizeof(int64_t));                 // 8
    printf("sizeof(uint64_t)                = %zu\n", sizeof(uint64_t));                // 8
    // printf("sizeof(int128_t)                = %zu\n", sizeof(int128_t));   // does not exist
    // printf("sizeof(uint128_t)               = %zu\n", sizeof(uint128_t));  // does not exist

    return 0;
}

/*
SAMPLE OUTPUT:

In C:

    eRCaGuy_hello_world/c$ gcc -Wall -Wextra -Werror -O3 -std=c17 sizeof_types.c -o bin/a -lm && bin/a
    sizeof('c')                     = 4
    sizeof(char)                    = 1
    sizeof(unsigned char)           = 1
    sizeof(short)                   = 2
    sizeof(unsigned short)          = 2
    sizeof(int)                     = 4
    sizeof(unsigned int)            = 4
    sizeof(long int)                = 8
    sizeof(unsigned long int)       = 8
    sizeof(long long int)           = 8
    sizeof(unsigned long long int)  = 8

    sizeof(float)                   = 4
    sizeof(double)                  = 8
    sizeof(long double)             = 16

    sizeof(int8_t)                  = 1
    sizeof(uint8_t)                 = 1
    sizeof(int16_t)                 = 2
    sizeof(uint16_t)                = 2
    sizeof(int32_t)                 = 4
    sizeof(uint32_t)                = 4
    sizeof(int64_t)                 = 8
    sizeof(uint64_t)                = 8


OR, in C++:

    eRCaGuy_hello_world/c$ g++ -Wall -Wextra -Werror -O3 -std=c++17 sizeof_types.c -o bin/a && bin/a
    sizeof('c')                     = 1
    sizeof(char)                    = 1
    sizeof(unsigned char)           = 1
    sizeof(short)                   = 2
    sizeof(unsigned short)          = 2
    sizeof(int)                     = 4
    sizeof(unsigned int)            = 4
    sizeof(long int)                = 8
    sizeof(unsigned long int)       = 8
    sizeof(long long int)           = 8
    sizeof(unsigned long long int)  = 8

    sizeof(float)                   = 4
    sizeof(double)                  = 8
    sizeof(long double)             = 16

    sizeof(int8_t)                  = 1
    sizeof(uint8_t)                 = 1
    sizeof(int16_t)                 = 2
    sizeof(uint16_t)                = 2
    sizeof(int32_t)                 = 4
    sizeof(uint32_t)                = 4
    sizeof(int64_t)                 = 8
    sizeof(uint64_t)                = 8

*/
