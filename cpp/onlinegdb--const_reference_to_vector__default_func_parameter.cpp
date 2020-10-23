
// This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

GS
22 Oct. 2020

const_reference_to_vector__default_func_parameter.cpp

Practice having a default const reference to a vector as an input parameter
to a function!

References:
1. https://en.cppreference.com/w/cpp/container/vector
2. https://en.cppreference.com/w/cpp/utility/pair

Shared Link:
https://onlinegdb.com/HJqOs0JOv

Build and run command:

    g++ -Wall -Wextra -Werror -ggdb -std=c++17 -o ./bin/tmp \
    onlinegdb--const_reference_to_vector__default_func_parameter.cpp && ./bin/tmp

*******************************************************************************/

#include <cstdio>
#include <iostream>
#include <string>
#include <utility> // std::pair
#include <vector>

void MyFunc(const std::vector<std::pair<std::string, std::string>>&
    keyValueVector = std::vector<std::pair<std::string, std::string>>())
{
    if (keyValueVector.empty())
    {
        printf("Using the default empty vector input param.\n");
    }
    else
    {
        // print whatever the user passed in
        printf("Printing the user-input vector.\n");
        for (std::pair<std::string, std::string> pair : keyValueVector)
        {
            std::cout << pair.first << ": " << pair.second << std::endl;
        }
    }
    printf("\n");
}

int main()
{
    printf("Hello World\n\n");

    MyFunc();

    // Vector of key/value type pairs.
    std::vector<std::pair<std::string, std::string>> myKeyValues =
    {
        std::pair<std::string, std::string>("apples", "5 times"),
        std::pair<std::string, std::string>("bananas", "10 slices"),
        std::pair<std::string, std::string>("peaches", "7 cups"),
        std::pair<std::string, std::string>("pineapples", "200 grams"),
    };

    MyFunc(myKeyValues);

    return 0;
}


