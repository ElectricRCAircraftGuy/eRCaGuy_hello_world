/*

This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
www.ElectricRCAircraftGuy.com
2 June 2021

Learn and practice a few ways to use and pass multi-dimensional (ex: 2D) arrays in C.
See my final answers here:
vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
1. [my main answer] https://stackoverflow.com/a/67814330/4561887                 <======== READ & STUDY THIS FOR FULL UNDERSTANDING OF THIS CODE
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
2. [my answer which is a snippet of the one above]
   https://stackoverflow.com/a/67814569/4561887


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
1. The Q I'm answering: https://stackoverflow.com/questions/67811354/passing-a-pointer-to-array-to-my-function
1. [my ans to another Q] https://stackoverflow.com/questions/6567742/passing-an-array-as-an-argument-to-a-function-in-c/51527502#51527502
1. another Q & A (where I should answer instead): https://stackoverflow.com/questions/2828648/how-to-pass-a-multidimensional-array-to-a-function-in-c-and-c
1. https://www.geeksforgeeks.org/pass-2d-array-parameter-c/


--------------------------------
CONCLUSIONS AND RECOMMENDATIONS:
--------------------------------

ALL APPROACHES BELOW ARE VALID. However, here are my recommendations:

Assume you have the following array:
```
int arr[][2] =
{
    {1, 2},
    {5, 6},
    {7, 8},
};
```

1. If the 2D array is ALWAYS the same size each time (3x2 rows x columns in this case), do this:
    ```
    void print_array2(int (*array_2d)[3][2]) {}
    // NB: `&` is REQUIRED! See my answer for why: https://stackoverflow.com/a/51527502/4561887
    print_array2(&arr);
    ```
2. If the 2D array has a VARIABLE number of rows, but a FIXED number of columns (2 in this case),
    do this:
    ```
    void print_array3(int array_2d[][2], size_t num_rows) {}
    print_array3(arr, NUM_ROWS(arr));
    ```
3. If the 2D array has a VARIABLE number of rows AND a VARIABLE number of columns, do this (this
   approach is the most-versatile and is generally my go-to approach for multidimensional arrays):
    ```
    void print_array4(int *array_2d, size_t num_rows, size_t num_cols) {}
    print_array4((int *)arr, NUM_ROWS(arr), NUM_COLS(arr));
    // OR: alternative call technique:
    print_array4(&arr[0][0], NUM_ROWS(arr), NUM_COLS(arr));
    ```

If you have the following array, however, you must do something different:
```
// Each row is an array of `int`s.
int row1[] = {1, 2};
int row2[] = {5, 6};
int row3[] = {7, 8};
// This is an array of `int *`, or "pointer to int". The blob of all rows together does NOT
// have to be in contiguous memory. This is very different from the `arr` array above, which
// contains all data in contiguous memory.
int* all_rows[] = {row1, row2, row3};
```

4. If the 2D array is actually built up of a bunch of ptrs to other arrays (as shown just above),
   do this:
    ```
    void print_array5(int* array_2d[], size_t num_rows, size_t num_cols) {}
    print_array5(all_rows, ARRAY_LEN(all_rows), ARRAY_LEN(row1));
    ```


*/

#include <stdint.h>
#include <stdio.h>

// Get the number of elements in any C array
// - from my repo here:
//   https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world/blob/master/c/utilities.h#L42
// - Usage example: [my own answer]:
//   https://arduino.stackexchange.com/questions/80236/initializing-array-of-structs/80289#80289
#define ARRAY_LEN(array) (sizeof(array) / sizeof(array[0]))

/// Definitions: `rows` = "rows"; `cols` = "columns"

/// Get number of rows in a 2D array
#define NUM_ROWS(array_2d) ARRAY_LEN(array_2d)

/// Get number of columns in a 2D array
#define NUM_COLS(array_2d) ARRAY_LEN(array_2d[0])


