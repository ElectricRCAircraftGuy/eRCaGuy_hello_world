/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
Sept. 2022

Practice taking the modulus of positive and negative numbers, to ensure, for instance, that
`-5 % 180` is 175, as my calculator and google show, *not* `-5`. This is a bit odd, for instance,
but kind of makes sense when you consider the modulus operator to be a sort of "wrap-around"
operator, not just a "remainder" operator.
Here is the google answer: do a search for "-5 mod 180" and it shows "175".

STATUS: done and works!

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
1. JavaScript % (modulo) gives a negative result for negative numbers:
   https://stackoverflow.com/q/4467539/4561887
1. ***** How does java do modulus calculations with negative numbers?:
   [great answer!] https://stackoverflow.com/a/4403570/4561887
    1. *****+ [MY OWN ANSWER WITH THIS CODE, FOR C AND C++]
       https://stackoverflow.com/a/73782011/4561887

*/

#include <assert.h>
#include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`

/// A function to perform and return the mathematical modulus as returned by
/// programming calculators and Google. In other words, it will **always**
/// return a positive value, unlike the `%` remainder operator in C!
/// Example:
/// So, `-5 % 180` in C or C++ is `-5`, but `mathematical_modulo(-5, 180)`
/// is the same as "-5 mod 180" in a calculator or on Google, and is `175`.
int mathematical_modulo(int num1, int num2)
{
    int mod = num1 % num2;
    if (mod < 0)
    {
        mod += num2;
    }

    return mod;
}

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("C and C++ remainder and modulo practice.\n\n");

    int mod;

    printf("========== C %% operator ==========\n");
    for (int i = -360; i <= 360; i += 10)
    {
        mod = i % 180;
        printf("%4i %% 180 = %4i\n", i, mod);
    }
    printf("\n");

    printf("==== mathematical_modulo() func ====\n");
    for (int i = -360; i <= 360; i += 10)
    {
        mod = mathematical_modulo(i, 180);
        printf("mathematical_modulo(%4i, 180) = %4i\n", i, mod);
    }
    printf("\n");

    // Do a few manual quick tests to print at the end

    printf("-10 %% 180 = %4i\n", -10 % 180);
    printf("  0 %% 180 = %4i\n",   0 % 180);
    printf(" 10 %% 180 = %4i\n",  10 % 180);
    printf("\n");

    printf("mathematical_modulo(-10, 180) = %4i\n",
            mathematical_modulo(-10, 180));
    printf("mathematical_modulo(  0, 180) = %4i\n",
            mathematical_modulo(  0, 180));
    printf("mathematical_modulo( 10, 180) = %4i\n",
            mathematical_modulo( 10, 180));
    printf("\n");

    // Do a few unit tests to ensure we don't break the `mathematical_modulo()`
    // func later.
    assert(mathematical_modulo(-180, 180) ==   0);
    assert(mathematical_modulo( -10, 180) == 170);
    assert(mathematical_modulo(   0, 180) ==   0);
    assert(mathematical_modulo(  10, 180) ==  10);
    assert(mathematical_modulo( 180, 180) ==   0);
    printf("Unit tests completed successfully.\n");


    return 0;
}


