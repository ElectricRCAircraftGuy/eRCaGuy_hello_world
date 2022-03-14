/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
13 Mar. 2022

Demonstrate the basic `sin()` and arcsin (`asin()`) functions in C.

STATUS: done!

To compile and run (assuming you've already `cd`ed into this dir):
1. In C:
```bash
# BE SURE TO INCLUDE `-lm` in the cmd!
# - See: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world#-lm
gcc -Wall -Wextra -Werror -O3 -std=c17 math_sin_and_asin.c -o bin/a -lm && bin/a
```
2. In C++
```bash
g++ -Wall -Wextra -Werror -O3 -std=c++17 math_sin_and_asin.c -o bin/a && bin/a
```

References:
1. eRCaGuy_hello_world/c/utilities.h

*/


#include <math.h>    // `sin()` and `asin()`
#include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`

// Get the number of elements in any C array
// - Usage example: [my own answer]:
//   https://arduino.stackexchange.com/questions/80236/initializing-array-of-structs/80289#80289
#define ARRAY_LEN(array) (sizeof(array) / sizeof(array[0]))

// See: https://docs.microsoft.com/en-us/cpp/c-runtime-library/math-constants?view=msvc-170
#define PI 3.14159265358979323846

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("sin() and asin() demo.\n\n");

    const size_t NUM_SLICES = 8;
    double vals[NUM_SLICES];

    // Print the fractions of pi
    printf("Fract of PI:  ");
    for (size_t i = 0; i < ARRAY_LEN(vals); i++)
    {
        printf("%9.3f  ", ((double)2*i)/NUM_SLICES);
    }
    printf("\n");


    // Do sin() over 0 to 2*PI in NUM_SLICES slices.
    printf("sin:          ");
    for (size_t i = 0; i < ARRAY_LEN(vals); i++)
    {
        vals[i] = sin(2*PI*i/NUM_SLICES);
        printf("%9.3f  ", vals[i]);
    }
    printf("\n");


    // Do asin() over the results of those sin() values above
    printf("asin:         ");
    for (size_t i = 0; i < ARRAY_LEN(vals); i++)
    {
        vals[i] = asin(vals[i]);
        printf("%9.3f  ", vals[i]);
    }
    printf("radians\n");

    printf("asin (/PI):   ");
    for (size_t i = 0; i < ARRAY_LEN(vals); i++)
    {
        printf("%9.3f  ", vals[i]/PI);
    }
    printf("*PI radians\n");


    return 0;
}

/*
SAMPLE OUTPUT:

In C:

    eRCaGuy_hello_world/c$ gcc -Wall -Wextra -Werror -O3 -std=c17 math_sin_and_asin.c -o bin/a -lm && bin/a
    sin() and asin() demo.

    Fract of PI:      0.000      0.250      0.500      0.750      1.000      1.250      1.500      1.750
    sin:              0.000      0.707      1.000      0.707      0.000     -0.707     -1.000     -0.707
    asin:             0.000      0.785      1.571      0.785      0.000     -0.785     -1.571     -0.785  radians
    asin (/PI):       0.000      0.250      0.500      0.250      0.000     -0.250     -0.500     -0.250  *PI radians


OR, in C++:

    eRCaGuy_hello_world/c$ g++ -Wall -Wextra -Werror -O3 -std=c++17 math_sin_and_asin.c -o bin/a && bin/a
    sin() and asin() demo.

    Fract of PI:      0.000      0.250      0.500      0.750      1.000      1.250      1.500      1.750
    sin:              0.000      0.707      1.000      0.707      0.000     -0.707     -1.000     -0.707
    asin:             0.000      0.785      1.571      0.785      0.000     -0.785     -1.571     -0.785  radians
    asin (/PI):       0.000      0.250      0.500      0.250      0.000     -0.250     -0.500     -0.250  *PI radians


*/
