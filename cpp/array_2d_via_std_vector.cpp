/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
25 Sept. 2022

I have this really great answer for how to use multi-dimensional C-style arrays in C and C++, but if
using C++, don't do that! Just use a `std::vector<>` of `std::vector`s instead!--like this:

    using Grid = std::vector<std::vector<int>>;
    Grid grid;

See also: puzzle__maze__smallest_sum_flowing_down_and_right.cpp

STATUS: done and works!
- This is **waaaay** easier to use than C-style 2D arrays! See my answer here
  for how to do that though if you need it in C or C++:
  https://stackoverflow.com/a/67814330/4561887


To compile and run (assuming you've already `cd`ed into this dir):
```bash
# NB: you may need to use `-std=gnu++17` instead of `-std=c++17` in order to obtain extra GNU
# gcc features, including gcc extensions, POSIX cmds, and Linux sytem cmds.
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# 1. In C++
time g++ -Wall -Wextra -Werror -O3 -std=c++17 array_2d_via_std_vector.cpp -o bin/a && bin/a
```

References:
1. *****+ [my answer: C-style multi-dimensional arrays in C and C++]
   https://stackoverflow.com/a/67814330/4561887
    1. *****++ [my answer with a LOT of this code!]
       "How to pass a multidimensional array to a function in C++ only, via
       `std::vector<std::vector<int>>&`":
       https://stackoverflow.com/a/73850641/4561887
1. puzzle__maze__smallest_sum_flowing_down_and_right.cpp
1. https://en.cppreference.com/w/cpp/container/vector
    1. `std::vector<>` constructor documentation:
       https://en.cppreference.com/w/cpp/container/vector/vector


*/


// C++ includes
#include <cstdint>  // For `uint8_t`, `int8_t`, etc.
#include <cstdio>   // For `printf()`
#include <iostream>  // For `std::cin`, `std::cout`, `std::endl`, etc.
#include <vector>


using array2d_t = std::vector<std::vector<int>>;
using grid_t = array2d_t; // alternative alias for a 2D array
// OR with typedef:
// typedef std::vector<std::vector<int>> array2d_t;
// typedef array2d_t grid_t; // alternative alias for a 2D array


// Version 1: demonstrate passing using the `array2d_t` above, and iterating
// using regular for loops.
void print_array2d_1(const array2d_t& array2d)
{
    // Option 1: regular for loops

    // Iterate over all rows
    for (size_t i_row = 0; i_row < array2d.size(); i_row++)
    {
        // To get access to just a row, do this if you like
        // const std::vector<int>* row = &array2d[i_row];
        // row->size();

        // Iterate over all columns
        for (size_t i_col = 0; i_col < array2d[i_row].size(); i_col++)
        {
            printf("array2d[%zu][%zu]=%i ",
                i_row, i_col, array2d[i_row][i_col]);
        }
        printf("\n");
    }
    printf("\n");
}

// Version 2: demonstrate passing the type withOUT the `array2d_t` type above,
// and iterating via range-based for loops.
void print_array2d_2(const std::vector<std::vector<int>>& array2d)
{
    // Option 2: range-based for loops

    // Iterate over all rows
    size_t i_row = 0;
    for (std::vector<int> row : array2d)
    {
        // Iterate over all columns
        size_t i_col = 0;
        for (int val : row)
        {
            printf("array2d[%zu][%zu]=%i ", i_row, i_col, val);
            i_col++;
        }
        i_row++;
        printf("\n");
    }
    printf("\n");
}


// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("\nPrint 2D arrays (vector of vectors) in C++!\n\n");
    printf("-------------\n\n");

    // a regular 2 x 3 2D grid or array
    array2d_t array2d_1 = {
        {11, 12, 13},
        {14, 15, 16},
    };
    print_array2d_1(array2d_1);
    print_array2d_2(array2d_1);
    printf("-------------\n\n");

    // Notice that having varying numbers of columns in each row in
    // `std::vector<>`-based 2D arrays is fine!
    array2d_t array2d_2 = {
        {1, 2, 3},
        {4, 5, 6, 7},
        {8, 9, 10},
    };
    print_array2d_1(array2d_2);
    print_array2d_2(array2d_2);
    printf("-------------\n\n");

    // now use the `grid_t` alias instead
    array2d_t array2d_3 = {
        {-1, -2, -3},
        {-4, -5},
    };
    print_array2d_1(array2d_3);
    print_array2d_2(array2d_3);
    printf("-------------\n\n");


    // Cool, now let's show an alternative way to create and populate a
    // `NUM_ROWS x NUM_COLS` 2D array
    constexpr size_t NUM_ROWS = 3;
    constexpr size_t NUM_COLS = 4;
    // By default, this creates a `NUM_ROWS x NUM_COLS` array with all zeros in
    // it, since that is the default value for type `int` when called as a
    // constructor-like default initializer, as in `int()`, which
    // performs "value initialization". See my Q:
    // https://stackoverflow.com/q/72367123/4561887
    array2d_t array2d_4(NUM_ROWS, std::vector<int>(NUM_COLS));
    // Let's just fill in a few of the values with non-zeros, as an example
    array2d_4[0][0] = 1;
    array2d_4[1][1] = 2;
    array2d_4[2][2] = 3;
    array2d_4[2][3] = 4;
    // array2d_4[3][3] = 5; // UNDEFINED BEHAVIOR! OUT OF ROW BOUNDS! Results
    //                      // in: `Segmentation fault (core dumped)`
    print_array2d_1(array2d_4);
    print_array2d_2(array2d_4);
    printf("-------------\n\n");


    return 0;
}



