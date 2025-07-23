/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
July 2025

A debug header file to easily see where something is coming from.
ie: file, function, line number, etc.

It is C-compatible, so it can be included in C code as well as C++. 
*/

#pragma once

// Local includes/
// NA

// 3rd-party includes
// NA

// Linux/Unix includes
// #include <libgen.h>  // For `basename()`

// C++ includes
// NA

// C includes 
#include <stdio.h>

// Update: we won't use GCC's string.h version of `basename()`, because it's not available on
// Windows in MSYS2, and we won't use the libgen.h version of `basename()` either, because it 
// accepts a `char*` argument, not a `const char*` argument, and it does, or may, modify the 
// input string, which is undefined behavior if we let the function modify a string literal, such
// as `__FILE__` below. 
// - So, we will write our own `basename()` function instead. 
// 
// NB: `string.h` also contains `basename()` in Linux/Unix, but not in C++.
// - See: https://man7.org/linux/man-pages/man3/basename.3.html:
//
//   > VERSIONS
//   >        There are two different versions of basename() - the POSIX version
//   >        described above, and the GNU version, which one gets after
//   > 
//   >                #define _GNU_SOURCE         /* See feature_test_macros(7) */
//   >                #include <string.h>
//   > 
//   >        The GNU version never modifies its argument, and returns the empty
//   >        string when path has a trailing slash, and in particular also when
//   >        it is "/".  There is no GNU version of dirname().
//   > 
//   >        With glibc, one gets the POSIX version of basename() when
//   >        <libgen.h> is included, and the GNU version otherwise.
//
// #include <string.h>  


#ifdef __cplusplus
extern "C" {
#endif

// Print a debug message with file, function, and line number, preceded by "TODO: "
// - NB: if your compiler/build system does not have `basename()` built into it, then write it 
//   yourself. 
//
// Usage example:
//      DEBUG_TODO("This is a debug message with value: %d\n", value);
//
// Example output:
//      TODO: src/my_file.cpp:my_func():123: This is a debug message with value: 42
//
#define DEBUG_TODO(format_str, ...) \
    printf( \
        "TODO: %s:%s():%d: " format_str, \
        debug_basename(__FILE__), \
        __FUNCTION__, \
        __LINE__, \
        ##__VA_ARGS__)

// Alias for `DEBUG_TODO()` above.
// - I prefer to call this actually because it sticks out to me more since it begins with `TODO`. 
#define TODO_PRINTF(format_str, ...) \
    DEBUG_TODO(format_str, ##__VA_ARGS__)

// Print a debug message with file, function, and line number
#define DEBUG_PRINTF(format_str, ...) \
    printf( \
        "%s:%s():%d: " format_str, \
        debug_basename(__FILE__), \
        __FUNCTION__, \
        __LINE__, \
        ##__VA_ARGS__)

// Obtain the base name of a file path.
// - This function returns the last component of the path, which is typically the file name.
// - It does not modify the input string, so it can safely be used with string literals
//   (e.g., `__FILE__`).
const char* debug_basename(const char* path);

#ifdef __cplusplus
}
#endif
