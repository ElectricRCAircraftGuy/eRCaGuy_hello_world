/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

See the .h file for details.

References:
1.

*/

// Local includes
#include "swap_bytes_lib.h"

// 3rd-party library includes
// NA

// Linux includes
// NA

// C and C++ includes
// NA

void swap_bytes(uint8_t * byte_array, size_t len)
{
    size_t i_left = 0;  // index for left side of the array
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

endianness_t endianness_get()
{
    endianness_t endianness = ENDIANNESS_UNKNOWN;
    const uint16_t NUM = 0x1234;
    uint8_t *bytes = (uint8_t *)&NUM;
    if (bytes[0] == 0x12 && bytes[1] == 0x34)
    {
        endianness = ENDIANNESS_BIG_ENDIAN;
    }
    else if (bytes[0] == 0x34 && bytes[1] == 0x12)
    {
        endianness = ENDIANNESS_LITTLE_ENDIAN;
    }

    return endianness;
}

const char * endianness_get_name(endianness_t endianness)
{
    const char * endianness_name = "TBD";

    switch (endianness)
    {
        case ENDIANNESS_UNKNOWN:
            endianness_name = "UNKNOWN";
            break;
        case ENDIANNESS_LITTLE_ENDIAN:
            endianness_name = "LITTLE_ENDIAN (least-significant byte first in memory)";
            break;
        case ENDIANNESS_BIG_ENDIAN:
            endianness_name = "BIG_ENDIAN (most-significant byte first in memory)";
            break;
    }

    return endianness_name;
}
