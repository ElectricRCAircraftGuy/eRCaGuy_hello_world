/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS

Concatenate some strings to make a path to a file.

To compile and run (assuming you've already `cd`ed into this dir):
1. In C++
    mkdir -p bin && g++ -Wall -Wextra -Werror -O3 -std=c++17 -save-temps=obj make_path_to_file.cpp \
    -o bin/make_path_to_file && bin/make_path_to_file

References:
1. https://en.cppreference.com/w/cpp/algorithm/max - where I learned this `std::initializer_list`
   trick.
1. https://en.cppreference.com/w/cpp/utility/initializer_list

*/

// C++ includes
#include <initializer_list>
#include <iostream>  // For `std::cin`, `std::cout`, `std::endl`, etc.

// C includes
#include <cstdint>  // For `uint8_t`, `int8_t`, etc.
#include <cstdio>   // For `printf()`

std::string make_path(std::initializer_list<std::string> str_list)
{
    std::string file_path;
    size_t i = 0;
    for (std::string str : str_list)
    {
        file_path.append(str);

        // Append a "/" between all elements in the list, but do NOT put one after the last element
        if (i < str_list.size() - 1)
        {
            file_path.append("/");
        }

        i++;
    }

    return file_path;
}

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    std::string file_path = make_path({"/dir1", "dir2", "dir3"}); // output: `"/dir1/dir2/dir3"`
    std::cout << file_path << std::endl;

    return 0;
}

/*
SAMPLE OUTPUT:

    eRCaGuy_hello_world/cpp$ mkdir -p bin && g++ -Wall -Wextra -Werror -O3 -std=c++17 -save-temps=obj make_path_to_file.cpp     -o bin/make_path_to_file && bin/make_path_to_file
    /dir1/dir2/dir3


*/
