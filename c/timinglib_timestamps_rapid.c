/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

Rapidly do `nanos()` calls and load the results into an array, and print it out to see how fast
the time samples could be taken.

STATUS: done

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# 1. In C:
gcc -Wall -Wextra -Werror -O3 -std=c17 timinglib_timestamps_rapid.c timinglib.c -o bin/a && bin/a

# 2. In C++
g++ -Wall -Wextra -Werror -O3 -std=c++17 timinglib_timestamps_rapid.c timinglib.c -o bin/a && bin/a
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

#define NUM_MEASUREMENTS 10000


// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Rapid timestamps.\n\n");

    static uint64_t nanos_array[NUM_MEASUREMENTS];
    for (size_t i = 0; i < ARRAY_LEN(nanos_array); i++)
    {
        nanos_array[i] = nanos();
    }

    // Now print out the time deltas
    uint64_t t_old_ns = nanos_array[0];
    uint64_t sum_ns = 0;
    uint64_t max_dt_ns = 0;
    uint64_t min_dt_ns = UINT64_MAX;
    for (size_t i = 0; i < ARRAY_LEN(nanos_array); i++)
    {
        uint64_t t_new_ns = nanos_array[i];
        uint64_t dt_ns = t_new_ns - t_old_ns;
        sum_ns += dt_ns;

        if (dt_ns > max_dt_ns)
        {
            max_dt_ns = dt_ns;
        }
        else if (dt_ns > 0 && dt_ns < min_dt_ns)
        {
            min_dt_ns = dt_ns;
        }


        t_old_ns = t_new_ns;

        printf("%3lu: %6lu ns\n", i, dt_ns);
    }

    printf("\n");
    double avg_dt_ns = (double)sum_ns/ARRAY_LEN(nanos_array);
    printf("average time required per `nanos()` call = %8.3f ns\n", avg_dt_ns);
    printf("minimum time > 0 for a `nanos()` call    = %4lu ns\n", min_dt_ns);
    printf("maximum time for a `nanos()` call        = %4lu ns\n", max_dt_ns);

    return 0;
}

/*
SAMPLE OUTPUT:

In C:

End of the output:

    9988:     18 ns
    9989:     19 ns
    9990:     19 ns
    9991:     19 ns
    9992:     18 ns
    9993:     19 ns
    9994:     18 ns
    9995:     19 ns
    9996:     19 ns
    9997:     18 ns
    9998:     19 ns
    9999:     19 ns

    average time required per `nanos()` call =   21.340 ns
    minimum time > 0 for a `nanos()` call    =   17 ns
    maximum time for a `nanos()` call        = 7286 ns



OR, in C++:




*/