/*
SAMPLE OUTPUT:

In C:

    eRCaGuy_hello_world/c$ gcc -Wall -Wextra -Werror -O3 -std=gnu17 modulus_of_positive_and_negative_integers.c -o bin/a -lm && bin/a
    C and C++ remainder and modulo practice.

    ========== C % operator ==========
    -360 % 180 =    0
    -350 % 180 = -170
    -340 % 180 = -160
    -330 % 180 = -150
    -320 % 180 = -140
    -310 % 180 = -130
    -300 % 180 = -120
    -290 % 180 = -110
    -280 % 180 = -100
    -270 % 180 =  -90
    -260 % 180 =  -80
    -250 % 180 =  -70
    -240 % 180 =  -60
    -230 % 180 =  -50
    -220 % 180 =  -40
    -210 % 180 =  -30
    -200 % 180 =  -20
    -190 % 180 =  -10
    -180 % 180 =    0
    -170 % 180 = -170
    -160 % 180 = -160
    -150 % 180 = -150
    -140 % 180 = -140
    -130 % 180 = -130
    -120 % 180 = -120
    -110 % 180 = -110
    -100 % 180 = -100
     -90 % 180 =  -90
     -80 % 180 =  -80
     -70 % 180 =  -70
     -60 % 180 =  -60
     -50 % 180 =  -50
     -40 % 180 =  -40
     -30 % 180 =  -30
     -20 % 180 =  -20
     -10 % 180 =  -10
       0 % 180 =    0
      10 % 180 =   10
      20 % 180 =   20
      30 % 180 =   30
      40 % 180 =   40
      50 % 180 =   50
      60 % 180 =   60
      70 % 180 =   70
      80 % 180 =   80
      90 % 180 =   90
     100 % 180 =  100
     110 % 180 =  110
     120 % 180 =  120
     130 % 180 =  130
     140 % 180 =  140
     150 % 180 =  150
     160 % 180 =  160
     170 % 180 =  170
     180 % 180 =    0
     190 % 180 =   10
     200 % 180 =   20
     210 % 180 =   30
     220 % 180 =   40
     230 % 180 =   50
     240 % 180 =   60
     250 % 180 =   70
     260 % 180 =   80
     270 % 180 =   90
     280 % 180 =  100
     290 % 180 =  110
     300 % 180 =  120
     310 % 180 =  130
     320 % 180 =  140
     330 % 180 =  150
     340 % 180 =  160
     350 % 180 =  170
     360 % 180 =    0

    ==== mathematical_modulo() func ====
    mathematical_modulo(-360, 180) =    0
    mathematical_modulo(-350, 180) =   10
    mathematical_modulo(-340, 180) =   20
    mathematical_modulo(-330, 180) =   30
    mathematical_modulo(-320, 180) =   40
    mathematical_modulo(-310, 180) =   50
    mathematical_modulo(-300, 180) =   60
    mathematical_modulo(-290, 180) =   70
    mathematical_modulo(-280, 180) =   80
    mathematical_modulo(-270, 180) =   90
    mathematical_modulo(-260, 180) =  100
    mathematical_modulo(-250, 180) =  110
    mathematical_modulo(-240, 180) =  120
    mathematical_modulo(-230, 180) =  130
    mathematical_modulo(-220, 180) =  140
    mathematical_modulo(-210, 180) =  150
    mathematical_modulo(-200, 180) =  160
    mathematical_modulo(-190, 180) =  170
    mathematical_modulo(-180, 180) =    0
    mathematical_modulo(-170, 180) =   10
    mathematical_modulo(-160, 180) =   20
    mathematical_modulo(-150, 180) =   30
    mathematical_modulo(-140, 180) =   40
    mathematical_modulo(-130, 180) =   50
    mathematical_modulo(-120, 180) =   60
    mathematical_modulo(-110, 180) =   70
    mathematical_modulo(-100, 180) =   80
    mathematical_modulo( -90, 180) =   90
    mathematical_modulo( -80, 180) =  100
    mathematical_modulo( -70, 180) =  110
    mathematical_modulo( -60, 180) =  120
    mathematical_modulo( -50, 180) =  130
    mathematical_modulo( -40, 180) =  140
    mathematical_modulo( -30, 180) =  150
    mathematical_modulo( -20, 180) =  160
    mathematical_modulo( -10, 180) =  170
    mathematical_modulo(   0, 180) =    0
    mathematical_modulo(  10, 180) =   10
    mathematical_modulo(  20, 180) =   20
    mathematical_modulo(  30, 180) =   30
    mathematical_modulo(  40, 180) =   40
    mathematical_modulo(  50, 180) =   50
    mathematical_modulo(  60, 180) =   60
    mathematical_modulo(  70, 180) =   70
    mathematical_modulo(  80, 180) =   80
    mathematical_modulo(  90, 180) =   90
    mathematical_modulo( 100, 180) =  100
    mathematical_modulo( 110, 180) =  110
    mathematical_modulo( 120, 180) =  120
    mathematical_modulo( 130, 180) =  130
    mathematical_modulo( 140, 180) =  140
    mathematical_modulo( 150, 180) =  150
    mathematical_modulo( 160, 180) =  160
    mathematical_modulo( 170, 180) =  170
    mathematical_modulo( 180, 180) =    0
    mathematical_modulo( 190, 180) =   10
    mathematical_modulo( 200, 180) =   20
    mathematical_modulo( 210, 180) =   30
    mathematical_modulo( 220, 180) =   40
    mathematical_modulo( 230, 180) =   50
    mathematical_modulo( 240, 180) =   60
    mathematical_modulo( 250, 180) =   70
    mathematical_modulo( 260, 180) =   80
    mathematical_modulo( 270, 180) =   90
    mathematical_modulo( 280, 180) =  100
    mathematical_modulo( 290, 180) =  110
    mathematical_modulo( 300, 180) =  120
    mathematical_modulo( 310, 180) =  130
    mathematical_modulo( 320, 180) =  140
    mathematical_modulo( 330, 180) =  150
    mathematical_modulo( 340, 180) =  160
    mathematical_modulo( 350, 180) =  170
    mathematical_modulo( 360, 180) =    0

    -10 % 180 =  -10
      0 % 180 =    0
     10 % 180 =   10

    mathematical_modulo(-10, 180) =  170
    mathematical_modulo(  0, 180) =    0
    mathematical_modulo( 10, 180) =   10

    Unit tests completed successfully.



OR, in C++:
[same output as in C]


*/
