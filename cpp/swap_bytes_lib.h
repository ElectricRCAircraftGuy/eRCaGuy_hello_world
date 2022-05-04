/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
2020~2022

This is a basic endianness and byte swap library to allow you to easily check endianness of your
system and swap bytes from little-endian to big-endian (network) byte order, or vice versa.

STATUS: done and works!

To compile and run (assuming you've already `cd`ed into this dir):
See "swap_bytes_lib_unittest.cpp" as one example, or see any other file which includes this header.

References:
1. *****+ [my answer with some of these functions] How to swap the bytes in any basic data
   type or array of bytes: https://stackoverflow.com/a/64056527/4561887
1. https://en.wikipedia.org/wiki/Endianness
1. ***** Linux byteswap and endianness and host-to-network byte order utilities: Linux also has a
   bunch of built-in utilities via gcc GNU extensions that you can use. See:
    1. https://man7.org/linux/man-pages/man3/bswap.3.html - `#include <byteswap.h>`
    1. https://man7.org/linux/man-pages/man3/endian.3.html - `#include <endian.h>`
    1. https://man7.org/linux/man-pages/man3/byteorder.3.html - `#include <arpa/inet.h>` - generally
       used for network sockets (Ethernet packets) and things; `inet` stands for "internet"

*/

#pragma once

#include <cstdint>  // For `uint8_t`, `int8_t`, etc.
#include <cstdio>   // `size_t`

/// \brief          Swap all the bytes in an array to convert from little-endian
///      byte order to big-endian byte order, or vice versa.
/// \note           Works for arrays of any size. Swaps the bytes **in place**
///                 in the array.
/// \param[in,out]  byte_array  The array in which to swap the bytes in-place.
/// \param[in]      len         The length (in bytes) of the array.
/// \return         None
void swap_bytes(uint8_t * byte_array, size_t len);

/// Template function wrapper to allow byte swapping any basic data type.
template <typename T>
void swap_bytes(T *var)
{
    // Note that `sizeof(*var)` is the exact same thing as `sizeof(T)`
    swap_bytes((uint8_t*)var, sizeof(*var));
}

// Endianness functions; from: "eRCaGuy_hello_world/c/endianness_get.c"

typedef enum endianness_e
{
    /// Could not be determined
    ENDIANNESS_UNKNOWN = 0,

    /// **Least**-significant byte first in memory.
    /// Note: "little-endianness is the dominant ordering for processor architectures (x86, most ARM
    /// implementations, base RISC-V implementations) and their associated memory."
    /// See: https://en.wikipedia.org/wiki/Endianness
    ENDIANNESS_LITTLE_ENDIAN,

    /// **Most**-significant byte first in memory.
    /// Note: Network byte order is big-endian. See: https://en.wikipedia.org/wiki/Endianness:
    /// "Big-endianness is the dominant ordering in networking protocols, such as in the internet
    /// protocol suite, where it is referred to as network order, transmitting the most
    /// significant byte first."
    ENDIANNESS_BIG_ENDIAN,
} endianness_t;

/// Get the endianness of the system on which this is running.
endianness_t endianness_get();

/// @brief      Obtain the endianness as an ASCII-printable name string
///             from an endianness type
/// @details    See a previous demo of this type of "get name" function here:
///             https://stackoverflow.com/a/54728664/4561887
/// @param[in]  endianness     The previously-obtained endianness
/// @return     A null-terminated ASCII name string describing the endianness
const char * endianness_get_name(endianness_t endianness);
