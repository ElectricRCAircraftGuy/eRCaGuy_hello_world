/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS

Write a function to determine and print out the endianness of the system.

STATUS: done and works!

To compile and run (assuming you've already `cd`ed into this dir):
1. In C:
```bash
gcc -Wall -Wextra -Werror -O3 -std=c17 endianness_get.c -o bin/a -lm && bin/a
```
2. In C++
```bash
g++ -Wall -Wextra -Werror -O3 -std=c++17 endianness_get.c -o bin/a && bin/a
```

References:
1. *****https://en.wikipedia.org/wiki/Endianness
1. *****https://cs-fundamentals.com/tech-interview/c/c-program-to-check-little-and-big-endian-architecture
   > As said earlier, big endian is also called network byte order, while little endian is called
     host byte order. There are a set of functions to convert 16-bit and 32-bit integers to network
     byte order and vice versa. The htons (host-to-network-short) and htonl
     (host-to-network-long) functions convert 16-bit and 32-bit values respectively from host
     (machine) to network byte order; the ntohs and ntohl functions convert from network to host
     byte order. You can read more on endianness and information representation here.
1. https://stackoverflow.com/questions/12791864/c-program-to-check-little-vs-big-endian
1. https://stackoverflow.com/questions/2100331/macro-definition-to-determine-big-endian-or-little-endian-machine

*/

#include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`

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

/// @brief      Obtain the endianness as an ASCII-printable name string
///             from an endianness type
/// @details    See a previous demo of this type of "get name" function here:
///             https://stackoverflow.com/a/54728664/4561887
/// @param[in]  endianness     The previously-obtained endianness
/// @return     A null-terminated ASCII name string describing the endianness
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

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Checking endianness of this system.\n");

    endianness_t endianness = endianness_get();
    printf("The endianness of this system is \"%s\".\n", endianness_get_name(endianness));

    return 0;
}

/*
SAMPLE OUTPUT:

In C:

    eRCaGuy_hello_world/c$ gcc -Wall -Wextra -Werror -O3 -std=c17 endianness_get.c -o bin/a -lm && bin/a
    Checking endianness of this system.
    The endianness of this system is "LITTLE_ENDIAN (least-significant byte first in memory)".



OR, in C++:

    eRCaGuy_hello_world/c$ g++ -Wall -Wextra -Werror -O3 -std=c++17 endianness_get.c -o bin/a && bin/a
    Checking endianness of this system.
    The endianness of this system is "LITTLE_ENDIAN (least-significant byte first in memory)".


*/
