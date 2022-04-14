/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
24 Jan. 2021

Q: Quick test: does a C-string get automatically cast to a `std::string` when
it is compared against one?

A: Yes! Makes sense now. Look at this documentation for the `operator==()` func too:
https://en.cppreference.com/w/cpp/string/basic_string/operator_cmp
Under the section titled "Compare a basic_string object and null-terminated array of T",
you can see that the right-hand side (rhs) can be a `const char*` C-string type!
(they show it as `const CharT* rhs`):

        template< class CharT, class Traits, class Alloc >
        bool operator==( const std::basic_string<CharT,Traits,Alloc>& lhs,
                         const CharT* rhs );


To compile and run (assuming you've already `cd`ed into this dir):
1. In C++
```bash
g++ -Wall -Wextra -Werror -O3 -std=c++17 string_compare_c_str_against_cpp_std_string.cpp -o bin/a && bin/a
```

References:
1. https://en.cppreference.com/w/cpp/string/basic_string/operator_cmp

*/


// C++ includes
#include <iostream>  // For `std::cin`, `std::cout`, `std::endl`, etc.
#include <string>

// C includes
#include <cstdint>  // For `uint8_t`, `int8_t`, etc.
#include <cstdio>   // For `printf()`

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    std::string s("hey");

    // I expect this to be "True", and it does!
    if (s == "hey")
    {
        printf("True\n");
    }
    else
    {
        printf("False\n");
    }

    // I expect this to result in "False", and it does!
    if (s == "hey ")
    {
        printf("True\n");
    }
    else
    {
        printf("False\n");
    }

    return 0;
}



/*
SAMPLE OUTPUT:

    eRCaGuy_hello_world/cpp$ g++ -Wall -Wextra -Werror -O3 -std=c++17 string_compare_c_str_against_cpp_std_string.cpp -o bin/a && bin/a
    True
    False

*/
