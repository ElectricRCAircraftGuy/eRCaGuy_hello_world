/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
2 Mar. 2022

Read a file in C into a C-string (array of chars), while also placing pointers to the start of each
line into another array of `char *`. This way you have all the data plus the
individually-addressable lines. Use static memory allocation, not dynamic, for these reasons:
1. It's a good demo.
1. It's faster at run-time since lots of dynamic memory allocation can add substantial overhead.
1. It's deterministic to use static memory allocation, making this implementation style good for
   safety-critical, memory-constrained, real-time, deterministic, embedded devices and programs.
1. It can access the first character of any line in the file in O(1) time via a simple index into
   an array.

STATUS: works!

To compile and run (assuming you've already `cd`ed into this dir):
1. In C:
```bash
gcc -Wall -Wextra -Werror -O3 -std=c17 read_file_into_c_string_and_array_of_lines.c -o bin/a && bin/a
```
2. In C++
```bash
g++ -Wall -Wextra -Werror -O3 -std=c++17 read_file_into_c_string_and_array_of_lines.c -o bin/a && bin/a
```

References:
1. I'm seeking to answer this question, more or less:
   [C function to load file content in string array](https://stackoverflow.com/q/71330345/4561887)
1. [my answer] TODO
1. https://en.cppreference.com/w/c/io/fopen
1. https://en.cppreference.com/w/c/string/byte/strerror - shows a good usage example of
   `printf("File opening error: %s\n", strerror(errno));` if `fopen()` fails when opening a file.
1. https://en.cppreference.com/w/c/io/fgetc


*/

#include <errno.h>
#include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`
#include <string.h>  // for `strerror()`


// Get the number of elements in any C array
// - Usage example: [my own answer]:
//   https://arduino.stackexchange.com/questions/80236/initializing-array-of-structs/80289#80289
#define ARRAY_LEN(array) (sizeof(array) / sizeof(array[0]))

/// Max and min gcc/clang **statement expressions** (safer than macros) for C. By Gabriel Staples.
/// See: https://stackoverflow.com/a/58532788/4561887
#define MAX(a, b)               \
    ({                          \
        __typeof__(a) _a = (a); \
        __typeof__(b) _b = (b); \
        _a > _b ? _a : _b;      \
    })
#define MIN(a, b)               \
    ({                          \
        __typeof__(a) _a = (a); \
        __typeof__(b) _b = (b); \
        _a < _b ? _a : _b;      \
    })

/// Bytes per megabyte
#define BYTES_PER_MB (1000*1000)
/// Bytes per mebibyte
#define BYTES_PER_MIB (1024*1024)

/// Convert bytes to megabytes
#define BYTES_TO_MB(bytes) (((double)(bytes))/BYTES_PER_MB)
/// Convert bytes to mebibytes
#define BYTES_TO_MIB(bytes) (((double)(bytes))/BYTES_PER_MIB)

#define MAX_NUM_LINES 10000UL
#define MAX_NUM_CHARS (MAX_NUM_LINES*200UL) // 2 MB

typedef struct file_s
{
    /// All characters read from the file.
    char file_str[MAX_NUM_CHARS];     // array of `char`

    /// The total number of chars read into the `file_str` string, including null terminator.
    size_t num_chars;

    /// A ptr to each line in the file.
    char* line_array[MAX_NUM_LINES];  // array of `char*` (ptr to char)

    /// The total number of lines in the file, and hence in the `line_array` above.
    size_t num_lines;
} file_t;

/// Print the entire line at 1-based line number `line_number` in file `file`, including the
/// '\n' at the end of the line.
void print_line(const file_t* file, size_t line_number)
{
    if (file == NULL)
    {
        printf("ERROR in function %s(): NULL ptr.\n", __func__);
        return;
    }

    // Ensure we don't read outside the `file->line_array`
    if (line_number > file->num_lines)
    {
        printf("ERROR in function %s(): line_number (%zu) is too large (file->num_lines = %zu).\n",
            __func__, line_number, file->num_lines);
        return;
    }

    size_t i_line = line_number - 1;
    char* line = file->line_array[i_line];
    if (line == NULL)
    {
        printf("ERROR in function %s(): line_array contains NULL ptr for line_number = %zu at "
               "index = %zu.\n", __func__, line_number, i_line);
        return;
    }

    // print all chars in the line
    size_t i_char = 0;
    while (true)
    {
        if (i_char > file->num_chars - 1)
        {
            // outside valid data
            break;
        }

        char c = line[i_char];
        if (c == '\n')
        {
            printf("%c", c);
            break;
        }
        else if (c == '\0')
        {
            // null terminator
            break;
        }

        printf("%c", c);
        i_char++;
    }
}

/// Print `num_lines` number of lines in a file, starting at 1-based line number `first_line`,
/// and including the '\n' at the end of each line.
/// At the start of each line, the line number is also printed, followed by a colon (:).
void print_lines(const file_t* file, size_t first_line, size_t num_lines)
{
    if (file == NULL)
    {
        printf("ERROR in function %s(): NULL ptr.\n", __func__);
        return;
    }

    if (num_lines == 0 || file->num_lines == 0)
    {
        printf("ERROR in function %s(): num_lines passed in == %zu; file->num_lines = %zu.\n",
            __func__, num_lines, file->num_lines);
        return;
    }

    // Ensure we don't read outside the valid data
    size_t last_line = MIN(first_line + num_lines - 1, file->num_lines);
    // printf("last_line = %zu\n", last_line); // DEBUGGING
    for (size_t line_number = first_line; line_number <= last_line; line_number++)
    {
        printf("%4lu: ", line_number);
        print_line(file, line_number);
    }
}

/// Print an entire file.
void print_file(const file_t* file)
{
    printf("num_chars to print = %zu\n", file->num_chars);
    printf("num_lines to print = %zu\n", file->num_lines);
    printf("========== FILE START ==========\n");
    print_lines(file, 1, file->num_lines);
    printf("=========== FILE END ===========\n");
}

/// Read all characters from a file on your system at path `path` into file object `file`.
void load_file(file_t* file, const char* path)
{
    FILE* fp = fopen(path, "r");
    if (fp == NULL)
    {
        printf("ERROR in function %s(): Failed to open file (%s).\n", __func__, strerror(errno));
        return;
    }

    // See: https://en.cppreference.com/w/c/io/fgetc
    int c; // note: int, not char, required to handle EOF
    size_t i_write_char = 0;
    size_t i_write_line = 0;
    bool start_of_line = true;
    const size_t I_WRITE_CHAR_MAX = ARRAY_LEN(file->file_str) - 1;
    const size_t I_WRITE_LINE_MAX = ARRAY_LEN(file->line_array) - 1;
    while ((c = fgetc(fp)) != EOF) // standard C I/O file reading loop
    {
        // 1. Write the char
        if (i_write_char > I_WRITE_CHAR_MAX)
        {
            printf("ERROR in function %s(): file is full (i_write_char = %zu, but "
                   "I_WRITE_CHAR_MAX is only %zu).\n",
                   __func__, i_write_char, I_WRITE_CHAR_MAX);
            break;
        }
        file->file_str[i_write_char] = c;

        // 2. Write the ptr to the line
        if (start_of_line)
        {
            start_of_line = false;

            if (i_write_line > I_WRITE_LINE_MAX)
            {
                printf("ERROR in function %s(): file is full (i_write_line = %zu, but "
                       "I_WRITE_LINE_MAX is only %zu).\n",
                       __func__, i_write_line, I_WRITE_LINE_MAX);
                break;
            }
            file->line_array[i_write_line] = &(file->file_str[i_write_char]);
            i_write_line++;
        }

        // end of line
        if (c == '\n')
        {
            // '\n' indicates the end of a line, so prepare to start a new line on the next
            // iteration
            start_of_line = true;
        }

        i_write_char++;
    }

    file->num_chars = i_write_char;
    file->num_lines = i_write_line;

    fclose(fp);
}

// Make this huge struct `static` so that the buffers it contains will be `static` so that they are
// neither on the stack **nor** the heap, thereby preventing stack overflow in the event you make
// them larger than the stack size, which is ~7.4 MB for Linux. See my answer here:
// https://stackoverflow.com/a/64085509/4561887.
static file_t file;

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("The size of the `file_t` struct is %zu bytes (%.6f MB; %.6f MiB).\n"
           "Max file size that can be read into this struct is %zu bytes or %lu lines, whichever "
           "limit is hit first.\n\n",
           sizeof(file_t), BYTES_TO_MB(sizeof(file_t)), BYTES_TO_MIB(sizeof(file_t)),
           sizeof(file.file_str), ARRAY_LEN(file.line_array));

    const char FILENAME[] = __FILE__;
    printf("Loading file \"%s\".\n", FILENAME);
    load_file(&file, FILENAME);
    print_file(&file);
    printf("\n");

    printf("Printing just one line now:\n");
    print_lines(&file, 254, 1);
    printf("\n");

    // FOR TESTING: intentionally cause some errors by trying to print some lines for an unpopulated
    // file object. Example errors:
    //      243: ERROR in function print_line(): line_array contains NULL ptr for line_number = 243 at index = 242.
    //      244: ERROR in function print_line(): line_array contains NULL ptr for line_number = 244 at index = 243.
    //      245: ERROR in function print_line(): line_array contains NULL ptr for line_number = 245 at index = 244.
    //      246: ERROR in function print_line(): line_array contains NULL ptr for line_number = 246 at index = 245.
    // Note: for kicks (since I didn't realize this was possible), I'm also using the variable name
    // `$` for this `file_t` object.
    printf("Causing some intentional errors here:\n");
    file_t $;
    print_lines(&$, 243, 4);


    return 0;
}

// SAMPLE OUTPUT:
//
// In C:
//
//  eRCaGuy_hello_world/c$ gcc -Wall -Wextra -Werror -O3 -std=c17 read_file_into_c_string_and_array_of_lines.c -o bin/a && bin/a
//  The size of the `file_t` struct is 2080016 bytes (2.080016 MB; 1.983658 MiB).
//  Max file size that can be read into this struct is 2000000 bytes or 10000 lines, whichever limit is hit first.
//
//  Loading file "read_file_into_c_string_and_array_of_lines.c".
//  num_chars to print = 10311
//  num_lines to print = 304
//  ========== FILE START ==========
//     1: /*
//     2: This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world
//     3:
//     4: GS
//     5: 2 Mar. 2022
//     6:
//     7: Read a file in C into a C-string (array of chars), while also placing pointers to the start of each
//     8: line into another array of `char *`. This way you have all the data plus the
//     9: individually-addressable lines. Use static memory allocation, not dynamic, for these reasons:
//    10: 1. It's a good demo.
//    11: 1. It's faster at run-time since lots of dynamic memory allocation can add substantial overhead.
//    12: 1. It's deterministic to use static memory allocation, making this implementation style good for
//    13:    safety-critical, memory-constrained, real-time, deterministic, embedded devices and programs.
//    14: 1. It can access the first character of any line in the file in O(1) time via a simple index into
//    15:    an array.
//    16:
//    17: STATUS: works!
//    18:
//    19: To compile and run (assuming you've already `cd`ed into this dir):
//    20: 1. In C:
//    21: ```bash
//    22: gcc -Wall -Wextra -Werror -O3 -std=c17 read_file_into_c_string_and_array_of_lines.c -o bin/a && bin/a
//    23: ```
//    24: 2. In C++
//    25: ```bash
//    26: g++ -Wall -Wextra -Werror -O3 -std=c++17 read_file_into_c_string_and_array_of_lines.c -o bin/a && bin/a
//    27: ```
//    28:
//    29: References:
//    30: 1. I'm seeking to answer this question, more or less:
//    31:    [C function to load file content in string array](https://stackoverflow.com/q/71330345/4561887)
//    32: 1. [my answer] TODO
//    33: 1. https://en.cppreference.com/w/c/io/fopen
//    34: 1. https://en.cppreference.com/w/c/string/byte/strerror - shows a good usage example of
//    35:    `printf("File opening error: %s\n", strerror(errno));` if `fopen()` fails when opening a file.
//    36: 1. https://en.cppreference.com/w/c/io/fgetc
//    37:
//    38:
//      .
//      .
//      .
//   274:
//   275:     // FOR TESTING: intentionally cause some errors by trying to print some lines for an unpopulated
//   276:     // file object. Example errors:
//   277:     //      243: ERROR in function print_line(): line_array contains NULL ptr for line_number = 243 at index = 242.
//   278:     //      244: ERROR in function print_line(): line_array contains NULL ptr for line_number = 244 at index = 243.
//   279:     //      245: ERROR in function print_line(): line_array contains NULL ptr for line_number = 245 at index = 244.
//   280:     //      246: ERROR in function print_line(): line_array contains NULL ptr for line_number = 246 at index = 245.
//   281:     // Note: for kicks (since I didn't realize this was possible), I'm also using the variable name
//   282:     // `$` for this `file_t` object.
//   283:     printf("Causing some intentional errors here:\n");
//   284:     file_t $;
//   285:     print_lines(&$, 243, 4);
//   286:
//   287:
//   288:     return 0;
//   289: }
//   290:
//   291: /*
//   292: SAMPLE OUTPUT:
//   293:
//   294: In C:
//   295:
//   296:     eRCaGuy_hello_world/c$ gcc -Wall -Wextra -Werror -O3 -std=c17 read_file_into_c_string_and_array_of_lines.c -o bin/a && bin/a
//   297:
//   298:
//   299: OR, in C++:
//   300:
//   301:     eRCaGuy_hello_world/c$ g++ -Wall -Wextra -Werror -O3 -std=c++17 read_file_into_c_string_and_array_of_lines.c -o bin/a && bin/a
//   302:
//   303:
//   304: */
//  =========== FILE END ===========
//
//  Printing just one line now:
//   255:
//
//  Causing some intentional errors here:
//   243: ERROR in function print_line(): line_array contains NULL ptr for line_number = 243 at index = 242.
//   244: ERROR in function print_line(): line_array contains NULL ptr for line_number = 244 at index = 243.
//   245: ERROR in function print_line(): line_array contains NULL ptr for line_number = 245 at index = 244.
//   246: ERROR in function print_line(): line_array contains NULL ptr for line_number = 246 at index = 245.
//
//
// OR, in C++:
//
// [SAME AS THE C OUTPUT]
