///usr/bin/env ccache gcc -Wall -Wextra -Werror -O3 -std=gnu17 "$0" -o /tmp/a -lm && /tmp/a "$@"; exit
// For the line just above, see my answer here: https://stackoverflow.com/a/75491834/4561887

/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world


GS
Aug. 2024

Learn how to use a double pointer as a 1D array of pointers to structs. 
Also check some `sizeof` stuff. 

Note that if you want to use a double pointer as a 2D array, you can do that too. See "Example 4" in
my answer here: https://stackoverflow.com/a/67814330/4561887. 

In that example I use `int* array_2d[]` as an argument to a function. It automatically adjusts
("decays") to `int** array_2d` in the function prototype. This is because `int* array_2d[]` is an
array of pointers, so it decays to a pointer to a pointer when passed to a function. Again, 
see my link above. 

STATUS: Done and works!

keywords to easily grep or ripgrep in this repo for this program and what it teaches
KEYWORDS:

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# Why `-std=gnu17` vs `-std=c17`, and `-std=gnu++17` vs `-std=c++17`?
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# [run once ever] install ccache
sudo apt update && sudo apt install ccache

# 1. In C:
./double_ptr_and_sizeof.c
# or:
gcc -Wall -Wextra -Werror -O3 -std=gnu17 double_ptr_and_sizeof.c -o bin/a -lm && bin/a

# 2. In C++
g++ -Wall -Wextra -Werror -O3 -std=gnu++17 double_ptr_and_sizeof.c -o bin/a && bin/a
```

References:
1. https://stackoverflow.com/a/67814330/4561887
    1. array_2d_practice.c
1. utilities.h
    1. ARRAY_LEN()

*/


#include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`


/// Get the number of elements in any C array
/// - Usage example: [my own answer]:
///   https://arduino.stackexchange.com/a/80289/7727
/// - Copied from utilities.h
#define ARRAY_LEN(array) (sizeof(array) / sizeof((array)[0]))

typedef struct Stuff_s
{
    uint8_t a;
    // 1 byte of automatic padding here
    uint16_t b;
    uint32_t c;
    uint64_t d;
} Stuff;  // size is 16 bytes

// Note to the non-English-native speaker: "stuffs" is *not* a valid English word. The proper 
// grammar usage of a plurality of "stuff" would be "things".

typedef struct Group_s
{
    const Stuff** list;  // a 1D array of `Stuff*` pointers
    size_t len;    // number of elements in the 1D `list` array
} Group;

// Print all `Stuff` entries in the `list` in the group
void printGroup(const Group* group)
{
    printf(
        "\nGroup printout:\n"
        "group address:             %p\n"
        "list start address:        %p\n"
        "list start address (same): %p\n",
        group,
        group->list,
        &((group->list)[0])
    );
    printf("\n");

    for (size_t i = 0; i < group->len; i++)
    {
        // Contents of `list` (ie: addresses of `Stuff` objects)
        printf("  list[%zu] (ie: address of this `Stuff` object): %p\n", i, group->list[i]);

        // Technique 1: index into the 1D `list` array using square brackets (`[]`)
        printf("  Technique 1: %zu: a=%u, b=%u, c=%u, d=%lu\n", 
            i, 
            group->list[i]->a, 
            group->list[i]->b, 
            group->list[i]->c, 
            group->list[i]->d
        );

        // Technique 2: index into the 1D `list` array using pointer arithmetic
        printf("  Technique 2: %zu: a=%u, b=%u, c=%u, d=%lu\n", 
            i, 
            (*(group->list + i))->a, 
            (*(group->list + i))->b, 
            (*(group->list + i))->c, 
            (*(group->list + i))->d
        ); 

        // Technique 3: obtain the list element first, and then do technique 1
        const Stuff **list = group->list;
        printf("  Technique 3: %zu: a=%u, b=%u, c=%u, d=%lu\n", 
            i, 
            list[i]->a, 
            list[i]->b, 
            list[i]->c, 
            list[i]->d
        );

        // Technique 4: obtain an element within `list` first, and then get what is inside that
        const Stuff * stuff = group->list[i];         // OR (same thing)
        // const Stuff * stuff = *(group->list + i);  // OR (same thing)
        printf("  Technique 4: %zu: a=%u, b=%u, c=%u, d=%lu\n", 
            i, 
            stuff->a, 
            stuff->b, 
            stuff->c, 
            stuff->d
        );

        printf("\n");
    }
    printf("\n");
}

// Now actually allocate the memory of objects

Stuff stuff1 = {1, 2, 3, 4};
Stuff stuff2 = {5, 6, 7, 8};
Stuff stuff3 = {9, 10, 11, 12};

