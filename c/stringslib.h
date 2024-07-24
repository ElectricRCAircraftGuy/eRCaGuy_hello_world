/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

Gabriel Staples
Written ~ Mar. 2019 to July 2024

`strcasecmp()` POSIX functions for case-insensitive string comparison

STATUS: done and works!

See: 
1. https://pubs.opengroup.org/onlinepubs/9699919799/functions/strcasecmp.html
1. strncmpci.c: 
    1. My answer: https://stackoverflow.com/a/55293507/4561887
    1. https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world/blob/master/c/strncmpci.c
*/

#pragma once

#include <stddef.h>  // size_t

// Case-insensitive string comparison between `str1` and `str2`:
// - "Upon completion, strcasecmp() shall return an integer greater than, equal to, or less than 0,
//   if the string pointed to by str1 is, ignoring case, greater than, equal to, or less than the
//   string pointed to by str2, respectively."
// - https://pubs.opengroup.org/onlinepubs/9699919799/functions/strcasecmp.html
int my_strcasecmp(const char *str1, const char *str2);

// Case-insensitive string comparison of the first `num_chars` characters of `str1` and `str2`:
// - "Upon successful completion, strncasecmp() shall return an integer greater than, equal to, or
//   less than 0, if the possibly null-terminated array pointed to by str1 is, ignoring case,
//   greater than, equal to, or less than the possibly null-terminated array pointed to by str2,
//   respectively."
// - https://pubs.opengroup.org/onlinepubs/9699919799/functions/strcasecmp.html
int my_strncasecmp(const char *str1, const char *str2, size_t num_chars);
