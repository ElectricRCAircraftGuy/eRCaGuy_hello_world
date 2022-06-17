/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
June 2022

Demonstrate how to containerize a dynamically-allocated array in C. This makes the `array_int_t`
struct below a little bit C++-like, similar to the `std::array<int, NUM_ELEMENTS>` type in C++!

STATUS: (status)

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# Why `-std=gnu17` vs `-std=c17`, and `-std=gnu++17` vs `-std=c++17`?
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# 1. In C:
gcc -Wall -Wextra -Werror -O3 -std=gnu17 containers_array_dynamic.c -o bin/a -lm && bin/a

# 2. In C++
g++ -Wall -Wextra -Werror -O3 -std=gnu++17 containers_array_dynamic.c -o bin/a && bin/a
```

References:
1. *****+ This code is in my answer here!: "Determine the length of a dynamic array after creation
   time in C" (incl. How to containerize a dynamically-allocated array in C):
   https://stackoverflow.com/a/72653068/4561887
1. Containers in C++: https://en.cppreference.com/w/cpp/container
    1. `std::array<T, N>` type in C++: https://en.cppreference.com/w/cpp/container/array
1. How to get dynamic array's size in C?: https://stackoverflow.com/a/65270682/4561887

*/


#include <stdio.h>
#include <stdlib.h>


/// A container representing a dynamically-allocated array of integers
typedef struct array_int_s
{
    /// Pointer to the first element in a dynamically-allocated array
    /// of ints
    int * start;

    /// Number of elements in the array
    size_t size;
} array_int_t;

/// A "factory" function to dynamically create and return an array of
/// `num_elements` of type `int`.
array_int_t array_int_create(size_t num_elements)
{
    array_int_t dynamic_array =
    {
        .start = (int*)malloc(sizeof(int)*num_elements),
        .size = num_elements,
    };

    return dynamic_array;
}

int main()
{
    const size_t NUM_INTS = 10;


    // 1. Basic demo

    int *p = (int*)malloc(sizeof(int)*NUM_INTS);
    printf("p can hold %zu integers\n", NUM_INTS);

    (void)p; // eliminate "unused variable" error


    // 2. Containerized demo

    array_int_t array_int;
    array_int.start = (int*)malloc(sizeof(int)*NUM_INTS);
    array_int.size = NUM_INTS;
    printf("array_int can hold %zu integers\n", array_int.size);


    // 3. Containerized demo with initializer function

    array_int_t array_int2 = array_int_create(NUM_INTS);
    printf("array_int2 can hold %zu integers\n", array_int2.size);


    return 0;
}

/*
SAMPLE OUTPUT:

In C:




OR, in C++:




*/
