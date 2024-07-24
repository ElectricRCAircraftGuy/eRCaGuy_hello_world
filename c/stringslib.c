/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world
*/


#include "stringslib.h"

#include <ctype.h>  // tolower()
#include <limits.h> // for `INT_MIN`


// Modified from `strncasecmp()` below. 
int my_strcasecmp(const char *str1, const char *str2)
{
    int ret_code = 0;

    // Check for NULL pointers
    if (!str1 || !str2)
    {
        ret_code = INT_MIN;
        return ret_code;
    }

    // NB: this while loop only runs if both `*str1` and `*str2` are NOT at their null terminators
    // yet. If both are at their null terminators, then the strings match, and the while loop does
    // not run again. 
    // Ie:
    // 1. If one char is a null terminator and one isn't, then they won't match, and it will break
    //    out inside the while loop.
    // 2. If both chars are null terminators, then they match, and the while loop will not run
    //    again.
    while (*str1 || *str2)
    {
        ret_code = tolower((int)(*str1)) - tolower((int)(*str2));
        if (ret_code != 0)
        {
            // The 2 chars just compared don't match
            break;
        }
        str1++;
        str2++;
    }

    return ret_code;
}

// Copied and modified from: https://stackoverflow.com/a/55293507/4561887 and
// https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world/blob/master/c/strncmpci.c
int my_strncasecmp(const char *str1, const char *str2, size_t num_chars)
{
    int ret_code = 0;
    size_t chars_compared = 0;

    // Check for NULL pointers
    if (!str1 || !str2)
    {
        ret_code = INT_MIN;
        return ret_code;
    }

    // Continue doing case-insensitive comparisons, one-character-at-a-time, of `str1` to `str2`, so
    // long as 1st: we have not yet compared the requested number of chars, and 2nd: the next char
    // of at least *one* of the strings is not zero (the null terminator for a C-string), meaning
    // that string still has more characters in it.
    // Note: you MUST check `(chars_compared < num)` FIRST or else dereferencing (reading) `str1` or
    // `str2` via `*str1` and `*str2`, respectively, is undefined behavior if you are reading one or
    // both of these C-strings outside of their array bounds.
    while ((chars_compared < num_chars) && (*str1 || *str2))
    {
        ret_code = tolower((int)(*str1)) - tolower((int)(*str2));
        if (ret_code != 0)
        {
            // The 2 chars just compared don't match
            break;
        }
        chars_compared++;
        str1++;
        str2++;
    }

    return ret_code;
}
