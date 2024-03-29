/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
16 Apr. 2022

Learn how to auto-generate unique variable names with the line number in them by using macros.

Ex: `uint64_t MAKE_UNIQUE_VARIABLE_NAME(counter) = 0;` would produce `uint64_t counter_7 = 0` if
this is on line 7!

STATUS: works!

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# Why `-std=gnu17` vs `-std=c17`, and `-std=gnu++17` vs `-std=c++17`?
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# 1. In C:
gcc -Wall -Wextra -Werror -O3 -std=gnu17 macro_make_unique_variable_name_with_line_number.c -o bin/a -lm && bin/a

# 2. In C++
g++ -Wall -Wextra -Werror -O3 -std=gnu++17 macro_make_unique_variable_name_with_line_number.c -o bin/a && bin/a
```

References:
1. [MY ANSWER CONTAINING THIS CODE] https://stackoverflow.com/a/71899854/4561887
1. *****+ [EXTREMELY USEFUL!] Create an identifier at compile time that has the line
   number as part of it: https://stackoverflow.com/a/35922379/4561887
1. Creating C macro with ## and __LINE__ (token concatenation with positioning macro):
   https://stackoverflow.com/a/1597129/4561887

*/


#include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`

// See: https://stackoverflow.com/a/71899854/4561887
#define CONCAT_(prefix, suffix) prefix##suffix
/// Concatenate `prefix, suffix` into `prefixsuffix`
#define CONCAT(prefix, suffix) CONCAT_(prefix, suffix)
/// Make a unique variable name containing the line number at the end of the
/// name. Ex: `uint64_t MAKE_UNIQUE_VARIABLE_NAME(counter) = 0;` would
/// produce `uint64_t counter_7 = 0` if the call is on line 7!
#define MAKE_UNIQUE_VARIABLE_NAME(prefix) CONCAT(prefix##_, __LINE__)


// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Autogenerate unique variable names containing the line number "
           "in them.\n\n");

    uint64_t MAKE_UNIQUE_VARIABLE_NAME(counter) = 0; // `uint64_t counter_56 = 0;
    uint64_t MAKE_UNIQUE_VARIABLE_NAME(counter) = 0; // `uint64_t counter_57 = 0;
    uint64_t MAKE_UNIQUE_VARIABLE_NAME(counter) = 0; // `uint64_t counter_58 = 0;

    // Uncomment this to suppress the errors.
    // (void)counter_56;
    // (void)counter_57;
    // (void)counter_58;

    return 0;
}

/*
SAMPLE OUTPUT:

In C:

Notice that the errors reveal the autogenerated variable names!:

    macro_make_unique_variable_name_with_line_number.c:58:40: error: unused variable ‘counter_58’ [-Werror=unused-variable]
    macro_make_unique_variable_name_with_line_number.c:57:40: error: unused variable ‘counter_57’ [-Werror=unused-variable]
    macro_make_unique_variable_name_with_line_number.c:56:40: error: unused variable ‘counter_56’ [-Werror=unused-variable]

Full output:


    eRCaGuy_hello_world/c$ gcc -Wall -Wextra -Werror -O3 -std=gnu17 macro_make_unique_variable_name_with_line_number.c -o bin/a -lm && bin/a
    macro_make_unique_variable_name_with_line_number.c: In function ‘main’:
    macro_make_unique_variable_name_with_line_number.c:58:40: error: unused variable ‘counter_58’ [-Werror=unused-variable]
       58 |     uint64_t MAKE_UNIQUE_VARIABLE_NAME(counter) = 0; // `uint64_t counter_58 = 0;
          |                                        ^~~~~~~
    macro_make_unique_variable_name_with_line_number.c:41:33: note: in definition of macro ‘CONCAT_’
       41 | #define CONCAT_(prefix, suffix) prefix##suffix
          |                                 ^~~~~~
    macro_make_unique_variable_name_with_line_number.c:47:43: note: in expansion of macro ‘CONCAT’
       47 | #define MAKE_UNIQUE_VARIABLE_NAME(prefix) CONCAT(prefix##_, __LINE__)
          |                                           ^~~~~~
    macro_make_unique_variable_name_with_line_number.c:58:14: note: in expansion of macro ‘MAKE_UNIQUE_VARIABLE_NAME’
       58 |     uint64_t MAKE_UNIQUE_VARIABLE_NAME(counter) = 0; // `uint64_t counter_58 = 0;
          |              ^~~~~~~~~~~~~~~~~~~~~~~~~
    macro_make_unique_variable_name_with_line_number.c:57:40: error: unused variable ‘counter_57’ [-Werror=unused-variable]
       57 |     uint64_t MAKE_UNIQUE_VARIABLE_NAME(counter) = 0; // `uint64_t counter_57 = 0;
          |                                        ^~~~~~~
    macro_make_unique_variable_name_with_line_number.c:41:33: note: in definition of macro ‘CONCAT_’
       41 | #define CONCAT_(prefix, suffix) prefix##suffix
          |                                 ^~~~~~
    macro_make_unique_variable_name_with_line_number.c:47:43: note: in expansion of macro ‘CONCAT’
       47 | #define MAKE_UNIQUE_VARIABLE_NAME(prefix) CONCAT(prefix##_, __LINE__)
          |                                           ^~~~~~
    macro_make_unique_variable_name_with_line_number.c:57:14: note: in expansion of macro ‘MAKE_UNIQUE_VARIABLE_NAME’
       57 |     uint64_t MAKE_UNIQUE_VARIABLE_NAME(counter) = 0; // `uint64_t counter_57 = 0;
          |              ^~~~~~~~~~~~~~~~~~~~~~~~~
    macro_make_unique_variable_name_with_line_number.c:56:40: error: unused variable ‘counter_56’ [-Werror=unused-variable]
       56 |     uint64_t MAKE_UNIQUE_VARIABLE_NAME(counter) = 0; // `uint64_t counter_56 = 0;
          |                                        ^~~~~~~
    macro_make_unique_variable_name_with_line_number.c:41:33: note: in definition of macro ‘CONCAT_’
       41 | #define CONCAT_(prefix, suffix) prefix##suffix
          |                                 ^~~~~~
    macro_make_unique_variable_name_with_line_number.c:47:43: note: in expansion of macro ‘CONCAT’
       47 | #define MAKE_UNIQUE_VARIABLE_NAME(prefix) CONCAT(prefix##_, __LINE__)
          |                                           ^~~~~~
    macro_make_unique_variable_name_with_line_number.c:56:14: note: in expansion of macro ‘MAKE_UNIQUE_VARIABLE_NAME’
       56 |     uint64_t MAKE_UNIQUE_VARIABLE_NAME(counter) = 0; // `uint64_t counter_56 = 0;
          |              ^~~~~~~~~~~~~~~~~~~~~~~~~
    cc1: all warnings being treated as errors





OR, in C++:

(very similar to the output in C)


*/
