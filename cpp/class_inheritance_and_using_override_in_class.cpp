/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
12 Jan. 2022

Learn how to bring in members (variables or functions) from a parent class into a child class using
the `using` keyword. Also brush up on class inheritance and run-time polymorphism.

STATUS: NOT YET FUNCTIONAL YET! THIS IS A WORK-IN-PROGRESS.

To compile and run (assuming you've already `cd`ed into this dir):
1. In C++
    mkdir -p bin && g++ -Wall -Wextra -Werror -O3 -std=c++17 -save-temps=obj class_inheritance_and_using_override_in_class.cpp.cpp \
    -o bin/class_inheritance_and_using_override_in_class.cpp && bin/class_inheritance_and_using_override_in_class.cpp

References:
1. https://en.cppreference.com/w/cpp/language/using_declaration
    """
    If the derived class already has a member with the same name, parameter list, and
    qualifications, the derived class member hides or overrides (doesn't conflict with) the member
    that is introduced from the base class.
    """
1. https://www.geeksforgeeks.org/polymorphism-in-c/

*/

// C++ includes
#include <iostream>  // For `std::cin`, `std::cout`, `std::endl`, etc.

// C includes
#include <cstdint>  // For `uint8_t`, `int8_t`, etc.
#include <cstdio>   // For `printf()`

class GrandParent
{
public:
    virtual void func(uint8_t num)
    {
        printf("GrandParent func(): num = %u\n", num);
    }

    void func2()
    {
        printf("GrandParent func2()\n");
        func(10);
    }
};

class Parent : public GrandParent
{
public:
    void func(uint8_t num) override
    {
        printf("Parent func(): num = %u\n", num);
    }
};

class Child : public Parent
{
public:
    void func(uint8_t num)
    {
        printf("Child func(): num = %u\n", num);
    }
};


// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Start\n");
    printf("\n");

    uint8_t u1;

    // Grandparent
    u1 = 8;
    GrandParent grandParent1;
    grandParent1.func(u1);
    grandParent1.func2();
    printf("\n");

    // Parent
    u1 = 7;
    Parent parent1;
    parent1.func(u1);
    printf("\n");

    // Child
    u1 = 6;
    Child child1;
    child1.func(u1);
    printf("\n");


    return 0;
}

/*
SAMPLE OUTPUT:

In C++:

    eRCaGuy_hello_world/cpp$ mkdir -p bin && g++ -Wall -Wextra -Werror -O3 -std=c++17 -save-temps=obj class_inheritance_and_using_override_in_class.cpp.cpp \
    >     -o bin/class_inheritance_and_using_override_in_class.cpp && bin/class_inheritance_and_using_override_in_class.cpp
    This is the start of `main()`.
      Hello world.
    This is the end of `main()`.
    the static_assert passed

*/
