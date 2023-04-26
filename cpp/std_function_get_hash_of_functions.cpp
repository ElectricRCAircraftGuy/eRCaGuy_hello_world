///usr/bin/env ccache g++ -Wall -Wextra -Werror -O3 -std=gnu++17 "$0" -o /tmp/a && /tmp/a "$@"; exit
// For the line just above, see my answer here: https://stackoverflow.com/a/75491834/4561887

/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

Try to get a function address, and/or a unique hash of a function, which is wrapped by a
`std::function<>` wrapper object.
See this Q here: https://stackoverflow.com/q/76114714/4561887

STATUS: wip

keywords to easily grep or ripgrep in this repo for this program and what it teaches
KEYWORDS:

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# NB: you may need to use `-std=gnu++17` instead of `-std=c++17` in order to obtain extra GNU
# gcc features, including gcc extensions, POSIX cmds, and Linux sytem cmds.
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# [run once ever] install ccache
sudo apt update && sudo apt install ccache

# 1. In C++
time g++ -Wall -Wextra -Werror -O3 -std=gnu++17 hello_world_extra_basic.cpp -o bin/a && bin/a
```

References:
1.

*/

// // C++ (incl. C) includes
// #include <cstdint>  // For `uint8_t`, `int8_t`, etc.
// #include <cstdio>   // For `printf()`
// #include <iostream>  // For `std::cin`, `std::cout`, `std::endl`, etc.

// // int main(int argc, char *argv[])  // alternative prototype
// int main()
// {
//     printf("Hello ");
//     std::cout << "world!\n\n";

//     return 0;
// }


#include <functional>
#include <iostream>
#include <vector>
#include <string>
#include <cstdint>

int f(int a)
{
    return -a;
}

int f2(int a)
{
    return a;
}

typedef int (*func_t)(int);

// void print_func_addr(int (*const * func_ptr)(int))
// {

// }

int main()
{
    std::vector<std::function<int(int)>> functions
    {
        f,
        f,
        f2,
        f2,
        [](int a) {return -a;},
        [](int a) {return -a;},
        [](int a) {return -a;},
    };

    // for (auto&& a : fn) {
    //     const auto t = a.target<int(*)(int)>();
    //     const auto hash = t ?
    //         (size_t)(uintptr_t)(void*)*t :
    //         std::hash<std::string_view>{}(a.target_type().name());
    //     std::cout << hash << '\n';
    // }

    printf("%zu\n", (size_t)f);
    // printf("%zu\n", (size_t)&f); // same as above

    printf("%zu\n", (size_t)f2);
    // printf("%zu\n", (size_t)&f2); // same as above

    printf("\n");

    for (const std::function<int(int)>& func : functions)
    {
        // obtain a ptr to the function wrapped by the `std::function<>`
        // int(*const * ptr)(int) = func.target<int(*)(int)>();
        // auto ptr = func.target<int(*)(int)>();

        // int (*const * func_ptr)(int)  = func.target<int(*)(int)>();
        const func_t* func_ptr = func.target<func_t>();

        if (func_ptr == nullptr)
        {
            printf("Error: nullptr!\n");
        }
        else
        {
            printf("%zu\n", (size_t)(*func_ptr));
        }
    }
}


/*
SAMPLE OUTPUT:

    eRCaGuy_hello_world/cpp$ time g++ -Wall -Wextra -Werror -O3 -std=c++17 hello_world_extra_basic.cpp -o bin/a && bin/a

    real    0m2.079s
    user    0m0.775s
    sys 0m0.087s
    Hello world!


You can also run this file as an executable directly!:

    eRCaGuy_hello_world/cpp$ ./hello_world_extra_basic.cpp
    Hello world!


*/
