/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
13 Mar. 2022

Reproduce the issue where `sin()` is an "undefined reference", so I can ask about it on Stack
Overflow to figure out what's going on. Here is my full build command and error output:
    eRCaGuy_hello_world/c$ gcc -Wall -Wextra -Werror -O3 -std=c17 math_sin_is_undefined.c -o bin/a && bin/a
    /tmp/ccl97wgv.o: In function `main':
    math_sin_is_undefined.c:(.text.startup+0x4a): undefined reference to `sin'
    collect2: error: ld returned 1 exit status
UPDATE: it turns out that this question and answer already exists on Stack Overflow. See the
solution in the References below. Just add `-lm` to the end of the build command to link to the
math library.

STATUS: done

To compile and run (assuming you've already `cd`ed into this dir):
1. In C:
```bash
# FAILS:
gcc -Wall -Wextra -Werror -O3 -std=c17 math_sin_is_undefined.c -o bin/a && bin/a
# PASSES (notice that `-lm` was added to the end!):
gcc -Wall -Wextra -Werror -O3 -std=c17 math_sin_is_undefined.c -o bin/a -lm && bin/a
```
2. In C++
```bash
g++ -Wall -Wextra -Werror -O3 -std=c++17 math_sin_is_undefined.c -o bin/a && bin/a
```

References:
1. Stack overflow search for "undefined reference to `sin'":
   https://stackoverflow.com/search?q=undefined+reference+to+%60sin%27
    1. *****+ [SOLUTION!!] Undefined reference to `sin` [duplicate]:
       https://stackoverflow.com/a/12165016/4561887


*/

#include <math.h>    // `sin()` and `asin()`
#include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`

// See: https://docs.microsoft.com/en-us/cpp/c-runtime-library/math-constants?view=msvc-170
#define PI 3.14159265358979323846

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("sin() and asin() demo.\n\n");

    const size_t NUM_SLICES = 8;
    double vals[NUM_SLICES];

    // Do sin() over 0 to 2*PI in NUM_SLICES slices.
    for (size_t i = 0; i < NUM_SLICES; i++)
    {
        vals[i] = sin(2*PI*i/NUM_SLICES);
        printf("%3.3f  ", vals[i]);
    }
    printf("\n");


    return 0;
}

/*
SAMPLE OUTPUT:

In C:

- FAILS (missing `-lm`):

    eRCaGuy_hello_world/c$ gcc -Wall -Wextra -Werror -O3 -std=c17 math_sin_is_undefined.c -o bin/a && bin/a
    /tmp/ccege9gc.o: In function `main':
    math_sin_is_undefined.c:(.text.startup+0x4a): undefined reference to `sin'
    collect2: error: ld returned 1 exit status

- PASSES (has `-lm` at the end in order to link against the math library):

    eRCaGuy_hello_world/c$ gcc -Wall -Wextra -Werror -O3 -std=c17 math_sin_is_undefined.c -o bin/a -lm && bin/a
    sin() and asin() demo.

    0.000  0.707  1.000  0.707  0.000  -0.707  -1.000  -0.707


OR, in C++:

    eRCaGuy_hello_world/c$ g++ -Wall -Wextra -Werror -O3 -std=c++17 math_sin_is_undefined.c -o bin/a && bin/a
    sin() and asin() demo.

    0.000  0.707  1.000  0.707  0.000  -0.707  -1.000  -0.707


*/