/// A function to demonstrate that the `3` below in the index has ZERO influence
/// on this function!
void print_sizeof_1d_array(int arr[3])
{
    // Not allowed!
    //      error: ‘sizeof’ on array function parameter ‘arr’ will return size
    //      of ‘int *’ [-Werror=sizeof-array-argument]
    // printf("sizeof(arr) = %zu\n", sizeof(arr));

    // Just takes the size of an int, which is 4 for my architecture!
    // Ignores the `3` above, since `arr` actually decayed into type `int *`!
    printf("sizeof(*arr) = %zu\n", sizeof(*arr));
}

void my_func(int (*array)[10])
{
    // suppress warning that this param is unused (`-Werror=unused-parameter`)
    (void)array;
}


/// \brief      Print a 2D array which has a VARIABLE number of rows but
///             FIXED number of columns.
/// \details    Don't use this approach at all, ever. It has a superfluous
///             `num_cols` parameter that we don't actually need! (see the
///             `print_array3` approach below instead for how we can get rid of
///             this). So, this approach is shown here for demonstration
///             purposes only.
/// \param[in]  array_2d    a 2D array; is of type `int [][2]` (n x 2 (2D) array
///                         of ints), which naturally decays to type
///                         `int (*)[2]` (ptr to (1D) array of 2 ints)
/// \param[in]  num_rows    The number of rows in the array
/// \param[in]  num_cols    The number of columns in the array
/// \return     None
void print_array1(const int array_2d[][2], size_t num_rows, size_t num_cols)
{
    printf("print_array1:\n");
    for (size_t row = 0; row < num_rows; row++)
    {
        for (size_t col = 0; col < num_cols; col++)
        {
            printf("array_2d[%zu][%zu]=%i ", row, col, array_2d[row][col]);
        }
        printf("\n");
    }
    printf("\n");
}

// Better way (WITH array size type safety on array size)
// `array_2d` here is a ptr to an array of size[3][2]. This **forces** type safety in C based on array
// size. See my answer here: https://stackoverflow.com/a/51527502/4561887
// I think this is overly-complicated, however (again, read my answer just above), so let's
// do another approach later withOUT type safety.
//
/// \brief      Print a 2D array which has a FIXED number of rows and
///             FIXED number of columns.
/// \param[in]  array_2d    a 2D array; is of type `int (*)[3][2]` (ptr to
///                         3 x 2 (2D) array of ints); since it is already
///                         explicitly a ptr, it does NOT naturally decay to
///                         any other type of ptr
/// \return     None
void print_array2(const int (*array_2d)[3][2])
{
    printf("print_array2:\n");
    for (size_t row = 0; row < NUM_ROWS(*array_2d); row++)
    {
        for (size_t col = 0; col < NUM_COLS(*array_2d); col++)
        {
            printf("array_2d[%zu][%zu]=%i ", row, col, (*array_2d)[row][col]);
        }
        printf("\n");
    }
    printf("\n");
}

// Better way (withOUT array size type safety on array size) (my preferred approach between this
// one and the one above, UNLESS all arrays are the same size, in which case use the one above)
//
/// \brief      Print a 2D array which has a VARIABLE number of rows but
///             FIXED number of columns.
/// \param[in]  array_2d    a 2D array; is of type `int [][2]` (n x 2 (2D) array
///                         of ints), which naturally decays to type
///                         `int (*)[2]` (ptr to (1D) array of 2 ints)
/// \param[in]  num_rows    The number of rows in the array
/// \return     None
void print_array3(const int array_2d[][2], size_t num_rows)
{
    printf("print_array3:\n");

    // Technique 1: use `array_2d` directly.
    printf("--- Technique 1: ---\n");
    for (size_t row = 0; row < num_rows; row++)
    {
        for (size_t col = 0; col < NUM_COLS(array_2d); col++)
        {
            printf("array_2d[%zu][%zu]=%i ", row, col, array_2d[row][col]);
        }
        printf("\n");
    }

    // Technique 2: cast the `array_2d` decayed ptr to a ptr to a sized array of
    // the correct size, then use that ptr to the properly-sized array
    // directly! NB: after obtaining this ptr via the cast below, this
    // technique is **exactly identical** to (I copy/pasted it from, then
    // renamed the variable) the implementation inside `print_array2()` above!
    printf("--- Technique 2: ---\n");
    int (*array_2d_ptr)[num_rows][NUM_COLS(array_2d)] =
        (int (*)[num_rows][NUM_COLS(array_2d)])array_2d;
    for (size_t row = 0; row < NUM_ROWS(*array_2d_ptr); row++)
    {
        for (size_t col = 0; col < NUM_COLS(*array_2d_ptr); col++)
        {
            printf("array_2d_ptr[%zu][%zu]=%i ", row, col, (*array_2d_ptr)[row][col]);
        }
        printf("\n");
    }

    printf("\n");
}

