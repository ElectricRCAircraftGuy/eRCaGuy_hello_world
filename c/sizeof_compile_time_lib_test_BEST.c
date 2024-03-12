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
gcc sizeof_compile_time_lib_test_BEST.c -o bin/a && bin/a

./sizeof_compile_time_lib_test_BEST.c
# or:
gcc -Wall -Wextra -Werror -O3 -std=gnu17 sizeof_compile_time_lib_test_BEST.c -o bin/a -lm && bin/a

# 2. In C++
# The most basic form that needs to work:
g++ sizeof_compile_time_lib_test_BEST.c -o bin/a && bin/a

g++ -Wall -Wextra -Werror -O3 -std=gnu++17 sizeof_compile_time_lib_test_BEST.c -o bin/a && bin/a
```

References:
1. See: "eRCaGuy_hello_world/c/sizeof_compile_time_lib.h"


*/


#include "sizeof_compile_time_lib.h"

#include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
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

struct My_struct2_s
{
              // For my X86-64 Linux machine:
    bool b;   // 1 byte + 3 padding bytes
    int i;    // 4 bytes
};            // 8 bytes total

COMPILE_TIME_PRINT_SIZEOF_GLOBAL(My_struct);                // 24
COMPILE_TIME_PRINT_SIZEOF_GLOBAL(struct My_struct2_s);      // 8

COMPILE_TIME_PRINT_SIZEOF_GLOBAL(bool);                     // 1
COMPILE_TIME_PRINT_SIZEOF_GLOBAL(int);                      // 4
COMPILE_TIME_PRINT_SIZEOF_GLOBAL(double);                   // 8

int main()
{
    printf("Testing 'sizeof_compile_time_lib.h'.\n\n");

    My_struct my_structs[10];
    COMPILE_TIME_PRINT_SIZEOF_LOCAL(My_struct);             // 24
    COMPILE_TIME_PRINT_SIZEOF_LOCAL(struct My_struct2_s);   // 8
    COMPILE_TIME_PRINT_SIZEOF_LOCAL(my_structs);            // 240

    COMPILE_TIME_PRINT_SIZEOF_LOCAL(bool);                  // 1
    COMPILE_TIME_PRINT_SIZEOF_LOCAL(int);                   // 4
    COMPILE_TIME_PRINT_SIZEOF_LOCAL(double);                // 8

    return 0;
}


/*
SAMPLE OUTPUT:

In C:

eRCaGuy_hello_world/c$ gcc -Wall -Wextra -Werror -O3 -std=gnu17 sizeof_compile_time_lib_test_BEST.c -o bin/a -lm && bin/a
In file included from sizeof_compile_time_lib_test_BEST.c:48:
sizeof_compile_time_lib_test_BEST.c: In function ‘compile_time_sizeof__line_72’:
sizeof_compile_time_lib.h:72:13: error: case value ‘24’ not in enumerated type ‘enum This_is_the_size_of_your_type_on__line_72’ [-Werror=switch]
   72 |             case sizeof(variable_or_data_type): \
      |             ^~~~
sizeof_compile_time_lib.h:86:9: note: in expansion of macro ‘COMPILE_TIME_PRINT_SIZEOF_LOCAL’
   86 |         COMPILE_TIME_PRINT_SIZEOF_LOCAL(variable_or_data_type); \
      |         ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
sizeof_compile_time_lib_test_BEST.c:72:1: note: in expansion of macro ‘COMPILE_TIME_PRINT_SIZEOF_GLOBAL’
   72 | COMPILE_TIME_PRINT_SIZEOF_GLOBAL(My_struct);                // 24
      | ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
sizeof_compile_time_lib_test_BEST.c: In function ‘compile_time_sizeof__line_73’:
sizeof_compile_time_lib.h:72:13: error: case value ‘8’ not in enumerated type ‘enum This_is_the_size_of_your_type_on__line_73’ [-Werror=switch]
   72 |             case sizeof(variable_or_data_type): \
      |             ^~~~
sizeof_compile_time_lib.h:86:9: note: in expansion of macro ‘COMPILE_TIME_PRINT_SIZEOF_LOCAL’
   86 |         COMPILE_TIME_PRINT_SIZEOF_LOCAL(variable_or_data_type); \
      |         ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
sizeof_compile_time_lib_test_BEST.c:73:1: note: in expansion of macro ‘COMPILE_TIME_PRINT_SIZEOF_GLOBAL’
   73 | COMPILE_TIME_PRINT_SIZEOF_GLOBAL(struct My_struct2_s);      // 8
      | ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
sizeof_compile_time_lib_test_BEST.c: In function ‘compile_time_sizeof__line_75’:
sizeof_compile_time_lib.h:72:13: error: case value ‘1’ not in enumerated type ‘enum This_is_the_size_of_your_type_on__line_75’ [-Werror=switch]
   72 |             case sizeof(variable_or_data_type): \
      |             ^~~~
sizeof_compile_time_lib.h:86:9: note: in expansion of macro ‘COMPILE_TIME_PRINT_SIZEOF_LOCAL’
   86 |         COMPILE_TIME_PRINT_SIZEOF_LOCAL(variable_or_data_type); \
      |         ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
sizeof_compile_time_lib_test_BEST.c:75:1: note: in expansion of macro ‘COMPILE_TIME_PRINT_SIZEOF_GLOBAL’
   75 | COMPILE_TIME_PRINT_SIZEOF_GLOBAL(bool);                     // 1
      | ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
sizeof_compile_time_lib_test_BEST.c: In function ‘compile_time_sizeof__line_76’:
sizeof_compile_time_lib.h:72:13: error: case value ‘4’ not in enumerated type ‘enum This_is_the_size_of_your_type_on__line_76’ [-Werror=switch]
   72 |             case sizeof(variable_or_data_type): \
      |             ^~~~
sizeof_compile_time_lib.h:86:9: note: in expansion of macro ‘COMPILE_TIME_PRINT_SIZEOF_LOCAL’
   86 |         COMPILE_TIME_PRINT_SIZEOF_LOCAL(variable_or_data_type); \
      |         ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
sizeof_compile_time_lib_test_BEST.c:76:1: note: in expansion of macro ‘COMPILE_TIME_PRINT_SIZEOF_GLOBAL’
   76 | COMPILE_TIME_PRINT_SIZEOF_GLOBAL(int);                      // 4
      | ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
sizeof_compile_time_lib_test_BEST.c: In function ‘compile_time_sizeof__line_77’:
sizeof_compile_time_lib.h:72:13: error: case value ‘8’ not in enumerated type ‘enum This_is_the_size_of_your_type_on__line_77’ [-Werror=switch]
   72 |             case sizeof(variable_or_data_type): \
      |             ^~~~
sizeof_compile_time_lib.h:86:9: note: in expansion of macro ‘COMPILE_TIME_PRINT_SIZEOF_LOCAL’
   86 |         COMPILE_TIME_PRINT_SIZEOF_LOCAL(variable_or_data_type); \
      |         ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
sizeof_compile_time_lib_test_BEST.c:77:1: note: in expansion of macro ‘COMPILE_TIME_PRINT_SIZEOF_GLOBAL’
   77 | COMPILE_TIME_PRINT_SIZEOF_GLOBAL(double);                   // 8
      | ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
sizeof_compile_time_lib_test_BEST.c: In function ‘main’:
sizeof_compile_time_lib.h:72:13: error: case value ‘24’ not in enumerated type ‘enum This_is_the_size_of_your_type_on__line_84’ [-Werror=switch]
   72 |             case sizeof(variable_or_data_type): \
      |             ^~~~
sizeof_compile_time_lib_test_BEST.c:84:5: note: in expansion of macro ‘COMPILE_TIME_PRINT_SIZEOF_LOCAL’
   84 |     COMPILE_TIME_PRINT_SIZEOF_LOCAL(My_struct);             // 24
      |     ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
sizeof_compile_time_lib.h:72:13: error: case value ‘8’ not in enumerated type ‘enum This_is_the_size_of_your_type_on__line_85’ [-Werror=switch]
   72 |             case sizeof(variable_or_data_type): \
      |             ^~~~
sizeof_compile_time_lib_test_BEST.c:85:5: note: in expansion of macro ‘COMPILE_TIME_PRINT_SIZEOF_LOCAL’
   85 |     COMPILE_TIME_PRINT_SIZEOF_LOCAL(struct My_struct2_s);   // 8
      |     ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
sizeof_compile_time_lib.h:72:13: error: case value ‘240’ not in enumerated type ‘enum This_is_the_size_of_your_type_on__line_86’ [-Werror=switch]
   72 |             case sizeof(variable_or_data_type): \
      |             ^~~~
sizeof_compile_time_lib_test_BEST.c:86:5: note: in expansion of macro ‘COMPILE_TIME_PRINT_SIZEOF_LOCAL’
   86 |     COMPILE_TIME_PRINT_SIZEOF_LOCAL(my_structs);            // 240
      |     ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
sizeof_compile_time_lib.h:72:13: error: case value ‘1’ not in enumerated type ‘enum This_is_the_size_of_your_type_on__line_88’ [-Werror=switch]
   72 |             case sizeof(variable_or_data_type): \
      |             ^~~~
sizeof_compile_time_lib_test_BEST.c:88:5: note: in expansion of macro ‘COMPILE_TIME_PRINT_SIZEOF_LOCAL’
   88 |     COMPILE_TIME_PRINT_SIZEOF_LOCAL(bool);                  // 1
      |     ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
sizeof_compile_time_lib.h:72:13: error: case value ‘4’ not in enumerated type ‘enum This_is_the_size_of_your_type_on__line_89’ [-Werror=switch]
   72 |             case sizeof(variable_or_data_type): \
      |             ^~~~
sizeof_compile_time_lib_test_BEST.c:89:5: note: in expansion of macro ‘COMPILE_TIME_PRINT_SIZEOF_LOCAL’
   89 |     COMPILE_TIME_PRINT_SIZEOF_LOCAL(int);                   // 4
      |     ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
sizeof_compile_time_lib.h:72:13: error: case value ‘8’ not in enumerated type ‘enum This_is_the_size_of_your_type_on__line_90’ [-Werror=switch]
   72 |             case sizeof(variable_or_data_type): \
      |             ^~~~
sizeof_compile_time_lib_test_BEST.c:90:5: note: in expansion of macro ‘COMPILE_TIME_PRINT_SIZEOF_LOCAL’
   90 |     COMPILE_TIME_PRINT_SIZEOF_LOCAL(double);                // 8
      |     ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
cc1: all warnings being treated as errors





OR, in C++:

eRCaGuy_hello_world/c$ g++ -Wall -Wextra -Werror -O3 -std=gnu++17 sizeof_compile_time_lib_test_BEST.c -o bin/a && bin/a
In file included from sizeof_compile_time_lib_test_BEST.c:48:
sizeof_compile_time_lib_test_BEST.c: In function ‘void compile_time_sizeof__line_72()’:
sizeof_compile_time_lib.h:72:13: error: case value ‘24’ not in enumerated type ‘compile_time_sizeof__line_72()::This_is_the_size_of_your_type_on__line_72’ [-Werror=switch]
   72 |             case sizeof(variable_or_data_type): \
      |             ^~~~
sizeof_compile_time_lib.h:86:9: note: in expansion of macro ‘COMPILE_TIME_PRINT_SIZEOF_LOCAL’
   86 |         COMPILE_TIME_PRINT_SIZEOF_LOCAL(variable_or_data_type); \
      |         ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
sizeof_compile_time_lib_test_BEST.c:72:1: note: in expansion of macro ‘COMPILE_TIME_PRINT_SIZEOF_GLOBAL’
   72 | COMPILE_TIME_PRINT_SIZEOF_GLOBAL(My_struct);                // 24
      | ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
sizeof_compile_time_lib_test_BEST.c: In function ‘void compile_time_sizeof__line_73()’:
sizeof_compile_time_lib.h:72:13: error: case value ‘8’ not in enumerated type ‘compile_time_sizeof__line_73()::This_is_the_size_of_your_type_on__line_73’ [-Werror=switch]
   72 |             case sizeof(variable_or_data_type): \
      |             ^~~~
sizeof_compile_time_lib.h:86:9: note: in expansion of macro ‘COMPILE_TIME_PRINT_SIZEOF_LOCAL’
   86 |         COMPILE_TIME_PRINT_SIZEOF_LOCAL(variable_or_data_type); \
      |         ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
sizeof_compile_time_lib_test_BEST.c:73:1: note: in expansion of macro ‘COMPILE_TIME_PRINT_SIZEOF_GLOBAL’
   73 | COMPILE_TIME_PRINT_SIZEOF_GLOBAL(struct My_struct2_s);      // 8
      | ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
sizeof_compile_time_lib_test_BEST.c: In function ‘void compile_time_sizeof__line_75()’:
sizeof_compile_time_lib.h:72:13: error: case value ‘1’ not in enumerated type ‘compile_time_sizeof__line_75()::This_is_the_size_of_your_type_on__line_75’ [-Werror=switch]
   72 |             case sizeof(variable_or_data_type): \
      |             ^~~~
sizeof_compile_time_lib.h:86:9: note: in expansion of macro ‘COMPILE_TIME_PRINT_SIZEOF_LOCAL’
   86 |         COMPILE_TIME_PRINT_SIZEOF_LOCAL(variable_or_data_type); \
      |         ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
sizeof_compile_time_lib_test_BEST.c:75:1: note: in expansion of macro ‘COMPILE_TIME_PRINT_SIZEOF_GLOBAL’
   75 | COMPILE_TIME_PRINT_SIZEOF_GLOBAL(bool);                     // 1
      | ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
sizeof_compile_time_lib_test_BEST.c: In function ‘void compile_time_sizeof__line_76()’:
sizeof_compile_time_lib.h:72:13: error: case value ‘4’ not in enumerated type ‘compile_time_sizeof__line_76()::This_is_the_size_of_your_type_on__line_76’ [-Werror=switch]
   72 |             case sizeof(variable_or_data_type): \
      |             ^~~~
sizeof_compile_time_lib.h:86:9: note: in expansion of macro ‘COMPILE_TIME_PRINT_SIZEOF_LOCAL’
   86 |         COMPILE_TIME_PRINT_SIZEOF_LOCAL(variable_or_data_type); \
      |         ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
sizeof_compile_time_lib_test_BEST.c:76:1: note: in expansion of macro ‘COMPILE_TIME_PRINT_SIZEOF_GLOBAL’
   76 | COMPILE_TIME_PRINT_SIZEOF_GLOBAL(int);                      // 4
      | ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
sizeof_compile_time_lib_test_BEST.c: In function ‘void compile_time_sizeof__line_77()’:
sizeof_compile_time_lib.h:72:13: error: case value ‘8’ not in enumerated type ‘compile_time_sizeof__line_77()::This_is_the_size_of_your_type_on__line_77’ [-Werror=switch]
   72 |             case sizeof(variable_or_data_type): \
      |             ^~~~
sizeof_compile_time_lib.h:86:9: note: in expansion of macro ‘COMPILE_TIME_PRINT_SIZEOF_LOCAL’
   86 |         COMPILE_TIME_PRINT_SIZEOF_LOCAL(variable_or_data_type); \
      |         ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
sizeof_compile_time_lib_test_BEST.c:77:1: note: in expansion of macro ‘COMPILE_TIME_PRINT_SIZEOF_GLOBAL’
   77 | COMPILE_TIME_PRINT_SIZEOF_GLOBAL(double);                   // 8
      | ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
sizeof_compile_time_lib_test_BEST.c: In function ‘int main()’:
sizeof_compile_time_lib.h:72:13: error: case value ‘24’ not in enumerated type ‘main()::This_is_the_size_of_your_type_on__line_84’ [-Werror=switch]
   72 |             case sizeof(variable_or_data_type): \
      |             ^~~~
sizeof_compile_time_lib_test_BEST.c:84:5: note: in expansion of macro ‘COMPILE_TIME_PRINT_SIZEOF_LOCAL’
   84 |     COMPILE_TIME_PRINT_SIZEOF_LOCAL(My_struct);             // 24
      |     ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
sizeof_compile_time_lib.h:72:13: error: case value ‘8’ not in enumerated type ‘main()::This_is_the_size_of_your_type_on__line_85’ [-Werror=switch]
   72 |             case sizeof(variable_or_data_type): \
      |             ^~~~
sizeof_compile_time_lib_test_BEST.c:85:5: note: in expansion of macro ‘COMPILE_TIME_PRINT_SIZEOF_LOCAL’
   85 |     COMPILE_TIME_PRINT_SIZEOF_LOCAL(struct My_struct2_s);   // 8
      |     ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
sizeof_compile_time_lib.h:72:13: error: case value ‘240’ not in enumerated type ‘main()::This_is_the_size_of_your_type_on__line_86’ [-Werror=switch]
   72 |             case sizeof(variable_or_data_type): \
      |             ^~~~
sizeof_compile_time_lib_test_BEST.c:86:5: note: in expansion of macro ‘COMPILE_TIME_PRINT_SIZEOF_LOCAL’
   86 |     COMPILE_TIME_PRINT_SIZEOF_LOCAL(my_structs);            // 240
      |     ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
sizeof_compile_time_lib.h:72:13: error: case value ‘1’ not in enumerated type ‘main()::This_is_the_size_of_your_type_on__line_88’ [-Werror=switch]
   72 |             case sizeof(variable_or_data_type): \
      |             ^~~~
sizeof_compile_time_lib_test_BEST.c:88:5: note: in expansion of macro ‘COMPILE_TIME_PRINT_SIZEOF_LOCAL’
   88 |     COMPILE_TIME_PRINT_SIZEOF_LOCAL(bool);                  // 1
      |     ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
sizeof_compile_time_lib.h:72:13: error: case value ‘4’ not in enumerated type ‘main()::This_is_the_size_of_your_type_on__line_89’ [-Werror=switch]
   72 |             case sizeof(variable_or_data_type): \
      |             ^~~~
sizeof_compile_time_lib_test_BEST.c:89:5: note: in expansion of macro ‘COMPILE_TIME_PRINT_SIZEOF_LOCAL’
   89 |     COMPILE_TIME_PRINT_SIZEOF_LOCAL(int);                   // 4
      |     ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
sizeof_compile_time_lib.h:72:13: error: case value ‘8’ not in enumerated type ‘main()::This_is_the_size_of_your_type_on__line_90’ [-Werror=switch]
   72 |             case sizeof(variable_or_data_type): \
      |             ^~~~
sizeof_compile_time_lib_test_BEST.c:90:5: note: in expansion of macro ‘COMPILE_TIME_PRINT_SIZEOF_LOCAL’
   90 |     COMPILE_TIME_PRINT_SIZEOF_LOCAL(double);                // 8
      |     ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
cc1plus: all warnings being treated as errors



*/
