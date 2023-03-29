///usr/bin/env ccache g++ -Wall -Wextra -Werror -O3 -std=gnu++17 "$0" -o /tmp/a && /tmp/a "$@"; exit
// For the line just above, see my answer here: https://stackoverflow.com/a/75491834/4561887

/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

Concatenate two (or more) C++ `std::string`s.
- For a comparison to the higher complexities in memory management required in C,
  see "eRCaGuy_hello_world/c/str_concatenate.c".

STATUS: done and works!

keywords to easily grep or ripgrep in this repo for this program and what it teaches
KEYWORDS: interview prep

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# NB: you may need to use `-std=gnu++17` instead of `-std=c++17` in order to obtain extra GNU
# gcc features, including gcc extensions, POSIX cmds, and Linux sytem cmds.
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# [run once ever] install ccache
sudo apt update && sudo apt install ccache

# 1. In C++
time g++ -Wall -Wextra -Werror -O3 -std=gnu++17 string_concatenate.cpp -o bin/a && bin/a
```

References:
1. `std::move()` template function: https://cplusplus.com/reference/utility/move/
1. ***** https://en.cppreference.com/w/cpp/utility/move - great example!
1. C++20's `std::format` lib: https://en.cppreference.com/w/cpp/utility/format/format
    1. Same thing, by the same author, for earlier versions of C++: `fmt` library:
       https://github.com/fmtlib/fmt

*/

// C++ includes
#include <cstdint>  // For `uint8_t`, `int8_t`, etc.
#include <cstdio>   // For `printf()`
#include <iostream>  // For `std::cin`, `std::cout`, `std::endl`, etc.
#include <string>

/// Concatenate **two** C++ `std::string`s, and efficiently return the result.
std::string str_concat(std::string str1, std::string str2)
{
    std::cout << "Calling 1st function\n"; // debugging

    std::string result = str1 + str2;
    return result; // compiler will optimize this using copy elision / return value optimization
}

// Polymorphism: overload the function name above:

/// Concatenate **any number** of C++ strings!
std::string str_concat(std::initializer_list<std::string> strings)
{
    std::cout << "Calling 2nd function\n"; // debugging

    std::string result;

    for (const std::string& str : strings)
    {
        result += str;
    }

    return result; // compiler will optimize this using copy elision / return value optimization
}

// TODO: write yet another example which concatenates with C++20's uber-fast `std::format`
// library, available as `fmt` for earlier versions of C++!
// See:
// 1. [older versions of C++] https://github.com/fmtlib/fmt
// 1. [C++20] https://en.cppreference.com/w/cpp/utility/format/format


// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    std::cout << str_concat("hello ", "world") << "\n";

    std::string str1 = str_concat("Hey", "you");
    std::cout << str1 << "\n\n";

    std::string str2 = str_concat({"Hey", " ", "you", " ", "Jimmy", ".\n"});
    std::cout << str2;

    return 0;
}



/*
SAMPLE OUTPUT:

You can also run this file as an executable directly!:

    eRCaGuy_hello_world$ cpp/string_concatenate.cpp
    Calling 1st function
    hello world
    Calling 1st function
    Heyyou

    Calling 2nd function
    Hey you Jimmy.

*/
