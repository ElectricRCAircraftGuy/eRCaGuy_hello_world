///usr/bin/env ccache gcc -Wall -Wextra -Werror -O3 -std=gnu17 "$0" -o /tmp/a -lm -latomic && /tmp/a "$@"; exit
// For the line just above, see my answer here: https://stackoverflow.com/a/75491834/4561887

/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
10 May 2023

Learn to use the `atomic_*` types in both C and C++!
See references below.

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
./atomic_types.c
# or:
gcc -Wall -Wextra -Werror -O3 -std=gnu17 atomic_types.c -o bin/a -lm -latomic && bin/a

# 2. In C++
g++ -Wall -Wextra -Werror -O3 -std=gnu++17 atomic_types.c -o bin/a -latomic && bin/a
```

References:
1. Atomic variable types:
    1. In C:    https://en.cppreference.com/w/c/thread#Atomic_operations
    1. In C++:  https://en.cppreference.com/w/cpp/atomic/atomic
    1.          https://en.cppreference.com/w/cpp/header/atomic
    1. ---
    1.          https://en.cppreference.com/w/cpp/header/stdatomic.h
    1. NB: "On gcc and clang, some of the functionality described here requires linking against
        `-latomic`." See: https://en.cppreference.com/w/cpp/atomic/atomic
        GS: I have *not* yet seen this to be needed, but I'll do it above anyway!
1.

*/

#ifdef __cplusplus
    #include <atomic> // for `atomic_*` types in C++
    // This is required for C++ since all `atomic_*` type aliases are in namespace `std`, as in
    // `std::atomic_bool`, for instance, instead of just `atomic_bool`!
    using namespace std;
#else
    #include <stdatomic.h> // for `atomic_*` types in C
#endif

#include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Atomic types test.\n\n");

    atomic_bool b1 = true;
    atomic_uint_fast32_t u1 = 12345;
    atomic_uint_least32_t u2 = 6789;

#ifdef __cplusplus
    // For C++, we *must* use `.load()` here! See the "Member functions" section here:
    // https://en.cppreference.com/w/cpp/atomic/atomic
    printf("b1 =   %s, sizeof(b1) = %zu\n", b1 ? "true" : "false", sizeof(b1));
    printf("u1 = %6lu, sizeof(u1) = %zu\n", u1.load(), sizeof(u1));
    printf("u2 = %6u, sizeof(u2) = %zu\n", u2.load(), sizeof(u2));
#else
    // For C, we must *not* use `load()`, as it doesn't exist for atomic types!
    printf("b1 =   %s, sizeof(b1) = %zu\n", b1 ? "true" : "false", sizeof(b1));
    printf("u1 = %6lu, sizeof(u1) = %zu\n", u1, sizeof(u1));
    printf("u2 = %6u, sizeof(u2) = %zu\n", u2, sizeof(u2));
#endif

    return 0;
}


/*
SAMPLE OUTPUT:

In C:

    eRCaGuy_hello_world/c$ ./atomic_types.c
    Atomic types test.

    b1 =   true, sizeof(b1) = 1
    u1 =  12345, sizeof(u1) = 8
    u2 =   6789, sizeof(u2) = 4

  OR:

    eRCaGuy_hello_world/c$ gcc -Wall -Wextra -Werror -O3 -std=gnu17 atomic_types.c -o bin/a -lm -latomic && bin/a
    Atomic types test.

    b1 =   true, sizeof(b1) = 1
    u1 =  12345, sizeof(u1) = 8
    u2 =   6789, sizeof(u2) = 4


OR, in C++:

    eRCaGuy_hello_world/c$ g++ -Wall -Wextra -Werror -O3 -std=gnu++17 atomic_types.c -o bin/a -latomic && bin/a
    Atomic types test.

    b1 =   true, sizeof(b1) = 1
    u1 =  12345, sizeof(u1) = 8
    u2 =   6789, sizeof(u2) = 4


*/
