/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
Sept. 2022

Main references:
1. What does `int()` do in C++? - https://stackoverflow.com/q/17131911/4561887
1. [my question] What is a call to `char()`, `uint8_t()`, `int64_t()`, integer `T()`, etc, as a
   function in C++? - https://stackoverflow.com/q/72367123/4561887
---
1. https://en.cppreference.com/w/cpp/language/value_initialization - using a
   constructor (for classes) or constructor-like initialization (for integers or
   floating point numbers) via `()` or `{}`.
1. https://en.cppreference.com/w/cpp/language/zero_initialization - not a
   dedicated type of initialization in C++; colloquially includes any other type
   of initialization which initializes to zero, such as a value initialization
   via `()` or `{}`, with no value specified.
1. https://en.cppreference.com/w/cpp/language/default_constructor - any class
   constructor which can be called with no arguments.
1. https://en.cppreference.com/w/cpp/language/constructor - any class
   constructor or member initialization list--using the colon operator, `:`.

BACKGROUND NOTES:

Note that integers and floating point types do not actually have "constructors"
in C++. That is a misnomer. So, me naming this file with the
phrase "integer_constructors", and me saying "default constructors" below is
actually a **misnomer**. It is a misnomer which should resonate with you,
however, because **that's what it looks like.**

The true term is simply "value initialization." Keep this in mind.
I **intentionally** use this misnomer to teach a principle, but I want you to
understand that integers and floating point types in C++ **are not classes**
and do NOT have true "constructors" like classes do. Rather, they allow this
weird "value initialization" syntax to simply allow **generic, template-based
programming** where these types of syntaxes are used for generic programming.
Ex: from here (https://stackoverflow.com/a/17131915/4561887):

    template <typename T>
    void reset(T& in)
    {
        in = T();
    }

DESCRIPTION:

Demonstrate the weird `T()` "default constructors" on various types in C++,
including even basic types like integers! You'll see this super weird
default-constructor syntax on cppreference.com all over the place, such as
here: https://en.cppreference.com/w/cpp/container/vector/vector:

```cpp
explicit vector( size_type count,
                 const T& value = T(),  // <===== notice the `T()`!
                 const Allocator& alloc = Allocator());
```

While I'm at it, show other initialization syntaxes too, such as brace
initialization of integers and other types.

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
initialize values to zero. Here is a quote from the link above:

    > Note that this is not the syntax for zero-initialization, which does not
      have a dedicated syntax in the language. These are examples of other
      types of initializations, which might perform zero-initialization.


STATUS: wip

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# NB: you may need to use `-std=gnu++17` instead of `-std=c++17` in order to obtain extra GNU
# gcc features, including gcc extensions, POSIX cmds, and Linux sytem cmds.
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# 1. In C++
time g++ -Wall -Wextra -Werror -O3 -std=c++17 "constructor__value_initialization_of_integers_int()_uint64_t()_int{}_T()_T{}_etc_WIP.cpp" -o bin/a && bin/a
```

References:
1. https://en.cppreference.com/w/cpp/container/vector/vector
1. https://stackoverflow.com/a/73564212/4561887 - my answer on "What is the
colon syntax (:) in the class constructor and what does passing an integer to a
std::vector<> constructor do?"
1. ***** https://stackoverflow.com/q/72367123/4561887 - my Q on "What is a call
to `char()`, `uint8_t()`, `int64_t()`, integer `T()`, etc, as a function in
C++?""
1. https://stackoverflow.com/q/17131911/4561887 - "What does int() do in C++?"


*/


// C & C++ includes
#include <cstdint>  // For `uint8_t`, `int8_t`, etc.
#include <cstdio>   // For `printf()`
#include <iostream>  // For `std::cin`, `std::cout`, `std::endl`, etc.


// Generic template programming which uses some of the syntax below
template <typename T>
void reinitializeVariable(T* variable_or_object, T inital_value = T{})
{
    *variable_or_object = inital_value;
}

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Default ");
    std::cout << "constructors [correction: **value initialization** of "
                 "integer and floating point types!]:\n\n";

    // These are all the same thing: initializing an int to 0
    int i0 = 0;     // 0
    int i1 = int(); // 0
    int i2 = int{}; // 0
    int i3{};       // 0
    int i4();       // incorrect integer initialization: this is actually a
                    // function declaration of function `i4()` which accepts
                    // `void` and returns `int`.

    std::cout << "i0 = " << i0 << "\n";
    std::cout << "i1 = " << i1 << "\n";
    std::cout << "i2 = " << i2 << "\n";
    std::cout << "i3 = " << i3 << "\n\n";
    // Can't print `i4` like this, since it's a function address, not an `int`.
    //     error: the address of ‘int i4()’ will never be NULL [-Werror=address]
    // std::cout << i4 << "\n";

    // These are all the same thing: initializing an int to 0
    int i10 = 0;        // 0
    int i11 = int();    // 0
    int i12 = int(0);   // 0
    int i13 = int{};    // 0
    int i14 = int{0};   // 0
    int i15{};          // 0
    int i16{0};         // 0
    std::cout << "i10 = " << i10 << "\n";
    std::cout << "i11 = " << i11 << "\n";
    std::cout << "i12 = " << i12 << "\n";
    std::cout << "i13 = " << i13 << "\n";
    std::cout << "i14 = " << i14 << "\n";
    std::cout << "i15 = " << i15 << "\n";
    std::cout << "i16 = " << i16 << "\n\n";

    // These are all the same thing: initializing an int to 99
    int i20 = 99;        // 99
    int i21 = int(99);   // 99
    int i22 = int{99};   // 99
    int i23{99};         // 99
    std::cout << "i20 = " << i20 << "\n";
    std::cout << "i21 = " << i21 << "\n";
    std::cout << "i22 = " << i22 << "\n";
    std::cout << "i23 = " << i23 << "\n\n";

    // A few more random examples, to show it works with other types too

    // Set all uint64_t types to 77
    uint64_t u64_00 = 77;           // 77
    uint64_t u64_01 = uint64_t(77); // 77
    uint64_t u64_02 = uint64_t{77}; // 77
    uint64_t u64_03{77};            // 77
    std::cout << "u64_00 = " << u64_00 << "\n";
    std::cout << "u64_01 = " << u64_01 << "\n";
    std::cout << "u64_02 = " << u64_02 << "\n";
    std::cout << "u64_03 = " << u64_03 << "\n\n";

    // Set all double types to 77.1234
    double d20 = 77.1234;           // 77.1234
    double d21 = double(77.1234);   // 77.1234
    double d22 = double{77.1234};   // 77.1234
    double d23{77.1234};            // 77.1234
    std::cout << "d20 = " << d20 << "\n";
    std::cout << "d21 = " << d21 << "\n";
    std::cout << "d22 = " << d22 << "\n";
    std::cout << "d23 = " << d23 << "\n\n";

    // Try it with types whose typename is multiple words. Ex: `unsigned int`

    //////////// todo: finish this ///////
    // unsigned int ui00 = (unsigned int){78};            // 77.1234


    return 0;
}



/*
SAMPLE OUTPUT:

    eRCaGuy_hello_world/cpp$ time g++ -Wall -Wextra -Werror -O3 -std=c++17 "constructor__value_initialization_of_integers_int()_uint64_t()_int{}_T()_T{}_etc_WIP.cpp" -o bin/a && bin/a

    real    0m0.568s
    user    0m0.496s
    sys 0m0.066s
    Default constructors [correction: **value initialization** of integer and floating point types!]:

    i0 = 0
    i1 = 0
    i2 = 0
    i3 = 0

    i10 = 0
    i11 = 0
    i12 = 0
    i13 = 0
    i14 = 0
    i15 = 0
    i16 = 0

    i20 = 99
    i21 = 99
    i22 = 99
    i23 = 99

    u64_00 = 77
    u64_01 = 77
    u64_02 = 77
    u64_03 = 77

    d20 = 77.1234
    d21 = 77.1234
    d22 = 77.1234
    d23 = 77.1234


*/
