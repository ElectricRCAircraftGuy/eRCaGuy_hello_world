/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

Practice finding a substring in a C++ `std::string`.

GS
1 Feb. 2022

To compile and run (assuming you've already `cd`ed into this dir):
1. In C++
```bash
g++ -Wall -Wextra -Werror -O3 -std=c++17 string_find_substring.cpp -o bin/a && bin/a
```

References:
1. https://en.cppreference.com/w/cpp/string/basic_string
1. https://en.cppreference.com/w/cpp/string/basic_string/basic_string (constructor)
1. https://en.cppreference.com/w/cpp/string/basic_string/find

*/


// C++ includes
#include <iostream>  // For `std::cin`, `std::cout`, `std::endl`, etc.
#include <string>

// C includes
#include <cstdint>  // For `uint8_t`, `int8_t`, etc.
#include <cstdio>   // For `printf()`

void checkSubstring(const std::string& string, const std::string& substring)
{
    std::string::size_type position = string.find(substring);
    if (position != std::string::npos)
    {
        printf("String %-12s contains the substring \"%s\" at index position %lu.\n",
            ("\"" + string + "\"").c_str(), substring.c_str(), position);
        // std::cout << "String \"" << string << "\" contains the substring \""
        //           << substring << "\".\n";
    }
    else
    {
        printf("String %-12s does NOT contain the substring \"%s\".\n",
            ("\"" + string + "\"").c_str(), substring.c_str());
        // std::cout << "String \"" << string << "\" does NOT contain the substring \""
        //           << substring << "\".\n";
    }
}

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Hello ");
    std::cout << "world!\n\n";

    const std::string s1 = "hello_1";
    const std::string s2 = "abchello_2";
    const std::string s3 = "dehello_3";
    const std::string s4 = "world_1";
    const std::string s5 = "abcworld_2";
    const std::string s6 = "deworld_3";

    checkSubstring(s1, "hello");
    checkSubstring(s2, "hello");
    checkSubstring(s3, "hello");
    checkSubstring(s4, "hello");
    checkSubstring(s5, "hello");
    checkSubstring(s6, "hello");
    printf("\n");

    checkSubstring(s1, "world");
    checkSubstring(s2, "world");
    checkSubstring(s3, "world");
    checkSubstring(s4, "world");
    checkSubstring(s5, "world");
    checkSubstring(s6, "world");
    printf("\n");

    return 0;
}



/*
SAMPLE OUTPUT:

    eRCaGuy_hello_world/cpp$ g++ -Wall -Wextra -Werror -O3 -std=c++17 string_find_substring.cpp -o bin/a && bin/a
    Hello world!

    String "hello_1"    contains the substring "hello" at index position 0.
    String "abchello_2" contains the substring "hello" at index position 3.
    String "dehello_3"  contains the substring "hello" at index position 2.
    String "world_1"    does NOT contain the substring "hello".
    String "abcworld_2" does NOT contain the substring "hello".
    String "deworld_3"  does NOT contain the substring "hello".

    String "hello_1"    does NOT contain the substring "world".
    String "abchello_2" does NOT contain the substring "world".
    String "dehello_3"  does NOT contain the substring "world".
    String "world_1"    contains the substring "world" at index position 0.
    String "abcworld_2" contains the substring "world" at index position 3.
    String "deworld_3"  contains the substring "world" at index position 2.

*/
