<!--
https://stackoverflow.com/a/67814330/4561887
-->

_Note: this answer doesn't answer the specifics of the OP's question. There are already answers for that. Rather, it answers only the **title** of the OP's question: "How to pass a multidimensional array to a function in C and C++", since Google searches for that phrase or similar lead right here, and I have a lot to say on the topic._ Keep in mind if I made my own question to post this as an answer, it would be closed as a duplicate of this question, so I'm posting this here instead.

_For passing 1D arrays, see my other answer here instead: https://stackoverflow.com/questions/6567742/passing-an-array-as-an-argument-to-a-function-in-c/51527502#51527502_


## If in a hurry:

...and:

1. you are **using C++, it really is best to represent a 2D array as a vector of vectors (ex: `std::vector<std::vector<int>>` (recommended!))**, so see my other answer here: [How to pass a multidimensional array to a function in C++ only, via `std::vector<std::vector<int>>&`](https://stackoverflow.com/a/73850641/4561887).
1. you really want to use **C-style multi-dimensional arrays** in C _or_ C++, jump straight down and look at the 4 print examples under the "Summary of Conclusions and Recommendations..." section.


## How to use multidimensional (ex: 2D) arrays, and pointers to them, as function parameters in C and C++

Multidimensional arrays are very confusing for just about everybody, myself included--for experienced programmers and beginners alike. So, I'd like to provide a canonical set of examples I can come back to and reference again and again (see comments below this answer, however; I don't cover it all), with some clear demonstrations and easy-to-follow guidelines. Here it goes.

