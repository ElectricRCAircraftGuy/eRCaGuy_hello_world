///usr/bin/env ccache gcc -Wall -Wextra -Werror -O3 -std=gnu17 "$0" -o /tmp/a -lm && /tmp/a "$@"; exit
// For the line just above, see my answer here: https://stackoverflow.com/a/75491834/4561887

/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
Mar. 2024

Print or display or otherwise put into a compile-time error a message containing a struct or
variable or data type **size** at compile-time!

STATUS: WIP

keywords to easily grep or ripgrep in this repo for this program and what it teaches
KEYWORDS:

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# Why `-std=gnu17` vs `-std=c17`, and `-std=gnu++17` vs `-std=c++17`?
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# [run once ever] install ccache
sudo apt update && sudo apt install ccache

# 1. In C:
# The most basic form that needs to work:
gcc sizeof_struct_or_datatype__print_at_compile_time.c -o bin/a && bin/a

./sizeof_struct_or_datatype__print_at_compile_timec.c
# or:
gcc -Wall -Wextra -Werror -O3 -std=gnu17 sizeof_struct_or_datatype__print_at_compile_timec.c -o bin/a -lm && bin/a

# 2. In C++
# The most basic form that needs to work:
g++ sizeof_struct_or_datatype__print_at_compile_time.c -o bin/a && bin/a

g++ -Wall -Wextra -Werror -O3 -std=gnu++17 sizeof_struct_or_datatype__print_at_compile_timec.c -o bin/a && bin/a
```

References:
1. How can I print the result of sizeof() at compile time in C? -
   https://stackoverflow.com/q/20979565/4561887
1. Is it possible to print out the size of a C++ class at compile-time? -
   https://stackoverflow.com/q/2008398/4561887
1. https://gcc.gnu.org/onlinedocs/gcc/Diagnostic-Pragmas.html
1. Usage of `_Pragma("string")`:
    1. https://gcc.gnu.org/onlinedocs/cpp/Pragmas.html
    1. https://stackoverflow.com/a/45477830/4561887


*/


#include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`

#define COMPILE_TIME_PRINT_SIZEOF_LOCAL_VAR(variable_or_data_type) \
    /* save the current GCC diagnostic state */ \
    _Pragma("GCC diagnostic push") \
    /* Activate -Wall and -Wextra warnings, and make them become errors, */ \
    /* so that the enum and switch case below will throw a compile-time */ \
    /* error with the `variable_or_data_type`'s size printed in it! */ \
    _Pragma("GCC diagnostic error \"-Wall\"") \
    _Pragma("GCC diagnostic error \"-Wextra\"") \
    typedef enum Dummy_e \
    { \
        DUMMY_VAL = 0 \
    } Dummy; \
    Dummy dummy = DUMMY_VAL; \
    switch (dummy) \
    { \
        case DUMMY_VAL: \
            break; \
        case sizeof(variable_or_data_type): \
            break; \
    } \
    /* restore the saved GCC diagnostic state */ \
    _Pragma("GCC diagnostic pop")

#define COMPILE_TIME_PRINT_SIZEOF_GLOBAL_VAR(variable_or_data_type) \
    void dummy_func() \
    { \
        COMPILE_TIME_PRINT_SIZEOF_LOCAL_VAR(variable_or_data_type); \
    }


typedef struct My_struct_s
{
              // For my X86-64 Linux machine:
    bool b;   // 1 byte + 3 padding bytes
    int i;    // 4 bytes
    float f;  // 4 bytes
    char c;   // 1 byte + 3 padding bytes
    double d; // 8 bytes
} My_struct;  // 24 bytes total

// COMPILE_TIME_PRINT_SIZEOF_GLOBAL_VAR(My_struct);
COMPILE_TIME_PRINT_SIZEOF_GLOBAL_VAR(My_struct);

// void dummy_func()
// {
//     #pragma GCC diagnostic push  // save the current GCC diagnostic state
//     #pragma GCC diagnostic error "-Wall"
//     #pragma GCC diagnostic error "-Wextra"
//     typedef enum Dummy_e
//     {
//         DUMMY_VAL = 0
//     } Dummy;
//     Dummy dummy = DUMMY_VAL;
//     switch (dummy)
//     {
//         case DUMMY_VAL:
//             break;
//         case sizeof(My_struct):
//             break;
//     }
//     #pragma GCC diagnostic pop  // restore the saved GCC diagnostic state
// }

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Compile-time size checks.\n\n");

    My_struct my_structs[10];

    // COMPILE_TIME_PRINT_SIZEOF_LOCAL_VAR(My_struct);
    // COMPILE_TIME_PRINT_SIZEOF_LOCAL_VAR(my_structs);

    return 0;
}


/*
SAMPLE OUTPUT:

In C:

    eRCaGuy_hello_world/c$ gcc -Wall -Wextra -Werror -O3 -std=c17 sizeof_struct_or_datatype__print_at_compile_timec.c -o bin/a -lm && bin/a
    Hello World.


OR, in C++:

    eRCaGuy_hello_world/c$ g++ -Wall -Wextra -Werror -O3 -std=c++17 sizeof_struct_or_datatype__print_at_compile_timec.c -o bin/a && bin/a
    Hello World.

*/

/*
I FOUND A GCC BUG!

eRCaGuy_hello_world/c$ gcc sizeof_struct_or_datatype__print_at_compile_time.c -o bin/a && bin/a
sizeof_struct_or_datatype__print_at_compile_time.c: In function ‘dummy_func’:
sizeof_struct_or_datatype__print_at_compile_time.c:69:9: internal compiler error: Segmentation fault
   69 |         DUMMY_VAL = 0 \
      |         ^~~~~~~~~
sizeof_struct_or_datatype__print_at_compile_time.c:85:9: note: in expansion of macro ‘COMPILE_TIME_PRINT_SIZEOF_LOCAL_VAR’
   85 |         COMPILE_TIME_PRINT_SIZEOF_LOCAL_VAR(variable_or_data_type); \
      |         ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
sizeof_struct_or_datatype__print_at_compile_time.c:100:1: note: in expansion of macro ‘COMPILE_TIME_PRINT_SIZEOF_GLOBAL_VAR’
  100 | COMPILE_TIME_PRINT_SIZEOF_GLOBAL_VAR(My_struct);
      | ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
0x7f2849a4251f ???
	./signal/../sysdeps/unix/sysv/linux/x86_64/libc_sigaction.c:0
0x7f2849a29d8f __libc_start_call_main
	../sysdeps/nptl/libc_start_call_main.h:58
0x7f2849a29e3f __libc_start_main_impl
	../csu/libc-start.c:392
Please submit a full bug report,
with preprocessed source if appropriate.
Please include the complete backtrace with any bug report.
See <file:///usr/share/doc/gcc-11/README.Bugs> for instructions.


*/
