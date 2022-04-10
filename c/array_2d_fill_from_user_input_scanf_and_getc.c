/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
9 Apr. 2022

(description)
STATUS: (status)

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# 1. In C:
gcc -Wall -Wextra -Werror -O3 -std=gnu17 array_2d_fill_from_user_input_scanf_and_getc.c -o bin/a -lm && bin/a

# 2. In C++
g++ -Wall -Wextra -Werror -O3 -std=gnu++17 array_2d_fill_from_user_input_scanf_and_getc.c -o bin/a && bin/a
```

References:
1. From this question: storing the user input to 2D array:
   https://stackoverflow.com/q/71809255/4561887
    1. *****+[my answer with this code!] How to populate a 2D array with user
       input from scanf() (with full error handling):
       https://stackoverflow.com/a/71813639/4561887
1. *****https://www.cplusplus.com/reference/cstdio/scanf/ - soooo much easier to understand than the
   reference below!
1. ****https://en.cppreference.com/w/c/io/fscanf - is more-complete than the reference above!
1. https://en.cppreference.com/w/c/string/byte/strtol
1. "array_2d_practice.c"
    1. [my answer] How to use multidimensional (ex: 2D) arrays, and pointers to
       them, as function parameters in C and C++:
       https://stackoverflow.com/a/67814330/4561887
1. "read_stdin_getc_until_only_enter_key.c"

*/

#include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`, `scanf()`


/// Get the number of elements in any C array
/// - Usage example: [my own answer]:
///   https://arduino.stackexchange.com/questions/80236/initializing-array-of-structs/80289#80289
#define ARRAY_LEN(array) (sizeof(array) / sizeof(array[0]))

// Definitions: `rows` = "rows"; `cols` = "columns"
// See usage of the next two macros in "array_2d_practice.c".
/// Get number of rows in a 2D array
#define NUM_ROWS(array_2d) ARRAY_LEN(array_2d)
/// Get number of columns in a 2D array
#define NUM_COLS(array_2d) ARRAY_LEN(array_2d[0])


/// Clear the stdin input stream by reading and discarding all incoming chars up
/// to and including the Enter key's newline ('\n') char. Once we hit the
/// newline char, stop calling `getc()`, as calls to `getc()` beyond that will
/// block again, waiting for more user input.
/// - I copied this function
///   from "eRCaGuy_hello_world/c/read_stdin_getc_until_only_enter_key.c".
/// - See my answer with this here: https://stackoverflow.com/a/71813113/4561887
void clear_stdin()
{
    // keep reading 1 more char as long as the end of the stream, indicated by
    // `EOF` (end of file), and the end of the line, indicated by the newline
    // char inserted into the stream when you pressed Enter, have NOT been
    // reached
    while (true)
    {
        int c = getc(stdin);
        if (c == EOF || c == '\n')
        {
            break;
        }
    }
}

/// \brief          Check the last `scanf()` call for errors. If there were
///     errors, print an error message and clear stdin to empty all erroneous
///     chars from it.
/// \param[in]      num_args_read   The number of arguments successfully read
///                     from stdin. This is the returned value from the last
///                     call to `scanf()`.
/// \param[in]      num_args_expected  The number of arguments the last call
///                     to `scanf()` **should have** successfully read.
/// \return         true if there were errors in the last call to `scanf()`,
///                 and false otherwise
bool check_scanf_for_error(int num_args_read, int num_args_expected)
{
    bool scanf_failed = false;

    if (num_args_read != num_args_expected)
    {
        scanf_failed = true;
        printf("ERROR reading from user via `scanf()`.\n"
               "  num_args_expected = %i, but num_args_read = %i.\n"
               "  Please try again.\n",
               num_args_expected, num_args_read);
        clear_stdin();
    }

    return scanf_failed;
}

