/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
27 Jan. 2022
Do a quick test to practice using the square bracket operator to add elements to a vector.

To compile and run (assuming you've already `cd`ed into this dir):
1. In C++
```bash
g++ -Wall -Wextra -Werror -O3 -std=c++17 vector_operator[].cpp -o bin/a && bin/a
```

References:
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

enum my_enum
{
    MY_ENUM_INDEX_0 = 0,
    MY_ENUM_INDEX_1,
    MY_ENUM_INDEX_2,
    MY_ENUM_INDEX_3,
    MY_ENUM_INDEX_4,
    MY_ENUM_INDEX_5,
    MY_ENUM_INDEX_6,
    MY_ENUM_INDEX_7,
    MY_ENUM_INDEX_8,
    MY_ENUM_INDEX_9,
    MY_ENUM_INDEX_10,
    /// Not a valid value; this is the number of members in this enum
    MY_ENUM_count, // equal to 11
};

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Hello ");
    std::cout << "world!\n";

    // ----------------
    // TEST 1:
    // ----------------

    // std::vector<int> v;

    // Add some elements. Oh, wait!:
    //      Segmentation fault (core dumped)

    // It turns out that none of this is allowed!: "Unlike std::map::operator[], this operator never
    // inserts a new element into the container. Accessing a nonexistent element through this
    // operator is undefined behavior."
    // (https://en.cppreference.com/w/cpp/container/vector/operator_at)
    // v[0] = 0;    // out of bounds of the vector! undefined behavior; does NOT add a new element!
    // v[1] = 1;    // out of bounds of the vector! undefined behavior; does NOT add a new element!
    // v[2] = 2;    // out of bounds of the vector! undefined behavior; does NOT add a new element!
    // v[10] = 10;  // out of bounds of the vector! undefined behavior; does NOT add a new element!

    // ----------------
    // TEST 2: Set the size of the vector upon initialization to avoid undefined behavior instead
    // ----------------

    // std::vector<int> v(10); // still too small!
    // v[10] = 10;  // may still be out of bounds of the vector! undefined behavior; will NOT add a new element!

    // Good! This is correct
    std::vector<int> v(MY_ENUM_count);
    // Now this is all safe!
    v[0] = 0;
    v[1] = 1;
    v[2] = 2;
    v[10] = 10;
    v[MY_ENUM_INDEX_6] = 6;

    // ----------------
    // Now print the output
    // ----------------

    // Technique 1 to print
    size_t i = 0;
    for (int element : v)
    {
        std::cout << i << ": " << element << "\n";
        i++;
    }
    std::cout << "\n";

    // Technique 2 to print
    for (size_t i = 0; i < v.size(); i++)
    {
        std::cout << i << ": " << v[i] << "\n";
    }
    std::cout << "\n";

    // Technique 3 to print [BEST, in my opinion, for this particular case]
    // (my preferred approach in this case; it's easier to align the output too; C++ text formatting
    // is convoluted)
    printf("index: value\n"
           "------------\n");
    for (size_t i = 0; i < v.size(); i++)
    {
        printf("%2lu: %2i\n", i, v[i]);
    }
    std::cout << "\n";

    return 0;
}



/*
SAMPLE OUTPUT:

    eRCaGuy_hello_world/cpp$ g++ -Wall -Wextra -Werror -O3 -std=c++17 vector_operator[].cpp -o bin/a && bin/a
    Hello world!
    0: 0
    1: 1
    2: 2
    3: 0
    4: 0
    5: 0
    6: 6
    7: 0
    8: 0
    9: 0
    10: 10

    0: 0
    1: 1
    2: 2
    3: 0
    4: 0
    5: 0
    6: 6
    7: 0
    8: 0
    9: 0
    10: 10

    index: value
    ------------
     0:  0
     1:  1
     2:  2
     3:  0
     4:  0
     5:  0
     6:  6
     7:  0
     8:  0
     9:  0
    10: 10

*/
