/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
June 2022

Learn how to construct `std::experimental::filesystem::path::path`s.

STATUS: (status)

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# NB: you may need to use `-std=gnu++17` instead of `-std=c++17` in order to obtain extra GNU
# gcc features, including gcc extensions, POSIX cmds, and Linux sytem cmds.
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# 1. In C++
time g++ -Wall -Wextra -Werror -O3 -std=c++17 std_experimental_filesystem_path__demo.cpp -o bin/a -lstdc++fs && bin/a
```

IMPORTANT: if you see this linker error:
    ```
    /tmp/ccfHRXrJ.o: In function `main':
    std_experimental_filesystem_path__demo.cpp:(.text.startup+0x9c): undefined reference to `std::experimental::filesystem::v1::__cxx11::path::_M_split_cmpts()'
    collect2: error: ld returned 1 exit status
    ```
...it's because you forgot to link to the library with `-lstdc++fs` above! Add that to your build
   flags! See: https://stackoverflow.com/a/33159746/4561887

References:
1. https://en.cppreference.com/w/cpp/experimental/fs
    1. https://en.cppreference.com/w/cpp/experimental/fs/path/path
1. https://stackoverflow.com/a/33159746/4561887 - use `-lstdc++fs` in your build arguments to link

*/

// C & C++ includes
#include <cstdint>  // For `uint8_t`, `int8_t`, etc.
#include <cstdio>   // For `printf()`
#include <experimental/filesystem>
#include <iostream>  // For `std::cin`, `std::cout`, `std::endl`, etc.

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Hello ");
    std::cout << "world!\n\n";

    // Error:
    //      /tmp/ccfHRXrJ.o: In function `main':
    //      std_experimental_filesystem_path__demo.cpp:(.text.startup+0x9c): undefined reference to `std::experimental::filesystem::v1::__cxx11::path::_M_split_cmpts()'
    //      collect2: error: ld returned 1 exit status
    // std::experimental::filesystem::path path1 = "json/single_include";

    // Error: same as above
    // std::experimental::filesystem::path path1 = std::string("json/single_include");

    // Error: same as above
    // std::experimental::filesystem::path path1("json/single_include");

    // Error: same as above
    // std::experimental::filesystem::path path1{"json/single_include"};

    // Error: same as above
    // std::string path_prefix = "json/single_include";
    // std::experimental::filesystem::path path1 = path_prefix;

    std::string path_prefix{"json/single_include"};
    std::experimental::filesystem::path path1 = path_prefix;

    std::cout << "path1 = " << path1 << "\n";


    return 0;
}



/*
SAMPLE OUTPUT:

    eRCaGuy_hello_world/cpp$ g++ -Wall -Wextra -Werror -O3 -std=c++17 std_experimental_filesystem_path__demo.cpp -o bin/a && bin/a
    Hello world!

*/
