/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world


2022

See my links in the References section below. I was going to use this file to learn how to use
string literals and the weird string literal suffixes and prefixes in C++, such as L, u8, u, U, R,
etc.

STATUS: todo

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# NB: you may need to use `-std=gnu++17` instead of `-std=c++17` in order to obtain extra GNU
# gcc features, including gcc extensions, POSIX cmds, and Linux sytem cmds.
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# 1. In C++
time g++ -Wall -Wextra -Werror -O3 -std=c++17 hello_world_extra_basic.cpp -o bin/a && bin/a
```

References:
1. A community-wiki-based reference page [very hard to read and understand :(] https://en.cppreference.com/w/cpp/language/string_literal
1. ***** https://www.geeksforgeeks.org/raw-string-literal-c/
1. ***** "JSON for Modern C++" library serialization and deserialization examples with
   and withOUT R-string raw string literals!:
   https://github.com/nlohmann/json#serialization--deserialization

*/

// C++ includes
#include <iostream>  // For `std::cin`, `std::cout`, `std::endl`, etc.

// C includes
#include <cstdint>  // For `uint8_t`, `int8_t`, etc.
#include <cstdio>   // For `printf()`

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Hello ");
    std::cout << "world!\n\n";

    return 0;
}



/*
SAMPLE OUTPUT:

    eRCaGuy_hello_world/cpp$ g++ -Wall -Wextra -Werror -O3 -std=c++17 hello_world_extra_basic.cpp -o bin/a && bin/a
    Hello world!

*/
