/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world
*/

// Primary include
#include "debug.h"

// Local includes
// NA

// 3rd-party includes
// NA

// Linux/Unix includes
// NA

// C++ includes
// NA

// C includes
// NA


// Prevent name mangling for C linkage
#ifdef __cplusplus
extern "C" {
#endif

const char* debug_basename(const char* path)
{
    const char* base = path;

    while (*path != '\0') // Until the string's null terminator 
    {
        if (*path == '/' || *path == '\\') 
        {
            base = path + 1;
        }
        path++;
    }
    
    return base;
}

#ifdef __cplusplus
}
#endif
