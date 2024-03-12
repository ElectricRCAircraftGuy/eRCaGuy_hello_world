/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
Mar. 2024

A library to print or display or otherwise put into a compile-time error a
message containing a struct or variable or data type **size** at compile-time!

STATUS: Done and works!

keywords to easily grep or ripgrep in this repo for this program and what it teaches
KEYWORDS:

References:
1. "eRCaGuy_hello_world/c/macro_make_unique_variable_name_with_line_number.c":
   for my `MAKE_UNIQUE_VARIABLE_NAME()` macro.
1. How can I print the result of sizeof() at compile time in C? -
   https://stackoverflow.com/q/20979565/4561887
    1. *****+ MY ANSWER: https://stackoverflow.com/a/78144837/4561887
1. Is it possible to print out the size of a C++ class at compile-time? -
   https://stackoverflow.com/q/2008398/4561887
    1. MY ANSWER: https://stackoverflow.com/a/78144806/4561887
1. https://gcc.gnu.org/onlinedocs/gcc/Diagnostic-Pragmas.html
1. Usage of `_Pragma("string")`:
    1. ***** https://gcc.gnu.org/onlinedocs/cpp/Pragmas.html
    1. https://stackoverflow.com/a/45477830/4561887
1. Doing arithmetic on `__LINE__` in the C preprocessor:
    1. https://stackoverflow.com/a/24551912/4561887
    1. https://stackoverflow.com/a/24941973/4561887
1. `__attribute__((unused))`:
    https://gcc.gnu.org/onlinedocs/gcc/Common-Function-Attributes.html#Common-Function-Attributes

Todo:
1. [x] Add answers to the first two questions just above!

*/

#pragma once

// See: 
// 1. https://stackoverflow.com/a/71899854/4561887
// 2. "eRCaGuy_hello_world/c/macro_make_unique_variable_name_with_line_number.c"
#define CONCAT_(prefix, suffix) prefix##suffix
/// Concatenate `prefix, suffix` into `prefixsuffix`
#define CONCAT(prefix, suffix) CONCAT_(prefix, suffix)
///
/// Make a unique variable name containing the line number at the end of the
/// name. Ex: `uint64_t MAKE_UNIQUE_VARIABLE_NAME(counter) = 0;` would
/// produce `uint64_t counter_7 = 0` if the call is on line 7!
#define MAKE_UNIQUE_VARIABLE_NAME(prefix) CONCAT(prefix##_, __LINE__)

// Macro to **locally** (meaning: from a local scope) print out the size of a
// type or variable into an error message at compile time. 
#define COMPILE_TIME_PRINT_SIZEOF_LOCAL(variable_or_data_type) \
    { \
        /* save the current GCC diagnostic state */ \
        _Pragma("GCC diagnostic push") \
        /* Activate `-Wswitch` switch case warnings, and make them become */ \
        /* errors, so that the enum and switch case below will throw */ \
        /* a compile-time error with the `variable_or_data_type`'s */ \
        /* size printed in it! */ \
        _Pragma("GCC diagnostic error \"-Wswitch\"") \
        enum MAKE_UNIQUE_VARIABLE_NAME(This_is_the_size_of_your_type_on__line) \
        { \
            DUMMY_VAL = 0 \
        } dummy = DUMMY_VAL; \
        switch (dummy) \
        { \
            case DUMMY_VAL: \
                break; \
            case sizeof(variable_or_data_type): \
                break; \
        } \
        /* restore the saved GCC diagnostic state */ \
        _Pragma("GCC diagnostic pop") \
    }

// Macro to **globally** (meaning: from a global scope) print out the size of a
// type or variable into an error message at compile time. 
#define COMPILE_TIME_PRINT_SIZEOF_GLOBAL(variable_or_data_type) \
    /* Make a unique function name for each usage of this macro */ \
    __attribute__((unused)) \
    void MAKE_UNIQUE_VARIABLE_NAME(compile_time_sizeof__line)() \
    { \
        COMPILE_TIME_PRINT_SIZEOF_LOCAL(variable_or_data_type); \
    }

