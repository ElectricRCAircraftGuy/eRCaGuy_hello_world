/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

Gabriel Staples
www.GabrielStaples.com
www.ElectricRCAircraftGuy.com
14 Jan. 2021

See how default arguments can or must be used in C++.

To compile and run:
    g++ -Wall -Werror -ggdb -std=c++17 -o bin/onlinegdb--cpp_default_args_practice \
    onlinegdb--cpp_default_args_practice.cpp && bin/onlinegdb--cpp_default_args_practice

Share link: https://onlinegdb.com/pgHhr19j1

*******************************************************************************/
#include <inttypes.h>
#include <stdio.h>

uint32_t getInt()
{
    return 45;
}

uint32_t foo1(uint32_t numIn = 32)
{
    return numIn;
}

uint32_t foo2(uint32_t numIn = foo1())
{
    return numIn;
}

struct S
{
    uint32_t num = 99;
};

// Does NOT work!:
// ```
// main.cpp:37:37: error: local variable ‘s’ may not appear in this context
//  uint32_t foo3(S s, uint32_t numIn = s.num)
//                                      ^
// ```
// uint32_t foo3(S s, uint32_t numIn = s.num)
// {
//     return numIn;
// }

uint32_t foo3(S s, uint32_t numIn = 61)
{
    return numIn + s.num;
}

int main()
{
    printf("Hello World\n");

    printf("%u\n", getInt()); // 45
    printf("%u\n", foo1());   // 32
    printf("%u\n", foo1(10)); // 10
    printf("%u\n", foo2());   // 32
    printf("%u\n", foo2(10)); // 10
    printf("%u\n", foo3({})); // 160 when using the 2nd `foo3()` above; won't compile when using
                              // the 1st `foo3()` above

    return 0;
}

/*
SAMPLE OUTPUT:

    eRCaGuy_hello_world/cpp$ g++ -Wall -Werror -ggdb -std=c++17 -o bin/onlinegdb--cpp_default_args_practice \
    onlinegdb--cpp_default_args_practice.cpp && bin/onlinegdb--cpp_default_args_practice
    Hello World
    45
    32
    10
    32
    10
    160

*/
