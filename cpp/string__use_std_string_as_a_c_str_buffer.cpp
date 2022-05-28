/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
May 2022

Examine how to use a C++ `std::string` as a C-style `char*` buffer.

Consider also my question here: https://en.cppreference.com/w/Talk:cpp/string/basic_string/operator_at
> `.size()` (expanded via `resize()`) vs `.capacity()` (expanded via `reserve()`):

STATUS: wip

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# NB: you may need to use `-std=gnu++17` instead of `-std=c++17` in order to obtain extra GNU
# gcc features, including gcc extensions, POSIX cmds, and Linux sytem cmds.
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# 1. In C++
time g++ -Wall -Wextra -Werror -O3 -std=c++17 string__use_std_string_as_a_c_str_buffer.cpp -o bin/a && bin/a
```

References:
1. How to convert a std::string to const char* or char*:
   https://stackoverflow.com/q/347949/4561887
1. Directly write into char* buffer of std::string:
   https://stackoverflow.com/q/39200665/4561887
1. Is there a way to get std:string's buffer:
   https://stackoverflow.com/q/7836863/4561887

(my content)
1. [my Q] See the "Adjacently related" section at the bottom of my question here:
   https://stackoverflow.com/q/72367123/4561887
1. *****+ [my comments about pre-allocating a buffer in the std::string]:
   https://stackoverflow.com/questions/39200665/directly-write-into-char-buffer-of-stdstring#comment127844941_39200666
1. *****+ [my comment on how to pre-allocate storage in a std::string, to be used as a char* buffer]
   https://stackoverflow.com/questions/7836863/is-there-a-way-to-get-stdstrings-buffer#comment127847227_15863513

(from the cppreference.com community wiki)
1. https://en.cppreference.com/w/cpp/string/basic_string:
   """
   The elements of a basic_string are stored contiguously, that is, for a basic_string s, &*(s.begin
   () + n) == &*s.begin() + n for any n in [0, s.size()), or, equivalently, a pointer to s[0] can
   be passed to functions that expect a pointer to the first element of a null-terminated
   (since C++11)CharT[] array.
   """
1. https://en.cppreference.com/w/cpp/string/basic_string/operator_at
   """
   Returns a reference to the character at specified location pos. No bounds checking is performed.
   If pos > size(), the behavior is undefined.
   """
1. https://en.cppreference.com/w/cpp/string/basic_string/resize
1. https://en.cppreference.com/w/cpp/string/basic_string/reserve
1. https://en.cppreference.com/w/cpp/string/basic_string/data
1. https://en.cppreference.com/w/cpp/string/basic_string/c_str
1. https://en.cppreference.com/w/cpp/string/basic_string/clear


*/


// C++ includes
#include <iostream>  // For `std::cin`, `std::cout`, `std::endl`, etc.
#include <string>

// C includes
#include <cstdint>  // For `uint8_t`, `int8_t`, etc.
#include <cstdio>   // For `printf()`
#include <cstring>  // `strcpy()`

void print_string_stats(const std::string& str)
{

}

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Hello ");
    std::cout << "world!\n\n";

    // Here is how to pre-allocate space in a `std::string` so you can use it like a `char*`
    // C-string:

    std::string str;
    std::cout << "str contains: " << str << "\n";
    std::cout << "str.size()          = " << str.size() << "\n";
    std::cout << "strlen(str.c_str()) = " << strlen(str.c_str()) << "\n";
    std::cout << "\n";
    // pre-allocate space for 100 chars, filling in every one of those bytes with a '\0' null
    // terminator.
    str.resize(100);
    std::cout << "str contains: " << str << "\n";
    std::cout << "str.size()          = " << str.size() << "\n";
    std::cout << "strlen(str.c_str()) = " << strlen(str.c_str()) << "\n";
    std::cout << "\n";

    // Now write into the `std::string` like you would a C-string.

    constexpr char cstr1[] = "abcde ";
    constexpr char cstr2[] = "fghijk";

    // ---------------------------------------------------------------------------------------------
    // Technique 1: use array indexing via `operator[]`; ex: `&str[0]`
    // ---------------------------------------------------------------------------------------------
    std::cout << "Technique 1:"
    strcpy(&str[0], cstr1);
    std::cout << "str contains: " << str << "\n";
    std::cout << "str.size()          = " << str.size() << "\n";
    std::cout << "strlen(str.c_str()) = " << strlen(str.c_str()) << "\n";
    strcpy(&str[sizeof(cstr1) - 1], cstr2); // `- 1` to overwrite the first null terminator
    std::cout << "str contains: " << str << "\n";
    std::cout << "str.size()          = " << str.size() << "\n";
    std::cout << "strlen(str.c_str()) = " << strlen(str.c_str()) << "\n";
    std::cout << "\n";

    // clear the string to prepare to try the next technique
    str.clear();

    // ---------------------------------------------------------------------------------------------
    // Technique 2: use the `.data()` method
    // ---------------------------------------------------------------------------------------------
    std::cout << "Technique 2:"
    strcpy(str.data(), cstr1);
    std::cout << "str contains: " << str << "\n";
    std::cout << "str.size()          = " << str.size() << "\n";
    std::cout << "strlen(str.c_str()) = " << strlen(str.c_str()) << "\n";
    strcpy(str.data() + (sizeof(cstr1) - 1), cstr2); // `- 1` to overwrite the first null terminator
    std::cout << "str contains: " << str << "\n";
    std::cout << "str.size()          = " << str.size() << "\n";
    std::cout << "strlen(str.c_str()) = " << strlen(str.c_str()) << "\n";
    std::cout << "\n";

    // Will NOT work since it returns const references only: try the const-only `.c_str()` method


    // shrink to fit
    // RESULT: no change!
    std::cout << "shrinking to fit" << "\n";
    str.shrink_to_fit();
    std::cout << "str contains: " << str << "\n";
    std::cout << "str.size()          = " << str.size() << "\n";
    std::cout << "strlen(str.c_str()) = " << strlen(str.c_str()) << "\n";
    std::cout << "\n";


    return 0;
}



/*
SAMPLE OUTPUT:

    eRCaGuy_hello_world/cpp$ g++ -Wall -Wextra -Werror -O3 -std=c++17 string__use_std_string_as_a_c_str_buffer.cpp -o bin/a && bin/a
    Hello world!

*/
