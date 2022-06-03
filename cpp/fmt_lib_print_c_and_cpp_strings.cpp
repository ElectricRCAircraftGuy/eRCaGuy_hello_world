/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
June 2022

Ensure I know how to properly print C and C++ strings using the fmt library.

STATUS: done and works!

To compile and run (assuming you've already `cd`ed into this dir):
[see the "BEST" option below for my final answer for this code]
```bash
# NB: you may need to use `-std=gnu++17` instead of `-std=c++17` in order to obtain extra GNU
# gcc features, including gcc extensions, POSIX cmds, and Linux sytem cmds.
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# **BEST:** with `-lfmt` AND `-DFMT_ENFORCE_COMPILE_STRING` in it to enforce static,
# compile-time format string checking. See:
# 1. *****+ [my notes] https://github.com/fmtlib/fmt/issues/2157#issuecomment-1117930229
# 1. ***** https://fmt.dev/latest/api.html#compile-time-format-string-checks
# 1. https://fmt.dev/latest/usage.html
#
# 1st: FIRST, follow the fmt library setup and installation instructions here:
# "eRCaGuy_hello_world/cpp/README.md"
# 2nd: THEN, run this build & run command:
#
time g++ -Wall -Wextra -Werror -O3 -std=c++17 -DFMT_ENFORCE_COMPILE_STRING fmt_lib_print_c_and_cpp_strings.cpp -o bin/a -lfmt && bin/a
```

References:
1. fmt library:
    1. https://github.com/fmtlib/fmt
    1. https://fmt.dev/latest/usage.html#building-the-library
    1. *****+ https://fmt.dev/latest/api.html - full API reference and description of the
       various header files!
    1. *****+ my own build and run notes:
       https://github.com/fmtlib/fmt/issues/2157#issuecomment-1117930229

*/



// Local includes
// NA

// 3rd-party library includes
// This include is OK now that I have fully installed the `fmt` library with `sudo make install`, I
// believe. Follow the `fmt` library installation instructions I wrote which I linked-to above.
#include <fmt/format.h>

// Linux includes
// NA

// C and C++ includes
#include <cstdint>   // For `uint8_t`, `int8_t`, etc.
#include <cstdio>    // For `printf()`
#include <iostream>  // For `std::cin`, `std::cout`, `std::endl`, etc.
#include <string>


// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Hello ");
    std::cout << "world!\n\n";

    fmt::print(FMT_STRING("Hello {}\n"), "worlds."); // Works!: `Hello worlds.`

    const char* cstr = nullptr;
    cstr = "kind sir.";
    fmt::print(FMT_STRING("Hello {}\n"), cstr); // Works!: `Hello kind sir.`

    // This is really goofy, but bear with me; I want to make sure I understand some things:
    std::string str = std::string("Hey ") + "How " "Are " "You?";
    std::cout << str << "\n";            // Works:  `Hey How Are You?`
    fmt::print(FMT_STRING("{}\n"), str); // Works!: `Hey How Are You?`


    str.pop_back();  // Remove the question mark at the end.
    // Combine both a C++ `std::string` and a C-style string into one format string to ensure both
    // work.
    std::string str2 = fmt::format(FMT_STRING("{} {}?\n"), str, cstr);
    std::cout << str2;  // Works!: `Hey How Are You kind sir.?` [has extraneous period]

    std::string kind_sir_str(cstr);
    kind_sir_str.pop_back(); // remove the period at the end
    fmt::print(FMT_STRING("{} {}?\n"), str, kind_sir_str); // Works!: `Hey How Are You kind sir?`


    return 0;
}



/*
SAMPLE OUTPUT:

    eRCaGuy_hello_world/cpp$ time g++ -Wall -Wextra -Werror -O3 -std=c++17 -DFMT_ENFORCE_COMPILE_STRING fmt_lib_print_c_and_cpp_strings.cpp -o bin/a -lfmt && bin/a

    real    0m0.567s
    user    0m0.503s
    sys 0m0.064s
    Hello world!

    Hello worlds.
    Hello kind sir.
    Hey How Are You?
    Hey How Are You?
    Hey How Are You kind sir.?
    Hey How Are You kind sir?


*/
