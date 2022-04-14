/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
Mar. 2022

Demo using `fgets()` to read an input string from the user.

STATUS: done!

To compile and run (assuming you've already `cd`ed into this dir):
1. In C:
```bash
gcc -Wall -Wextra -Werror -O3 -std=c17 read_stdin_fgets_basic_input_from_user.c -o bin/a && bin/a
```
2. In C++
```bash
g++ -Wall -Wextra -Werror -O3 -std=c++17 read_stdin_fgets_basic_input_from_user.c -o bin/a && bin/a
```

References:
1. Why is the gets function so dangerous that it should not be used?:
    1. [my answer] https://stackoverflow.com/a/71366629/4561887
    1. [Jonathan Leffler's answer] https://stackoverflow.com/a/4309845/4561887
1. https://en.cppreference.com/w/c/io
1. *****https://en.cppreference.com/w/c/io/fgets
1. https://en.cppreference.com/w/c/io/gets - NEVER USE `gets()`!
1. https://en.cppreference.com/w/c/io/feof
1. https://en.cppreference.com/w/c/io/ferror
1. __func__: https://gcc.gnu.org/onlinedocs/cpp/Standard-Predefined-Macros.html
1. https://en.cppreference.com/w/c/string/byte/strlen

*/

// #include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
// #include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <errno.h>   // `errno`
#include <stdio.h>   // `printf()`, `fgets()`
#include <stdlib.h>  // `exit()`
#include <string.h>  // `strerror()`

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    char buf[10];

    // NEVER USE `gets()`! USE `fgets()` BELOW INSTEAD!

    // USE THIS!: `fgets()`: "file get string", which reads until either EOF is reached, OR a
    // newline (`\n`) is found, keeping the newline char in `buf`.
    // For `feof()` and `ferror()`, see:
    // 1. https://en.cppreference.com/w/c/io/feof
    // 1. https://en.cppreference.com/w/c/io/ferror
    printf("Enter up to %zu chars: ", sizeof(buf) - 1); // - 1 to save room for null terminator
    char* retval = fgets(buf, sizeof(buf), stdin);
    if (feof(stdin))
    {
        // Check for `EOF`, which means "End of File was reached".
        // - This doesn't really make sense on `stdin` I think, but it is a good check to have when
        //   reading from a regular file with `fgets()`. Keep it here regardless, just in case.
        printf("EOF (End of File) reached.\n");
    }
    if (ferror(stdin))
    {
        printf("Error indicator set. IO error when reading from file `stdin`.\n");
    }
    if (retval == NULL)
    {
        printf("ERROR in %s(): fgets() failed; errno = %i: %s\n",
            __func__, errno, strerror(errno));

        exit(EXIT_FAILURE);
    }

    size_t num_chars_written = strlen(buf) + 1; // + 1 for null terminator
    if (num_chars_written >= sizeof(buf))
    {
        printf("Warning: user input may have been truncated! All %zu chars were written into "
               "buffer.\n", num_chars_written);
    }
    printf("You entered \"%s\".\n", buf);


    return 0;
}

/*
SAMPLE OUTPUT:

In C:

    eRCaGuy_hello_world/c$ gcc -Wall -Wextra -Werror -O3 -std=c17 read_stdin_fgets_basic_input_from_user.c -o bin/a && bin/a
    Enter up to 9 chars: hello world!
    Warning: user input may have been truncated! All 10 chars were written into buffer.
    You entered "hello wor".

    eRCaGuy_hello_world/c$ gcc -Wall -Wextra -Werror -O3 -std=c17 read_stdin_fgets_basic_input_from_user.c -o bin/a && bin/a
    Enter up to 9 chars: hey
    You entered "hey
    ".


OR, in C++:

(same as in C)


*/
