/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

Just to demo and test some std::vector and std::array initialization techniques.

GS
Jan. 2022

To compile and run (assuming you've already `cd`ed into this dir):
1. In C++
```bash
g++ -Wall -Wextra -Werror -O3 -std=c++17 vector_and_array_initialization.cpp -o bin/a && bin/a
```

References:
1. https://en.cppreference.com/w/cpp/container/array
1. https://en.cppreference.com/w/cpp/container/vector
1. [my answer] https://stackoverflow.com/a/70889843/4561887 - where I got `enum fruits`

*/


// C++ includes
#include <array>
#include <iostream>  // For `std::cin`, `std::cout`, `std::endl`, etc.
#include <vector>

// C includes
#include <cstdint>  // For `uint8_t`, `int8_t`, etc.
#include <cstdio>   // For `printf()`


#define SUBSET_LEN(start, end) ((end) - (start) + 1)

template <typename T>
void printArrayOrVector(T arrayOrVector)
{
    printf("index: value\n"
           "------------\n");
    for (size_t i = 0; i < arrayOrVector.size(); i++)
    {
        printf("%2lu: %2i\n", i, arrayOrVector[i]);
    }
    printf("\n");
}

enum fruits
{
    FRUITS_APPLE = 0,
    FRUITS_BANANA,
    FRUITS_PEAR,
    FRUITS_LEMON,
    FRUITS_KIWI,
    /// Not a valid value; this is the number of members in this enum
    FRUITS_count,
    // Other, special values:
    FRUITS_subset_start = FRUITS_PEAR,
    FRUITS_subset_end = FRUITS_KIWI,
};


// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Hello ");
    std::cout << "world!\n\n";

    constexpr std::array<int, 5> A =
    {
        1,
        2,
        3,
        4,
        5,
    };

    // NB: `std::vector` types can NOT be `constexpr`! It is not allowed. So, use `const` instead.
    // Here is the error if you try `constexpr`:
    //      error: the type ‘const std::vector<int>’ of ‘constexpr’ variable ‘V’ is not literal
    // So, apparently only "literal" constant types can be constexpr, and std::vector doesn't
    // count--probably because it was intended to be automatically-dynamically-expandable, unlike
    // C-style arrays and C++ `std::array`, both of which are fixed-size.

    // constexpr std::vector<int> V =
    const std::vector<int> V =
    {
        1,
        2,
        3,
        4,
        5,
    };

    printf("array A:\n");
    printArrayOrVector(A);

    printf("vector V:\n");
    printArrayOrVector(V);


    // Now ensure a non-constexpr std::array can be edited as I expect it can

    std::array<int, 5> a; // NB: all values are left UNinitialized here

    a[3] = 12345;

    printf("array a:\n");
    printArrayOrVector(a);

    // Now try to use the enum to make and modify the array

    std::array<int, FRUITS_count> fruitsArray; // NB: all values are left UNinitialized here
    fruitsArray[FRUITS_PEAR] = 999999;

    printf("array fruitsArray:\n");
    printArrayOrVector(fruitsArray);

    // Make another enum-based array, but use only a *subset of the enum!*

    constexpr std::array<int, SUBSET_LEN(FRUITS_subset_start, FRUITS_subset_end)>
    favoriteFruitsArray =
    {                 // enum integer values are:
        FRUITS_PEAR,  // 2
        FRUITS_LEMON, // 3
        FRUITS_KIWI,  // 4
    };

    printf("array favoriteFruitsArray:\n");
    printArrayOrVector(favoriteFruitsArray);


    return 0;
}



/*
SAMPLE OUTPUT:

Notice that array `a` is uninitialized except for index 3, so only that index location
has a predictable, defined value!

    eRCaGuy_hello_world/cpp$ g++ -Wall -Wextra -Werror -O3 -std=c++17 vector_and_array_initialization.cpp -o bin/a && bin/a
    Hello world!

    array A:
    index: value
    ------------
     0:  1
     1:  2
     2:  3
     3:  4
     4:  5

    vector V:
    index: value
    ------------
     0:  1
     1:  2
     2:  3
     3:  4
     4:  5

    array a:
    index: value
    ------------
     0:  1
     1:  0
     2:  1
     3: 12345
     4:  2

    array fruitsArray:
    index: value
    ------------
     0:  1
     1:  0
     2: 999999
     3: 22091
     4: 98376512

    array favoriteFruitsArray:
    index: value
    ------------
     0:  2
     1:  3
     2:  4


*/
