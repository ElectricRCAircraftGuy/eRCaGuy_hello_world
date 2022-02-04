/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
3 Feb. 2022

Class constructor with default args, initializer list, `std::make_unique<>()` and `std::unique_ptr<>`
STATUS: works

To compile and run (assuming you've already `cd`ed into this dir):
1. In C++
```bash
g++ -Wall -Wextra -Werror -O3 -std=c++17 class_constructor_w_default_args.cpp -o bin/a && bin/a
```

References:
1. https://en.cppreference.com/w/cpp/memory/unique_ptr/make_unique

*/


// C++ includes
#include <iostream>  // For `std::cin`, `std::cout`, `std::endl`, etc.
#include <memory>  // `std::make_unique<>()`

// C includes
#include <cstdint>  // For `uint8_t`, `int8_t`, etc.
#include <cstdio>   // For `printf()`

class Foo
{
public:
    Foo(const std::string str = "hey", const int val = 7);

    void print();

private:
    const int _val;
    std::string _str;
};

Foo::Foo(const std::string str, int val) :
    // NB: since _val comes before _str in the private list order above, it MUST come in this same
    // order in the initializer list here too!
    _val(val),
    _str(str)
{
}

void Foo::print()
{
    std::cout << "_str = " << _str << "\n";
    std::cout << "_val = " << _val << "\n";
}

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Hello ");
    std::cout << "world!\n\n";

    Foo foo;
    std::cout << "foo:\n";
    foo.print();
    std::cout << "\n";

    std::unique_ptr<Foo> foo_p = std::make_unique<Foo>();
    std::cout << "foo_p:\n";
    foo_p->print();
    std::cout << "\n";

    return 0;
}



/*
SAMPLE OUTPUT:

    eRCaGuy_hello_world/cpp$ g++ -Wall -Wextra -Werror -O3 -std=c++17 class_constructor_w_default_args.cpp -o bin/a && bin/a
    Hello world!

    foo:
    _str = hey
    _val = 7

    foo_p:
    _str = hey
    _val = 7


*/
