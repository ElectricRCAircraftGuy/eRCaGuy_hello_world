///usr/bin/env ccache gcc -Wall -Wextra -Werror -O3 -std=gnu17 "$0" -o /tmp/a -lm && /tmp/a "$@"; exit
// For the line just above, see my answer here: https://stackoverflow.com/a/75491834/4561887

/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
Jan. 2024

Practice initializing and zero-initializing structs in C. 
See also: 
1. My answer: https://stackoverflow.com/a/61240590/4561887
1. Answer to my follow-up question: https://stackoverflow.com/a/61532117/4561887

STATUS: done and works!
It works in C, but NOT in C++! C++ is stricter and requires **all** elements to be specified, and/or
the elements to be specified in the **same order** as in the struct definition.

keywords to easily grep or ripgrep in this repo for this program and what it teaches
KEYWORDS:

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# Why `-std=gnu17` vs `-std=c17`, and `-std=gnu++17` vs `-std=c++17`?
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# [run once ever] install ccache
sudo apt update && sudo apt install ccache

# 1. In C:
./struct_initialization2.c
# or:
gcc -Wall -Wextra -Werror -O3 -std=gnu17 struct_initialization2.c -o bin/a -lm && bin/a

# 2. In C++
g++ -Wall -Wextra -Werror -O3 -std=gnu++17 struct_initialization2.c -o bin/a && bin/a
```

References:
1. The 2 links above. 
1. eRCaGuy_hello_world/cpp/struct_initialization.c
1. eRCaGuy_hello_world/cpp/struct_initialization.cpp
1.

*/


#include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`

typedef struct my_data_s
{
    int i1;
    int i2;
    int i3;
} my_data_t;

void print_my_data(const my_data_t* my_data)
{
    printf("my_data->i1 = %d\n", my_data->i1);
    printf("my_data->i2 = %d\n", my_data->i2);
    printf("my_data->i3 = %d\n", my_data->i3);
    printf("\n");
}

#define PRINT_MY_DATA(data) \
    do { \
        printf(#data "\n"); \
        print_my_data(&data); \
    } while (0)

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("%s\n\n", __FILE__);
    // printf("struct_initialization2.c\n\n");

    // Value initialization of all but the first member of the struct:
    // initialize first member to 0, and all the rest to defaults (also 0)
    // - See: https://stackoverflow.com/a/61532117/4561887
    my_data_t my_data1 = {0}; 
    PRINT_MY_DATA(my_data1);

    // Value initialization of all members of the struct:
    // - with no explicit initializer, all members are default-initialized to zero
    my_data_t my_data2 = {};
    PRINT_MY_DATA(my_data2);

    //      ./struct_initialization2.c:85:5: error: missing initializer for field ‘i2’ of ‘my_data_t’ {aka ‘struct my_data_s’} [-Werror=missing-field-initializers]
    //         85 |     my_data_t my_data3 = {1};
    //            |     ^~~~~~~~~
    // my_data_t my_data3 = {1};
    my_data_t my_data3 = {1, 0, 0};
    PRINT_MY_DATA(my_data3);

    // my_data_t my_data4 = {1, 2};
    my_data_t my_data4 = {.i1 = 1};
    PRINT_MY_DATA(my_data4);

    my_data_t my_data5 = {1, 2, 3};
    PRINT_MY_DATA(my_data5);

    my_data_t my_data6 = {.i1 = 1, .i2 = 2, .i3 = 3};
    PRINT_MY_DATA(my_data6);

    my_data_t my_data7 = {.i3 = 3, .i2 = 2, .i1 = 1};
    PRINT_MY_DATA(my_data7);

    my_data_t my_data8 = {.i3 = 3, .i1 = 1, .i2 = 2};
    PRINT_MY_DATA(my_data8);

    my_data_t my_data9 = {.i2 = 2};
    PRINT_MY_DATA(my_data9);

    my_data_t my_data10 = {.i2 = 2, .i3 = 3};
    PRINT_MY_DATA(my_data10);


    return 0;
}


