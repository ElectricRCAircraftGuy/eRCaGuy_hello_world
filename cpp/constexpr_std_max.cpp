/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
~ Dec. 2021 or Jan. 2022

Q: See if I can have compile-time constexpr variables assigned from `std::max()` output.
A: Yep! I can! It works.

That actually makes perfect sense because the `std::max()` function declarations here
(https://en.cppreference.com/w/cpp/algorithm/max) all have a `constexpr` version, which means that
the function can act like a compile-time macro and be optionally statically evaluated at
compile-time if possible--ie: if all inputs are also literals or `constexpr` (I think).

To compile and run (assuming you've already `cd`ed into this dir):
1. In C++
```
mkdir -p bin && g++ -Wall -Wextra -Werror -O3 -std=c++17 -save-temps=obj constexpr_std_max.cpp -o bin/a && bin/a
```

References:
1. https://en.cppreference.com/w/cpp/algorithm/max

*/

// C++ includes
#include <algorithm> // `std::max()`
#include <iostream>  // For `std::cin`, `std::cout`, `std::endl`, etc.

// C includes
#include <cstdint>  // For `uint8_t`, `int8_t`, etc.
#include <cstdio>   // For `printf()`

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    constexpr uint32_t NUM1 = 100;
    constexpr uint32_t NUM2 = 105;
    constexpr uint32_t NUM3 = 95;
    constexpr uint32_t MAX_NUM = std::max({NUM1, NUM2, NUM3});

    static_assert(NUM1 <= MAX_NUM);
    static_assert(NUM2 <= MAX_NUM);
    static_assert(NUM3 <= MAX_NUM);

    printf("All passed.\n");

    return 0;
}

/*
SAMPLE OUTPUT:

In C++:

    eRCaGuy_hello_world/cpp$ mkdir -p bin && g++ -Wall -Wextra -Werror -O3 -std=c++17 -save-temps=obj constexpr_std_max.cpp -o bin/a && bin/a
    All passed.


*/
