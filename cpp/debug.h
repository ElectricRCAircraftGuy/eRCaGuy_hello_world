/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
July 2025

A debug header file to easily see where something is coming from.
ie: file, function, line number, etc.

It is C-compatible, so it can be included in C code as well as C++. 
*/

#pragma once

#include <stdio.h>


#ifdef __cplusplus
extern "C" {
#endif

// Print a debug message with file, function, and line number, preceded by "TODO: "
// Usage example:
//   DEBUG_TODO("This is a debug message with value: %d\n", value);
// Example output:
//  TODO: src/debug.h:debug_function_name():123: This is a debug message with value: 42
#define DEBUG_TODO(format_str, ...) \
    printf("TODO: %s:%s():%d: " format_str, __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)

#define TODO_PRINTF(format_str, ...) \
    DEBUG_TODO(format_str, ##__VA_ARGS__)



/*
constexpr const char* filename_only(const char* path) {
    const char* file = path;
    while (*path) {
        if (*path == '/' || *path == '\\') {
            file = path + 1;
        }
        path++;
    }
    return file;
}

// Usage:
#define __FILENAME__ filename_only(__FILE__)
*/

#ifdef __cplusplus
}
#endif
