///usr/bin/env ccache gcc -Wall -Wextra -Werror -O3 -std=gnu17 "$0" -o /tmp/a -lm && /tmp/a "$@"; exit
// For the line just above, see my answer here: https://stackoverflow.com/a/75491834/4561887

/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
Mar. 2024

Print or display or otherwise put into a compile-time error a message containing a struct or
variable or data type **size** at compile-time!

STATUS: Done and works!

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
gcc sizeof_compile_time__print_sizeof_struct_or_datatype.c -o bin/a && bin/a

./sizeof_compile_time__print_sizeof_struct_or_datatype.c
# or:
gcc -Wall -Wextra -Werror -O3 -std=gnu17 sizeof_compile_time__print_sizeof_struct_or_datatype.c -o bin/a -lm && bin/a

# 2. In C++
# The most basic form that needs to work:
g++ sizeof_compile_time__print_sizeof_struct_or_datatype.c -o bin/a && bin/a

g++ -Wall -Wextra -Werror -O3 -std=gnu++17 sizeof_compile_time__print_sizeof_struct_or_datatype.c -o bin/a && bin/a
```

References:
1. See: "eRCaGuy_hello_world/c/sizeof_compile_time_lib.h"


*/


#include <stdbool.h> // For `bool` type
#include <stdio.h>   // For `printf()`


typedef struct My_struct_s
{
              // For my X86-64 Linux machine:
    bool b;   // 1 byte + 3 padding bytes
    int i;    // 4 bytes
    float f;  // 4 bytes
    char c;   // 1 byte + 3 padding bytes
    double d; // 8 bytes
} My_struct;  // 24 bytes total

// Ex. 1: Globally check the size of the `My_struct` type, OR some variable. 
// Let's check the `sizeof(My_struct)` below:
#pragma GCC diagnostic push  // save the current GCC diagnostic state
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma GCC diagnostic error "-Wswitch"
// This function is required since this check is outside of all other functions
// otherwise.
void dummy_func() 
{
    typedef enum Dummy_e
    {
        DUMMY_VAL = 0
    } Dummy;
    Dummy dummy = DUMMY_VAL;
    switch (dummy)
    {
        case DUMMY_VAL:
            break;
        case sizeof(My_struct): // <== THIS CHECKS THE SIZE OF YOUR TYPE OR VAR
            break;
    }
}
#pragma GCC diagnostic pop  // restore the saved GCC diagnostic state

int main()
{
    printf("Compile-time size checks.\n\n");

    My_struct my_structs[10];

    // Ex. 2: Locally check the size of the `My_struct` type, OR  some variable. 
    // Let's check the `sizeof(my_structs)` array below:
    #pragma GCC diagnostic push  // save the current GCC diagnostic state
    #pragma GCC diagnostic error "-Wswitch"
    {
        typedef enum Dummy_e
        {
            DUMMY_VAL = 0
        } Dummy;
        Dummy dummy = DUMMY_VAL;
        switch (dummy)
        {
            case DUMMY_VAL:
                break;
            case sizeof(my_structs): // <== THIS IS THE CHECK
                break;
        }
    }
    #pragma GCC diagnostic pop  // restore the saved GCC diagnostic state


    return 0;
}


/*
SAMPLE OUTPUT:

In C:

    eRCaGuy_hello_world/c$ gcc sizeof_compile_time__print_sizeof_struct_or_datatype.c -o bin/a && bin/a
    sizeof_compile_time__print_sizeof_struct_or_datatype.c: In function ‘dummy_func’:
    sizeof_compile_time__print_sizeof_struct_or_datatype.c:80:9: error: case value ‘24’ not in enumerated type ‘Dummy’ {aka ‘enum Dummy_e’} [-Werror=switch]
       80 |         case sizeof(My_struct): // <== THIS CHECKS THE SIZE OF YOUR TYPE OR VAR
          |         ^~~~
    sizeof_compile_time__print_sizeof_struct_or_datatype.c: In function ‘main’:
    sizeof_compile_time__print_sizeof_struct_or_datatype.c:106:13: error: case value ‘240’ not in enumerated type ‘Dummy’ {aka ‘enum Dummy_e’} [-Werror=switch]
      106 |             case sizeof(my_structs): // <== THIS IS THE CHECK
          |             ^~~~
    cc1: some warnings being treated as errors



OR, in C++:

    eRCaGuy_hello_world/c$ g++ sizeof_compile_time__print_sizeof_struct_or_datatype.c -o bin/a && bin/a
    sizeof_compile_time__print_sizeof_struct_or_datatype.c: In function ‘void dummy_func()’:
    sizeof_compile_time__print_sizeof_struct_or_datatype.c:80:9: error: case value ‘24’ not in enumerated type ‘Dummy’ {aka ‘dummy_func()::Dummy_e’} [-Werror=switch]
       80 |         case sizeof(My_struct): // <== THIS CHECKS THE SIZE OF YOUR TYPE OR VAR
          |         ^~~~
    sizeof_compile_time__print_sizeof_struct_or_datatype.c: In function ‘int main()’:
    sizeof_compile_time__print_sizeof_struct_or_datatype.c:106:13: error: case value ‘240’ not in enumerated type ‘Dummy’ {aka ‘main()::Dummy_e’} [-Werror=switch]
      106 |             case sizeof(my_structs): // <== THIS IS THE CHECK
          |             ^~~~
    cc1plus: some warnings being treated as errors



*/
