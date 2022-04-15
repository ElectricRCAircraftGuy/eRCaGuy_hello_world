/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

Learn how to use the `std::unordered_map::count()` method.

GS
2 Feb. 2022

To compile and run (assuming you've already `cd`ed into this dir):
1. In C++
```bash
g++ -Wall -Wextra -Werror -O3 -std=c++17 unordered_map_count.cpp -o bin/a && bin/a
```

References:
1. `std::unordered_map`:
    1. ***** https://en.cppreference.com/w/cpp/container/unordered_map/count
    1. ***** https://www.cplusplus.com/reference/unordered_map/unordered_map/count/
1. `std::map`:
    1. [no example] https://en.cppreference.com/w/cpp/container/map/count
    1. ***** https://www.cplusplus.com/reference/map/map/count/

*/


// C++ includes
#include <iostream>  // For `std::cin`, `std::cout`, `std::endl`, etc.
#include <string>
#include <unordered_map>

// C includes
#include <cstdint>  // For `uint8_t`, `int8_t`, etc.
#include <cstdio>   // For `printf()`

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Hello ");
    std::cout << "world!\n\n";

    std::unordered_map<std::string, int> map;
    map["apples"] = 22;
    map["bananas"] = 33;
    map["pears"] = 44;

    // Print key:value pairs using automatic "structured binding" to `key`, `value` variables
    // (**since C++17**)
    for (auto const& [key, value] : map)
    {
        std::cout << key << ": " << value << "\n";
    }
    std::cout << "\n";

    // Print counts
    // explicitly do this one outside the for loop below since it's not in the map!
    std::cout << "count(kiwis) = " << map.count("kiwis") << "\n";
    for (const std::pair<const std::string, int> element : map)
    {
        size_t count = map.count(element.first);
        std::cout << "count(" << element.first << ") = " << count << "\n";
    }
    // explicitly do this one outside the for loop above since it's not in the map!
    std::cout << "count(strawberries) = " << map.count("strawberries") << "\n";

    return 0;
}



/*
SAMPLE OUTPUT:

    eRCaGuy_hello_world/cpp$ g++ -Wall -Wextra -Werror -O3 -std=c++17 unordered_map_count.cpp -o bin/a && bin/a
    Hello world!

    pears: 44
    apples: 22
    bananas: 33

    count(kiwis) = 0
    count(pears) = 1
    count(apples) = 1
    count(bananas) = 1
    count(strawberries) = 0

*/
