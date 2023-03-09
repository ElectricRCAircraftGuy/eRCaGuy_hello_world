///usr/bin/env ccache g++ -Wall -Wextra -Werror -O3 -std=gnu++17 "$0" -o /tmp/a && /tmp/a "$@"; exit
// For the line just above, see my answer here: https://stackoverflow.com/a/75491834/4561887

/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
9 Mar. 2023

Practice using constructors in a child class which call constructors in a parent class.
This file is a continuation
of "class_inheritance_constructors_and_initialization_of_derived_classes.cpp"!

My content herein will be modified and originally learned from Alex's content, here:
https://www.learncpp.com/cpp-tutorial/constructors-and-initialization-of-derived-classes/

STATUS: done and works! GREAT DEMO

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# NB: you may need to use `-std=gnu++17` instead of `-std=c++17` in order to obtain extra GNU
# gcc features, including gcc extensions, POSIX cmds, and Linux sytem cmds.
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# [run once ever] install ccache
sudo apt update && sudo apt install ccache

# 1. In C++ (General format)
time g++ -Wall -Wextra -Werror -O3 -std=gnu++17 hello_world_extra_basic.cpp -o bin/a && bin/a
```

References:
1. *****+ https://www.learncpp.com/cpp-tutorial/constructors-and-initialization-of-derived-classes/

*/

// C++ includes
#include <iostream>  // For `std::cin`, `std::cout`, `std::endl`, etc.

// C includes
// None

class A
{
public:
    // constructor
    A(int a)
    {
        std::cout << "A: " << a << '\n';
    }
};

class B: public A
{
public:
    // constructor
    B(int a, double b)
    : A{a}
    {
        std::cout << "B: " << b << '\n';
    }
};

class C: public B
{
public:
    // constructor
    C(int a, double b, char c)
    : B{a, b}
    {
        std::cout << "C: " << c << '\n';
    }
};


int main()
{
    C c{5, 4.3, 'R'};

    return 0;
}



/*
SAMPLE OUTPUT:

    eRCaGuy_hello_world$ cpp/class_inheritance_chains_GREAT.cpp
    A: 5
    B: 4.3
    C: R

*/
