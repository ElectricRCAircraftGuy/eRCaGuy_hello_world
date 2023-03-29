/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
June 2022

Demonstrate how to containerize a dynamically-allocated array in C. This makes the `array_of_int_t`
struct below a little bit C++-like, similar to the `std::array<int, NUM_ELEMENTS>` type in C++!

STATUS: done and works!

keywords to easily grep or ripgrep in this repo for this program and what it teaches
KEYWORDS: interview prep

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# Why `-std=gnu17` vs `-std=c17`, and `-std=gnu++17` vs `-std=c++17`?
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# 1. In C:
gcc -Wall -Wextra -Werror -O3 -std=gnu17 containers_array_dynamic_array_of_int_with_factory_create_func.c -o bin/a -lm && bin/a

# 2. In C++
g++ -Wall -Wextra -Werror -O3 -std=gnu++17 containers_array_dynamic_array_of_int_with_factory_create_func.c -o bin/a && bin/a
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
#include <string.h> // `memset()`


/// A container representing a dynamically-allocated array of integers
typedef struct array_of_int_s
{
    /// Pointer to the first element in a dynamically-allocated array
    /// of ints
    int * data;

    /// Number of elements in the array
    size_t size;
} array_of_int_t;

/// "Zero", or "clear", an array by setting all of its data elements to zero!
void array_of_int_zero(array_of_int_t* array_of_int)
{
    if (array_of_int == NULL)
    {
        printf("ERROR: null ptr\n");
        return;
    }

    // debugging; sample output: 40
    // printf("array_of_int->size*sizeof(array_of_int->data[0]) = %zu\n",
    //     array_of_int->size*sizeof(array_of_int->data[0]));

    memset(&array_of_int->data[0], 0,
        array_of_int->size*sizeof(array_of_int->data[0]));
}

/// A "factory" function to dynamically create and return a ptr to a
/// dynamically-allocated object containing an array of `num_elements` of type
/// `int`.
///
/// The data in the array is zeroed by this function.
///
/// See also this answer which helped me to some extent:
///     https://stackoverflow.com/a/65270682/4561887
/// and my answer where I shared this code:
///     https://stackoverflow.com/a/72653068/4561887
///
/// Returns NULL if malloc() fails due to "out of memory".
array_of_int_t* array_of_int_create(size_t num_elements)
{
    // Allocate memory for the entire struct, as well as the actual array space
    // that the `.data` member will point to, which will be located just
    // **after** the `array_of_int_t` object.
    // - Note: `sizeof(*(array_of_int->data))` is the equivalent to `sizeof
    //   (int)` in this case, except that it's more robust because if you
    //   change the `data` type in the `array_of_int_t` struct from `int*` to
    //   something else, you do NOT also have to change this `malloc()` call
    //   here!. It could also be written like this:
    //   `sizeof(array_of_int->data[0])`.
    //
    // // debugging; is 56 bytes
    // size_t num_bytes = sizeof(array_of_int_t) + num_elements*sizeof(int);
    // printf("num_bytes = %zu\n", num_bytes);
    array_of_int_t *array_of_int = (array_of_int_t*)malloc(sizeof(*array_of_int)
        + num_elements*sizeof(*(array_of_int->data)));

    if (array_of_int == NULL)
    {
        printf("ERROR: out of memory\n");
        return array_of_int;
    }

    // Set the array data to point to the first byte just past the end of the
    // `array_of_int_t` struct, which data has also been `malloc`ed just above
    // for exactly this purpose. Note that in "pointer arithmetic", doing
    // `array_of_int + 1` jumps one "element" forward, where "element" is one
    // entire `array_of_int_t` struct. Therefore, that jumps forward to point
    // to the first byte **after** the `array_of_int` object.
    //
    // I then cast it to an `int*` to point the `->data` member to it. I could
    // also cast it to a `void*` to make this code generic if I wanted, but
    // casting to `void*` can also be more error-prone because it makes the
    // compiler no longer verify the pointer type of the variable being
    // assigned, since **any** pointer can point to a `void*` type. So, I'll
    // avoid casting to `void*` here.
    array_of_int->data = (int*)(array_of_int + 1);

    array_of_int->size = num_elements;
    array_of_int_zero(array_of_int);

    return array_of_int;
}

