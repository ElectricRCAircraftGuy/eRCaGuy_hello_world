/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

Test all of the timinglib "sleep" and "sleep until" functions. The "sleep until" functions are how
we get precise periodic loops, and are very similar to the `vTaskDelayUntil()` function in
FreeRTOS, here: https://www.freertos.org/vtaskdelayuntil.html.

STATUS: works!

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# 1. In C:
gcc -Wall -Wextra -Werror -O3 -std=c17 timinglib_sleep_and_sleep_until.c timinglib.c -o bin/a && time bin/a

# 2. In C++
g++ -Wall -Wextra -Werror -O3 -std=c++17 timinglib_sleep_and_sleep_until.c timinglib.c -o bin/a && time bin/a
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
    printf("timinglib sleep tests.\n\n");


    // ==========================================================
    printf("== `sleep_ms()` tests ==\n");
    // ==========================================================

    printf("sleeping 1 second\n");
    sleep_ms(MS_PER_SEC*1);

    printf("sleeping 2 seconds\n");
    sleep_ms(MS_PER_SEC*2);

    // ==========================================================
    printf("== `sleep_us()` tests ==\n");
    // ==========================================================

    printf("sleeping 1 second\n");
    sleep_us(US_PER_SEC*1);

    printf("sleeping 2 seconds\n");
    sleep_us(US_PER_SEC*2);

    // ==========================================================
    printf("== `sleep_ns()` tests ==\n");
    // ==========================================================

    printf("sleeping 1 second\n");
    sleep_ns(NS_PER_SEC*1);

    printf("sleeping 2 seconds\n");
    sleep_ns(NS_PER_SEC*2);



    printf("\n");
    // ==========================================================
    printf("== `sleep_until_ms()` tests ==\n");
    // ==========================================================

    printf("sleeping 1 second\n");
    uint64_t last_wake_time_ms = millis();
    sleep_until_ms(&last_wake_time_ms, MS_PER_SEC*1);

    printf("sleeping 2 seconds\n");
    sleep_until_ms(&last_wake_time_ms, MS_PER_SEC*2);

    // ==========================================================
    printf("== `sleep_until_us()` tests ==\n");
    // ==========================================================

    printf("sleeping 1 second\n");
    uint64_t last_wake_time_us = micros();
    sleep_until_us(&last_wake_time_us, US_PER_SEC*1);

    printf("sleeping 2 seconds\n");
    sleep_until_us(&last_wake_time_us, US_PER_SEC*2);

    // ==========================================================
    printf("== `sleep_until_ns()` tests ==\n");
    // ==========================================================

    printf("sleeping 1 second\n");
    uint64_t last_wake_time_ns = nanos();
    sleep_until_ns(&last_wake_time_ns, NS_PER_SEC*1);

    printf("sleeping 2 seconds\n");
    sleep_until_ns(&last_wake_time_ns, NS_PER_SEC*2);



    printf("\nTOTAL SLEEP TIME SHOULD BE 18 SECONDS! Compare it against the time "
           "printed below to ensure it is!\n");

    return 0;
}

/*
SAMPLE OUTPUT:

    In C:

    eRCaGuy_hello_world/c$ gcc -Wall -Wextra -Werror -O3 -std=c17 timinglib_sleep_and_sleep_until.c timinglib.c -o bin/a && time bin/a
    timinglib sleep tests.

    == `sleep_ms()` tests ==
    sleeping 1 second
    sleeping 2 seconds
    == `sleep_us()` tests ==
    sleeping 1 second
    sleeping 2 seconds
    == `sleep_ns()` tests ==
    sleeping 1 second
    sleeping 2 seconds

    == `sleep_until_ms()` tests ==
    sleeping 1 second
    sleeping 2 seconds
    == `sleep_until_us()` tests ==
    sleeping 1 second
    sleeping 2 seconds
    == `sleep_until_ns()` tests ==
    sleeping 1 second
    sleeping 2 seconds

    TOTAL SLEEP TIME SHOULD BE 18 SECONDS! Compare it against the time printed below to ensure it is!

    real    0m18.003s
    user    0m0.001s
    sys 0m0.000s




OR, in C++:

(Same as in C)


*/