/// \brief      Print a 2D array which has a VARIABLE number of rows and
///             VARIABLE number of columns.
/// \details    See `print_array4()` here:
///     1. "array_2d_practice.c"
///     2. [my answer] https://stackoverflow.com/a/67814330/4561887
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
void print_2d_array(const int *array_2d, size_t num_rows, size_t num_cols)
{
    printf("Printing the whole array:\n");
    // cast the `array_2d` decayed ptr to a ptr to a sized array of
    // the correct size, then use that ptr to the properly-sized array
    // directly!
    int (*array_2d_ptr)[num_rows][num_cols] =
        (int (*)[num_rows][num_cols])array_2d;
    for (size_t row = 0; row < NUM_ROWS(*array_2d_ptr); row++)
    {
        for (size_t col = 0; col < NUM_COLS(*array_2d_ptr); col++)
        {
            printf("[%zu][%zu]=%-3i ", row, col, (*array_2d_ptr)[row][col]);
        }
        printf("\n");
    }
    printf("\n");
}

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    int num_args_read;
    int num_args_expected;
    // will be set to true if the last `scanf()` call had errors
    bool scanf_failed;

    printf("Read integers from a user and fill them into a 2D array.\n\n");

    printf("Below, you will enter the number of rows and columns to use for\n"
           "your square matrix. Ex: if you enter 4, it will be a 4x4 matrix,\n"
           "and you'll have to enter 4x4 = 16 numbers. Max allowed num without\n"
           "stack overflow on Linux with glibc is 1447, because that\n"
           "is the number that maxes out the 8 MiB stack size. See here:\n"
           "https://stackoverflow.com/a/64085509/4561887. Calculation:\n"
           "1447^2 x 4 bytes per int = 8375236 bytes / 1024 bytes/KiB /\n"
           "1024 KiB/MiB = 7.987 MiB. Any higher than 1447 therefore\n"
           "will cause a stack overflow and you'll see \"Segmentation\n"
           "fault (core dumped)\".\n\n");

    size_t num_rows_and_cols;

    // Repeatedly try to read user input until the user inputs valid data.
    // Set `scanf_failed` to true to get the while loop below to run at least
    // once.
    scanf_failed = true;
    while (scanf_failed)
    {
        // Note: to receive inputs > 1447, you'll have to **dynamically**
        // allocate memory onto the heap via `malloc()` rather than
        // **statically** allocating it onto the stack as we do when we create
        // the `array_2d` below.
        printf("Enter the number of rows and columns to use for your square "
               "matrix: ");
        num_args_read = scanf("%zu", &num_rows_and_cols);
        num_args_expected = 1;
        scanf_failed = check_scanf_for_error(num_args_read, num_args_expected);
    }
    printf("You entered %zu, so your square matrix will have %zu rows and\n"
           "columns each, for a total of %zu x %zu = %zu elements.\n",
           num_rows_and_cols, num_rows_and_cols, num_rows_and_cols,
           num_rows_and_cols, num_rows_and_cols*num_rows_and_cols);

    // Create the 2D array of the proper size. See the note and printed string
    // above. Any `num_rows_and_cols` value > 1447 will cause stack overflow,
    // so to go larger than that you'd have to use `malloc()` instead.
    int array_2d[num_rows_and_cols][num_rows_and_cols];

    // Fill in the 2D array with user input, one element at a time
    for (size_t i_row = 0; i_row < NUM_ROWS(array_2d); i_row++)
    {
        for (size_t i_col = 0; i_col < NUM_COLS(array_2d); i_col++)
        {
            // Repeatedly try to read user input until the user inputs valid
            // data. Set to true to get the while loop below to run at least
            // once.
            scanf_failed = true;
            while (scanf_failed)
            {
                printf("Enter an integer in hex, octal, or decimal, for "
                       "[row][col] [%zu][%zu]: ", i_row, i_col);
                num_args_read = scanf("%i", &array_2d[i_row][i_col]);
                num_args_expected = 1;
                scanf_failed = check_scanf_for_error(num_args_read,
                    num_args_expected);
            }
        }
    }

    // print the 2D array
    print_2d_array((int*)array_2d, NUM_ROWS(array_2d), NUM_COLS(array_2d));

    return 0;
}

/*
SAMPLE OUTPUT:

In C:

    eRCaGuy_hello_world/c$ gcc -Wall -Wextra -Werror -O3 -std=gnu17 array_2d_fill_from_user_input_scanf_and_getc.c -o bin/a -lm && bin/a
    Read integers from a user and fill them into a 2D array.

    Below, you will enter the number of rows and columns to use for
    your square matrix. Ex: if you enter 4, it will be a 4x4 matrix,
    and you'll have to enter 4x4 = 16 numbers. Max allowed num without
    stack overflow on Linux with glibc is 1447, because that
    is the number that maxes out the 8 MiB stack size. See here:
    https://stackoverflow.com/a/64085509/4561887. Calculation:
    1447^2 x 4 bytes per int = 8375236 bytes / 1024 bytes/KiB /
    1024 KiB/MiB = 7.987 MiB. Any higher than 1447 therefore
    will cause a stack overflow and you'll see "Segmentation
    fault (core dumped)".

    Enter the number of rows and columns to use for your square matrix: adddad
    ERROR reading from user via `scanf()`.
      num_args_expected = 1, but num_args_read = 0.
      Please try again.
    Enter the number of rows and columns to use for your square matrix: dddd
    ERROR reading from user via `scanf()`.
      num_args_expected = 1, but num_args_read = 0.
      Please try again.
    Enter the number of rows and columns to use for your square matrix: 3
    You entered 3, so your square matrix will have 3 rows and
    columns each, for a total of 3 x 3 = 9 elements.
    Enter an integer in hex, octal, or decimal, for [row][col] [0][0]: 1
    Enter an integer in hex, octal, or decimal, for [row][col] [0][1]: 2
    Enter an integer in hex, octal, or decimal, for [row][col] [0][2]: 0xA
    Enter an integer in hex, octal, or decimal, for [row][col] [1][0]: 4
    Enter an integer in hex, octal, or decimal, for [row][col] [1][1]: 5
    Enter an integer in hex, octal, or decimal, for [row][col] [1][2]: 6
    Enter an integer in hex, octal, or decimal, for [row][col] [2][0]: 077
    Enter an integer in hex, octal, or decimal, for [row][col] [2][1]: 8
    Enter an integer in hex, octal, or decimal, for [row][col] [2][2]: 9
    Printing the whole array:
    [0][0]=1   [0][1]=2   [0][2]=10
    [1][0]=4   [1][1]=5   [1][2]=6
    [2][0]=63  [2][1]=8   [2][2]=9




OR, in C++:




*/
