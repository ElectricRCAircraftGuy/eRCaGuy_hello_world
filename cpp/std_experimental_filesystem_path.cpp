/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
June 2022

Learn how to construct and concatenate `std::experimental::filesystem::path::path`s.

STATUS: done and works!

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# NB: you may need to use `-std=gnu++17` instead of `-std=c++17` in order to obtain extra GNU
# gcc features, including gcc extensions, POSIX cmds, and Linux sytem cmds.
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# 1. In C++
time g++ -Wall -Wextra -Werror -O3 -std=c++17 std_experimental_filesystem_path.cpp -o bin/a -lstdc++fs && bin/a
```

IMPORTANT: if you see this linker error:
    ```
    /tmp/ccfHRXrJ.o: In function `main':
    std_experimental_filesystem_path.cpp:(.text.startup+0x9c): undefined reference to `std::experimental::filesystem::v1::__cxx11::path::_M_split_cmpts()'
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

    std::experimental::filesystem::path path1 = "json/single_include";
    std::experimental::filesystem::path path2 = std::string("json/single_include");
    std::experimental::filesystem::path path3("json/single_include");
    std::experimental::filesystem::path path4{"json/single_include"};

    std::string path_prefix1 = "json/single_include";
    std::experimental::filesystem::path path5 = path_prefix1;

    std::string path_prefix2{"json/single_include"};
    std::experimental::filesystem::path path6 = path_prefix2;


    std::cout << "path1 = " << path1 << "\n";
    std::cout << "path2 = " << path2 << "\n";
    std::cout << "path3 = " << path3 << "\n";
    std::cout << "path4 = " << path4 << "\n";
    std::cout << "path5 = " << path5 << "\n";
    std::cout << "path6 = " << path6 << "\n";


    // Now append a string to a path using the path class member `operator/=()`. See:
    // https://en.cppreference.com/w/cpp/experimental/fs/path/append
    path1 /= "nlohmann";
    std::cout << "path1 = " << path1 << "\n";

    // Now append a string to a path using the non-member function `operator/()`. See:
    // https://en.cppreference.com/w/cpp/experimental/fs/path/operator_slash
    path1 = path1 / "test";
    std::cout << "path1 = " << path1 << "\n";


    return 0;
}



/*
SAMPLE OUTPUT:

    eRCaGuy_hello_world/cpp$ time g++ -Wall -Wextra -Werror -O3 -std=c++17 std_experimental_filesystem_path.cpp -o bin/a -lstdc++fs && bin/a

    real    0m0.672s
    user    0m0.619s
    sys 0m0.053s
    Hello world!

    path1 = "json/single_include"
    path2 = "json/single_include"
    path3 = "json/single_include"
    path4 = "json/single_include"
    path5 = "json/single_include"
    path6 = "json/single_include"
    path1 = "json/single_include/nlohmann"
    path1 = "json/single_include/nlohmann/test"


*/
