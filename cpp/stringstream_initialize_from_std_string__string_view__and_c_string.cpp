/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
2 Sept. 2022

Basic `std::stringstream` demo:

Practice initializing a `std::stringstream` from a `std::string`, a `std::string_view`, and a
C-string (char array).

Note: a `std::string_view` is intended to be a C++ wrapper around a constexpr C-string. It gives the
C-string some extra, fancy methods you can use on it, such as `substr()`, `find()`,
`starts_with()`, etc. The underlying C-string it wraps, or points, to, however, is constexpr
and cannot be modified. See:
1. https://en.cppreference.com/w/cpp/string/basic_string_view
1. https://cplusplus.com/forum/beginner/240488/:
    > in general: `std::string_view` is the replacement for `std::string` when you don't own the
      string.


STATUS: done and works!

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# NB: you may need to use `-std=gnu++17` instead of `-std=c++17` in order to obtain extra GNU
# gcc features, including gcc extensions, POSIX cmds, and Linux sytem cmds.
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# 1. In C++
g++ -Wall -Wextra -Werror -O3 -std=c++17 stringstream_initialize_from_std_string__string_view__and_c_string.cpp -o bin/a && bin/a
```

References:
1. *****+ https://en.cppreference.com/w/cpp/io/basic_stringstream
    1. https://en.cppreference.com/w/cpp/io/basic_stringstream/str `.str()` func
1. https://stackoverflow.com/q/73589589/4561887 - Why doesn't `std::stringstream` work with
   `std::string_view`?
1. https://en.cppreference.com/w/cpp/string/basic_string_view

*/


// C & C++ includes
#include <cstdint>  // For `uint8_t`, `int8_t`, etc.
#include <cstdio>   // For `printf()`
#include <iostream>  // For `std::cin`, `std::cout`, `std::endl`, etc.
#include <sstream>
#include <string_view>

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    std::string str("Hello ");

    constexpr char c_str[] = "Hey and how are you ";

    std::string_view sv(c_str);

    // 1. Construct a `std::stringstream` from a `std::string`. This is constructor #3 from the link
    // below: reference page for the `std::stringstream` constructors:
    // https://en.cppreference.com/w/cpp/io/basic_stringstream/basic_stringstream
    // - Open in mode `std::ios_base::app` as well in order to **append** all new writes to the end
    //   of the stream! See link above **and**: https://stackoverflow.com/a/8786212/4561887
    std::stringstream ss1(str, std::ios_base::in | std::ios_base::out | std::ios_base::app);
    ss1 << "world.\n";  // since `std::ios_base::app` was used above, this **appends** rather than
                        // **overwrites** the data in the stringstream.
    std::cout << ss1.str();

    // 2. Construct a `std::stringstream` from a `std::string_view`. This is also constructor #3
    // from the link above (passing in a `std::string), but we must first construct a `std::string`
    // from the `std::string_view`. We are using constructor #10 from the `std::string`
    // constructors shown here to create a `std::string` from a `std::string_view`:
    // https://en.cppreference.com/w/cpp/string/basic_string/basic_string
    // - See also the note about the `std::ios_base::app` mode above.
    std::stringstream ss2(std::string(sv),
        std::ios_base::in | std::ios_base::out | std::ios_base::app);
    ss2 << "today?\n";
    std::cout << ss2.str();

    // 3. Construct a `std::stringstream` from a C-string. This is also constructor #3
    // from the link above (passing in a `std::string), but we must first construct a `std::string`
    // from the C-string. We are using constructor #5 from the `std::string`
    // constructors shown here to create a `std::string` from a C-string (`const char*`):
    // https://en.cppreference.com/w/cpp/string/basic_string/basic_string
    // - See also the note about the `std::ios_base::app` mode above. Note that the C-string is
    //   used to automatically, implicitly construct a `std::string` here, I believe.
    std::stringstream ss3(c_str,
        std::ios_base::in | std::ios_base::out | std::ios_base::app);
    ss3 << "doing?\n";
    std::cout << ss3.str();
    // 4. ALTERNATIVE: be explicit in constructing the `std::string` from the C-string
    std::stringstream ss4(std::string(c_str),
        std::ios_base::in | std::ios_base::out | std::ios_base::app);
    ss4 << "feeling?\n";
    std::cout << ss4.str();


    return 0;
}



/*
SAMPLE OUTPUT:

    eRCaGuy_hello_world/cpp$ g++ -Wall -Wextra -Werror -O3 -std=c++17 stringstream_initialize_from_std_string__string_view__and_c_string.cpp -o bin/a && bin/a
    Hello world.
    Hey and how are you today?
    Hey and how are you doing?
    Hey and how are you feeling?

*/
