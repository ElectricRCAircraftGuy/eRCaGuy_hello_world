/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
Sept. 2022

Demonstrate the weird `T()` "default constructors" on various types in C++,
including even basic types like integers! You'll see this super weird
default-constructor syntax on cppreference.com all over the place, such as
here: https://en.cppreference.com/w/cpp/container/vector/vector:

```cpp
explicit vector( size_type count,
                 const T& value = T(),  // <===== notice the `T()`!
                 const Allocator& alloc = Allocator());
```

While I'm at it, show other initialization syntaxes too, such as brace initialization of integers and other types.

Examples:
```
int i2{77};
# or
int i2 = int{77};
# or
int i2 = int(77);
```

See also: https://en.cppreference.com/w/cpp/language/zero_initialization. "Zero
initialization" is not really a concept in C++, but it has a reference page
because some other types of initialization, such as "value initialization", may
initialize values to zero.  Here is a quote from the link above: _"Note that
this is not the syntax for zero-initialization, which does not have a dedicated
syntax in the language. These are examples of other types of initializations,
which might perform zero-initialization."_


STATUS: wip

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# NB: you may need to use `-std=gnu++17` instead of `-std=c++17` in order to obtain extra GNU
# gcc features, including gcc extensions, POSIX cmds, and Linux sytem cmds.
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# 1. In C++
time g++ -Wall -Wextra -Werror -O3 -std=c++17 constructor__default_integer_constructors.cpp -o bin/a && bin/a
```

References:
1. https://en.cppreference.com/w/cpp/container/vector/vector
1.

*/

// C++ includes
#include <iostream>  // For `std::cin`, `std::cout`, `std::endl`, etc.

// C includes
#include <cstdint>  // For `uint8_t`, `int8_t`, etc.
#include <cstdio>   // For `printf()`

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Default ");
    std::cout << "constructors:\n\n";

    // These are all the same thing: initializing an int to 0
    int i1 = int(); // 0
    int i5 = int{}; ////////////////
    int i2{};       // 0
    int i3();       // incorrect integer initialization: this is actually a
                    // function declaration of function `i2()` which accepts
                    // `void` and returns `int`.

    std::cout << "i1 = " << i1 << "\n";
    std::cout << "i5 = " << i5 << "\n"; ///////////////
    std::cout << "i2 = " << i2 << "\n\n";
    // Can't print `i3` like this, since it's a function address, not an `int`.
    //     error: the address of ‘int i3()’ will never be NULL [-Werror=address]
    // std::cout << i3 << "\n";

    // These are all the same thing: initializing an int to 0
    int i10 = 0;        // 0
    int i11 = int();    // 0
    int i12 = int(0);   // 0
    int i13{};          // 0
    int i14{0};         // 0
    std::cout << "i10 = " << i10 << "\n";
    std::cout << "i11 = " << i11 << "\n";
    std::cout << "i12 = " << i12 << "\n";
    std::cout << "i13 = " << i13 << "\n";
    std::cout << "i14 = " << i14 << "\n\n";

    // These are all the same thing: initializing an int to 99
    int i20 = 99;        // 99
    int i21 = int(99);   // 99
    int i22{99};         // 99
    std::cout << "i20 = " << i20 << "\n";
    std::cout << "i21 = " << i21 << "\n";
    std::cout << "i22 = " << i22 << "\n\n";

    // A few more random examples, to show it works with other types too

    // Set all uint64_t types to 77
    uint64_t u1 = 77;
    uint64_t u2 = uint64_t(77);
    uint64_t u3{77};
    std::cout << "u1 = " << u1 << "\n";
    std::cout << "u2 = " << u2 << "\n";
    std::cout << "u3 = " << u3 << "\n\n";

    // double d1{0.1234}; ////////////



    return 0;
}



/*
SAMPLE OUTPUT:

    eRCaGuy_hello_world/cpp$ time g++ -Wall -Wextra -Werror -O3 -std=c++17 constructor__default_integer_constructors.cpp -o bin/a && bin/a

    real    0m2.079s
    user    0m0.775s
    sys 0m0.087s
    Hello world!

*/
