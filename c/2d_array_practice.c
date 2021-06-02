/*

This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
www.ElectricRCAircraftGuy.com
2 June 2021

Learn and practice a few ways to use and pass multi-dimensional (ex: 2D) arrays in C.

I'm trying to help someone on Stack Overflow...
See: https://stackoverflow.com/questions/67811354/passing-a-pointer-to-array-to-my-function

To compile and run (assuming you've already `cd`ed into this dir):
1. In C:
    mkdir -p bin && gcc -Wall -Wextra -Werror -O3 -std=c11 -save-temps=obj 2d_array_practice.c \
    -o bin/2d_array_practice && bin/2d_array_practice
2. In C++
    mkdir -p bin && g++ -Wall -Wextra -Werror -O3 -std=c++17 -save-temps=obj 2d_array_practice.c \
    -o bin/2d_array_practice && bin/2d_array_practice

References:
1. https://www.geeksforgeeks.org/pass-2d-array-parameter-c/

*/

#include <stdint.h>
#include <stdio.h>

// Get the number of elements in any C array
// - from my repo here:
//   https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world/blob/master/c/utilities.h#L42
// - Usage example: [my own answer]:
//   https://arduino.stackexchange.com/questions/80236/initializing-array-of-structs/80289#80289
#define ARRAY_LEN(array) (sizeof(array) / sizeof(array[0]))

/// Get number of rows in a 2D array
#define NUM_ROWS(array_2d) ARRAY_LEN(array_2d)

/// Get number of columns in a 2D array
#define NUM_COLS(array_2d) ARRAY_LEN(array_2d[0])

/// This works, but there's a better way we will do later.
/// Note: `rows` = number of rows; `cols` = number of columns
void printArray1(int a[][2], size_t a_rows, size_t a_cols)
{
    printf("printArray1:\n");
    for (size_t row = 0; row < a_rows; row++)
    {
        for (size_t col = 0; col < a_cols; col++)
        {
            printf("a[%zu][%zu]=%i ", row, col, a[row][col]);
        }
        printf("\n");
    }
    printf("\n");
}

/// Better way (WITH array size type safety on array size)
/// `a` here is a ptr to an array of size[3][2]. This **forces** type safety in C based on array
/// size. See my answer here: https://stackoverflow.com/a/51527502/4561887
/// I think this is overly-complicated, however (again, read my answer just above), so let's
/// do another approach later withOUT type safety.
void printArray2(int (*a)[3][2])
{
    printf("printArray2:\n");
    for (size_t row = 0; row < NUM_ROWS(*a); row++)
    {
        for (size_t col = 0; col < NUM_COLS(*a); col++)
        {
            printf("a[%zu][%zu]=%i ", row, col, (*a)[row][col]);
        }
        printf("\n");
    }
    printf("\n");
}

/// Better way (withOUT array size type safety on array size) (my preferred approach)
void printArray3(int a[][2], size_t num_rows)
{
    printf("printArray3:\n");
    for (size_t row = 0; row < num_rows; row++)
    {
        for (size_t col = 0; col < NUM_COLS(a); col++)
        {
            printf("a[%zu][%zu]=%i ", row, col, a[row][col]);
        }
        printf("\n");
    }
    printf("\n");
}

/// Much more-versatile approach.
/// NB: `a` is a pointer to the start of a contiguous 2D array of `int`s. So, treat it as such.
void printArray4(int *a, size_t num_rows, size_t num_cols)
{
    printf("printArray4:\n");
    for (size_t row = 0; row < num_rows; row++)
    {
        int *row_start = &a[row*num_cols];

        for (size_t col = 0; col < num_cols; col++)
        {
            // NB: THIS PART IS VERY DIFFERENT FROM THE OTHERS! Notice `row_start[col]`.
            printf("a[%zu][%zu]=%i ", row, col, row_start[col]);
        }
        printf("\n");
    }
    printf("\n");
}


// /// Same as `printArray3()`, but with slightly-different and less-readable, yet more-versatile
// ///  prototype--same as the original asker's function prototype style in the Question:
// /// `void matrixMultiply(int *A[], int *B[])`. See: https://stackoverflow.com/q/67811354/4561887
// /// NB: `a` is still a 2D array of `int`s.
// void printArray5(int* a[], size_t num_rows, size_t num_cols)
// {
//     printf("printArray5:\n");
//     for (size_t row = 0; row < num_rows; row++)
//     {

//         for (size_t col = 0; col < num_cols; col++)
//         {
//             printf("a[%zu][%zu]=%i ", row, col, a[row][col]);
//         }
//         printf("\n");
//     }
//     printf("\n");
// }




int main()
{
    printf("hello\n\n");

    int arr[][2] =
    {
        {1, 2},
        {5, 6},
        {7, 8},
    };

    printf("num_rows = ARRAY_LEN(arr) = %zu\n", ARRAY_LEN(arr));
    printf("num_cols = ARRAY_LEN(arr[0]) = %zu\n", ARRAY_LEN(arr[0]));
    printf("\n");
    printf("NUM_ROWS(arr) = %zu\n", NUM_ROWS(arr));
    printf("NUM_COLS(arr) = %zu\n", NUM_COLS(arr));
    printf("\n");

    // int arr2[][1] =
    // {
    //     {11},
    //     {55},
    // };

    printArray1(arr, NUM_ROWS(arr), NUM_COLS(arr));

    // Better way WITH array type safety on array size. Notice you MUST pass the **address** of the
    // array here! `&arr` is of type `int (*)[3][2]`, which means: "pointer to a 3x2 array of ints".
    // See my answer here (https://stackoverflow.com/a/51527502/4561887) under the section
    // "Forcing type safety on arrays in C" for an explanation of this for 1D arrays.
    printArray2(&arr);
    // Better way withOUT array type safety on array size (my preferred approach)
    printArray3(arr, NUM_ROWS(arr));

    // more-versatile approach (can handle 2D arrays of any arbitrary number of rows and cols)
    printArray4((int *)arr, NUM_ROWS(arr), NUM_COLS(arr));
    // OR: alternate way to call this function: get the address of the array (ie: a ptr to an int)
    // at [row, col] = [0, 0]
    printArray4(&arr[0][0], NUM_ROWS(arr), NUM_COLS(arr));




    return 0;
}


/*
SAMPLE OUTPUT (ran on an x86-64 little endian Linux Ubuntu 20.04 machine):



*/
