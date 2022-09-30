/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
29 Sept. 2022

Demonstrate variadic templates (parameter packs) and variadic functions in C++.
Ex: demonstrate calling a function within a function, passing whatever arguments (to the outer
function) which the inner functions need!

Main sources: see "References" section below.


STATUS: done and works!
TODO: this demonstrates C++ variadic templates and parameter packs perfectly, but I need to add a
C-style variadic function demo still too! See: https://en.cppreference.com/w/c/variadic

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# NB: you may need to use `-std=gnu++17` instead of `-std=c++17` in order to obtain extra GNU
# gcc features, including gcc extensions, POSIX cmds, and Linux sytem cmds.
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# 1. In C++
time g++ -Wall -Wextra -Werror -O3 -std=c++17 variadic_templates_parameter_packs_and_functions.cpp -o bin/a && bin/a
```

References:
1. [my own answer with this code] https://stackoverflow.com/a/73904874/4561887
1. ***** Variadic templates and parameter packs:
    https://en.cppreference.com/w/cpp/language/parameter_pack:
    > A template with at least one parameter pack is called a _variadic template_.
1. Variadic functions:
    C:   https://en.cppreference.com/w/c/variadic
    C++: https://en.cppreference.com/w/cpp/utility/variadic
1. Something similar in Python using an arguments array:
    Passing functions with arguments to another function in Python?:
    https://stackoverflow.com/a/803632/4561887:
    ```python
    def perform(fun, *args):
        fun(*args)

    def action1(args):
        # something

    def action2(args):
        # something

    perform(action1)
    perform(action2, p)
    perform(action3, p, r)
    ```

*/

// C++ includes
#include <cstdint>  // For `uint8_t`, `int8_t`, etc.
#include <cstdio>   // For `printf()`
#include <iostream>  // For `std::cin`, `std::cout`, `std::endl`, etc.
#include <string>


// -------------------- Some inner functions to choose from START -------------------

void print1(int i)
{
    printf("print1: %i\n", i);
}

void print2(double d, int i)
{
    printf("print2: %f, %i\n", d, i);
}

void print3(int i, double d, const std::string& str)
{
    printf("print3: %i, %f, %s\n", i, d, str.c_str());
}

// -------------------- Some inner functions to choose from END ---------------------

// The outer function, which is a variadic template, containing one `typename...` parameter pack.
// See: https://en.cppreference.com/w/cpp/language/parameter_pack
template<typename FuncType, typename... FuncArgs>
void OuterFunc(FuncType innerFunc, FuncArgs... args)
{
    printf("OuterFunc start.\n");

    // Call the inner function with all passed-in args!
    printf("Calling inner function with all passed-in args.\n");
    // See the "Expansion loci" section of this documentation here:
    // https://en.cppreference.com/w/cpp/language/parameter_pack
    // This is really cool, because calling the inner function like this is **just like the Python
    // example here!**: https://stackoverflow.com/a/803632/4561887--except you pass the arguments
    // to the inner function as `args...` in C++ here instead of as `*args` (the contents of the
    // arguments list) in Python.
    innerFunc(args...);

    printf("OuterFunc end.\n\n");
}

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Demonstrate variadic templates (parameter packs) in C++!\n\n");

    OuterFunc(print1, 100);
    OuterFunc(print2, 99.1234, 77);
    OuterFunc(print3, 123, 10.55, "hey you!");

    return 0;
}



/*
SAMPLE OUTPUT:

    eRCaGuy_hello_world/cpp$ time g++ -Wall -Wextra -Werror -O3 -std=c++17 variadic_templates_parameter_packs_and_functions.cpp -o bin/a && bin/a

    real    0m0.281s
    user    0m0.245s
    sys 0m0.036s
    Demonstrate variadic templates (parameter packs) in C++!

    OuterFunc start.
    Calling inner function with all passed-in args.
    print1: 100
    OuterFunc end.

    OuterFunc start.
    Calling inner function with all passed-in args.
    print2: 99.123400, 77
    OuterFunc end.

    OuterFunc start.
    Calling inner function with all passed-in args.
    print3: 123, 10.550000, hey you!
    OuterFunc end.


*/
