/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

Demonstrate `millis()`, `micros()`, and `nanos()` calls.
STATUS: done!

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# 1. In C:
gcc -Wall -Wextra -Werror -O3 -std=c17 timinglib_timestamps_basic.c timinglib.c -o bin/a && bin/a

# 2. In C++
g++ -Wall -Wextra -Werror -O3 -std=c++17 timinglib_timestamps_basic.c timinglib.c -o bin/a && bin/a
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

    for (size_t i = 0; i < 20; i++)
    {
        printf("millis() = %lu ms;    micros() = %lu us;    nanos() = %lu ns\n",
            millis(), micros(), nanos());
    }

    return 0;
}

/*
SAMPLE OUTPUT:

In C:

    eRCaGuy_hello_world/c$ gcc -Wall -Wextra -Werror -O3 -std=c17 timinglib_timestamps_basic.c timinglib.c -o bin/a && bin/a
    Hello World.

    millis() = 1649039834814 ms;    micros() = 1649039834814543 us;    nanos() = 1649039834814543828 ns
    millis() = 1649039834814 ms;    micros() = 1649039834814546 us;    nanos() = 1649039834814546647 ns
    millis() = 1649039834814 ms;    micros() = 1649039834814547 us;    nanos() = 1649039834814547961 ns
    millis() = 1649039834814 ms;    micros() = 1649039834814549 us;    nanos() = 1649039834814549786 ns
    millis() = 1649039834814 ms;    micros() = 1649039834814550 us;    nanos() = 1649039834814550812 ns
    millis() = 1649039834814 ms;    micros() = 1649039834814552 us;    nanos() = 1649039834814552607 ns
    millis() = 1649039834814 ms;    micros() = 1649039834814554 us;    nanos() = 1649039834814554478 ns
    millis() = 1649039834814 ms;    micros() = 1649039834814556 us;    nanos() = 1649039834814556094 ns
    millis() = 1649039834814 ms;    micros() = 1649039834814558 us;    nanos() = 1649039834814558355 ns
    millis() = 1649039834814 ms;    micros() = 1649039834814560 us;    nanos() = 1649039834814560451 ns
    millis() = 1649039834814 ms;    micros() = 1649039834814562 us;    nanos() = 1649039834814562322 ns
    millis() = 1649039834814 ms;    micros() = 1649039834814564 us;    nanos() = 1649039834814563994 ns
    millis() = 1649039834814 ms;    micros() = 1649039834814565 us;    nanos() = 1649039834814565622 ns
    millis() = 1649039834814 ms;    micros() = 1649039834814567 us;    nanos() = 1649039834814567352 ns
    millis() = 1649039834814 ms;    micros() = 1649039834814569 us;    nanos() = 1649039834814569246 ns
    millis() = 1649039834814 ms;    micros() = 1649039834814571 us;    nanos() = 1649039834814571032 ns
    millis() = 1649039834814 ms;    micros() = 1649039834814572 us;    nanos() = 1649039834814572865 ns
    millis() = 1649039834814 ms;    micros() = 1649039834814574 us;    nanos() = 1649039834814574496 ns
    millis() = 1649039834814 ms;    micros() = 1649039834814577 us;    nanos() = 1649039834814577243 ns
    millis() = 1649039834814 ms;    micros() = 1649039834814579 us;    nanos() = 1649039834814579028 ns




OR, in C++:




*/
