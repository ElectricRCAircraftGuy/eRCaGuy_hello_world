///usr/bin/env ccache gcc -Wall -Wextra -Werror -O3 -std=gnu17 "$0" -o /tmp/a -lm && /tmp/a "$@"; exit
// For the line just above, see my answer here: https://stackoverflow.com/a/75491834/4561887

/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
20 Mar. 2023

Print `size_t` types in a variety of ways, including cross-platform ways.
See my answer here: https://stackoverflow.com/a/55943527/4561887

STATUS: done and works!

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# Why `-std=gnu17` vs `-std=c17`, and `-std=gnu++17` vs `-std=c++17`?
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# [run once ever] install ccache
sudo apt update && sudo apt install ccache

# 1. In C:
./print_size_t.c
# or:
gcc -Wall -Wextra -Werror -O3 -std=gnu17 print_size_t.c -o bin/a -lm && bin/a

# 2. In C++
g++ -Wall -Wextra -Werror -O3 -std=gnu++17 print_size_t.c -o bin/a && bin/a
```

References:
1. My answer with this code!: https://stackoverflow.com/a/55943527/4561887
1. https://cplusplus.com/reference/cinttypes/
1. https://cplusplus.com/reference/cstdio/printf/

*/


#include <stdio.h>
#include <inttypes.h>

// Custom printf format strings for `size_t` variable types, which are nearly
// always the same size as pointers on any given architecture (though this is
// NOT enforced by the standard!)
//
// `size_t` is an unsigned decimal integer (ex: usually 8 bytes on a 64-bit
// system, 4 bytes on a 32-bit system, or 2 bytes on an 8-bit system) so you
// can simply print it as though it was a pointer!:
#define PRIuSZT PRIuPTR  // u = unsigned decimal integer
#define PRIxSZT PRIxPTR  // x = unsigned decimal integer in lower-case hex
#define PRIXSZT PRIXPTR  // X = unsigned decimal integer in upper-case hex
#define PRIoSZT PRIoPTR  // o = unsigned decimal integer in octal

// The above representations make the most sense. Other representations are
// below, though these will interpret the `size_t` type as though it was
// signed, which doesn't make much sense, since it's not:
#define PRIdSZT PRIdPTR  // d = signed decimal integer
#define PRIiSZT PRIiPTR  // i = signed decimal integer

// For `ssize_t` (signed size_t) types, however, the d and i specifiers *do*
// make sense, so you could do this:
#define PRIdSSZT PRIdPTR  // d = signed decimal integer
#define PRIiSSZT PRIiPTR  // i = signed decimal integer


int main()
{
    printf("Hello World\n");

    size_t my_variable = 123456789;
    printf("sizeof(my_variable) = %" PRIuSZT "\n", sizeof(my_variable));

    // -------------------------------------------------------------------------
    // Option 1 (best and most-robust answer for cross-platform usage):
    // `inttypes.h` hack using `PRIuPTR` type specifiers
    // -------------------------------------------------------------------------
    printf("\n===== Option 1 =====\n");

    // print the `size_t` type as an unsigned decimal integer
    printf("%" PRIuSZT "\n", my_variable);
    // print the `size_t` type as an unsigned decimal integer in lower-case hex
    printf("0x%" PRIxSZT "\n", my_variable);
    // print the `size_t` type as an unsigned decimal integer in upper-case hex
    printf("0X%" PRIXSZT "\n", my_variable);
    // print the `size_t` type as an unsigned decimal integer in octal
    printf("0%" PRIoSZT "\n", my_variable);

    // Print the hex values again, this time with leading zero-padding to print
    // a full 8-bytes (16 chars) worth of data
    printf("\n");
    printf("0x%016" PRIxSZT "\n", my_variable); // lower-case unsigned hex
    printf("0X%016" PRIXSZT "\n", my_variable); // upper-case unsigned hex

    // Print the octal value again, this time with leading zero-padding to print
    // a full 8-bytes (22 chars) worth of data
    printf("\n");
    printf("0%022" PRIoSZT "\n", my_variable);  // unsigned octal


    // -------------------------------------------------------------------------
    // Option 2: use `%zu` where it is supported
    // -------------------------------------------------------------------------
    printf("\n===== Option 2 =====\n");

    printf("%zu\n", my_variable);


    // -------------------------------------------------------------------------
    // Option 3 (virtually guaranteed to work since `uint64_t` is large enough
    // to hold all known `size_t` types on all existing architectures): use the
    // `inttypes.h` `PRIu64` specifier, with the addition of casting your
    // `size_t` variable to `uint64_t` before printing
    // -------------------------------------------------------------------------
    printf("\n===== Option 3 =====\n");

    // print the `size_t` type as an unsigned decimal integer
    printf("%" PRIu64 "\n", (uint64_t)my_variable);
    // print the `size_t` type as an unsigned decimal integer in lower-case hex
    printf("0x%" PRIx64 "\n", (uint64_t)my_variable);
    // print the `size_t` type as an unsigned decimal integer in upper-case hex
    printf("0X%" PRIX64 "\n", (uint64_t)my_variable);

    // etc etc. See the Option 1 examples and follow the same patterns.


    return 0;
}



/*
SAMPLE OUTPUT:

In C:

    eRCaGuy_hello_world/c$ gcc -Wall -Wextra -Werror -O3 -std=gnu17 print_size_t.c -o bin/a -lm && bin/a
    Hello World
    sizeof(my_variable) = 8

    ===== Option 1 =====
    123456789
    0x75bcd15
    0X75BCD15
    0726746425

    0x00000000075bcd15
    0X00000000075BCD15

    00000000000000726746425

    ===== Option 2 =====
    123456789

    ===== Option 3 =====
    123456789
    0x75bcd15
    0X75BCD15


OR, in C++:

    [exact same output as above]

*/
