/*

This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

Gabriel Staples
9 Apr. 2021

check_empty_func_addresses.cpp
- Prove that gcc `weak` functions have a nil (zero) address if they are not defined! This is how
Arduino implements the weak and strong `serialEvent()` functions and calls to that function! Very
ingenious! 
- See my answer here for details and links to the Arduino source code of interest:
https://stackoverflow.com/a/67016917/4561887

To compile and run:
    mkdir -p bin && g++ -Wall -Werror -Wextra -ggdb -std=c++17 -o bin/check_empty_func_addresses \
    check_empty_func_addresses.cpp && bin/check_empty_func_addresses

References:
1. My answer: https://stackoverflow.com/a/67016917/4561887

*/

// C includes
#include <stdio.h>

// C++ includes
#include <iostream>

// using namespace std;

int get2()
{
    return 2;
}

int get3()
{
    return 3;
}

// Func definition
void doNothing1() {};

// Func declarations ONLY, NOT definitions
void doNothing2() __attribute__((weak));
void doNothing3() __attribute__((weak));
void doNothing4() __attribute__((weak));

// Strong func definition for the weak prototype (declaration) above
void doNothing4() {};

/// Check to see if a function address is zero
void checkForNilFuncAddress(const char* func_string, uint64_t func_addr) 
{
    if (func_addr)
    {
        printf("%s = 0x%lx\n", func_string, func_addr);
    }
    else
    {
        printf("%s = 0x%lx (nil, or zero)\n", func_string, func_addr);
    }
}

int main()
{
    // C-style print
    printf("Hello World1\n");
    // C++-style print
    std::cout << "Hello world2" << std::endl;
    std::cout << "\n";

    printf("&get2 = %p\n"
           "&get3 = %p\n"
           "&doNothing1 = %p\n"
           "&doNothing2 = %p\n"
           "&doNothing3 = %p\n"
           "&doNothing4 = %p\n\n",
           &get2,
           &get3,
           &doNothing1,
           &doNothing2,
           &doNothing3,
           &doNothing4);

    checkForNilFuncAddress("&get2", (uint64_t)&get2);
    checkForNilFuncAddress("&get3", (uint64_t)&get3);
    checkForNilFuncAddress("&doNothing1", (uint64_t)&doNothing1);
    checkForNilFuncAddress("&doNothing2", (uint64_t)&doNothing2);
    checkForNilFuncAddress("&doNothing3", (uint64_t)&doNothing3);
    checkForNilFuncAddress("&doNothing4", (uint64_t)&doNothing4);

    return 0;
}

/*
Sample Output:

    eRCaGuy_hello_world/cpp$ mkdir -p bin && g++ -Wall -Werror -Wextra -ggdb -std=c++17 -o bin/check_empty_func_addresses     check_empty_func_addresses.cpp && bin/check_empty_func_addresses
    Hello World1
    Hello world2

    &get2 = 0x5653b20819da
    &get3 = 0x5653b20819e5
    &doNothing1 = 0x5653b20819f0
    &doNothing2 = (nil)
    &doNothing3 = (nil)
    &doNothing4 = 0x5653b20819f7

    &get2 = 0x5653b20819da
    &get3 = 0x5653b20819e5
    &doNothing1 = 0x5653b20819f0
    &doNothing2 = 0x0 (nil, or zero)
    &doNothing3 = 0x0 (nil, or zero)
    &doNothing4 = 0x5653b20819f7

*/
