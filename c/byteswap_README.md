This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

Here are various byteswap and endianness-related libraries, functions, and tools to be aware of. Many of them are either GNU gcc extensions, or for Linux only.


## `#include <byteswap.h>` - generic byte swaps

https://man7.org/linux/man-pages/man3/bswap.3.html


```c
#include <byteswap.h>

uint16_t bswap_16(uint16_t x);
uint32_t bswap_32(uint32_t x);
uint64_t bswap_64(uint64_t x);
```

EXAMPLES

The program below swaps the bytes of the 8-byte integer supplied
as its command-line argument.  The following shell session
demonstrates the use of the program:

    $ ./a.out 0x0123456789abcdef
    0x123456789abcdef ==> 0xefcdab8967452301

Program source

```c
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>
#include <byteswap.h>
 
int
main(int argc, char *argv[])
{
    uint64_t x;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <num>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    x = strtoull(argv[1], NULL, 0);
    printf("%#" PRIx64 " ==> %#" PRIx64 "\n", x, bswap_64(x));

    exit(EXIT_SUCCESS);
}
```


## `#include <endian.h>` - endianness-based byte swaps (to/from host to little or big endian)

https://man7.org/linux/man-pages/man3/endian.3.html

```c
#include <endian.h>

uint16_t htobe16(uint16_t host_16bits);
uint16_t htole16(uint16_t host_16bits);
uint16_t be16toh(uint16_t big_endian_16bits);
uint16_t le16toh(uint16_t little_endian_16bits);

uint32_t htobe32(uint32_t host_32bits);
uint32_t htole32(uint32_t host_32bits);
uint32_t be32toh(uint32_t big_endian_32bits);
uint32_t le32toh(uint32_t little_endian_32bits);

uint64_t htobe64(uint64_t host_64bits);
uint64_t htole64(uint64_t host_64bits);
uint64_t be64toh(uint64_t big_endian_64bits);
uint64_t le64toh(uint64_t little_endian_64bits);
```


## `#include <arpa/inet.h>` - network-order byte swaps (host to network, or vice versa)

Note that "network" is _big-endian_, and "host" is architecture-dependent, but for Linux x86-64 is _little-endian._ Also, `inet` stands for "internet".

```c
#include <arpa/inet.h>

uint32_t htonl(uint32_t hostlong);
uint16_t htons(uint16_t hostshort);

uint32_t ntohl(uint32_t netlong);
uint16_t ntohs(uint16_t netshort);
```


## `swap_bytes_in_array()` - my own answer on Stack Overflow: How to swap the bytes in place in any array, variable, or any other memory block

See: https://stackoverflow.com/a/64056527/4561887

```c
/// \brief          Swap all the bytes in an array to convert from little-endian byte order 
///                 to big-endian byte order, or vice versa.
/// \note           Works for arrays of any size. Swaps the bytes **in place** in the array.
/// \param[in,out]  byte_array  The array in which to swap the bytes in-place.
/// \param[in]      len         The length (in bytes) of the array.
/// \return         None
void swap_bytes_in_array(uint8_t * byte_array, size_t len) {
    size_t i_left = 0; // index for left side of the array
    size_t i_right = len - 1; // index for right side of the array
    while (i_left < i_right) {
        // swap left and right bytes
        uint8_t left_copy = byte_array[i_left];
        byte_array[i_left] = byte_array[i_right];
        byte_array[i_right] = left_copy;
        i_left++;
        i_right--;
    }
}
```

Usage:

```c
double d;
// Swap the bytes in the double in place
swap_bytes_in_array((uint8_t*)(&d), sizeof(d));

uint64_t u64;
// swap the bytes in a uint64_t in place
swap_bytes_in_array((uint8_t*)(&u64), sizeof(u64));
```

