/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
June 2022

What happens if two `std::string` instances match exactly **except** for their sizes because I
manually resized one, giving it extra null-terminators at the end? Will they fail to match when
compared?
I think they will fail to match since their *sizes* are different. Let's find out!

ANSWER:

Having two `std::string` objects of different sizes DOES cause a problem, causing them NOT to match
even if they differ only in the number of null-terminators at the end! Therefore, I have
demonstrated 3 approaches to solving this:
1. Use `strcmp()` instead. It is fast and efficient.
2. [MOST EFFICIENT!] Use `strncmp()` instead. It is safe, fast and efficient.
3. Resize the expanded-size string down to its `strlen()` using `str1.resize(strlen(str1.c_str()));`
   in order to remove all extraneous null-terminators from it, and *then* do the standard
   `std::string` comparison using the `==` operator!


STATUS: done and works!

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# NB: you may need to use `-std=gnu++17` instead of `-std=c++17` in order to obtain extra GNU
# gcc features, including gcc extensions, POSIX cmds, and Linux sytem cmds.
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# 1. In C++
time g++ -Wall -Wextra -Werror -O3 -std=c++17 string_comparison_between_strings_of_different_sizes.cpp -o bin/a && bin/a
```

References:
1.

*/

// C++ includes
#include <algorithm>
#include <iostream>  // For `std::cin`, `std::cout`, `std::endl`, etc.

// C includes
#include <cassert>
#include <cstdint>  // For `uint8_t`, `int8_t`, etc.
#include <cstdio>   // For `printf()`
#include <cstring>

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Hello ");
    std::cout << "world!\n\n";

    std::string str1 = "hello";
    std::string str2 = "hello";

    std::cout << "str1.size() = " << str1.size() << "\n";
    std::cout << "str2.size() = " << str2.size() << "\n";
    std::cout << "str1 = " << str1 << "\n";
    std::cout << "str2 = " << str2 << "\n";
    std::cout << "\n";
    assert(str1 == str2); // passes!

    str1.resize(100);
    std::cout << "str1.size() = " << str1.size() << "\n";
    std::cout << "str2.size() = " << str2.size() << "\n";
    std::cout << "str1 = " << str1 << "\n";
    std::cout << "str2 = " << str2 << "\n";
    std::cout << "\n";
    // assert(str1 == str2); // FAILS!--since the sizes differ! <============

    // Can I do a C string comparison instead? Try this:
    assert(strcmp(str1.c_str(), str2.c_str()) == 0); // passes! <====== ONE VALID APPROACH TO FIX
                                                     //              IT: DO A C-STRING COMPARISON
    // Even safer: use `strncmp()` to ensure you don't read too far
    assert(strncmp(str1.c_str(), str2.c_str(), std::min(str1.size(), str2.size())) == 0); // <====== BEST: SAFE, AND FASTEST/MOST-EFFICIENT

    // Can I resize the string back to a normal size? Yes!:
    str1.resize(strlen(str1.c_str())); // <========== ANOTHER VALID APPROACH TO FIX IT: RESIZE THE
                                       // TOO-LONG STRING TO BE THE RIGHT SIZE, STRIPPING OFF ALL
                                       // NULL-TERMINATING chars at the end!
    std::cout << "str1.size() = " << str1.size() << "\n";
    std::cout << "str2.size() = " << str2.size() << "\n";
    std::cout << "str1 = " << str1 << "\n";
    std::cout << "str2 = " << str2 << "\n";
    std::cout << "\n";
    assert(str1 == str2); // passes!

    // What if I resize it to a shorter size?
    str1.resize(4);
    std::cout << "str1.size() = " << str1.size() << "\n";
    std::cout << "str2.size() = " << str2.size() << "\n";
    std::cout << "str1 = " << str1 << "\n";
    std::cout << "str2 = " << str2 << "\n";
    std::cout << "\n";
    // assert(str1 == str2); // FAILS!--since I cut part of str1 off at the end <============

    return 0;
}



/*
SAMPLE OUTPUT:

    eRCaGuy_hello_world/cpp$ time g++ -Wall -Wextra -Werror -O3 -std=c++17 string_comparison_between_strings_of_different_sizes.cpp -o bin/a && bin/a

    real    0m0.345s
    user    0m0.300s
    sys 0m0.045s
    Hello world!

    str1.size() = 5
    str2.size() = 5
    str1 = hello
    str2 = hello

    str1.size() = 100
    str2.size() = 5
    str1 = hello
    str2 = hello

    str1.size() = 5
    str2.size() = 5
    str1 = hello
    str2 = hello

    str1.size() = 4
    str2.size() = 5
    str1 = hell
    str2 = hello


*/
