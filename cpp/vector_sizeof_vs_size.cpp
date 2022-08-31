/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
30 Aug. 2022

Show that the `sizeof` a `std::vector<>` does NOT change as the vector grows, because the internal
implementation of the vector just points to a memory block to hold elements, while the
`vector.size()`, of course, DOES change as the vector grows!

STATUS: done and works!

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# NB: you may need to use `-std=gnu++17` instead of `-std=c++17` in order to obtain extra GNU
# gcc features, including gcc extensions, POSIX cmds, and Linux sytem cmds.
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# 1. In C++
time g++ -Wall -Wextra -Werror -O3 -std=c++17 vector_sizeof_vs_size.cpp -o bin/a && bin/a
```

References:
1.

*/

// C and C++ includes
#include <cassert>
#include <cstdint>  // For `uint8_t`, `int8_t`, etc.
#include <cstdio>   // For `printf()`
#include <iostream>  // For `std::cin`, `std::cout`, `std::endl`, etc.
#include <vector>

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Hello ");
    std::cout << "world!\n";

    std::vector<uint8_t> v1;
    v1.resize(1);

    std::vector<uint8_t> v2;
    v2.resize(1000000);  // 1 MB of bytes

    printf("sizeof(v1) = %zu bytes\n", sizeof(v1));  // 24 bytes
    assert(sizeof(v1) == sizeof(v2));


    return 0;
}



/*
SAMPLE OUTPUT:

    eRCaGuy_hello_world/cpp$ time g++ -Wall -Wextra -Werror -O3 -std=c++17 vector_sizeof_vs_size.cpp -o bin/a && bin/a

    real    0m0.324s
    user    0m0.298s
    sys 0m0.027s
    Hello world!
    sizeof(v1) = 24 bytes


*/
