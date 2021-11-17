/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
16 Nov 2021

Practice using the `system()` call to call `ls -l` in C.

To compile and run (assuming you've already `cd`ed into this dir):
1. In C:
    mkdir -p bin && gcc -Wall -Wextra -Werror -O3 -std=c11 -save-temps=obj system_call_list_files.c \
    -o bin/system_call_list_files && bin/system_call_list_files
2. In C++
    mkdir -p bin && g++ -Wall -Wextra -Werror -O3 -std=c++17 -save-temps=obj system_call_list_files.c \
    -o bin/system_call_list_files && bin/system_call_list_files

References:
1. https://www.cplusplus.com/reference/cstdlib/system/
1. https://man7.org/linux/man-pages/man3/system.3.html
1. https://www.tutorialspoint.com/c_standard_library/c_function_system.htm
1. [going further: how to run a system command and read the output back out, probably via a pipe]
    1. https://stackoverflow.com/questions/646241/c-run-a-system-command-and-get-output
    1. https://stackoverflow.com/questions/43116/how-can-i-run-an-external-program-from-c-and-parse-its-output/28971647#28971647

*/

// #include <assert.h>  // For `assert()` and `static_assert()` macro wrappers in C11
#include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
#include <stdlib.h>  // For `system()`
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("This is the start of `main()`.\n");

    // List all files
    const char CMD[] = "ls -l";
    printf("=== START OF SYSTEM CALL TO `%s` ===\n", CMD);
    int retval = system(CMD);
    printf("==== END OF SYSTEM CALL TO `%s` ====\n", CMD);
    // Check return value for error
    if (retval != 0)
    {
        printf("Unable to run system call with cmd `%s`. retval = %i\n", CMD, retval);
    }

    return 0;
}

/*
SAMPLE OUTPUT:



*/