// Much more-versatile approach. (My overall preferred approach since it's the most-versatile).
// NB: `array_2d` is a pointer to the start of a contiguous 2D array of `int`s. So, treat it as such.
//
/// \brief      Print a 2D array which has a VARIABLE number of rows and
///             VARIABLE number of columns.
/// \param[in]  array_2d    a 2D array; is of type `int *` (ptr to int); even
///                         though a 1D array of type `int []` (array of ints)
///                         naturally decays to this type, don't think about it
///                         that way; rather, think of it as a ptr to the first
///                         `int` in a contiguous block of memory containing a
///                         multidimensional array, and we will manually index
///                         into it as required and according to its dimensions
/// \param[in]  num_rows    The number of rows in the array
/// \param[in]  num_cols    The number of columns in the array
/// \return     None
void print_array4(const int *array_2d, size_t num_rows, size_t num_cols)
{
    printf("print_array4:\n");

    // Technique 1: use `array_2d` directly, manually indexing into this
    // contiguous block of memory holding the 2D array data.
    printf("--- Technique 1: ---\n");
    for (size_t row = 0; row < num_rows; row++)
    {
        const int *row_start = &array_2d[row*num_cols];

        for (size_t col = 0; col < num_cols; col++)
        {
            // NB: THIS PART IS VERY DIFFERENT FROM THE OTHERS! Notice `row_start[col]`.
            printf("array_2d[%zu][%zu]=%i ", row, col, row_start[col]);
        }
        printf("\n");
    }

    // Technique 2: cast the `array_2d` decayed ptr to a ptr to a sized array of
    // the correct size, then use that ptr to the properly-sized array
    // directly! NB: after obtaining this ptr via the cast below, this
    // technique is **exactly identical** to (I copy/pasted it from, then
    // renamed the variable) the implementation inside `print_array2()` above!
    printf("--- Technique 2: ---\n");
    int (*array_2d_ptr)[num_rows][num_cols] =
        (int (*)[num_rows][num_cols])array_2d;
    for (size_t row = 0; row < NUM_ROWS(*array_2d_ptr); row++)
    {
        for (size_t col = 0; col < NUM_COLS(*array_2d_ptr); col++)
        {
            printf("array_2d_ptr[%zu][%zu]=%i ", row, col, (*array_2d_ptr)[row][col]);
        }
        printf("\n");
    }

    printf("\n");
}


