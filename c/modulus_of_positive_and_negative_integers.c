/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
Sept. 2022

Practice taking the modulus of positive and negative numbers, to ensure, for instance, that
`-5 % 180` is 175, as my calculator and google show, *not* `-5`. This is a bit odd, for instance,
but kind of makes sense when you consider the modulus operator to be a sort of "wrap-around"
operator, not just a "remainder" operator.
Here is the google answer: do a search for "-5 mod 180" and it shows "175".

STATUS: wip

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# Why `-std=gnu17` vs `-std=c17`, and `-std=gnu++17` vs `-std=c++17`?
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# 1. In C:
gcc -Wall -Wextra -Werror -O3 -std=gnu17 modulus_of_positive_and_negative_integers.c -o bin/a -lm && bin/a

# 2. In C++
g++ -Wall -Wextra -Werror -O3 -std=gnu++17 modulus_of_positive_and_negative_integers.c -o bin/a && bin/a
```

References:
1.

*/

#include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`

/// A function to perform and return the mathematical modulus as returned by
/// programming calculators and Google. In other words, it will **always**
/// return a positive value, unlike the `%` remainder operator in C!
int mathematical_modulo(int num1, int num2)
{
    int mod = (num1 % num2) + num2;
    return mod;
}

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("C and C++ remainder and modulo practice.\n\n");

    int mod;

    for (int i = -360; i <= 360; i++)
    {
        mod = i % 180;
        printf("%4i %% 180 = %4i\n", i, mod);
    }
    printf("\n");

    mod = -5 % 180;
    printf("%i\n", mod);
    printf("-5 %% 180 = %i\n", -5 % 180);
    printf("\n");


    return 0;
}


/*
SAMPLE OUTPUT:

In C:

    eRCaGuy_hello_world/c$ gcc -Wall -Wextra -Werror -O3 -std=c17 modulus_of_positive_and_negative_integers.c -o bin/a -lm && bin/a
    Hello World.


OR, in C++:

    eRCaGuy_hello_world/c$ g++ -Wall -Wextra -Werror -O3 -std=c++17 modulus_of_positive_and_negative_integers.c -o bin/a && bin/a
    Hello World.


*/
