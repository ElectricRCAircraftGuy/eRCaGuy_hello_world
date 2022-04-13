/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
Jan. 2022

Learn how the "using declaration" affects your ability to inherit functions from parent classes when
there exists class inheritance and parent-child class relationships.

Summary of results and learning objectives:
vvvvvvvvvvvvvvvvvvvvvvvv
Putting `using Parent::foo;` in the child class **exposes** that function prototype from the parent
class, when otherwise the parent class's version of `void foo(int)` would be "shadowed" and
hidden/blocked by the child's version of `void foo(std::string)`, since it has the same name `foo`!
^^^^^^^^^^^^^^^^^^^^^^^^

This code example is adapted from Kilian Leport's example code, here:
http://coliru.stacked-crooked.com/a/60d65a3be033acc3

STATUS: done!

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# NB: you may need to use `-std=gnu++17` instead of `-std=c++17` in order to obtain extra GNU
# gcc features, including gcc extensions, POSIX cmds, and Linux sytem cmds.
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# 1. In C++
g++ -Wall -Wextra -Werror -O3 -std=c++17 class_using_declaration_basic__expose_shadowed_parent_foo_in_child.cpp -o bin/a && bin/a
```

References:
1. https://en.cppreference.com/w/cpp/language/using_declaration
1.

*/



// What is this `<bits/stdc++.h>` header file? It turns out it is a gcc "include all headers" header
// file. See:
// 1. https://www.geeksforgeeks.org/bitsstdc-h-c/
// 1. https://stackoverflow.com/questions/25311011/how-does-include-bits-stdc-h-work-in-c/33764128#33764128
// #include <bits/stdc++.h>

#include <iostream>

// Other common `using` declarations to automatically include:
// using namespace std;
// using namespace std::chrono;

struct Parent
{
    /// function that accepts `int` as an argument
    void foo(int)
    {
        std::cout << "foo from parent\n";
    }
};

struct Child : Parent
{
    /// function that accepts `std::string` as an argument
    void foo(std::string)
    {
        std::cout << "foo from child\n";
    }

    // uncomment to expose foo from parent <==========
    using Parent::foo;
};


int main(int argc, char *argv[])
{
    (void)argc; // ignore this input variable
    (void)argv; // ignore this input variable


    Child c;
    c.foo("a string");

    // Calling this requires that you have uncommented `using Parent::foo;` above! <==========
    // Otherwise, the only exposed `foo()` function prototype is `void foo(std::string)`, and there
    // is no known conversion from `int` 13 to `std::string`!
    //
    // Example error:
    //      class_using_declaration_basic__expose_shadowed_parent_foo_in_child.cpp: In function ‘int main(int, char**)’:
    //      class_using_declaration_basic__expose_shadowed_parent_foo_in_child.cpp:74:13: error: no matching function for call to ‘Child::foo(int)’
    //           c.foo(13);
    //                   ^
    //      class_using_declaration_basic__expose_shadowed_parent_foo_in_child.cpp:54:10: note: candidate: ‘void Child::foo(std::__cxx11::string)’
    //           void foo(std::string)
    //                ^~~
    //      class_using_declaration_basic__expose_shadowed_parent_foo_in_child.cpp:54:10: note:   no known conversion for argument 1 from ‘int’ to ‘std::__cxx11::string’ {aka ‘std::__cxx11::basic_string<char>’}
    c.foo(13);

    return 0;
}


/*
SAMPLE OUTPUT:

    eRCaGuy_hello_world/cpp$ g++ -Wall -Wextra -Werror -O3 -std=c++17 class_using_declaration_basic__expose_shadowed_parent_foo_in_child.cpp -o bin/a && bin/a
    foo from child
    foo from parent


*/