// Now let's force some code into the mold (prototype) style the OP requested for completeness.
//
/// \brief      Print a 2D-like array, where the array passed in is an array of
///             ptrs (int *) to other sub-arrays. Each index into the outer
///             array is the row, then each index into a sub-array in a given
///             row is the column. This handles a VARIABLE number of rows and
///             VARIABLE number of columns.
/// \details    `array_2d` here is different from all of the cases above. It is
///             NOT a contiguous 2D array of `int`s; rather, it is an array of
///             pointers to ints, where each pointer in the array can be
///             thought of as a sub-array. Therefore, the length of the outer
///             array is the number of rows, and the length of each sub-array,
///             or inner array, is the number of columns. Each sub-array
///             (a single row of `int`s) DOES have to be in contiguous memory,
///             and the array of _pointers_ DOES have to be in contiguous
///             memory, but the actual _storage space_ for each row can be in
///             NON-contiguous memory. Again, this is VERY different from every
///             other function above.
/// \param[in]  array_2d    a 2D array; is of type `int * []` (array of ptrs to
///                         int) (where each ptr is a sub-array of ints)
/// \param[in]  num_rows    The number of rows in the array (number of elements
///                         in the `array_2d` outer array)
/// \param[in]  num_cols    The number of columns in the array (number of
///                         elements in each sub-array)
/// \return     None
void print_array5(const int* array_2d[], size_t num_rows, size_t num_cols)
{
    printf("print_array5:\n");
    for (size_t row = 0; row < num_rows; row++)
    {
        const int *row_start = array_2d[row]; // VERY DIFFERENT FROM `print_array4` above!
        for (size_t col = 0; col < num_cols; col++)
        {
            // Identical to `print_array4` above.
            printf("array_2d[%zu][%zu]=%i ", row, col, row_start[col]);
        }
        printf("\n");
    }
    printf("\n");
}


typedef struct data_s
{
    int x;
    int y;
} data_t;

void print_struct_data(data_t * data, size_t len)
{
    for (size_t i = 0; i < len; i++)
    {
        printf("[data[i].x, data[i].y] = [%i, %i]\n", data[i].x, data[i].y);
    }
    printf("\n");
}




