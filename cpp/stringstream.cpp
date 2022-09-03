/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
2 Sept. 2022

Basic `std::stringstream` demo:

Practice using `std::stringstream` objects, which can be used in C++ to store formatted strings,
kind of like `sprintf()` is used in C to store special formatting into C-strings.

My notes: `std::stringstream` is for IO into or out of a **string** in C++! This gives you the C++
equivalent of C's `sprintf()` feature, for instance, for printing TO a string!

Think of a `std::stringstream` as a wrapper around a `std::string` container, whereby all of the
methods in the `std::stringstream` class allow special formatting of additional strings and
content _into_ this underlying `std::string` container.


STATUS: done and works!

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# NB: you may need to use `-std=gnu++17` instead of `-std=c++17` in order to obtain extra GNU
# gcc features, including gcc extensions, POSIX cmds, and Linux sytem cmds.
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# 1. In C++
time g++ -Wall -Wextra -Werror -O3 -std=c++17 stringstream.cpp -o bin/a && bin/a
```

References:
1. *****+ https://en.cppreference.com/w/cpp/io/basic_stringstream
    1. https://en.cppreference.com/w/cpp/io/basic_stringstream/str `.str()` func
1. https://stackoverflow.com/q/73589589/4561887 - Why doesn't `std::stringstream` work with
   `std::string_view`?

*/


// C & C++ includes
#include <cstdint>  // For `uint8_t`, `int8_t`, etc.
#include <cstdio>   // For `printf()`
#include <iostream>  // For `std::cin`, `std::cout`, `std::endl`, etc.
#include <sstream>

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Hello ");
    std::cout << "world!\n\n";

    int i = 77;
    double d = 1234.5678;

    std::stringstream ss;

    // format some data into the underlying `std::string` inside `ss`.
    ss << "i = " << i << "; d = " << d << "\n";

    // print the underlying `std::string`
    std::cout << ss.str();

    // copy and print the underlying `std::string`
    std::string str = ss.str();
    std::cout << str;

    // Print via C's `printf()` func on the copied `std::string` above.
    printf("%s", str.c_str());  // Ok

    // NB: you can NOT call `.c_str()` on the ss object directly or else it will rely on a
    // dangling pointer and technically be undefined behavior! From
    // https://en.cppreference.com/w/cpp/io/basic_stringstream/str:
    //
    // > The copy of the underlying string returned by str is a temporary object that will be
    //   destructed at the end of the expression, so directly calling `c_str()` on the result of
    //   `str()` (for example in `auto *ptr = out.str().c_str();`) results in a dangling pointer.
    //
    printf("Undefined behavior apparently, although it appears to work: ");
    printf("%s", ss.str().c_str()); // UNDEFINED BEHAVIOR! `.c_str()` is accessing a dangling ptr.
                                    // You must **copy** out the underlying string first for this
                                    // to be okay. Again, this is ok:
    std::string str2 = ss.str();
    printf("%s", str2.c_str());  // Ok


    return 0;
}



/*
SAMPLE OUTPUT:

    eRCaGuy_hello_world/cpp$ time g++ -Wall -Wextra -Werror -O3 -std=c++17 stringstream.cpp -o bin/a && bin/a

    real    0m0.346s
    user    0m0.306s
    sys 0m0.039s
    Hello world!

    i = 77; d = 1234.57
    i = 77; d = 1234.57
    i = 77; d = 1234.57
    Undefined behavior apparently, although it appears to work: i = 77; d = 1234.57
    i = 77; d = 1234.57


*/
