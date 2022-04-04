/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

Try to sleep the SMALLEST time interval possible, and see how it does! How long does it actually sleep?

Do a general `nanosleep()` and `clock_nanosleep()` demo on Linux!

STATUS: wip

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# 1. In C:
gcc -Wall -Wextra -Werror -O3 -std=c17 sleep_nanosleep.c -o bin/a -lm && time bin/a

# 2. In C++
g++ -Wall -Wextra -Werror -O3 -std=c++17 sleep_nanosleep.c -o bin/a && time bin/a
```

References:
1. *****[MY ANSWER] sleep in nanoseconds - https://stackoverflow.com/a/55860234/4561887
1. [MY ANSWER] Get a timestamp in C in microseconds? - https://stackoverflow.com/a/67731965/4561887
1. *****https://man7.org/linux/man-pages/man2/clock_nanosleep.2.html

*/

// This line **must** come **before** including <time.h> in order to bring in
// the POSIX functions such as `clock_gettime()`, `nanosleep()`, etc., from
// `<time.h>`!
#define _POSIX_C_SOURCE 199309L

// Local includes

// Linux includes

// C includes
#include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`
#include <time.h>


// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Practice sleeping!\n\n");

    // 1 second
    struct timespec ts_requested =
    {
        .tv_sec = 1,
        .tv_nsec = 0,
    };

    printf("Sleeping 1 second using `nanosleep()`.\n");
    // See: https://man7.org/linux/man-pages/man2/nanosleep.2.html
    nanosleep(&ts_requested, NULL);

    // See: https://man7.org/linux/man-pages/man2/clock_nanosleep.2.html
    // clock_nanosleep(CLOCK_MONOTONIC_RAW)


    return 0;
}

/*
SAMPLE OUTPUT:

In C:

    eRCaGuy_hello_world/c$ gcc -Wall -Wextra -Werror -O3 -std=c17 sleep_nanosleep.c -o bin/a -lm && bin/a
    Hello World.


OR, in C++:

    eRCaGuy_hello_world/c$ g++ -Wall -Wextra -Werror -O3 -std=c++17 sleep_nanosleep.c -o bin/a && bin/a
    Hello World.


*/