int main()
{
    printf("hello\n\n");

    // ===========================
    printf("1D array tests:\n\n");
    // ===========================

    int array_1d[] = {1, 2, 3};
    int * array_1d_p = array_1d;
    print_sizeof_1d_array(array_1d);
    print_sizeof_1d_array(array_1d_p);
    printf("\n");

    // 1. Create arrays

    int array1[5];
    int *array1_p = array1; // array1_p is of type `int *` (ptr to int)
    int (*array1_p2)[5] = &array1; // array1_p2 is of type `int (*)[5]` (ptr
                                   // to array of 5 ints)
    // Suppress `-Werror=unused-variable` errors
    (void)array1;
    (void)array1_p;
    (void)array1_p2;

    int array2[10];
    int *array2_p = array2; // array2_p is of type `int *` (ptr to int)
    int (*array2_p2)[10] = &array2; // array2_p2 is of type `int (*)[10]` (ptr
                                    // to array of 10 ints)
    // Suppress `-Werror=unused-variable` errors
    (void)array2;
    (void)array2_p;
    (void)array2_p2;

    // 2. Make some calls

    // 2.1. calling with `int array1[5]`

    // FAILS! Expected `int (*)[10]` (ptr to array of 10 ints) but argument is
    // of type `int *` (ptr to int); due to **natural type decay** from
    // `int[5]` (array of 5 ints) to `int *` (ptr to int)
    // my_func(array1);

    // FAILS! Expected `int (*)[10]` (ptr to array of 10 ints) but argument is
    // of type `int *` (ptr to int); due to dereferencing to `int[5]` (array
    // of 5 ints), followed by **natural type decay** from `int[5]`
    // (array of 5 ints) to `int *` (ptr to int)
    // my_func(*array1_p2);

    // FAILS! Expected `int (*)[10]` (ptr to array of 10 ints) but argument is
    // of type `int *` (ptr to int)
    // my_func(array1_p);

    // FAILS! Expected `int (*)[10]` (ptr to array of 10 ints) but argument is
    // of type `int`; due to **natural type decay** from `int[5]` (array of
    // 5 ints) to `int *` (ptr to int), in conjunction with dereferencing
    // from that to `int`
    // my_func(*array1);

    // FAILS! Expected `int (*)[10]` (ptr to array of 10 ints) but argument is
    // of type `int`
    // my_func(*array1_p);

    // FAILS! Expected `int (*)[10]` (ptr to array of 10 ints) but argument is
    // of type `int (*)[5]` (ptr to array of 5 ints)
    // my_func(&array1);

    // FAILS! Expected `int (*)[10]` (ptr to array of 10 ints) but argument is
    // of type `int (*)[5]` (ptr to array of 5 ints)
    // my_func(array1_p2);

    // FAILS! Expected `int (*)[10]` (ptr to array of 10 ints) but argument is
    // of type `int (**)[5]` (ptr to "ptr to array of 5 ints")
    // my_func(&array1_p2);

    // 2.2. calling with `int array2[10]`

    // FAILS! Expected `int (*)[10]` (ptr to array of 10 ints) but argument is
    // of type `int *` (ptr to int); due to **natural type decay** from
    // `int[10]` (array of 10 ints) to `int *` (ptr to int)
    // my_func(array2);

    // FAILS! Expected `int (*)[10]` (ptr to array of 10 ints) but argument is
    // of type `int *` (ptr to int); due to dereferencing to `int[10]` (array
    // of 10 ints), followed by **natural type decay** from `int[10]`
    // (array of 10 ints) to `int *` (ptr to int)
    // my_func(*array2_p2);

    // FAILS! Expected `int (*)[10]` (ptr to array of 10 ints) but argument is
    // of type `int *` (ptr to int)
    // my_func(array2_p);

    // FAILS! Expected `int (*)[10]` (ptr to array of 10 ints) but argument is
    // of type `int`; due to **natural type decay** from `int[10]` (array of
    // 10 ints) to `int *` (ptr to int), in conjunction with dereferencing
    // from that to `int`
    // my_func(*array2);

    // FAILS! Expected `int (*)[10]` (ptr to array of 10 ints) but argument is
    // of type `int`
    // my_func(*array2_p);

    // <===============
    // <=== WORKS! ====
    // <===============
    // Expected and received `int (*)[10]` (ptr to array of 10 ints)
    my_func(&array2);

    // <===============
    // <=== WORKS! ====
    // <===============
    // Expected and received `int (*)[10]` (ptr to array of 10 ints)
    my_func(array2_p2);

    // FAILS! Expected `int (*)[10]` (ptr to array of 10 ints) but argument is
    // of type `int (**)[10]` (ptr to "ptr to array of 10 ints")
    // my_func(&array2_p2);

    // ===========================
    printf("2D array tests: print a 2D array in a bunch of different ways:\n\n");
    // ===========================

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

    print_array1(arr, NUM_ROWS(arr), NUM_COLS(arr));

    // Better way WITH array type safety on array size. Notice you MUST pass the **address** of the
    // array here! `&arr` is of type `int (*)[3][2]`, which means: "pointer to a 3x2 array of ints".
    // See my answer here (https://stackoverflow.com/a/51527502/4561887) under the section
    // "Forcing type safety on arrays in C" for an explanation of this for 1D arrays.
    print_array2(&arr);
    // Better way withOUT array type safety on array size (my preferred approach)
    print_array3(arr, NUM_ROWS(arr));

    // more-versatile approach (can handle 2D arrays of any arbitrary number of rows and cols)
    print_array4((int *)arr, NUM_ROWS(arr), NUM_COLS(arr));
    // OR: alternate way to call this function: get the address of the array (ie: a ptr to an int)
    // at [row, col] = [0, 0]
    print_array4(&arr[0][0], NUM_ROWS(arr), NUM_COLS(arr));


    // ===========================
    printf("Now let's force some code into the mold (prototype) style the OP requested, "
           "for completeness:\n\n");
    // ===========================

    // Each row is an array of `int`s.
    int row1[] = {1, 2};
    int row2[] = {5, 6};
    int row3[] = {7, 8};
    // This is an array of `int *`, or "pointer to int". The blob of all rows together does NOT
    // have to be in contiguous memory. This is very different from the `arr` array above, which
    // contains all data in contiguous memory.
    const int* all_rows[] = {row1, row2, row3};

    print_array5(all_rows, ARRAY_LEN(all_rows), ARRAY_LEN(row1));


    // ===========================
    printf("Using pointers: what if we need references (pointers) to each of the above arrays? "
           "How can we carry around and use such pointers in each of the function calls above? "
           "Like this:\n\n");
    // ===========================

    // `print_array1()`.
    // `int array_2d[][2]` naturally decays to `int* [2]`
    int (*p1)[2] = arr; // MUST USE THESE PARENTHESIS!
    print_array1(p1, NUM_ROWS(arr), NUM_COLS(p1));
    // OR
    print_array1(p1, NUM_ROWS(arr), NUM_COLS(arr));

    // `print_array2()`.
    // `int (*array_2d)[3][2]` is an explicit ptr to a 3x2 array of `int`. This array pointer does NOT
    // naturally decay to a simpler type.
    int (*p2)[3][2] = &arr; // must use `&` and MUST USE THESE PARENTHESIS!
    print_array2(p2);

    // `print_array3()`.
    // `int array_2d[][2]` naturally decays to `int* [2]`
    int (*p3)[2] = arr; // MUST USE THESE PARENTHESIS!
    print_array3(p3, NUM_ROWS(arr));

    // `print_array4()`.
    // The easiest one by far!
    int *p4_1 = (int*)arr;
    // OR
    int *p4_2 = &arr[0][0];
    print_array4(p4_1, NUM_ROWS(arr), NUM_COLS(arr));
    print_array4(p4_2, NUM_ROWS(arr), NUM_COLS(arr));


    // `print_array5()`.
    // `int* array_2d[]` naturally decays to `int**`
    const int **p5 = all_rows;
    print_array5(p5, ARRAY_LEN(all_rows), ARRAY_LEN(row1));


    // ===========================
    printf("Don't forget about just using structs and arrays of structs instead, "
           "which is sometimes much easier!\n\n");
    // ===========================

    // Array of the above struct
    data_t data_array[] =
    {
        {1, 2},
        {5, 6},
        {7, 8},
    };

    print_struct_data(data_array, ARRAY_LEN(data_array));


    return 0;
}