static const Stuff * list[] = 
{
    &stuff1,
    &stuff2,
    &stuff3,
};  // size is 24 bytes (8 bytes per ptr x 3 ptrs)

Group group = 
{
    .list = list,
    .len = ARRAY_LEN(list),
};


// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Double ptr, and sizeof, practice.\n\n");

    printf("sizeof(Stuff) = %zu\n", sizeof(Stuff));        // 16 bytes
    printf("sizeof(list) = %zu\n", sizeof(list));          // 24 bytes
    printf("sizeof(*list) = %zu\n", sizeof(*list));        // 8 bytes, since `*list` is a 
                                                           //     `Stuff*`, which is a ptr
    printf("sizeof(**list) = %zu\n", sizeof(**list));      // 16 bytes, since `**list` is a 
                                                           //     `Stuff`, which is a 16-byte 
                                                           //     struct
    printf("sizeof(list[0]) = %zu\n", sizeof(list[0]));    // 8 bytes, since `list[0]` is a 
                                                           //     `Stuff*`, which is a ptr
    printf("sizeof(*list[0]) = %zu\n", sizeof(*list[0]));  // 16 bytes, since `*list[0]` is a 
                                                           //     `Stuff`, which is a 16-byte 
                                                           //     struct
    printf("\n");

    // 3 elements: 24 / 8 = 3
    printf("sizeof(list)/sizeof(list[0]) = %zu\n", sizeof(list)/sizeof(list[0]));
    // (same thing) 3 elements: 24 / 8 = 3
    printf("sizeof(list)/sizeof(*list) = %zu\n", sizeof(list)/sizeof(*list));
    printf("\n");

    printGroup(&group);

    // Print addresses of all the `Stuff` objects in different ways
    printf(
        "stuff1 address:  %p %p\n"
        "stuff2 address:  %p %p\n"
        "stuff3 address:  %p %p\n"
        "\n",
        &stuff1, group.list[0],
        &stuff2, group.list[1],
        &stuff3, group.list[2]
    );

    // Print the contents of the `list` array, which contains a list of addresses of `Stuff`
    // objects, thereby matching the output just above
    printf(
        "list[0]:         %p\n"
        "list[1]:         %p\n"
        "list[2]:         %p\n"
        "\n",
        list[0],
        list[1],
        list[2]
    );

    // Print addresses of the `list` array and its elements
    printf(
        "list address:    %p\n"
        "list[0] address: %p\n"
        "list[1] address: %p\n"
        "list[2] address: %p\n"
        "\n",
        list,
        &(list[0]),
        &(list[1]),
        &(list[2])
    );


    return 0;
}


/*
SAMPLE OUTPUT:

--------------------------------
In C:
--------------------------------

eRCaGuy_hello_world/c$ ./double_ptr_and_sizeof.c 
Double ptr, and sizeof, practice.

sizeof(Stuff) = 16
sizeof(list) = 24
sizeof(*list) = 8
sizeof(**list) = 16
sizeof(list[0]) = 8
sizeof(*list[0]) = 16

sizeof(list)/sizeof(list[0]) = 3
sizeof(list)/sizeof(*list) = 3


Group printout:
group address:             0x5951bc679040
list start address:        0x5951bc679050
list start address (same): 0x5951bc679050

  list[0] (ie: address of this `Stuff` object): 0x5951bc679030
  Technique 1: 0: a=1, b=2, c=3, d=4
  Technique 2: 0: a=1, b=2, c=3, d=4
  Technique 3: 0: a=1, b=2, c=3, d=4
  Technique 4: 0: a=1, b=2, c=3, d=4

  list[1] (ie: address of this `Stuff` object): 0x5951bc679020
  Technique 1: 1: a=5, b=6, c=7, d=8
  Technique 2: 1: a=5, b=6, c=7, d=8
  Technique 3: 1: a=5, b=6, c=7, d=8
  Technique 4: 1: a=5, b=6, c=7, d=8

  list[2] (ie: address of this `Stuff` object): 0x5951bc679010
  Technique 1: 2: a=9, b=10, c=11, d=12
  Technique 2: 2: a=9, b=10, c=11, d=12
  Technique 3: 2: a=9, b=10, c=11, d=12
  Technique 4: 2: a=9, b=10, c=11, d=12


stuff1 address:  0x5951bc679030 0x5951bc679030
stuff2 address:  0x5951bc679020 0x5951bc679020
stuff3 address:  0x5951bc679010 0x5951bc679010

list[0]:         0x5951bc679030
list[1]:         0x5951bc679020
list[2]:         0x5951bc679010

list address:    0x5951bc679050
list[0] address: 0x5951bc679050
list[1] address: 0x5951bc679058
list[2] address: 0x5951bc679060


--------------------------------
OR, in C++:
--------------------------------

(same as in C)

*/
