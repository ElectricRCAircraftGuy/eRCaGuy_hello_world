///usr/bin/env ccache g++ -Wall -Wextra -Werror -O3 -std=gnu++17 "$0" -o /tmp/a && /tmp/a "$@"; exit
// For the line just above, see my answer here: https://stackoverflow.com/a/75491834/4561887

/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
9 May 2023

Demonstrate rotating a 2D array upwards my rotating the indices, which is very
efficient, rather than the data, which is inefficient. This is a type of "ring
buffer", or "circular buffer".

STATUS: done and works!

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
time g++ -Wall -Wextra -Werror -O3 -std=gnu++17 ring_buffer_rotate_2d_array_up.cpp -o bin/a && bin/a
```

References:
1. The question: https://stackoverflow.com/q/76209654/4561887
    1. ***** [my answer to this, with this code!]
       https://stackoverflow.com/a/76210820/4561887
1. My answer on 2D arrays: https://stackoverflow.com/a/67814330/4561887

*/


// C++ (incl. C) includes
#include <cstdio>   // For `printf()`
#include <iostream>  // For `std::cin`, `std::cout`, `std::endl`, etc.

// Get the number of elements in any C array
// - from my repo here:
//   https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world/blob/master/c/utilities.h#L42
#define ARRAY_LEN(array) (sizeof(array) / sizeof((array)[0]))

/// Definitions: `rows` = "rows"; `cols` = "columns"

/// Get number of rows in a 2D array
#define NUM_ROWS(array_2d) ARRAY_LEN(array_2d)
/// Get number of columns in a 2D array
#define NUM_COLS(array_2d) ARRAY_LEN((array_2d)[0])


struct Array2d
{
    // the actual C-style 2D array of data
    int array[4][4];
    // the starting index for the array, which represents the "first row"
    size_t i_start = 0;
};

// Print the 2D array.
// - Note: pass by const reference since we won't change the array while
//   printing.
void array2d_print(const Array2d& array2d)
{
    const size_t NUM_ROWS = NUM_ROWS(array2d.array);
    const size_t NUM_COLS = NUM_COLS(array2d.array);

    size_t i_row = array2d.i_start;
    for (size_t row = 0; row < NUM_ROWS; row++)
    {
        for (size_t i_col = 0; i_col < NUM_COLS; i_col++)
        {
            printf("%3i", (array2d.array)[i_row][i_col]);
            if (i_col < NUM_COLS - 1)
            {
                printf(",");
            }
            else
            {
                printf("\n");
            }
        }

        // increment our "ring-buffer-style" row index
        i_row = (i_row + 1) % NUM_ROWS;
    }
    printf("\n");
}

// Rotate the 2D array up.
// - Note: pass by ptr since we **will** change the array (the `i_start` index
//   in this case), and we want this fact to be obvious when the user calls
//   this function.
void array2d_rotateup(Array2d* array2d)
{
    const size_t NUM_ROWS = NUM_ROWS(array2d->array);
    // Note: since the `i_start` index is an **unsigned** integer `size_t` type,
    // this approach works perfectly fine even if the integer value overflows
    // upward and rolls over, so there is never a need to check for overflow.
    // This works fine and is well-defined behavior as-is. **Signed** integers,
    // however, have technically **undefined** behavior during overflow and
    // underflow.
    array2d->i_start = (array2d->i_start + 1) % NUM_ROWS;
}

int main()
{
    Array2d array2d =
    {
        .array =
        {
            {1,   2,  3,  4},
            {5,   6,  7,  8},
            {9,  10, 11, 12},
            {13, 14, 15, 16},
        }
    };

    // print the starting array
    array2d_print(array2d);

    // now rotate and print the array NUM_ROWS times
    for (size_t i = 0; i < NUM_ROWS(array2d.array); i++)
    {
        array2d_rotateup(&array2d);
        array2d_print(array2d);
    }

    return 0;
}



/*
SAMPLE OUTPUT:

    eRCaGuy_hello_world$ cpp/ring_buffer_rotate_2d_array_up.cpp
      1,  2,  3,  4
      5,  6,  7,  8
      9, 10, 11, 12
     13, 14, 15, 16

      5,  6,  7,  8
      9, 10, 11, 12
     13, 14, 15, 16
      1,  2,  3,  4

      9, 10, 11, 12
     13, 14, 15, 16
      1,  2,  3,  4
      5,  6,  7,  8

     13, 14, 15, 16
      1,  2,  3,  4
      5,  6,  7,  8
      9, 10, 11, 12

      1,  2,  3,  4
      5,  6,  7,  8
      9, 10, 11, 12
     13, 14, 15, 16


*/
