/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
6 Mar. 2022

Calculate `e`, AKA: Euler's number! This is a "magic" number used in finance to
calculate compounding interest. e is approximately equal to 2.71828

STATUS: wip: I need to follow through with my TODO/design notes below still, but it does indeed
calculate e!


TODO/Design notes:

Calculate e for many cases by using an increasingly large value for n. Use
`snprintf()` to convert the number to a string, and compare it to the 10,000
char long string. Print it with the matching numbers in green, and the
non-matching numbers in red (using ANSI color codes). Count how many correct
digits I got. Increase n repeatedly and repeat the process, printing out a new
line each time the number of correct digits changes. Go until the number of
correct digits stops increasing, then go beyond that a bit too. I predict that
as n increases, the number of correct digits will too, until you reach a point
where numerical error takes over and starts decreasing the number of correct
digits as you further increase n.

- for a quick understanding of whether `long double` is helping us at all, start
  by printing out `sizeof(float)`, `sizeof(double)` and `sizeof(long double)`
  at the start of the program.

- try it with float type, then double, then long double to see how that affects the result.

- plot the results when done; consider using `gnuplot` (ex: `sudo apt install
  gnuplot-qt`), python with matplotlib or whatever, or PlotJuggler
  (https://github.com/facontidavide/PlotJuggler).

- Equation: e = the limit of `1*(1+1/n)^n` as n --> infinity
  - see the "History" and "Compound interest" sections of the Wikipedia article below!


To compile and run (assuming you've already `cd`ed into this dir):
1. In C:
```bash
gcc -Wall -Wextra -Werror -O3 -std=c17 calculate_e__eulers_number.c -o bin/a -lm && bin/a
```
2. In C++
```bash
g++ -Wall -Wextra -Werror -O3 -std=c++17 calculate_e__eulers_number.c -o bin/a && bin/a
```

References:
1. `long double`: https://en.cppreference.com/w/cpp/language/types
1. Euler's number to 10,000 digits: https://www.math.utah.edu/~pa/math/e.html
1. *****+Euler's number (Wikipedia): https://en.wikipedia.org/wiki/E_(mathematical_constant)
    1. See and read especially the "Compound interest" section:
       https://en.wikipedia.org/wiki/E_(mathematical_constant)#Compound_interest
1. https://en.cppreference.com/w/c/numeric/math
1. *****My answer on ANSI color codes: https://stackoverflow.com/a/71305350/4561887



*/

#include <math.h>
#include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`

// Get the number of elements in any C array
// - Usage example: [my own answer]:
//   https://arduino.stackexchange.com/questions/80236/initializing-array-of-structs/80289#80289
#define ARRAY_LEN(array) (sizeof(array) / sizeof(array[0]))


// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Calculating Euler's Number, e.\n\n");

    // See: https://www.math.utah.edu/~pa/math/e.html
    printf("Actual value of e:   2.718281828459045235360287471352662497757247093\n\n");

    // Super quick test
    double n_array[] =
    {
        1,
        10,
        100,
        1000,  // 1K
        10000,
        100000,
        1000000, // 1M
        10000000,
        100000000, // best (most accurate) result so far!: 2.7182817983473577
        1000000000, // 1B -- we may be hitting numerical rounding error as soon as here for
                    //       type `double`! I need to do some testing and experimenting.
        10000000000,
        100000000000,
    };

    for (size_t i = 0; i < ARRAY_LEN(n_array); i++)
    {
        double n = n_array[i];
        double e = pow(1*(1 + 1/n), n);
        printf("%19.0f: %.16f\n", n, e);
    }

    return 0;
}

/*
SAMPLE OUTPUT:

In C:

    eRCaGuy_hello_world/c$ gcc -Wall -Wextra -Werror -O3 -std=c17 calculate_e__eulers_number.c -o bin/a -lm && bin/a
    Calculating Euler's Number, e.

    Actual value of e:   2.718281828459045235360287471352662497757247093

                      1: 2.0000000000000000
                     10: 2.5937424601000023
                    100: 2.7048138294215285
                   1000: 2.7169239322355936
                  10000: 2.7181459268249255
                 100000: 2.7182682371922975
                1000000: 2.7182804690957534
               10000000: 2.7182816941320818
              100000000: 2.7182817983473577
             1000000000: 2.7182820520115603
            10000000000: 2.7182820532347876
           100000000000: 2.7182820533571102



OR, in C++:




*/
