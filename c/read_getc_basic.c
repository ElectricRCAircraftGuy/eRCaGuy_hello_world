/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
3 Feb. 2022

Lean how to read in chars with getc().
What I learned: stdin is line-buffered, meaning it will block and wait for you to type a char if all
chars up to the newline caused by the Enter key have already been read.

STATUS: done

To compile and run (assuming you've already `cd`ed into this dir):
1. In C:
```bash
gcc -Wall -Wextra -Werror -O3 -std=c17 read_getc_basic.c -o bin/a && bin/a
```
2. In C++
```bash
g++ -Wall -Wextra -Werror -O3 -std=c++17 read_getc_basic.c -o bin/a && bin/a
```

References:
1. https://stackoverflow.com/questions/70975906/how-do-i-take-in-the-enter-key-as-an-input-in-c

*/

// #include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
// #include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Repeatedly type 1 or more chars, and press Enter. Repeat until the program exits.\n");

    printf("You typed decimal value %i\n", getc(stdin));
    printf("  feof(stdin) = %i\n", feof(stdin));
    printf("  ftell(stdin) = %li\n", ftell(stdin));

    printf("You typed decimal value %i\n", getc(stdin));
    printf("  feof(stdin) = %i\n", feof(stdin));
    printf("  ftell(stdin) = %li\n", ftell(stdin));

    printf("You typed decimal value %i\n", getc(stdin));
    printf("  feof(stdin) = %i\n", feof(stdin));
    printf("  ftell(stdin) = %li\n", ftell(stdin));

    printf("You typed decimal value %i\n", getc(stdin));
    printf("  feof(stdin) = %i\n", feof(stdin));
    printf("  ftell(stdin) = %li\n", ftell(stdin));

    printf("You typed decimal value %i\n", getc(stdin));
    printf("  feof(stdin) = %i\n", feof(stdin));
    printf("  ftell(stdin) = %li\n", ftell(stdin));

    printf("You typed decimal value %i\n", getc(stdin));
    printf("  feof(stdin) = %i\n", feof(stdin));
    printf("  ftell(stdin) = %li\n", ftell(stdin));

    return 0;
}

/*
SAMPLE OUTPUT:

In C:

    eRCaGuy_hello_world/c$ gcc -Wall -Wextra -Werror -O3 -std=c17 read_getc_basic.c -o bin/a && bin/a
    Repeatedly type 1 or more chars, and press Enter. Repeat until the program exits.
    e
    You typed decimal value 101
      feof(stdin) = 0
      ftell(stdin) = -1
    You typed decimal value 10
      feof(stdin) = 0
      ftell(stdin) = -1

    You typed decimal value 10
      feof(stdin) = 0
      ftell(stdin) = -1
    abcd
    You typed decimal value 97
      feof(stdin) = 0
      ftell(stdin) = -1
    You typed decimal value 98
      feof(stdin) = 0
      ftell(stdin) = -1
    You typed decimal value 99
      feof(stdin) = 0
      ftell(stdin) = -1



OR, in C++:



*/
