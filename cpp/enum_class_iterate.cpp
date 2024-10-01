///usr/bin/env ccache g++ -Wall -Wextra -Werror -O3 -std=gnu++17 "$0" -o /tmp/a && /tmp/a "$@"; exit
// For the line just above, see my answer here: https://stackoverflow.com/a/75491834/4561887

/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
Sep. 2024

Iterate over a C++ enum class. 
This code is for my answer here: https://stackoverflow.com/a/69762682/4561887

STATUS: Done & works!

keywords to easily grep or ripgrep in this repo for this program and what it teaches
KEYWORDS:

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# NB: you may need to use `-std=gnu++17` instead of `-std=c++17` in order to obtain extra GNU
# gcc features, including gcc extensions, POSIX cmds, and Linux sytem cmds.
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# [run once ever] install ccache
sudo apt update && sudo apt install ccache

# 1. In C++
time g++ -Wall -Wextra -Werror -O3 -std=gnu++17 enum_class_iterate.cpp -o bin/a && bin/a

# OR (just call this file as an exectuable directly)
time ./enum_class_iterate.cpp
```

References:
1.

*/

// C++ (incl. C) includes
// #include <cstdint>  // For `uint8_t`, `int8_t`, etc.
#include <cstdio>   // For `printf()`
// #include <iostream>  // For `std::cin`, `std::cout`, `std::endl`, etc.

enum class MyErrorType 
{
    SOMETHING_1 = 0,
    SOMETHING_2,
    SOMETHING_3,
    SOMETHING_4,
    SOMETHING_5,
    // Helpers for iterating over the enum:
    // - Note: adding these helpers adds no new enum values, since `begin`
    //   already has the same value as `SOMETHING_1`, and `end` already has the
    //   same value as `SOMETHING_5`. These are just aliased names is all. 
    begin = 0,
    end = SOMETHING_5,
};

int main()
{
    printf("C++ enum class iteration demo.\n");

    // Iterate over the enum class
    for (MyErrorType myErrorType = MyErrorType::begin;
        myErrorType <= MyErrorType::end;
        myErrorType = static_cast<MyErrorType>(
            static_cast<size_t>(myErrorType) + 1))
    {
        switch (myErrorType)
        {
            case MyErrorType::SOMETHING_1:
                printf("MyErrorType::SOMETHING_1\n");
                break;
            case MyErrorType::SOMETHING_2:
                printf("MyErrorType::SOMETHING_2\n");
                break;
            case MyErrorType::SOMETHING_3:
                printf("MyErrorType::SOMETHING_3\n");
                break;
            case MyErrorType::SOMETHING_4:
                printf("MyErrorType::SOMETHING_4\n");
                break;
            case MyErrorType::SOMETHING_5:
                printf("MyErrorType::SOMETHING_5\n");
                break;
        }
    }
}



/*
SAMPLE OUTPUT:

eRCaGuy_hello_world/cpp$ ./enum_class_iterate.cpp 
C++ enum class iteration demo.
MyErrorType::SOMETHING_1
MyErrorType::SOMETHING_2
MyErrorType::SOMETHING_3
MyErrorType::SOMETHING_4
MyErrorType::SOMETHING_5

*/
