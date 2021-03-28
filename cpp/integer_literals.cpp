/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

Mar. 2021

integer_literals
- examine these weird ways to write integers as of C++14:
        30000
        30'000
        3'0'0'0'0
        etc.

To compile and run (assuming you've already `cd`ed into this dir):
    mkdir -p bin && g++ -Wall -Wextra -Werror -ggdb -std=c++17 -o bin/integer_literals \
    integer_literals.cpp && bin/integer_literals


References:
1. https://en.cppreference.com/w/cpp/language/integer_literal
    Ex: see these examples from there:
    """
        Example. The following variables are also initialized to the same value:
        ```
        unsigned long long l1 = 18446744073709550592ull; // C++11
        unsigned long long l2 = 18'446'744'073'709'550'592llu; // C++14
        unsigned long long l3 = 1844'6744'0737'0955'0592uLL; // C++14
        unsigned long long l4 = 184467'440737'0'95505'92LLU; // C++14
        ```
    """

*/

#include <cstdint>
#include <cstdio>
#include <iostream>

/// Return true if they are equal, and false otherwise
template <typename T>
bool expect_eq(T a, T b)
{
    bool are_equal = a == b;

    if (are_equal)
    {
        std::cout << "Equal! a == b\n"
            "  a is " << a << "\n"
            "  b is " << b << std::endl;
    }
    else
    {
        std::cout << "NOT EQUAL! a and b are not equal!\n"
            "  a is " << a << "\n"
            "  b is " << b << std::endl;
    }

    return are_equal;
}

int main()
{
    printf("C++14 integer literals demo. Single quotes (') can arbitrarily\n"
           "be added anywhere you want in an integer as of C++14. This allows,\n"
           "for instance, you to easily mark every 3 or whatever places, to more\n"
           "easily keep track of large numbers. Ex: `30000`, `30'000`, and `3'0'0'0'0`\n"
           "are all equal.\n\n");

    uint32_t u1 = 30000;
    uint32_t u2 = 30'000;
    uint32_t u3 = 3'0'0'0'0;
    uint32_t u4 = 300'00;

    uint32_t u5 = 300'01;

    expect_eq(u1, u2); // equal
    expect_eq(u1, u3); // equal
    expect_eq(u1, u4); // equal
    expect_eq(u4, u5); // NOT equal

    return 0;
}

/*
SAMPLE OUTPUT:

    $ mkdir -p bin && g++ -Wall -Wextra -Werror -ggdb -std=c++17 -o bin/integer_literals     integer_literals.cpp && bin/integer_literals
    C++14 integer literals demo. Single quotes (') can arbitrarily
    be added anywhere you want in an integer as of C++14. This allows,
    for instance, you to easily mark every 3 or whatever places, to more
    easily keep track of large numbers. Ex: `30000`, `30'000`, and `3'0'0'0'0`
    are all equal.

    Equal! a == b
      a is 30000
      b is 30000
    Equal! a == b
      a is 30000
      b is 30000
    Equal! a == b
      a is 30000
      b is 30000
    NOT EQUAL! a and b are not equal!
      a is 30000
      b is 30001

*/