/*
SAMPLE OUTPUT:

In C:

eRCaGuy_hello_world/c$ ./struct_initialization2.c
./struct_initialization2.c

my_data1
my_data->i1 = 0
my_data->i2 = 0
my_data->i3 = 0

my_data2
my_data->i1 = 0
my_data->i2 = 0
my_data->i3 = 0

my_data3
my_data->i1 = 1
my_data->i2 = 0
my_data->i3 = 0

my_data4
my_data->i1 = 1
my_data->i2 = 0
my_data->i3 = 0

my_data5
my_data->i1 = 1
my_data->i2 = 2
my_data->i3 = 3

my_data6
my_data->i1 = 1
my_data->i2 = 2
my_data->i3 = 3

my_data7
my_data->i1 = 1
my_data->i2 = 2
my_data->i3 = 3

my_data8
my_data->i1 = 1
my_data->i2 = 2
my_data->i3 = 3

my_data9
my_data->i1 = 0
my_data->i2 = 2
my_data->i3 = 0

my_data10
my_data->i1 = 0
my_data->i2 = 2
my_data->i3 = 3



OR, in C++:

eRCaGuy_hello_world/c$ g++ -Wall -Wextra -Werror -O3 -std=gnu++17 struct_initialization2.c -o bin/a && bin/a
struct_initialization2.c: In function ‘int main()’:
struct_initialization2.c:77:28: error: missing initializer for member ‘my_data_s::i2’ [-Werror=missing-field-initializers]
   77 |     my_data_t my_data1 = {0};
      |                            ^
struct_initialization2.c:77:28: error: missing initializer for member ‘my_data_s::i3’ [-Werror=missing-field-initializers]
struct_initialization2.c:93:34: error: missing initializer for member ‘my_data_s::i2’ [-Werror=missing-field-initializers]
   93 |     my_data_t my_data4 = {.i1 = 1};
      |                                  ^
struct_initialization2.c:93:34: error: missing initializer for member ‘my_data_s::i3’ [-Werror=missing-field-initializers]
struct_initialization2.c:102:52: error: missing initializer for member ‘my_data_s::i1’ [-Werror=missing-field-initializers]
  102 |     my_data_t my_data7 = {.i3 = 3, .i2 = 2, .i1 = 1};
      |                                                    ^
struct_initialization2.c:102:52: error: missing initializer for member ‘my_data_s::i2’ [-Werror=missing-field-initializers]
struct_initialization2.c:102:52: error: designator order for field ‘my_data_s::i2’ does not match declaration order in ‘my_data_t’ {aka ‘my_data_s’}
struct_initialization2.c:105:52: error: missing initializer for member ‘my_data_s::i1’ [-Werror=missing-field-initializers]
  105 |     my_data_t my_data8 = {.i3 = 3, .i1 = 1, .i2 = 2};
      |                                                    ^
struct_initialization2.c:105:52: error: missing initializer for member ‘my_data_s::i2’ [-Werror=missing-field-initializers]
struct_initialization2.c:105:52: error: designator order for field ‘my_data_s::i1’ does not match declaration order in ‘my_data_t’ {aka ‘my_data_s’}
struct_initialization2.c:108:34: error: missing initializer for member ‘my_data_s::i1’ [-Werror=missing-field-initializers]
  108 |     my_data_t my_data9 = {.i2 = 2};
      |                                  ^
struct_initialization2.c:108:34: error: missing initializer for member ‘my_data_s::i3’ [-Werror=missing-field-initializers]
struct_initialization2.c:111:44: error: missing initializer for member ‘my_data_s::i1’ [-Werror=missing-field-initializers]
  111 |     my_data_t my_data10 = {.i2 = 2, .i3 = 3};
      |                                            ^
cc1plus: all warnings being treated as errors


*/
