///usr/bin/env ccache gcc -Wall -Wextra -Werror -O3 -std=gnu17 "$0" -o /tmp/a -lm && /tmp/a "$@"; exit
// For the line just above, see my answer here: https://stackoverflow.com/a/75491834/4561887

/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
12 Oct. 2023

Show to how interpret a byte array as a uint64_t in big-endian or little-endian
order.

STATUS: done and works!

keywords to easily grep or ripgrep in this repo for this program and what it teaches
KEYWORDS:

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# Why `-std=gnu17` vs `-std=c17`, and `-std=gnu++17` vs `-std=c++17`?
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# [run once ever] install ccache
sudo apt update && sudo apt install ccache

# 1. In C:
./byte_array_reinterpret_cast_to_uint64_t.c
# or:
gcc -Wall -Wextra -Werror -O3 -std=gnu17 byte_array_reinterpret_cast_to_uint64_t.c -o bin/a -lm && bin/a

# 2. In C++
g++ -Wall -Wextra -Werror -O3 -std=gnu++17 byte_array_reinterpret_cast_to_uint64_t.c -o bin/a && bin/a
```

References:
1. *****+ See my answer on this here:
1.

*/


#include <inttypes.h> // for `PRIu64`, etc.
#include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`

// From my answer here: https://stackoverflow.com/a/64056527/4561887
/// \brief          Swap all the bytes in an array to convert from little-endian
///                 byte order to big-endian byte order, or vice versa.
/// \note           Works for arrays of any size. Swaps the bytes **in place**
///                 in the array.
/// \param[in,out]  byte_array  The array in which to swap the bytes in-place.
/// \param[in]      len         The length (in bytes) of the array.
/// \return         None
void swap_bytes_in_array(uint8_t *byte_array, size_t len)
{
    size_t i_left = 0;         // index for left side of the array
    size_t i_right = len - 1;  // index for right side of the array
    while (i_left < i_right)
    {
        // swap left and right bytes
        uint8_t left_copy = byte_array[i_left];
        byte_array[i_left] = byte_array[i_right];
        byte_array[i_right] = left_copy;
        i_left++;
        i_right--;
    }
}

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    uint8_t byte[8];

    // assume the bytes are stored in big-endian order, for instance
    byte[0] = 0x15;
    byte[1] = 0x15;
    byte[2] = 0x17;
    byte[3] = 0x18;
    byte[4] = 0x19;
    byte[5] = 0x20;
    byte[6] = 0x21;
    byte[7] = 0x12;

    // swap the bytes around to little-endian order
    swap_bytes_in_array(byte, sizeof(byte));

    // Now reinterpret-cast the bytes as a uint64_t; ie: look at the bytes
    // through the lens of a uint64_t, as I like to call it.
    uint64_t *val = (uint64_t*)byte;

    // Print the uint64_t value
    printf("val (as uint64_t) = %" PRIu64 "\n", *val);        // as an unsigned integer
    printf("val (in hex)      = 0x%08" PRIX64 "\n\n", *val);  // in hex

    // now change the bytes in the array
    *val = 12345;

    // print the uint64_t value again
    printf("val (as uint64_t) = %" PRIu64 "\n", *val);        // as an unsigned integer
    printf("val (in hex)      = 0x%08" PRIX64 "\n\n", *val);  // in hex

    // and print out the bytes:
    for (size_t i = 0; i < sizeof(byte); i++)
    {
        printf("byte[%zu] = 0x%02X\n", i, byte[i]);
    }

    return 0;
}

/*
SAMPLE OUTPUT:

In C:

    eRCaGuy_hello_world$ c/byte_array_reinterpret_cast_to_uint64_t.c
    val (as uint64_t) = 1519145841575600402
    val (in hex)      = 0x1515171819202112

    val (as uint64_t) = 12345
    val (in hex)      = 0x00003039

    byte[0] = 0x39
    byte[1] = 0x30
    byte[2] = 0x00
    byte[3] = 0x00
    byte[4] = 0x00
    byte[5] = 0x00
    byte[6] = 0x00
    byte[7] = 0x00


OR, in C++:

    g++ -Wall -Wextra -Werror -O3 -std=gnu++17 byte_array_reinterpret_cast_to_uint64_t.c -o bin/a && bin/a
    (same results as in C)

*/