/// "Destroy" the array object by `free`ing its dynamically-allocated memory.
/// This function should be called when done using the object, to prevent
/// memory leaks.
///
/// Same as with calling `free()`, calling this function multiple times on the
/// same object is **undefined behavior**, so don't do that!
/// See: https://en.cppreference.com/w/c/memory/free
void array_of_int_destroy(array_of_int_t *array_of_int)
{
    // Only free it if it's a valid pointer.
    if (array_of_int)
    {
        free(array_of_int);
    }
}

/// Print all elements in an array
void array_of_int_print(const array_of_int_t* array_of_int)
{
    if (array_of_int == NULL)
    {
        printf("ERROR: null ptr\n");
        return;
    }

    printf("array data: {");
    for (size_t i = 0; i < array_of_int->size; i++)
    {
        printf("%i", array_of_int->data[i]);
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
    if (p == NULL)
    {
        printf("ERROR: malloc() failed (out of memory)!\n");
        exit(EXIT_FAILURE);
    }
    printf("p can hold %zu integers\n", NUM_INTS);

    // write some data to this array
    for (size_t i = 0; i < NUM_INTS; i++)
    {
        p[i] = i;
    }

    // print the data out now
    for (size_t i = 0; i < NUM_INTS; i++)
    {
        printf("p[%zu] = %i\n", i, p[i]);
    }
    printf("\n");

    // Free the dynamically-allocated memory when done, to prevent memory leaks
    if (p)
    {
        free(p);
    }


    // 2. Containerized demo

    array_of_int_t array_of_int;
    // Note: `sizeof(array_of_int->data[0])` is the same as `sizeof(int)` in
    // this case, except it is more-robust since it doesn't require changing
    // the code here if you ever change the type of `.data` from `int*` to
    // something else.
    //
    // // debugging: is 40 bytes
    // size_t num_bytes = sizeof(array_of_int.data[0])*NUM_INTS;
    // printf("num_bytes = %zu\n", num_bytes);
    array_of_int.data = (int*)malloc(sizeof(array_of_int.data[0])*NUM_INTS);
    if (array_of_int.data == NULL)
    {
        printf("ERROR: malloc() failed (out of memory)!\n");
        exit(EXIT_FAILURE);
    }
    array_of_int.size = NUM_INTS;
    printf("array_of_int_t can hold %zu integers\n", array_of_int.size);

    // write all zeros to this array, then write a few values, then print the
    // whole array
    array_of_int_zero(&array_of_int);
    array_of_int.data[2] = 123;
    array_of_int.data[7] = 456789;
    array_of_int_print(&array_of_int);
    printf("\n");

    // Free the dynamically-allocated memory when done, to prevent memory leaks
    if (array_of_int.data)
    {
        free(array_of_int.data);
    }


    // 3. [BEST!] A fully containerized demo, with a factory "create" function
    // to dynamically make an array object! Also, with full error checking to
    // ensure `malloc()` actually worked!

    array_of_int_t * array_of_int2 = array_of_int_create(NUM_INTS);
    if (array_of_int2 == NULL)
    {
        printf("ERROR: array_of_int_create() failed (out of memory)!\n");
        exit(EXIT_FAILURE);
    }

    printf("array_of_int2 can hold %zu integers\n", array_of_int2->size);
    // the `array_of_int_create()` function already zeroed all the data, so
    // let's just write in some values then print out the whole array!
    array_of_int2->data[1] = 1;
    array_of_int2->data[5] = 5;
    array_of_int2->data[9] = 9;
    array_of_int_print(array_of_int2);
    printf("\n");
    // Free the dynamically-allocated memory when done, to prevent memory leaks
    array_of_int_destroy(array_of_int2);


    return 0;
}

/*
SAMPLE OUTPUT:

In C:

    eRCaGuy_hello_world/c$ gcc -Wall -Wextra -Werror -O3 -std=gnu17 containers_array_dynamic_array_of_int_with_factory_create_func.c -o bin/a -lm && bin/a
    p can hold 10 integers
    p[0] = 0
    p[1] = 1
    p[2] = 2
    p[3] = 3
    p[4] = 4
    p[5] = 5
    p[6] = 6
    p[7] = 7
    p[8] = 8
    p[9] = 9

    array_of_int_t can hold 10 integers
    array data: {0, 0, 123, 0, 0, 0, 0, 456789, 0, 0}

    array_of_int2 can hold 10 integers
    array data: {0, 1, 0, 0, 0, 5, 0, 0, 0, 9}



OR, in C++:
(same output as in C; see C++ cmd above)


*/
