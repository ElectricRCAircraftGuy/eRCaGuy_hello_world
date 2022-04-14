/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
4 Feb. 2022
2nd function ptr file today

Is it possible to have a function pointer to any function type? I don't think so, but let's do some
experimenting!

STATUS: wip
TODO: ADD PTR TO MEMBER FUNCTION EXAMPLES TOO! <=============

To compile and run (assuming you've already `cd`ed into this dir):
1. In C++
```bash
g++ -Wall -Wextra -Werror -O3 -std=c++17 hello_world_extra_basic.cpp -o bin/a && bin/a
```

References:
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
    printf("Hello ");
    std::cout << "world!\n\n";

    return 0;
}



/*
SAMPLE OUTPUT:

    eRCaGuy_hello_world/cpp$ g++ -Wall -Wextra -Werror -O3 -std=c++17 hello_world_extra_basic.cpp -o bin/a && bin/a
    Hello world!

*/
