///usr/bin/env ccache g++ -Wall -Wextra -Werror -O3 -std=gnu++17 "$0" -o /tmp/a && /tmp/a "$@"; exit
// For the line just above, see my answer here: https://stackoverflow.com/a/75491834/4561887

/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
11 Mar. 2023

Show that you will get a linking error if you have `main()` in a namespace!

STATUS: done and works! (it produces the error as expected until you comment out the namespace)

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# NB: you may need to use `-std=gnu++17` instead of `-std=c++17` in order to obtain extra GNU
# gcc features, including gcc extensions, POSIX cmds, and Linux sytem cmds.
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# [run once ever] install ccache
sudo apt update && sudo apt install ccache

# 1. In C++
time g++ -Wall -Wextra -Werror -O3 -std=gnu++17 cpp/namespace_around_main__undefined_reference_to_main_when_linking.cpp -o bin/a && bin/a
```

References:
1.

*/

// C++ includes
#include <iostream>  // For `std::cin`, `std::cout`, `std::endl`, etc.

// <========== comment out the namespace (this lines plus the opening and closing braces) to make
// this program link!
namespace my_module
{

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Hello ");
    std::cout << "world!\n\n";

    return 0;
}

} // namespace my_module


/*
SAMPLE OUTPUT:

(won't link since `main()` is inside a namespace)

    eRCaGuy_hello_world$ cpp/namespace_around_main__undefined_reference_to_main_when_linking.cpp
    /usr/bin/ld: /usr/lib/gcc/x86_64-linux-gnu/9/../../../x86_64-linux-gnu/Scrt1.o: in function `_start':
    (.text+0x24): undefined reference to `main'
    collect2: error: ld returned 1 exit status


*/
