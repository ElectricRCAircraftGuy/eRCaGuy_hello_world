///usr/bin/env ccache gcc -Wall -Wextra -Werror -O3 -std=gnu17 "$0" -o /tmp/a -lm && /tmp/a "$@"; exit
// For the line just above, see my answer here: https://stackoverflow.com/a/75491834/4561887

/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
Feb. 2024

Print UINT32_MAX and UINT64_MAX values. I need this information for writing to buffers with 
`snprintf()`. ie: I need to know how big the buffer needs to be to hold max values!

STATUS: Done and works!

keywords to easily grep or ripgrep in this repo for this program and what it teaches
KEYWORDS:

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# Why `-std=gnu17` vs `-std=c17`, and `-std=gnu++17` vs `-std=c++17`?
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# [run once ever] install ccache
sudo apt update && sudo apt install ccache

# 1. In C:
./print_UINT64_MAX_inttypes.c
# or:
gcc -Wall -Wextra -Werror -O3 -std=gnu17 print_UINT64_MAX_inttypes.c -o bin/a -lm && bin/a

# 2. In C++
g++ -Wall -Wextra -Werror -O3 -std=gnu++17 print_UINT64_MAX_inttypes.c -o bin/a && bin/a
```

References:
1. https://cplusplus.com/reference/cstdint/
1.

*/


#include <inttypes.h> // For `PRIu64`, etc.
#include <stdbool.h>  // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>   // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>    // For `printf()`

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("print_UINT64_MAX_inttypes.c:\n\n");

    printf("UINT8_MAX = %" PRIu8 "\n", UINT8_MAX);
    printf("UINT16_MAX = %" PRIu16 "\n", UINT16_MAX);
    printf("UINT32_MAX = %" PRIu32 "\n", UINT32_MAX);
    printf("UINT64_MAX = %" PRIu64 "\n", UINT64_MAX);

    return 0;
}


/*
SAMPLE OUTPUT:

In C:

    eRCaGuy_hello_world/c$ gcc -Wall -Wextra -Werror -O3 -std=c17 print_UINT64_MAX_inttypes.c -o bin/a -lm && bin/a
    print_UINT64_MAX_inttypes.c:

    UINT8_MAX = 255
    UINT16_MAX = 65535
    UINT32_MAX = 4294967295
    UINT64_MAX = 18446744073709551615


OR, in C++:

    eRCaGuy_hello_world/c$ g++ -Wall -Wextra -Werror -O3 -std=c++17 print_UINT64_MAX_inttypes.c -o bin/a && bin/a
    
    [same as above]

*/
