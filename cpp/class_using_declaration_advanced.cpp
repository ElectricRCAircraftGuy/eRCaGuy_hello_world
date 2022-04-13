/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
Jan. 2022

Demo to show the `using` declaration and how it affects overloaded functions which are overloaded in
classes through inheritance.

See some of this code online in an older version of the cppreference.com wiki:
https://en.cppreference.com/mwiki/index.php?title=cpp/language/using_declaration&oldid=137409

STATUS: done!
Result: various `using` declarations in the child (derived) class below expose various declarations
in the parent (base) class. However, as explained in the comments, some of the `using` declarations
in the child are useless and don't actually do anything.

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# NB: you may need to use `-std=gnu++17` instead of `-std=c++17` in order to obtain extra GNU
# gcc features, including gcc extensions, POSIX cmds, and Linux sytem cmds.
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# 1. In C++
g++ -Wall -Wextra -Werror -O3 -std=c++17 class_using_declaration_advanced.cpp -o bin/a && bin/a
```

References:
1. https://en.cppreference.com/w/cpp/language/using_declaration
    1. SEE MY VERSION HERE (which has since been reverted on the cppreference.com wiki):
       https://en.cppreference.com/mwiki/index.php?title=cpp/language/using_declaration&oldid=137409
1. this example below
1. Kilian Leport's example:
    1. http://coliru.stacked-crooked.com/a/60d65a3be033acc3
    1. See it in "class_using_declaration_basic__expose_shadowed_parent_foo_in_child.cpp"
        1. *****+ "class_using_declaration_basic__expose_shadowed_parent_foo_in_child.cpp" - a
        really **really simple** example to clearly show how the `using` directive can be used
        to **expose in a child class any parent/child overloaded functions which are in the parent
        class and _not already exposed_ by the child class**.

*/


#include <iostream>

// **Base** (parent) class B
struct B {
    virtual void f(int) { std::cout << "B::f\n"; }
    void g(char)        { std::cout << "B::g(char)\n"; }
    void h(int)         { std::cout << "B::h\n"; }
 protected:
    int m; // B::m is protected
    typedef int value_type;
};

// **Derived** (child) class D
struct D : B {
    using B::m; // D::m is public
    using B::value_type; // D::value_type is public

    // UNnecessary usage of `using`; `B::f` is already public and also publicly
    // available as `D::f`, and `D::f` below has the same signature as `B::f`
    // above.
    using B::f;
    void f(int) { std::cout << "D::f\n"; } // D::f(int) **overrides** B::f(int)

    // NECESSARY usage of `using`; `B::g(char)` gets hidden by `D::g(int)`
    // unless it is explicitly exposed as `D::g(char)` here with `using B::g`.
    // WithOUT this usage of `using B::g`, a char passed to a call of
    // `D::g(char)` would get implicitly cast to `int`, resulting in a call to
    // the `D::g(int)` function defined just below instead!
    using B::g; // exposes `B::g(char)` as `D::g(char)`, which is a completely
                // different function from `D::g(int)` defined next.
    void g(int) { std::cout << "D::g(int)\n"; } // both g(int) and g(char) are
                                                // visible as members of D

    // UNnecessary usage of `using`; `B::h` is already public and also publicly available as `D::h`
    // at this point. Since `D::h` below, however, has the same signature as `B::h`, it **hides**
    // the `B::h` function above!
    using B::h;
    void h(int) { std::cout << "D::h\n"; } // D::h(int) **hides** B::h(int)
};

int main()
{
    D d;
    B& b = d;

//    b.m = 2; // error, B::m is protected
    d.m = 1;  // protected B::m is accessible as public D::m

    b.f(1);   // calls derived f()
    d.f(1);   // calls derived f()
    std::cout << "----------\n";

    d.g(1);   // calls derived g(int)
    d.g('a'); // calls base g(char), which was exposed **only because** of the
              // `using B::g;` usage in the derived class.
    std::cout << "----------\n";

    b.h(1);   // calls base h()
    d.h(1);   // calls derived h()
}


/*
SAMPLE OUTPUT:

    eRCaGuy_hello_world/cpp$ g++ -Wall -Wextra -Werror -O3 -std=c++17 class_using_declaration_advanced.cpp -o bin/a && bin/a
    D::f
    D::f
    ----------
    D::g(int)
    B::g(char)
    ----------
    B::h
    D::h

*/
