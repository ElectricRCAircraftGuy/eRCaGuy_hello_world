/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

Read a file in C into a C-string (array of chars), while also placing pointers to the start of each
line into another array of `char *`. This way you have all the data plus the
individually-addressable lines. Use static memory allocation, not dynamic, for these reasons:
1. It's a good demo.
2. It's faster at run-time since lots of dynamic memory allocation can add substantial overhead.
3. It's deterministic to use static memory allocation, making this implementation style good for
   safety-critical, memory-constrained, real-time, deterministic, embedded devices and programs.

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

/// Print the entire line at index `i_line` in file `file`, including the '\n' at the end of the
/// line.
void print_line(const file_t* file, size_t i_line)
{
    if (file == NULL)
    {
        printf("ERROR in function %s: NULL ptr.\n", __func__);
        return;
    }

    // Ensure we don't read outside the `file->line_array`
    if (i_line > file->num_lines - 1)
    {
        printf("ERROR in function %s: i_line (%zu) is too large (file->num_lines = %zu).\n",
            __func__, i_line, file->num_lines);
        return;
    }

    char* line = file->line_array[i_line];
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

/// Print `num_lines` number of lines in a file, starting at index `i_start`, and including the
/// '\n' at the end of each line. The line number is also printed, followed by a colon (:), at
/// the start of each line.
void print_lines(const file_t* file, size_t i_start, size_t num_lines)
{
    if (file == NULL)
    {
        printf("ERROR in function %s: NULL ptr.\n", __func__);
        return;
    }

    if (num_lines == 0)
    {
        printf("ERROR in function %s: num_lines == 0.\n", __func__);
        return;
    }

    // Ensure we don't read outside the valid data
    size_t i_end = MIN(i_start + num_lines - 1, file->num_lines - 1);
    // printf("i_end = %zu\n", i_end); // DEBUGGING
    for (size_t i_line = i_start; i_line <= i_end; i_line++)
    {
        size_t line_number = i_line + 1;
        printf("%4lu: ", line_number);
        print_line(file, i_line);
    }
}

/// Print an entire file.
void print_file(const file_t* file)
{
    printf("num_chars to print = %zu\n", file->num_chars);
    printf("num_lines to print = %zu\n", file->num_lines);
    printf("========== FILE START ==========\n");
    print_lines(file, 0, file->num_lines);
    printf("=========== FILE END ===========\n");
}

/// Read all characters from a file on your system at path `path` into file object `file`.
void load_file(file_t* file, const char* path)
{
    FILE* fp = fopen(path, "r");
    if (fp == NULL)
    {
        printf("ERROR in function %s: Failed to open file (%s).\n", __func__, strerror(errno));
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
            printf("ERROR in function %s: file is full (i_write_char = %zu, but "
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
                printf("ERROR in function %s: file is full (i_write_line = %zu, but "
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

    return 0;
}

/*
SAMPLE OUTPUT:

In C:

    eRCaGuy_hello_world/c$ gcc -Wall -Wextra -Werror -O3 -std=c17 read_file_into_c_string_and_array_of_lines.c -o bin/a && bin/a


OR, in C++:

    eRCaGuy_hello_world/c$ g++ -Wall -Wextra -Werror -O3 -std=c++17 read_file_into_c_string_and_array_of_lines.c -o bin/a && bin/a


*/
