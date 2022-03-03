/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

Read a file in C into a C-string (array of chars), while also placing pointers to the start of each
line into another array of `char *`. This way you have all the data plus the
individually-addressable lines. Use static memory allocation, not dynamic, for these reasons:
1. It's a good demo.
2. It's faster at run-time since lots of dynamic memory allocation can add substantial overhead.
3. It's deterministic to use static memory allocation, making this implementation style good for
   safety-critical, memory-constrained, real-time, deterministic, embedded devices and programs.

STATUS: wip

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

*/

#include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`


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

// Make this huge struct `static` so that the buffers it contains will be `static` so that they are
// neither on the stack **nor** the heap, thereby preventing stack overflow in the event you make
// them larger than the stack size, which is ~7.4 MB for Linux. See my answer here:
// https://stackoverflow.com/a/64085509/4561887.
static file_t file;

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("The size of the `file_t` struct is %zu bytes.\n", sizeof(file_t));

    const char FILENAME[] = __FILE__;
    printf("Loading file \"%s\".\n", FILENAME);



    return 0;
}

/*
SAMPLE OUTPUT:

In C:

    eRCaGuy_hello_world/c$ gcc -Wall -Wextra -Werror -O3 -std=c17 read_file_into_c_string_and_array_of_lines.c -o bin/a && bin/a
    Hello World.


OR, in C++:

    eRCaGuy_hello_world/c$ g++ -Wall -Wextra -Werror -O3 -std=c++17 read_file_into_c_string_and_array_of_lines.c -o bin/a && bin/a
    Hello World.


*/
