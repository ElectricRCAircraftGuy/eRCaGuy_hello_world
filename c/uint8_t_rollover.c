///usr/bin/env ccache gcc -Wall -Wextra -Werror -O3 -std=gnu17 "$0" -o /tmp/a -lm && /tmp/a "$@"; exit
// For the line just above, see my answer here: https://stackoverflow.com/a/75491834/4561887

/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
Feb. 2024

Show that uint8_t has well-defined-behavior rollover. 
STATUS: Done and works!

keywords to easily grep or ripgrep in this repo for this program and what it teaches
KEYWORDS:

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# Why `-std=gnu17` vs `-std=c17`, and `-std=gnu++17` vs `-std=c++17`?
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# [run once ever] install ccache
sudo apt update && sudo apt install ccache

# 1. In C:
./uint8_t_rollover.c
# or:
gcc -Wall -Wextra -Werror -O3 -std=gnu17 uint8_t_rollover.c -o bin/a -lm && bin/a

# 2. In C++
g++ -Wall -Wextra -Werror -O3 -std=gnu++17 uint8_t_rollover.c -o bin/a && bin/a
```

References:
1. 
1.

*/


#include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Test uint8_t rollover.\n");

    uint8_t i1 = 200;
    uint8_t i2 = i1*2;  // 400, but rolls over to 144
    printf("i1 = %d\n", i1); // 200
    printf("i2 = %d\n", i2); // 144

    return 0;
}


/*
SAMPLE OUTPUT:

In C:

    eRCaGuy_hello_world$ c/uint8_t_rollover.c 
    Test uint8_t rollover.
    i1 = 200
    i2 = 144


OR, in C++:

    eRCaGuy_hello_world/c$ g++ -Wall -Wextra -Werror -O3 -std=gnu++17 uint8_t_rollover.c -o bin/a && bin/a

    [same as above]

*/
