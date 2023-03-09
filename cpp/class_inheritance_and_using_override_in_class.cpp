/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
12 Jan. 2022

Learn how to bring in members (variables or functions) from a parent class into a child class using
the `using` keyword. Also brush up on class inheritance and run-time polymorphism.

STATUS: NOT YET FUNCTIONAL YET! THIS IS A WORK-IN-PROGRESS.

To compile and run (assuming you've already `cd`ed into this dir):
1. In C++
    mkdir -p bin && g++ -Wall -Wextra -Werror -O3 -std=c++17 -save-temps=obj class_inheritance_and_using_override_in_class.cpp \
    -o bin/class_inheritance_and_using_override_in_class.cpp && bin/class_inheritance_and_using_override_in_class.cpp

References:
1. https://en.cppreference.com/w/cpp/language/using_declaration
    """
    If the derived class already has a member with the same name, parameter list, and
    qualifications, the derived class member hides or overrides (doesn't conflict with) the member
    that is introduced from the base class.
    """
1. https://www.geeksforgeeks.org/polymorphism-in-c/
1. *****+ EXCELLENT EXAMPLE HERE!: https://www.tutorialspoint.com/cplusplus/cpp_polymorphism.htm

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

    void func3()
    {
        printf("Parent func3()\n");
        func2();
    }
};

class Child : public Parent
{
public:
    void func(uint8_t num) override
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


    GrandParent * grandParent_p;

    // Grandparent
    printf("GRANDPARENT:\n");

    u1 = 8;
    GrandParent grandParent1;
    grandParent_p = &grandParent1;
    grandParent1.func(u1);
    grandParent1.func2();
    printf("--------\n");
    grandParent_p->func(u1);
    grandParent_p->func2();
    // grandParent_p->func3();
    printf("\n\n");


    // Parent
    printf("PARENT:\n");

    u1 = 7;
    Parent parent1;
    grandParent_p = &parent1;
    parent1.func(u1);
    parent1.func3();
    printf("--------\n");
    grandParent_p->func(u1);
    // THIS CALL HERE IS a **great** example of run-time (late binding) polymorphism!
    // --which occurs via the C++ run-time "vtable" (virtual table).
    //
    // EXPLANATION: `grandParent_p` is a pointer to the most-base (or highest up, depending on how
    // you think about it) class, since it is of type `GrandParent*`. However, it currently points
    // to a `Parent` type. So, when you call `func2()`, it first tries to see if a `func2()`
    // function exists in the type it points to, which is `Parent`. `func2()` does NOT exist in that
    // class, so it moves up one level **at run-time** to check the next class up, which is the
    // `GrandParent` class. `func2()` exists there, so it calls `GrandParent::func2()`. That
    // function calls `func(10)`. This is where it gets crazy! Even though there is a
    // `GrandParent::func()` it could call, **it calls the `Parent::func()`, which is down one
    // level, instead! This is because the pointer points to a `Parent` object, so it always tries
    // to call the lowest-level first before moving up to a higher level in the inheritance
    // hierarchy.
    grandParent_p->func2();
    // grandParent_p->func3();
    printf("\n\n");


    // Child
    printf("CHILD:\n");

    u1 = 6;
    Child child1;
    grandParent_p = &child1;
    child1.func(u1);
    printf("--------\n");
    grandParent_p->func(u1);
    // THIS CALL HERE IS a **great** example of run-time (late binding) polymorphism! See explanation
    // above.
    grandParent_p->func2();
    // grandParent_p->func3();
    printf("\n\n");


    return 0;
}

/*
==============
SAMPLE OUTPUT:
==============

eRCaGuy_hello_world/cpp$ mkdir -p bin && g++ -Wall -Wextra -Werror -O3 -std=c++17 -save-temps=obj class_inheritance_and_using_override_in_class.cpp     -o bin/class_inheritance_and_using_override_in_class.cpp && bin/class_inheritance_and_using_override_in_class.cpp
Start

GrandParent func(): num = 8
GrandParent func2()
GrandParent func(): num = 10
--------
GrandParent func(): num = 8
GrandParent func2()
GrandParent func(): num = 10


Parent func(): num = 7
--------
Parent func(): num = 7
GrandParent func2()
Parent func(): num = 10


Child func(): num = 6
--------
Child func(): num = 6
GrandParent func2()
Child func(): num = 10



*/