/*
SAMPLE OUTPUT:

    eRCaGuy_hello_world/cpp$ time g++ -Wall -Wextra -Werror -O3 -std=c++17 array_2d_via_std_vector.cpp -o bin/a && bin/a

    real    0m0.389s
    user    0m0.355s
    sys 0m0.034s

    Print 2D arrays (vector of vectors) in C++!

    -------------

    array2d[0][0]=11 array2d[0][1]=12 array2d[0][2]=13
    array2d[1][0]=14 array2d[1][1]=15 array2d[1][2]=16

    array2d[0][0]=11 array2d[0][1]=12 array2d[0][2]=13
    array2d[1][0]=14 array2d[1][1]=15 array2d[1][2]=16

    -------------

    array2d[0][0]=1 array2d[0][1]=2 array2d[0][2]=3
    array2d[1][0]=4 array2d[1][1]=5 array2d[1][2]=6 array2d[1][3]=7
    array2d[2][0]=8 array2d[2][1]=9 array2d[2][2]=10

    array2d[0][0]=1 array2d[0][1]=2 array2d[0][2]=3
    array2d[1][0]=4 array2d[1][1]=5 array2d[1][2]=6 array2d[1][3]=7
    array2d[2][0]=8 array2d[2][1]=9 array2d[2][2]=10

    -------------

    array2d[0][0]=-1 array2d[0][1]=-2 array2d[0][2]=-3
    array2d[1][0]=-4 array2d[1][1]=-5

    array2d[0][0]=-1 array2d[0][1]=-2 array2d[0][2]=-3
    array2d[1][0]=-4 array2d[1][1]=-5

    -------------

    array2d[0][0]=1 array2d[0][1]=0 array2d[0][2]=0 array2d[0][3]=0
    array2d[1][0]=0 array2d[1][1]=2 array2d[1][2]=0 array2d[1][3]=0
    array2d[2][0]=0 array2d[2][1]=0 array2d[2][2]=3 array2d[2][3]=4

    array2d[0][0]=1 array2d[0][1]=0 array2d[0][2]=0 array2d[0][3]=0
    array2d[1][0]=0 array2d[1][1]=2 array2d[1][2]=0 array2d[1][3]=0
    array2d[2][0]=0 array2d[2][1]=0 array2d[2][2]=3 array2d[2][3]=4

    -------------

*/
