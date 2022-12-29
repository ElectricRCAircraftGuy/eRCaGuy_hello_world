/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
Fall 2022

Print numbers in binary. Ex: uint8_t 129 would print as "10000001", etc.

vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
UPDATE 29 DEC 2022:
This (https://stackoverflow.com/a/3974138/4561887) is the best answer and is pretty much what I
would have come up with myself. So, just tweak it to fix it up a bit and give it good variable
names and refactor it a bit. Ex: `i` should be `i_byte` or `byte_index` and `j` should be `i_bit`
or `bit_index`, and `b` should be `byte_array`, and get rid of the unnecessary `const`s, etc. Maybe
also pretty-format it to print in groups of 8 bits, and add sample output and a link to onlinegdb
to run it, to the answer.
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Allow it to handle printing numbers of **any** type in binary! See references below to get started.
==> Note: just write your own function from scratch to do this! No sense in doing any
magical "hacks". Just write a regular C function that takes any input type and size, casts to a
pointer to a byte, iterates over the bytes one-at-a-time, and prints bytes in binary. This should
be pretty straight-forward. You can always look at other peoples' solutions and the Arduino
`Serial.print(x, BIN)` function, and optimize what I come up with, *after* I first
get *something* working!

STATUS: wip/todo

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# Why `-std=gnu17` vs `-std=c17`, and `-std=gnu++17` vs `-std=c++17`?
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# 1. In C:
gcc -Wall -Wextra -Werror -O3 -std=gnu17 hello_world_extra_basic.c -o bin/a -lm && bin/a

# 2. In C++
g++ -Wall -Wextra -Werror -O3 -std=gnu++17 hello_world_extra_basic.c -o bin/a && bin/a
```

References:
1. Google search for "print binary":
   https://www.google.com/search?q=print+binary&oq=print+binary&aqs=chrome..69i57j69i65l3.3118j0j7&sourceid=chrome&ie=UTF-8
1. https://stackoverflow.com/questions/111928/is-there-a-printf-converter-to-print-in-binary-format
    1. *****+ https://stackoverflow.com/a/3974138/4561887
1. https://www.arduino.cc/reference/en/language/functions/communication/serial/print/
1. Google search for "arduino print binary":
   https://www.google.com/search?q=arduino+print+binary&oq=arduino+print+binary&aqs=chrome.0.69i59j69i64l2.2293j0j7&sourceid=chrome&ie=UTF-8

*/

#include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Hello World.\n\n");

    return 0;
}

/*
SAMPLE OUTPUT:

In C:

    eRCaGuy_hello_world/c$ gcc -Wall -Wextra -Werror -O3 -std=c17 hello_world_extra_basic.c -o bin/a -lm && bin/a
    Hello World.


OR, in C++:

    eRCaGuy_hello_world/c$ g++ -Wall -Wextra -Werror -O3 -std=c++17 hello_world_extra_basic.c -o bin/a && bin/a
    Hello World.


*/