Upfront notes:
1. NB: as of C2x (C20 or later), the following "original principle" guideline 15 is in effect (source: [Wikipedia: C2x](https://en.wikipedia.org/wiki/C2x#Features) --> original source: [Programming Language C - C2x Charter](http://www.open-std.org/jtc1/sc22/wg14/www/docs/n2086.htm)): 

    > 15. **Application Programming Interfaces (APIs) should be self-documenting when possible.** In particular, the order of parameters in function declarations should be arranged such that the size of an array appears before the array. The purpose is to allow Variable-Length Array (VLA) notation to be used. This not only makes the code's purpose clearer to human readers, but also makes static analysis easier. Any new APIs added to the Standard should take this into consideration.

    So, if you'd like to be C2x-compliant (most std C functions to date are not), then re-arrange all of my functions below to put the array size arguments _before_ the array or pointer-to-array arguments.
1. I began this answer as a response to this question: https://stackoverflow.com/questions/67811354/passing-a-pointer-to-array-to-my-function. But, it fits better here, so I'm putting it here instead. 
1. The code below is found in my [eRCaGuy_hello_world][1] repo here: [c/array_2d_practice.c][2]. It compiles and runs in both C and C++ (tested in C11 and C++17). See the build and run commands at the top of the source code file. I use gcc build options `-Wall -Wextra -Werror` for safety. 
1. My answer focuses on multidimensional 2D arrays, but could be easily extended to any number of dimensions: 3D, 4D, 5D, etc...ND arrays. 
1. I use `const` in my print functions since I'm just printing the arrays and not modifying them. Remove `const` if you ever need to modify the arrays in-place.


## Array Notes to be aware of first:

#### 1. Fixed vs unspecified dimensions:

Arrays must be **fixed (specified) size** on all dimensions except the 1st (outermost) dimension, which can optionally be unspecified.

```c
// OK; 1D array with unspecified 1st (and only) dimension
int array[] = {1, 2, 3};
// OK; 2D array with unspecified 1st dimensions
int array[][2] = {{1, 2}, {3, 4}};
// NOT allowed; 2D array with both dimensions unspecified!:
// `error: array type has incomplete element type ‘int[]’`
int array[][] = {{1, 2}, {3, 4}};
```

#### 2. Natural type decay of array types:

First, let me distinguish between "array types", and "pointers to array types". "Array types" are arrays, and "pointers to array types" are pointers. Pointers cannot decay to (AKA "adjust" to become) pointers, because they are _already_ pointers. Arrays, however can and do decay to ("adjust" to become) pointers. 

(1) So, here are some examples of **array types**, meaning they are just regular **"arrays"**: `int array_2d[][2]`, `int* array_2d[]`, `int array_2d[3][2]`. The first is a 2D array of ints, the 2nd is a 1D array of `int*`, and the 3rd is a 2D array of ints.  

(2) However, this is a **ptr to array type**, or **"pointer to array"**: `int (*array_2d)[3][2]`. The ptrs to arrays always have the parenthesis around the asterisk, like this: `(*)`, just before the square braces. That's how you can recognize them. So, the first 3 arrays just above decay to ptrs when used as arguments, whereas the last one does not, since it's already a ptr.

**The principle is:** when used as function parameters, all **array types** (but NOT ptrs to array types) decay the first dimension down into a ptr, whether that dimension's size is explicitly specified or not! So, although `int arr[]` (array of ints) and `int * arr` (pointer to an int) are NOT the same types, a function definition with either of those in it will naturally decay the 1st dimension in the array (which is the only dimension in this 1D array case) down to a pointer, resulting in type (`int * arr`) being passed to the function in both cases:

```c
// accepts `int *` as `array` parameter
void my_func(int * array, size_t len) {}
// also accepts `int *` as `array` parameter, since the `int []` type 
// (array of ints) naturally decays down to type `int *` (ptr to int`).
void my_func(int array[], size_t len) {}
```

Taking this further, specifying the size to the first dimension on the array has no bearing on this effect. ie: it makes no difference whatsoever and is meaningless to the compiler. It simply serves as a _visual indicator_ or type of "self documentation" _to the programmer_ is all, that this particular function expects an array of at least this size or larger. See my answer here (https://stackoverflow.com/questions/6567742/passing-an-array-as-an-argument-to-a-function-in-c/51527502#51527502) where I talk about this and also quote the MISRA-C standard which recommends using this feature for self-documentation purposes.

So, these are all the same as the functions above too:

```c
// same as above: these ALL accept `int *` as the 1st parameter, and the 
// specified size here in square brackets [] has no effect on the compiler.
void my_func(int array[1], size_t len) {}
void my_func(int array[10], size_t len) {}
void my_func(int array[100], size_t len) {}
```

So, this is fine:
```c
int array[10];
my_func(array); // ok; `array` naturally decays down to type `int *`
```

And this is fine too:
```c
int array[10];
int * array_p = array;
my_func(array_p); // ok; is already of type `int *`
```

HOWEVER, for **pointers to arrays**, the actual array type and size DOES matter, and no natural type decay from an array to a ptr occurs because the type is _already_ a ptr--to an array of a specified type and size! Read [my answer above][3].

Example: the following function REQUIRES an input parameter of type _ptr to 1D array of size 10_. It's already a ptr, so no natural type decay to a ptr occurs! Since this parameter is a _ptr_ to an array, you _must_ also pass the _address_ of the array via the `&` character when making the function calls, as shown below. Notice that only 2 of the calls below work: `my_func(&array2);` and `my_func(array2_p2);`. I went through the effort of showing all of these calls, however, to be able to explain and demonstrate the various array types and how and when they decay to pointers, and of what type.
```c
// 0. Define a function

/// `array` is a "ptr to an array of 10 ints". 
void my_func(int (*array)[10]) {}

// 1. Create arrays

int array1[5];
int *array1_p = array1; // array1_p is of type `int *` (ptr to int)
int (*array1_p2)[5] = &array1; // array1_p2 is of type `int (*)[5]` (ptr
                               // to array of 5 ints)

int array2[10];
int *array2_p = array2; // array2_p is of type `int *` (ptr to int)
int (*array2_p2)[10] = &array2; // array2_p2 is of type `int (*)[10]` (ptr
                                // to array of 10 ints)

// 2. Make some calls 

// 2.1. calling with `int array1[5]`

// FAILS! Expected `int (*)[10]` (ptr to array of 10 ints) but argument is
// of type `int *` (ptr to int); due to **natural type decay** from
// `int[5]` (array of 5 ints) to `int *` (ptr to int)
my_func(array1);

// FAILS! Expected `int (*)[10]` (ptr to array of 10 ints) but argument is
// of type `int *` (ptr to int); due to dereferencing to `int[5]` (array
// of 5 ints), followed by **natural type decay** from `int[5]`
// (array of 5 ints) to `int *` (ptr to int)
my_func(*array1_p2);

// FAILS! Expected `int (*)[10]` (ptr to array of 10 ints) but argument is
// of type `int *` (ptr to int)
my_func(array1_p);

// FAILS! Expected `int (*)[10]` (ptr to array of 10 ints) but argument is
// of type `int`; due to **natural type decay** from `int[5]` (array of
// 5 ints) to `int *` (ptr to int), in conjunction with dereferencing
// from that to `int`
my_func(*array1);

// FAILS! Expected `int (*)[10]` (ptr to array of 10 ints) but argument is
// of type `int`
my_func(*array1_p);

// FAILS! Expected `int (*)[10]` (ptr to array of 10 ints) but argument is
// of type `int (*)[5]` (ptr to array of 5 ints)
my_func(&array1);

// FAILS! Expected `int (*)[10]` (ptr to array of 10 ints) but argument is
// of type `int (*)[5]` (ptr to array of 5 ints)
my_func(array1_p2);

// FAILS! Expected `int (*)[10]` (ptr to array of 10 ints) but argument is
// of type `int (**)[5]` (ptr to "ptr to array of 5 ints")
my_func(&array1_p2);

// 2.2. calling with `int array2[10]`

// FAILS! Expected `int (*)[10]` (ptr to array of 10 ints) but argument is
// of type `int *` (ptr to int); due to **natural type decay** from
// `int[10]` (array of 10 ints) to `int *` (ptr to int)
my_func(array2);

// FAILS! Expected `int (*)[10]` (ptr to array of 10 ints) but argument is
// of type `int *` (ptr to int); due to dereferencing to `int[10]` (array
// of 10 ints), followed by **natural type decay** from `int[10]`
// (array of 10 ints) to `int *` (ptr to int)
my_func(*array2_p2);

// FAILS! Expected `int (*)[10]` (ptr to array of 10 ints) but argument is
// of type `int *` (ptr to int)
my_func(array2_p);

// FAILS! Expected `int (*)[10]` (ptr to array of 10 ints) but argument is
// of type `int`; due to **natural type decay** from `int[10]` (array of
// 10 ints) to `int *` (ptr to int), in conjunction with dereferencing
// from that to `int`
my_func(*array2);

// FAILS! Expected `int (*)[10]` (ptr to array of 10 ints) but argument is
// of type `int`
my_func(*array2_p);

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
my_func(&array2_p2);
```

#### 3. A quick reminder on pointers:

Remember that the types `int *[2]` and `int (*)[2]` are NOT the same type! The parenthesis matter! `int *[2]` is an "array of 2 `int *`s (pointers to int)", whereas `int (*)[2]` is a "ptr to an array of 2 `int`s". These are two _very_ different things.

Also, a ptr can be indexed _like an array_, which leads to the very-frequent confusion that _an array IS a ptr_, which is FALSE. An array is NOT a ptr! But, the following concept is critical to understanding the code below: `int array_2d[][2]` is a 2D array. Variable `array_2d` is of type `int [][2]` (n x 2 (2D) array of ints), which is a 2D array with an unspecified number of rows (dimension 1), and 2 columns (dimension 2). When used as a function parameter, this `int [][2]` type _naturally decays_ to type `int (*)[2]` (ptr to (1D) array of 2 ints). So, if this decayed type is a ptr, how is it still an array? Well, since a ptr can be indexed _like an array_, you can still do things like this to index into it: `array_2d[row][col]`. The outer dimension is the ptr, which is indexable as the `row`, while the inner dimension is the `[2]` (2 ints) part, which is indexable as the `col`umn since it is a sub-array within an array. This means that each row contains 2 ints, so once you index into a `row`, you then need to index into a `col`umn. So, the confusion between ptrs and arrays lies in the fact that **_all ptrs are indexable like arrays_, even though _arrays are NOT ptrs_--rather, the first dimension of all arrays (but NOT ptrs to arrays) _decays into a ptr_ when used as an argument**.


So, with the above concepts in mind, the following will make more sense. For each function definition, pay attention to what the array type is and whether or not it will naturally decay, and to what. Again, when used as function parameters, all _non-pointer_ array types decay the first dimension of the array down into a ptr, which is still indexable like an array.


## Summary of Conclusions and Recommendations for passing multidimensional arrays:

Here are my 4 use-cases and techniques to pass multi-dimensional arrays as parameters, and recommendations on when to use each. _You can see from the function prototypes and definitions for each technique the varying tradeoffs, complexities, and benefits that each offers._

Assume you have the following 2D array:
```c
int arr[][2] =
{
    {1, 2},
    {5, 6},
    {7, 8},
};
```

...and the following macro definitions:
```c
// Get the number of elements in any C array
// - from my repo here:
//   https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world/blob/master/c/utilities.h#L42
#define ARRAY_LEN(array) (sizeof(array) / sizeof(array[0]))

/// Definitions: `rows` = "rows"; `cols` = "columns"

/// Get number of rows in a 2D array
#define NUM_ROWS(array_2d) ARRAY_LEN(array_2d)

/// Get number of columns in a 2D array
#define NUM_COLS(array_2d) ARRAY_LEN(array_2d[0])
```

1. **Example 1:** Fixed-size multi-dimensional arrays: if **the 2D array is ALWAYS the same size each time (it has a FIXED number of rows, and a FIXED number of columns)** (3 rows and 2 columns in the below example), do this:
    ```c
    // 1. Function definition
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

    // 2. Basic usage
    // NB: `&` is REQUIRED! See my answer for why: https://stackoverflow.com/a/51527502/4561887
    print_array2(&arr);

    // 3. Usage via a pointer
    // `int (*array_2d)[3][2]` is an explicit ptr to a 3x2 array of `int`. This
    // pointer to an array does NOT naturally decay to a simpler type.
    int (*p2)[3][2] = &arr; // must use `&` and MUST USE THESE PARENTHESIS!
    print_array2(p2);
    ```
2. **Example 2:** If **the 2D array has a VARIABLE number of rows, but a FIXED number of columns** (2 in this case),
    do this:
    ```c
    // 1. Function definition
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

    // 2. Basic usage
    print_array3(arr, NUM_ROWS(arr));

    // 3. Usage via a pointer
    // `int array_2d[][2]` (n x 2 (2D) array of ints) naturally decays to 
    // `int (*)[2]` (ptr to (1D) array of 2 ints)
    int (*p3)[2] = arr; // MUST USE THESE PARENTHESIS!
    print_array3(p3, NUM_ROWS(arr));
    ```
3. **Example 3:** If **the 2D array has a VARIABLE number of rows AND a VARIABLE number of columns**, do this (_this
   approach is the most-versatile and is therefore generally my overall preferred approach, and go-to approach for multidimensional arrays_):
    ```c
    // 1. Function definition
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

    // 2. Basic usage
    print_array4((int *)arr, NUM_ROWS(arr), NUM_COLS(arr));
    // OR: alternative call technique:
    print_array4(&arr[0][0], NUM_ROWS(arr), NUM_COLS(arr));

    // 3. Usage via a pointer
    // The easiest one by far!
    int *p4_1 = (int*)arr;
    // OR
    int *p4_2 = &arr[0][0];
    print_array4(p4_1, NUM_ROWS(arr), NUM_COLS(arr));
    print_array4(p4_2, NUM_ROWS(arr), NUM_COLS(arr));
    ```

If you have the following "2D" array, however, you must do something different:
```c
// Each row is an array of `int`s.
int row1[] = {1, 2};
int row2[] = {5, 6};
int row3[] = {7, 8};
// This is an array of `int *`, or "pointer to int". The blob of all rows
// together does NOT have to be in contiguous memory. This is very different
// from the `arr` array above, which contains all data in contiguous memory.
int* all_rows[] = {row1, row2, row3}; // "2D" array
```

4. **Example 4:** If **the 2D array is actually built up of a bunch of ptrs to other arrays** (as shown just above),
   do this:
    ```c
    // 1. Function definition
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
    ///             memory, but the total _storage space_ for the combined total of
    ///             all rows can be in NON-contiguous memory. Again, this is VERY
    ///             different from every other function above.
    /// \param[in]  array_2d    a 2D array; is of type `int * []` (array of ptrs to
    ///                         int) (where each ptr is a sub-array of ints);
    ///                         `int * []` naturally decays to type `int**` (ptr to
    ///                         "ptr to int")
    /// \param[in]  num_rows    The number of rows in the array (number of elements
    ///                         in the `array_2d` outer array)
    /// \param[in]  num_cols    The number of columns in the array (number of
    ///                         elements in each sub-array)
    /// \return     None
    void print_array5(const int* array_2d[], size_t num_rows, size_t num_cols)
    {
        printf("print_array5:\n");

        printf("--- Technique 1: use `row_start[col]` ---\n");
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

        printf("--- Technique 2: use `array_2d[row][col]` ---\n");
        for (size_t row = 0; row < num_rows; row++)
        {
            for (size_t col = 0; col < num_cols; col++)
            {
                // OR you can simply do this!
                printf("array_2d[%zu][%zu]=%i ", row, col, array_2d[row][col]);
            }
            printf("\n");
        }

        printf("\n");
    }

    // 2. Basic usage
    print_array5(all_rows, ARRAY_LEN(all_rows), ARRAY_LEN(row1));

    // 3. Usage via a pointer
    //
    // 3.1. Easier way: ptr to "ptr to int"; note: `int* array_2d[]` naturally
    // decays to `int**`.
    const int **p5_1 = all_rows;
    print_array5(p5_1, ARRAY_LEN(all_rows), ARRAY_LEN(row1));
    //
    // 3.2. OR this more-complicated way, for the sake of demonstration:
    // ptr to array of 3 `int*`s
    const int* (*p5_2)[ARRAY_LEN(all_rows)] = &all_rows;
    // Explanation: the type of `p5_2` is `int* (*)[3]` (ptr to array of 3
    // int*), so the type of `*p5_2` is `int* [3]` (array of 3 int*), which
    // decays naturally to `int**`, which is what `*p5_2` ends up passing to
    // this function call! So, this call to `print_array5()` here and the one
    // just above are therefore exactly identical!
    print_array5(*p5_2, ARRAY_LEN(all_rows), ARRAY_LEN(row1));
    ```


## Don't forget about structs!

Don't forget, however, that sometimes, just using structs is so much easier! 

Example:

```c
typedef struct data_s
{
    int x;
    int y;
} data_t;

// Array of the above struct
data_t data_array[] =
{
    {1, 2},
    {5, 6},
    {7, 8},
};

void print_struct_data(data_t * data, size_t len)
{
    for (size_t i = 0; i < len; i++)
    {
        printf("[data[%zu].x, data[%zu].y] = [%i, %i]\n",
               i, i, data[i].x, data[i].y);
    }
    printf("\n");
}

print_struct_data(data_array, ARRAY_LEN(data_array));
```

Output:

>     [data[0].x, data[0].y] = [1, 2]
>     [data[1].x, data[1].y] = [5, 6]
>     [data[2].x, data[2].y] = [7, 8]


## The full, runnable code:

The full, runnable code causes this answer to exceed the 30000 max chars allowed in an answer. So, download the full code here: [c/array_2d_practice.c][2], in my [eRCaGuy_hello_world][1] repo. 

Sample output (reduced; please run the full code yourself):

> ```
> print_array1:
> array_2d[0][0]=1 array_2d[0][1]=2
> array_2d[1][0]=5 array_2d[1][1]=6
> array_2d[2][0]=7 array_2d[2][1]=8
> 
> print_array2:
> array_2d[0][0]=1 array_2d[0][1]=2
> array_2d[1][0]=5 array_2d[1][1]=6
> array_2d[2][0]=7 array_2d[2][1]=8
> 
> print_array3:
> --- Technique 1: ---
> array_2d[0][0]=1 array_2d[0][1]=2
> array_2d[1][0]=5 array_2d[1][1]=6
> array_2d[2][0]=7 array_2d[2][1]=8
> --- Technique 2: ---
> array_2d_ptr[0][0]=1 array_2d_ptr[0][1]=2
> array_2d_ptr[1][0]=5 array_2d_ptr[1][1]=6
> array_2d_ptr[2][0]=7 array_2d_ptr[2][1]=8
> 
> print_array4:
> --- Technique 1: ---
> array_2d[0][0]=1 array_2d[0][1]=2
> array_2d[1][0]=5 array_2d[1][1]=6
> array_2d[2][0]=7 array_2d[2][1]=8
> --- Technique 2: ---
> array_2d_ptr[0][0]=1 array_2d_ptr[0][1]=2
> array_2d_ptr[1][0]=5 array_2d_ptr[1][1]=6
> array_2d_ptr[2][0]=7 array_2d_ptr[2][1]=8
> 
> print_array5:
> --- Technique 1: use `row_start[col]` ---
> ...
> --- Technique 2: use `array_2d[row][col]` ---
> ...
> 
> Don't forget about just using structs and arrays of structs instead, which
> is sometimes much easier!
> 
> [data[0].x, data[0].y] = [1, 2]
> [data[1].x, data[1].y] = [5, 6]
> [data[2].x, data[2].y] = [7, 8]
> ```


## References:
1. The main reference I used: _my own answer_ containing information on "Forcing type safety on arrays in C", and how to interpret and read 1D pointers to arrays like this: `int (*a)[2]`: https://stackoverflow.com/questions/6567742/passing-an-array-as-an-argument-to-a-function-in-c/51527502#51527502
1. https://www.geeksforgeeks.org/pass-2d-array-parameter-c/


## Related/See Also:
1. [my answer] [How to make a 1D PROGMEM array of 2D PROGMEM arrays](https://stackoverflow.com/a/72624681/4561887) - I borrowed heavily from my "Example 2" code above to write this answer where I use PROGMEM to store and read an array of 2D arrays into Flash memory on an AVR/Arduino microcontroller.
1. [my answer] [Arduino Stack Exchange: Initializing Array of structs][4]
1. [my answer which references this answer] https://stackoverflow.com/questions/67811354/passing-a-pointer-to-array-to-my-function/67814569#67814569 


  [1]: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world
  [2]: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world/blob/master/c/array_2d_practice.c
  [3]: https://stackoverflow.com/a/51527502/4561887
  [4]: https://arduino.stackexchange.com/questions/80236/initializing-array-of-structs/80289#80289
