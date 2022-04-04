/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

Test the new get_resolution() function to estimate the resolution of timestamps.
STATUS: done!

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# 1. In C:
gcc -Wall -Wextra -Werror -O3 -std=c17 timinglib_get_resolution.c timinglib.c -o bin/a && time bin/a

# 2. In C++
g++ -Wall -Wextra -Werror -O3 -std=c++17 timinglib_get_resolution.c timinglib.c -o bin/a && time bin/a
```

References:
1.

*/

// Local includes
#include "timinglib.h"

// Linux includes

// C includes
#include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Hello World.\n\n");

    uint64_t estimated_resolution_ns = get_estimated_resolution();
    printf("estimated_resolution_ns = %lu ns\n", estimated_resolution_ns);

    uint64_t specified_resolution_ns = get_specified_resolution();
    printf("specified_resolution_ns = %lu ns\n", specified_resolution_ns);

    return 0;
}

/*
SAMPLE OUTPUT:

In both C and C++, typical resolutions for me are ~14~27 ns.

In C:

    eRCaGuy_hello_world/c$ g++ -Wall -Wextra -Werror -O3 -std=c++17 timinglib_get_resolution.c timinglib.c -o bin/a && time bin/a
    Hello World.

    estimated_resolution_ns = 15 ns
    specified_resolution_ns = 1 ns

    real    0m0.001s
    user    0m0.001s
    sys 0m0.000s



OR, in C++:

    eRCaGuy_hello_world/c$ g++ -Wall -Wextra -Werror -O3 -std=c++17 timinglib_get_resolution.c timinglib.c -o bin/a && time bin/a
    Hello World.

    estimated_resolution_ns = 15 ns
    specified_resolution_ns = 1 ns

    real    0m0.001s
    user    0m0.001s
    sys 0m0.000s



*/
