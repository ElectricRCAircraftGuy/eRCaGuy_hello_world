/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
June 2022

Demonstrate how to containerize a dynamically-allocated array in C. This makes the `array_of_int_t`
struct below a little bit C++-like, similar to the `std::array<int, NUM_ELEMENTS>` type in C++!

STATUS: wip

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# Why `-std=gnu17` vs `-std=c17`, and `-std=gnu++17` vs `-std=c++17`?
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# 1. In C:
gcc -Wall -Wextra -Werror -O3 -std=gnu17 containers_array_dynamic_array_of_int.c -o bin/a -lm && bin/a

# 2. In C++
g++ -Wall -Wextra -Werror -O3 -std=gnu++17 containers_array_dynamic_array_of_int.c -o bin/a && bin/a
```

References:
1. *****+ This code is in my answer here!: "Determine the length of a dynamic array after creation
   time in C" (incl. How to containerize a dynamically-allocated array in C):
   https://stackoverflow.com/a/72653068/4561887
1. Containers in C++: https://en.cppreference.com/w/cpp/container
    1. `std::array<T, N>` type in C++: https://en.cppreference.com/w/cpp/container/array
1. How to get dynamic array's size in C?: Answer by @0___________:
   https://stackoverflow.com/a/65270682/4561887
   - Great answer! It reminded me that I need to fully dynamically allocate memory for the whole
   `array_of_int_t`, NOT just the array of ints within it, and then return a **ptr** to that
   dynamically-allocated object rather than passing it by copy, else it requires some allocation
   for the container itself to be statically-allocated, which defeats the purpose of dynamic
   allocation in the first place.

*/


#include <stdio.h>
#include <stdlib.h>


/// A container representing a dynamically-allocated array of integers
typedef struct array_of_int_s
{
    /// Pointer to the first element in a dynamically-allocated array
    /// of ints
    int * data;

    /// Number of elements in the array
    size_t size;
} array_of_int_t;

/// "Zero", or "clear", an array by setting all of its elements to zeor!
void array_of_int_zero(const array_of_int_t* array_of_int)
{
    if (array_of_int == NULL)
    {
        printf("ERROR: null ptr\n");
        return;
    }

    printf("{");
    for (size_t i = 0; i < array_of_int->size; i++)
    {
        printf("%i");
        if (i < array_of_int->size - 1)
        {
            printf(", ");
        }
    }
    printf("}\n");
}

/// A "factory" function to dynamically create and return a ptr to a dynamically-allocated object
/// containing an array of `num_elements` of type `int`.
/// See also this answer which helped me: https://stackoverflow.com/a/65270682/4561887
/// and my answer where I shared this: https://stackoverflow.com/a/72653068/4561887
array_of_int_t* array_of_int_create(size_t num_elements)
{
    // Note: `sizeof(*(array_of_int->data))` is the equivalent to `sizeof(int)` in this case, except
    // that it's more robust because if you chance the `data` type in the `array_of_int_t` struct,
    // you do NOT also have to change this `malloc()` call here!. It could also be written like
    // this: `sizeof(array_of_int->data[0])`.
    array_of_int_t *array_of_int = malloc(sizeof(*array_of_int)
        + num_elements*sizeof(*(array_of_int->data)));

    if (array_of_int == NULL)
    {
        printf("ERROR: out of memory\n");
        return array_of_int;
    }

    array_of_int->size = num_elements;
    array_of_int_zero(array_of_int);

    return array_of_int;
}

/// Print all elements in an array
void array_of_int_print(const array_of_int_t* array_of_int)
{
    if (array_of_int == NULL)
    {
        printf("ERROR: null ptr\n");
        return;
    }

    printf("{");
    for (size_t i = 0; i < array_of_int->size; i++)
    {
        printf("%i");
        if (i < array_of_int->size - 1)
        {
            printf(", ");
        }
    }
    printf("}\n");
}

int main()
{
    const size_t NUM_INTS = 10;


    // 1. Basic demo

    int *p = (int*)malloc(sizeof(int)*NUM_INTS);
    printf("p can hold %zu integers\n", NUM_INTS);

    p[0] = 123;
    p[NUM_INTS - 1] = 456;


    // 2. Containerized demo

    array_of_int_t array_int;
    array_int.data = (int*)malloc(sizeof(int)*NUM_INTS);
    array_int.size = NUM_INTS;
    printf("array_int can hold %zu integers\n", array_int.size);


    // 3. Containerized demo with initializer function

    array_of_int_t array_int2 = array_of_int_create(NUM_INTS);
    printf("array_int2 can hold %zu integers\n", array_int2.size);


    return 0;
}

/*
SAMPLE OUTPUT:

In C:




OR, in C++:




*/
