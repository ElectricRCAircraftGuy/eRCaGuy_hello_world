/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
28 Jan. 2022
Do a quick test to practice using the square bracket operator to add elements to a vector.
Ensure this works with a vector of structs too.

To compile and run (assuming you've already `cd`ed into this dir):
1. In C++
```bash
g++ -Wall -Wextra -Werror -O3 -std=c++17 vector_operator[]_of_structs.cpp -o bin/a && bin/a
```

References:
1. vector_operator[].cpp
1. https://en.cppreference.com/w/cpp/container/vector
1. https://en.cppreference.com/w/cpp/container/vector/operator_at - for operator[]
1. constructors (see #3): https://en.cppreference.com/w/cpp/container/vector/vector
1. https://stackoverflow.com/a/69774217/4561887 - my answer on how to iterate over C and C++ enums
1. ***** [my ans on "Is there a way to initialize a vector by index in c++11?"]
   https://stackoverflow.com/a/70889843/4561887


*/


// C++ includes
#include <iostream>  // For `std::cin`, `std::cout`, `std::endl`, etc.
#include <vector>

// C includes
#include <cstdint>  // For `uint8_t`, `int8_t`, etc.
#include <cstdio>   // For `printf()`

struct my_struct
{
    int i1 = 2;
    std::string s1 = "hey";
};

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Hello ");
    std::cout << "world!\n";

    std::vector<my_struct> v(10);

    v[1] =
    {
        .i1 = 7,
        .s1 = "you",
    };


    printf("index: value\n"
           "------------\n");
    for (size_t i = 0; i < v.size(); i++)
    {
        printf("%2lu: %2i, %s\n", i, v[i].i1, v[i].s1.c_str());
    }
    printf("\n");

    return 0;
}



/*
SAMPLE OUTPUT:

    eRCaGuy_hello_world/cpp$ g++ -Wall -Wextra -Werror -O3 -std=c++17 vector_operator[]_of_structs.cpp -o bin/a && bin/a
    Hello world!
    index: value
    ------------
     0:  2, hey
     1:  7, you
     2:  2, hey
     3:  2, hey
     4:  2, hey
     5:  2, hey
     6:  2, hey
     7:  2, hey
     8:  2, hey
     9:  2, hey

*/
