/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
Sept. 2022

Learn to use `std::ref()` to wrap parameters passed to `std::thread` as
references, when needed.

I needed to wrap my pass-by-reference parameter to `std::thread()` with
`std::ref()`. Ex:
`std::thread t1 = std::thread(foo, std::ref(my_reference_param))`
instead of
`std::thread t1 = std::thread(foo, my_reference_param)`.
See the `std::thread::thread()` constructor reference pg here:
https://en.cppreference.com/w/cpp/thread/thread/thread:
> The arguments to the thread function are moved or copied by value. If a
  reference argument needs to be passed to the thread function, it has to be
  wrapped (e.g., with `std::ref` or `std::cref`).


STATUS: done and works!

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# NB: you may need to use `-std=gnu++17` instead of `-std=c++17` in order to obtain extra GNU
# gcc features, including gcc extensions, POSIX cmds, and Linux sytem cmds.
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# 1. In C++
g++ -Wall -Wextra -Werror -O3 -std=c++17 -pthread std_thread__pass_parameter_by_reference_to_constructor_via_std_ref.cpp -o bin/a && bin/a
```

References:
1. *****+ [my answer with this code] https://stackoverflow.com/a/73642536/4561887
1. `std::thread::thread` constructor page:
   https://en.cppreference.com/w/cpp/thread/thread/thread:
   > The arguments to the thread function are moved or copied by value. If a
     reference argument needs to be passed to the thread function, it has to be
     wrapped (e.g., with `std::ref` or `std::cref`).
1. My comment, and this answer:
   https://stackoverflow.com/questions/29949670/c11-stdthread-accepting-function-with-rvalue-parameter?answertab=scoredesc#comment130044374_47049374
1. https://en.cppreference.com/w/cpp/container/queue

*/


// C & C++ includes
#include <cstdint>  // For `uint8_t`, `int8_t`, etc.
#include <cstdio>   // For `printf()`
#include <iostream>  // For `std::cin`, `std::cout`, `std::endl`, etc.
#include <thread>

struct Data
{
    int i = 7;
};

// Accepts a reference
void foo(Data& data)
{
    printf("data.i = %i\n", data.i);
}

// Accepts a const reference
void foo2(const Data& data)
{
    printf("data.i = %i\n", data.i);
}

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("`std::thread` test\n");

    Data data;
    std::thread t1 = std::thread(foo, std::ref(data));
    std::thread t2 = std::thread(foo2, std::cref(data));
    t1.join();
    t2.join();

    return 0;
}



/*
SAMPLE OUTPUT:

    eRCaGuy_hello_world/cpp$ g++ -Wall -Wextra -Werror -O3 -std=c++17 -pthread std_thread__pass_parameter_by_reference_to_constructor_via_std_ref.cpp -o bin/a && bin/a
    `std::thread` test
    data.i = 7
    data.i = 7


*/
