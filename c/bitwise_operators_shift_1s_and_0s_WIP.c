/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
16 Oct. 2022

This person is left shifting 0s, as in `0 << some_number`, and I'm pretty sure
those are no-ops. I just want to check.
See: https://stackoverflow.com/q/74042828/4561887:
```c
TCA0.SINGLE.CTRLB = 0 << TCA_SINGLE_ALUPD_bp         // Auto Lock Update: disabled
                    | 1 << TCA_SINGLE_CMP0EN_bp      // Setting: enabled
                    | 1 << TCA_SINGLE_CMP1EN_bp      // Setting: enabled
                    | 0 << TCA_SINGLE_CMP2EN_bp      // Setting: disabled
                    | TCA_SINGLE_WGMODE_DSBOTTOM_gc; //
```
NB: IF YOU ARE LOOKING FOR HOW TO DO BIT-WISE OPERATIONS SUCH AS bitSet()
and bitClear(), see here instead: "eRCaGuy_hello_world/c/utilities.h". Look
for `bitRead`, `bitSet`, `bitClear`, `bitWrite`, etc.

STATUS: wip

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# Why `-std=gnu17` vs `-std=c17`, and `-std=gnu++17` vs `-std=c++17`?
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# 1. In C:
gcc -Wall -Wextra -Werror -O3 -std=gnu17 bitwise_operators_shift_1s_and_0s.c -o bin/a -lm && bin/a

# 2. In C++
g++ -Wall -Wextra -Werror -O3 -std=gnu++17 bitwise_operators_shift_1s_and_0s.c -o bin/a && bin/a
```

References:
1. NB: IF YOU ARE LOOKING FOR HOW TO DO BIT-WISE OPERATIONS SUCH AS bitSet()
and bitClear(), see here instead: "eRCaGuy_hello_world/c/utilities.h". Look
for `bitRead`, `bitSet`, `bitClear`, `bitWrite`, etc.
1. The question I'm looking at: https://stackoverflow.com/q/74042828/4561887
1.

*/


#define DO_NOT_INCLUDE_MAIN_FUNCS
// #include <print_binary_lib.h> /////// make this library!

#include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`

// TODO: move to print_binary_lib.h. Add gtest unit tests for it too! Make note
// that my binary print lib is intended to work well on ANY system, from 8-bit
// ATMega328 microcontrollers, to 64-bit power-house development machines.

/// A binary print function to print all bits in any data-type up to 64-bits
/// in size, in C (in C++ I could also use a template if I was okay with code
/// bloat in program size).
void print_binary()
{

}

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Demo to bit shift some zeros and stuff.\n\n");

    // this is NOT good code; this is just test code to see what happens
    // if I do these things

    uint32_t var1;

    var1 = 0xFF;
    printf("%u\n", var1);

    var1 |= 0 << 2; // does nothing
    printf("%u\n", var1);

    // var1 = 1 <<  ///////////// wip

    return 0;
}

/*
SAMPLE OUTPUT:

In C:

    eRCaGuy_hello_world/c$ gcc -Wall -Wextra -Werror -O3 -std=c17 bitwise_operators_shift_1s_and_0s.c -o bin/a -lm && bin/a
    Hello World.


OR, in C++:

    eRCaGuy_hello_world/c$ g++ -Wall -Wextra -Werror -O3 -std=c++17 bitwise_operators_shift_1s_and_0s.c -o bin/a && bin/a
    Hello World.


*/
