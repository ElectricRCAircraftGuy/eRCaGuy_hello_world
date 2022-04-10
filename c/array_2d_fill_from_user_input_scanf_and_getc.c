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
1. *****https://www.cplusplus.com/reference/cstdio/scanf/ - soooo much easier to understand than the
   reference below!
1. ****https://en.cppreference.com/w/c/io/fscanf - is more-complete than the reference above!
1. https://en.cppreference.com/w/c/string/byte/strtol

*/

#include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`, `scanf()`


/// Get the number of elements in any C array
/// - Usage example: [my own answer]:
///   https://arduino.stackexchange.com/questions/80236/initializing-array-of-structs/80289#80289
#define ARRAY_LEN(array) (sizeof(array) / sizeof(array[0]))

/// Definitions: `rows` = "rows"; `cols` = "columns"
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

/// \brief          Check the last `scanf()` call for errors. If there were errors, print an error
///                 message and clear stdin to empty all erroneous chars from it.
/// \param[in]      num_args_read   The number of arguments successfully read from stdin. This
///                                 is the returned value from the last call to `scanf()`.
/// \param[in]      num_args_expected  The number of arguments the last call to `scanf()` **should
///                                 have** successfully read.
/// \return         true if there were errors in the last call to `scanf()`, and false otherwise
bool check_scanf_for_error(int num_args_read, int num_args_expected)
{
    bool scanf_failed = false;

    if (num_args_read != num_args_expected)
    {
        scanf_failed = true;
        printf("ERROR reading from user via `scanf()`. num_args_expected = %i, but "
               "num_args_read = %i. Please try again.\n", num_args_expected, num_args_read);
        clear_stdin();
    }

    return scanf_failed;
}

void print

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    int num_args_read;
    int num_args_expected;
    bool scanf_failed; // will be set to true if the last `scanf()` call had errors

    printf("Read integers from a user and fill them into a 2D array.\n\n");

    size_t num_rows_and_cols;

    // Repeatedly try to read user input until the user inputs valid data.
    scanf_failed = true; // set to true to get the while loop below to run at least once
    while (scanf_failed)
    {
        printf("Enter the number of rows and columns to use for your square matrix (ex: \n"
               "if you enter 4, it will be a 4x4 matrix, and you'll have to enter 16 \n"
               "numbers): ");
        num_args_read = scanf("%zu", &num_rows_and_cols);
        num_args_expected = 1;
        scanf_failed = check_scanf_for_error(num_args_read, num_args_expected);
    }
    printf("You entered %zu, so your square matrix will have %zu rows and columns each,\n"
           "for a total of %zu x %zu = %zu elements.\n",
           num_rows_and_cols, num_rows_and_cols, num_rows_and_cols, num_rows_and_cols,
           num_rows_and_cols*num_rows_and_cols);

    int array_2d[num_rows_and_cols][num_rows_and_cols];

    for (size_t i_row = 0; i_row < NUM_ROWS(array_2d); i_row++)
    {
        for (size_t i_col = 0; i_col < NUM_COLS(array_2d); i_col++)
        {
            // Repeatedly try to read user input until the user inputs valid data.
            scanf_failed = true; // set to true to get the while loop below to run at least once
            while (scanf_failed)
            {
                printf("Enter an integer in hex, octal, or decimal, for [row][col] [%zu][%zu]: ",
                    i_row, i_col);
                num_args_read = scanf("%i", &array_2d[i_row][i_col]);
                num_args_expected = 1;
                scanf_failed = check_scanf_for_error(num_args_read, num_args_expected);
            }
        }
    }

    return 0;
}

/*
SAMPLE OUTPUT:

In C:

    eRCaGuy_hello_world/c$ gcc -Wall -Wextra -Werror -O3 -std=c17 array_2d_fill_from_user_input_scanf_and_getc.c -o bin/a -lm && bin/a
    Hello World.


OR, in C++:

    eRCaGuy_hello_world/c$ g++ -Wall -Wextra -Werror -O3 -std=c++17 array_2d_fill_from_user_input_scanf_and_getc.c -o bin/a && bin/a
    Hello World.


*/
