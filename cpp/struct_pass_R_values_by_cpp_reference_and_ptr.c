/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

Gabriel Staples
25 Feb. 2022

Ask for help on Stack Overflow on how to disable this fpermisive warning and error. Search for
"How do I disable this" in my comments below for the full question and context.
SEE MY QUESTION: https://stackoverflow.com/q/71270747/4561887
SEE MY ANSWER: https://stackoverflow.com/a/71270918/4561887

STATUS: works!

To compile and run (assuming you've already `cd`ed into this dir):
1. In C
```bash
gcc -Wall -Wextra -Werror -O3 -std=c17 struct_pass_R_values_by_cpp_reference_and_ptr.c -o bin/a && bin/a
```
1. In C++
```bash
g++ -Wall -Wextra -Werror -O3 -std=c++17 struct_pass_R_values_by_cpp_reference_and_ptr.c -o bin/a && bin/a
```

References:
1. eRCaGuy_hello_world/c/struct_pass_R_values_and_L_values_by_value_and_reference.c
1. My Q: gcc c++ how to disable the `-Wno-error=permissive` error when `-fpermissive` and `-Werror`
   are both on? - https://stackoverflow.com/q/71270747/4561887
    1. SEE MY ANSWER: https://stackoverflow.com/a/71270918/4561887


*/


// C++ includes
#ifdef __cplusplus
    #include <iostream>  // For `std::cin`, `std::cout`, `std::endl`, etc.
#endif

// C includes
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`

typedef struct data_s
{
    int i1;
    int i2;
} data_t;

void print_data_passed_by_ptr(const data_t *data)
{
    printf("  i1 = %i\n"
           "  i2 = %i\n\n",
           data->i1,
           data->i2);
}

#ifdef __cplusplus
void print_data_passed_by_cpp_reference(const data_t& data)
{
    printf("  i1 = %i\n"
           "  i2 = %i\n\n",
           data.i1,
           data.i2);
}
#endif

// =============== TO HANDLE BOTH C **AND** C++ START ==========================
#ifndef __cplusplus
// For C
void print_data(const data_t *data)
{
    printf("  i1 = %i\n"
           "  i2 = %i\n\n",
           data->i1,
           data->i2);
}
#else
// For C++
void print_data(const data_t& data)
{
    printf("  i1 = %i\n"
           "  i2 = %i\n\n",
           data.i1,
           data.i2);
}
#endif


#ifndef __cplusplus
// For C
#define DATA_T &(data_t)
#else
// For C++
#define DATA_T  // leave empty
#endif
// =============== TO HANDLE BOTH C **AND** C++ END ==========================


// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Hello world.\n\n");

    // Pass R-value struct to each print function

#ifndef __cplusplus
    // for C only

    // Error if you try to compile this as C++:
    //      error: taking address of temporary [-fpermissive]
    // Add `-fpermissive` to the C++ build command:
    //      g++ -Wall -Wextra -Werror -O3 -std=c++17 -fpermissive struct_pass_R_values_by_cpp_reference_and_ptr.c -o bin/a && bin/a
    // Now you get:
    //      `error: taking address of temporary [-Werror=permissive]`
    // Q: How do I disable this `-Werror=permissive` error? Trying `-Wno-error=permissive` fails
    // with:
    //      `cc1plus: error: -Werror=permissive: no option -Wpermissive`
    // That full cmd:
    //      g++ -Wall -Wextra -Werror -O3 -std=c++17 -fpermissive -Wno-error=permissive struct_pass_R_values_by_cpp_reference_and_ptr.c -o bin/a && bin/a
    //
    // Print R-value struct passed by ptr
    print_data_passed_by_ptr(&(data_t){
        .i1 = 7,
        .i2 = 8,
    });
#endif

#ifdef __cplusplus
    // for C++ only

    // Print R-value struct passed by C++ reference
    print_data_passed_by_cpp_reference({
        .i1 = 9,
        .i2 = 10,
    });
#endif

    // =============== FOR BOTH C **AND** C++! ==========================
    // SEE MY ANSWER: https://stackoverflow.com/a/71270918/4561887
    //
    // Print R-value struct passed by C++ reference, OR by C ptr, depending on
    // whether this code is compiled as C or C++
    print_data(DATA_T{
        .i1 = 9,
        .i2 = 10,
    });


    return 0;
}



/*
SAMPLE OUTPUT:

As C:

    eRCaGuy_hello_world/cpp$ gcc -Wall -Wextra -Werror -O3 -std=c17 struct_pass_R_values_by_cpp_reference_and_ptr.c -o bin/a && bin/a
    Hello world.

      i1 = 7
      i2 = 8

      i1 = 9
      i2 = 10


As C++:

    eRCaGuy_hello_world/cpp$ g++ -Wall -Wextra -Werror -O3 -std=c++17 struct_pass_R_values_by_cpp_reference_and_ptr.c -o bin/a && bin/a
    Hello world.

      i1 = 9
      i2 = 10

      i1 = 9
      i2 = 10


*/
