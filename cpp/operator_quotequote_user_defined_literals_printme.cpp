///usr/bin/env ccache g++ -Wall -Wextra -Werror -O3 -std=gnu++17 "$0" -o /tmp/a && /tmp/a "$@"; exit
// For the line just above, see my answer here: https://stackoverflow.com/a/75491834/4561887

/*
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
Sept. 2023

In order to practice making my own `operator ""()` type "trailing-end" functions, let's write a
user-defined literal named `operator ""printme()` to automatically print any data type which comes
right before it! Yeah, that's just silly, but [C++ is nuts!]
(https://stackoverflow.com/questions/47002799/what-does-the-ampersand-at-the-end-of-member-function-signature-mean/47003980#comment135796477_47003980)

NB: you *must* precede your user-defined literal function name with an underscore (`_`), or else
you'll get this error:
```
error: literal operator suffixes not preceded by ‘_’ are reserved for future standardization
```

STATUS: Done and works!

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
time g++ -Wall -Wextra -Werror -O3 -std=gnu++17
operator_quotequote_user_defined_literals_printme.cpp -o bin/a && bin/a
```

References:
1. `operator ""()` user-defined literals: https://en.cppreference.com/w/cpp/language/user_literal
1. My answer: see the "ADDENDUM" at the end about user-defined literals. This is where I first
   discovered them: https://stackoverflow.com/a/49066369/4561887
1. C++ is nuts:
   https://stackoverflow.com/questions/47002799/what-does-the-ampersand-at-the-end-of-member-function-signature-mean/47003980#comment135796477_47003980
1. ***** https://learn.microsoft.com/en-us/cpp/cpp/user-defined-literals-cpp?view=msvc-170 - see the
   the "User-defined literal operator signatures" section for all of the valid options!

*/

// C++ (incl. C) includes
#include <cstdint>  // For `uint8_t`, `int8_t`, etc.
#include <cstdio>   // For `printf()`
#include <iostream>  // For `std::cin`, `std::cout`, `std::endl`, etc.

// For C-style strings; WORKS!
void operator""_printme(const char* c_str, [[maybe_unused]] std::size_t len)
{
    std::cout << c_str << std::endl;
}

// =============== copied from Microsoft START ===============
// THESE FUNCTIONS COPIED FROM MICROSOFT HERE!:
// https://learn.microsoft.com/en-us/cpp/cpp/user-defined-literals-cpp?view=msvc-170#example-limitations-of-raw-literals

// Literal operator for user-defined INTEGRAL literal
void operator"" _dump(unsigned long long int lit)
{
    printf("operator \"\" _dump(unsigned long long int) : ===>%llu<===\n", lit);
};

// Literal operator for user-defined FLOATING literal
void operator"" _dump(long double lit)
{
    printf("operator \"\" _dump(long double)            : ===>%Lf<===\n", lit);
};

// Literal operator for user-defined CHARACTER literal
void operator"" _dump(char lit)
{
    printf("operator \"\" _dump(char)                   : ===>%c<===\n", lit);
};

void operator"" _dump(wchar_t lit)
{
    printf("operator \"\" _dump(wchar_t)                : ===>%d<===\n", lit);
};

void operator"" _dump(char16_t lit)
{
    printf("operator \"\" _dump(char16_t)               : ===>%d<===\n", lit);
};

void operator"" _dump(char32_t lit)
{
    printf("operator \"\" _dump(char32_t)               : ===>%d<===\n", lit);
};

// Literal operator for user-defined STRING literal
void operator"" _dump(const char* lit, size_t)
{
    printf("operator \"\" _dump(const     char*, size_t): ===>%s<===\n", lit);
};

void operator"" _dump(const wchar_t* lit, size_t)
{
    printf("operator \"\" _dump(const  wchar_t*, size_t): ===>%ls<===\n", lit);
};

void operator"" _dump([[maybe_unused]] const char16_t* lit, size_t)
{
    printf("operator \"\" _dump(const char16_t*, size_t):\n");
};

void operator"" _dump([[maybe_unused]] const char32_t* lit, size_t)
{
    printf("operator \"\" _dump(const char32_t*, size_t):\n");
};

// Raw literal operator
void operator"" _dump_raw(const char* lit)
{
    printf("operator \"\" _dump_raw(const char*)        : ===>%s<===\n", lit);
};

template <char...>
void operator"" _dump_template();  // Literal operator template

// =============== copied from Microsoft END ===============


// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Hello ");
    std::cout << "world!\n";

    std::cout << "Using my custom user-defined literal \"trailing end functions\" now:" << "\n";

    "Hello world!"_printme;

    printf("\nMicrosoft tests:\n");
    // =============== copied from Microsoft START ===============

    42_dump;
    3.1415926_dump;
    3.14e+25_dump;
    'A'_dump;
    L'B'_dump;
    u'C'_dump;
    U'D'_dump;
    "Hello World"_dump;
    L"Wide String"_dump;
    u8"UTF-8 String"_dump;
    u"UTF-16 String"_dump;
    U"UTF-32 String"_dump;
    42_dump_raw;
    3.1415926_dump_raw;
    3.14e+25_dump_raw;

    // =============== copied from Microsoft END ===============

    // TODO: Try to make these work too!

    // 123_printme;
    // 123.456_printme;
    // 'a'_printme;
    // true_printme;
    // false_printme;
    // 0b1010_printme;
    // 0x1234_printme;
    // 01234_printme;
    // 0.1234e-5_printme;
    // 0.1234e+5_printme;
    // 0.1234e5_printme;
    // 0.1234e5f_printme;
    // 0.1234e5F_printme;

    return 0;
}

/*
SAMPLE OUTPUT:

    eRCaGuy_hello_world$ cpp/operator_quotequote_user_defined_literals_printme.cpp
    Hello world!
    Using my custom user-defined literal "trailing end functions" now:
    Hello world!

    Microsoft tests:
    operator "" _dump(unsigned long long int) : ===>42<===
    operator "" _dump(long double)            : ===>3.141593<===
    operator "" _dump(long double)            : ===>31400000000000000000000000.000000<===
    operator "" _dump(char)                   : ===>A<===
    operator "" _dump(wchar_t)                : ===>66<===
    operator "" _dump(char16_t)               : ===>67<===
    operator "" _dump(char32_t)               : ===>68<===
    operator "" _dump(const     char*, size_t): ===>Hello World<===
    operator "" _dump(const  wchar_t*, size_t): ===>Wide String<===
    operator "" _dump(const     char*, size_t): ===>UTF-8 String<===
    operator "" _dump(const char16_t*, size_t):
    operator "" _dump(const char32_t*, size_t):
    operator "" _dump_raw(const char*)        : ===>42<===
    operator "" _dump_raw(const char*)        : ===>3.1415926<===
    operator "" _dump_raw(const char*)        : ===>3.14e+25<===

*/