/*
SAMPLE OUTPUT (run on an x86-64 little endian (not that endianness matters here)
Linux Ubuntu 20.04 machine):

    eRCaGuy_hello_world/c$ mkdir -p bin && gcc -Wall -Wextra -Werror -O3 \
    -std=c11 -save-temps=obj 2d_array_practice.c \
    -o bin/2d_array_practice && bin/2d_array_practice
    hello

    1D array tests:

    sizeof(*arr) = 4
    sizeof(*arr) = 4

    2D array tests: print a 2D array in a bunch of different ways:

    num_rows = ARRAY_LEN(arr) = 3
    num_cols = ARRAY_LEN(arr[0]) = 2

    NUM_ROWS(arr) = 3
    NUM_COLS(arr) = 2

    print_array1:
    array_2d[0][0]=1 array_2d[0][1]=2
    array_2d[1][0]=5 array_2d[1][1]=6
    array_2d[2][0]=7 array_2d[2][1]=8

    print_array2:
    array_2d[0][0]=1 array_2d[0][1]=2
    array_2d[1][0]=5 array_2d[1][1]=6
    array_2d[2][0]=7 array_2d[2][1]=8

    print_array3:
    --- Technique 1: ---
    array_2d[0][0]=1 array_2d[0][1]=2
    array_2d[1][0]=5 array_2d[1][1]=6
    array_2d[2][0]=7 array_2d[2][1]=8
    --- Technique 2: ---
    array_2d_ptr[0][0]=1 array_2d_ptr[0][1]=2
    array_2d_ptr[1][0]=5 array_2d_ptr[1][1]=6
    array_2d_ptr[2][0]=7 array_2d_ptr[2][1]=8

    print_array4:
    --- Technique 1: ---
    array_2d[0][0]=1 array_2d[0][1]=2
    array_2d[1][0]=5 array_2d[1][1]=6
    array_2d[2][0]=7 array_2d[2][1]=8
    --- Technique 2: ---
    array_2d_ptr[0][0]=1 array_2d_ptr[0][1]=2
    array_2d_ptr[1][0]=5 array_2d_ptr[1][1]=6
    array_2d_ptr[2][0]=7 array_2d_ptr[2][1]=8

    print_array4:
    --- Technique 1: ---
    array_2d[0][0]=1 array_2d[0][1]=2
    array_2d[1][0]=5 array_2d[1][1]=6
    array_2d[2][0]=7 array_2d[2][1]=8
    --- Technique 2: ---
    array_2d_ptr[0][0]=1 array_2d_ptr[0][1]=2
    array_2d_ptr[1][0]=5 array_2d_ptr[1][1]=6
    array_2d_ptr[2][0]=7 array_2d_ptr[2][1]=8

    Now let's force some code into the mold (prototype) style the OP requested,
    for completeness:

    print_array5:
    array_2d[0][0]=1 array_2d[0][1]=2
    array_2d[1][0]=5 array_2d[1][1]=6
    array_2d[2][0]=7 array_2d[2][1]=8

    Using pointers: what if we need references (pointers) to each of the above
    arrays? How can we carry around and use such pointers in each of the
    function calls above? Like this:

    print_array1:
    array_2d[0][0]=1 array_2d[0][1]=2
    array_2d[1][0]=5 array_2d[1][1]=6
    array_2d[2][0]=7 array_2d[2][1]=8

    print_array1:
    array_2d[0][0]=1 array_2d[0][1]=2
    array_2d[1][0]=5 array_2d[1][1]=6
    array_2d[2][0]=7 array_2d[2][1]=8

    print_array2:
    array_2d[0][0]=1 array_2d[0][1]=2
    array_2d[1][0]=5 array_2d[1][1]=6
    array_2d[2][0]=7 array_2d[2][1]=8

    print_array3:
    --- Technique 1: ---
    array_2d[0][0]=1 array_2d[0][1]=2
    array_2d[1][0]=5 array_2d[1][1]=6
    array_2d[2][0]=7 array_2d[2][1]=8
    --- Technique 2: ---
    array_2d_ptr[0][0]=1 array_2d_ptr[0][1]=2
    array_2d_ptr[1][0]=5 array_2d_ptr[1][1]=6
    array_2d_ptr[2][0]=7 array_2d_ptr[2][1]=8

    print_array4:
    --- Technique 1: ---
    array_2d[0][0]=1 array_2d[0][1]=2
    array_2d[1][0]=5 array_2d[1][1]=6
    array_2d[2][0]=7 array_2d[2][1]=8
    --- Technique 2: ---
    array_2d_ptr[0][0]=1 array_2d_ptr[0][1]=2
    array_2d_ptr[1][0]=5 array_2d_ptr[1][1]=6
    array_2d_ptr[2][0]=7 array_2d_ptr[2][1]=8

    print_array4:
    --- Technique 1: ---
    array_2d[0][0]=1 array_2d[0][1]=2
    array_2d[1][0]=5 array_2d[1][1]=6
    array_2d[2][0]=7 array_2d[2][1]=8
    --- Technique 2: ---
    array_2d_ptr[0][0]=1 array_2d_ptr[0][1]=2
    array_2d_ptr[1][0]=5 array_2d_ptr[1][1]=6
    array_2d_ptr[2][0]=7 array_2d_ptr[2][1]=8

    print_array5:
    array_2d[0][0]=1 array_2d[0][1]=2
    array_2d[1][0]=5 array_2d[1][1]=6
    array_2d[2][0]=7 array_2d[2][1]=8

    Don't forget about just using structs and arrays of structs instead, which
    is sometimes much easier!

    [data[i].x, data[i].y] = [1, 2]
    [data[i].x, data[i].y] = [5, 6]
    [data[i].x, data[i].y] = [7, 8]

*/
