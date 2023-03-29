///usr/bin/env ccache gcc -Wall -Wextra -Werror -O3 -std=gnu17 "$0" -o /tmp/a -lm && /tmp/a "$@"; exit
// For the line just above, see my answer here: https://stackoverflow.com/a/75491834/4561887

/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

Concatenate two (or more) C-strings (character arrays) in various ways.

- For a comparison to the simpler usage in C++ (just use the `+` operator),
  see "eRCaGuy_hello_world/cpp/string_concatenate.cpp".  <======

  - C++ is seemingly simpler since it handles the low-level memory management **for you**! However,
    this is at the trade-off of:
    1) syntax and language complexity: you need to know what the non-member template function
    `operator+()` is, and how it works, and
    2) speed, safety, determinism, and control: since C++ controls the low-level memory management
    for you, and automatically dynamically allocates memory at-will in most of the STL containers,
    it may run slower, is non-deterministic when it calls `new` (the C++ equivalent of `malloc())`),
    and may be more-likely to throw run-time errors and have run-time crashes when out of
    memory since it may dynamically allocate memory without your explicit awareness otherwise.

STATUS: done and works!

keywords to easily grep or ripgrep in this repo for this program and what it teaches
KEYWORDS: interview prep

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# Why `-std=gnu17` vs `-std=c17`, and `-std=gnu++17` vs `-std=c++17`?
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# [run once ever] install ccache
sudo apt update && sudo apt install ccache

# 1. In C:
./str_concatenate.c
# or:
gcc -Wall -Wextra -Werror -O3 -std=gnu17 str_concatenate.c -o bin/a -lm && bin/a

# 2. In C++
g++ -Wall -Wextra -Werror -O3 -std=gnu++17 str_concatenate.c -o bin/a && bin/a
```

References:
1. https://cplusplus.com/reference/cstring/
1. C-strings: null-terminated byte (or char) strings: https://en.cppreference.com/w/c/string/byte

Potentially useful functions to be aware of to aid with string concatenation in C:
See: https://en.cppreference.com/w/c/string/byte
```c
strcpy()
strncpy()

strcat()
strncat()

sprintf()
snprintf()

memcpy()
memset()

strlen()

strdup()
strndup()

malloc()  // in stdlib.h
```

*/


#include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdlib.h>  // `malloc()`
#include <stdio.h>   // For `printf()`, `snprintf()`, etc.
#include <string.h>

/// Get the number of elements in any C array
/// - Usage example: [my own answer]: https://arduino.stackexchange.com/a/80289/7727
#define ARRAY_LEN(array) (sizeof(array) / sizeof(array[0]))

/// Concatenate **two** C-strings with dynamic memory allocation.
char* str_concat_dynamic(const char* str1, const char* str2)
{
    if (str1 == NULL || str2 == NULL)
    {
        printf("Error: invalid input strings.\n");
        return NULL;
    }

    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);

    char* str_combined = malloc(len1 + len2 + 1); // +1 for null terminator
    if (str_combined == NULL)
    {
        printf("Error: out of memory!\n");
        return NULL;
    }

    // Let's demonstrate a few ways to do this part:

    // Option 1 [what came to my mind 1st]: `strcpy()` followed by `strcat()`
    // strcpy(str_combined, str1); // write str1
    // strcat(str_combined, str2); // write str2

    // Option 2 [also works fine]: `strcat()` twice; just make sure to begin the combined string
    // with a null terminator!
    // str_combined[0] = '\0';
    // strcat(str_combined, str1); // write str1
    // strcat(str_combined, str2); // write str2

    // <======= GREAT OPTION ======
    // Option 3 [best, because it's the most efficient!]: use `strcpy()` twice. Just manually point
    // to the new, correct location for each string. This is the fastest and best of the 3 options
    // because `strcat()` must first walk the string to look for the null character (at which point
    // it will begin writing the new string), making it take roughly O(2n) to do the concatenation,
    // whereas this technique traverses the whole combined string only once, in O(1n) time!
    strcpy(str_combined, str1);         // write str1
    strcpy(&str_combined[len1], str2);  // write str2

    // <======= GREAT OPTION ======
    // Option 4 [also a great option since it's so short and easy to use!]: use `sprintf()`
    // TODO: read the return code and check for errors too!
    // See:
    // 1. https://cplusplus.com/reference/cstdio/sprintf/
    // 2. https://en.cppreference.com/w/c/io/fprintf
    // sprintf(str_combined, "%s%s", str1, str2);

    return str_combined;
}

/// \brief          Concatenate **two** C-strings with **static** memory allocation.
/// \param[out]     str_combined    The buffer that the combined string will be written into.
/// \param[in]      len             The max number of bytes that the buffer can hold.
/// \param[in]      str1            Input null-terminated C-string 1.
/// \param[in]      str2            Input null-terminated C-string 2.
/// \return         < 0 if an error; otherwise 0 for no error
int str_concat_static(char* str_combined, size_t len, const char* str1, const char* str2)
{
    if (str1 == NULL || str2 == NULL)
    {
        printf("Error: invalid input strings.\n");
        return -1; // TODO: RETURN ENUM-BASED ERROR CODES FOR ALL ERRORS IN THIS FUNC. INSTEAD!
    }

    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    const size_t len_required = len1 + len2 + 1; // +1 for null terminator

    if (len < len_required)
    {
        printf("Error: buffer is too small. len = %zu but len_required = %zu.\n",
            len, len_required);
        return -2; // See TODO above.
    }

    // [Option 4 above]
    sprintf(str_combined, "%s%s", str1, str2);

    return 0; // See TODO above.
}

/// \brief          Concatenate **any number** C-strings with **dynamic** memory allocation.
char* str_concat_dynamic_multi(const char* array_of_strings[], size_t num_strings)
{
    if (array_of_strings == NULL)
    {
        printf("Error: invalid input (NULL ptr).\n");
        return NULL;
    }

    // Figure out how big of a memory block we need to allocate
    size_t num_bytes_required = 0;
    for (size_t i = 0; i < num_strings; i++)
    {
        num_bytes_required += strlen(array_of_strings[i]);
    }

    // for debugging
    printf("num_bytes_required (not counting null terminator) = %zu\n", num_bytes_required);

    char* str_combined = malloc(num_bytes_required + 1); // +1 for null terminator
    if (str_combined == NULL)
    {
        printf("Error: out of memory!\n");
        return NULL;
    }

    // Concatenate all strings into the new, combined string.
    char* str_start = str_combined;
    for (size_t i = 0; i < num_strings; i++)
    {
        strcpy(str_start, array_of_strings[i]);
        str_start += strlen(array_of_strings[i]);
    }

    return str_combined;
}

/// struct to encapsulate the array of strings
typedef struct str_array_s
{
    char** strings; /// array of C-strings (array of char*)
    size_t len;     /// number of elements (C-strings) in the array above
} str_array_t;

/// \brief          Same as just above, except using a struct to encapsulate the strings this time.
///                 Concatenate **any number** C-strings with **dynamic** memory allocation.
char* str_concat_dynamic_multi2(const str_array_t* str_array)
{
    return str_concat_dynamic_multi((const char **)str_array->strings, str_array->len);
}


// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    // ---------------------------------------------------------------------------------------------
    // 1. Concatenate 2 strings with **dynamic** memory allocation
    // ---------------------------------------------------------------------------------------------

    printf("%s\n", str_concat_dynamic("hello ", "world"));
    char* str1 = str_concat_dynamic("Hey", "you");
    printf("%s\n", str1);
    printf("\n");

    // NB: don't forget to `free()` the concatenated C-string to prevent memory leaks! See example
    // farther below. To do this, you'll have to call `str_concat_dynamic()` *outside* of the
    // `printf()` function so you can keep track of (and later free via) the ptr to the returned
    // string.


    // ---------------------------------------------------------------------------------------------
    // 2. Concatenate 2 strings with **static** memory allocation
    // ---------------------------------------------------------------------------------------------

    static char buffer[10];
    int retcode;

    // Fails! Buffer too small.
    retcode = str_concat_static(buffer, sizeof(buffer), "hello ", "world");
    if (retcode != 0)
    {
        printf("Failed. retcode = %i\n", retcode);
    }
    printf("%s\n", buffer);

    retcode = str_concat_static(buffer, sizeof(buffer), "Hey", "you");
    if (retcode != 0)
    {
        printf("Failed. retcode = %i\n", retcode);
    }
    printf("%s\n", buffer);

    // Redo the failed one just above; this time with a buffer that is big enough.
    static char buffer2[100];
    retcode = str_concat_static(buffer2, sizeof(buffer2), "hello ", "world");
    if (retcode != 0)
    {
        printf("Failed. retcode = %i\n", retcode);
    }
    printf("%s\n", buffer2);

    printf("\n");


    // ---------------------------------------------------------------------------------------------
    // 3. Concatenate **any number** of strings with **dynamic** memory allocation
    // - Note: again, the same could be done with **static** memory allocation just fine too, but
    //   let's just use dynamic memory allocation for this example since it's cleaner and simpler
    //   and we can assume we are running this on a large, non-safety-critical,
    //   non-memory-constrained, non-microcontroller, non-deterministic, and non-realtime system.
    // ---------------------------------------------------------------------------------------------

    // Note: this array of strings contains a total of 24 chars + null terminator.
    char* array_of_strings[] = {"hello", " ", "world", " ", "how", " ", "are ", "you?"};
    printf("%s\n", str_concat_dynamic_multi(
        (const char**)array_of_strings, ARRAY_LEN(array_of_strings)));

    // Now call `str_concat_dynamic_multi2()` as well.
    str_array_t str_array = {
        .strings = array_of_strings,
        .len = ARRAY_LEN(array_of_strings),
    };
    printf("%s\n", str_concat_dynamic_multi2(&str_array));

    printf("\n");


    // ---------------------------------------------------------------------------------------------
    // DON'T FORGET TO CALL `free()` TO PREVENT MEMORY LEAKS!
    // I didn't do it above, but I want to point out you need to `free()` any `malloc()`ed memory
    // above when done with it in order to avoid memory leaks too. Here's how.
    // ---------------------------------------------------------------------------------------------

    // 1. two-string example:

    char* str2 = str_concat_dynamic("Hey", "you");
    printf("%s\n", str2);
    // when done with the dynamically-allocated memory, free it!
    free(str2);
    // trying to use the memory, like this now, *after* freeing it, would be **undefined behavior**
    // and is a bug!
    // printf("%s\n", str2);


    // 2. multi-string example

    char* array_of_strings2[] = {"again: ", "hello", " ", "world", " ", "how", " ", "are ", "you?"};
    char* str3 =
        str_concat_dynamic_multi((const char**)array_of_strings2, ARRAY_LEN(array_of_strings2));
    printf("%s\n", str3);
    // when done with the dynamically-allocated memory, free it!
    free(str3);

    // NB: if you try to double-free memory (ie: call `free()` again on memory on which
    // you **already** called `free()`), you get **undefined behavior** and a run-time crash bug!
    // So, don't do this!:
    //
    // Example run-time error:
    //
    //      free(): double free detected in tcache 2
    //      c/str_concatenate.c: line 1: 322598 Aborted                 (core dumped) /tmp/a "$@"
    //
    // free(str3);


    return 0;
}


/*
SAMPLE OUTPUT:

In C:

    eRCaGuy_hello_world/c$ gcc -Wall -Wextra -Werror -O3 -std=gnu17 str_concatenate.c -o bin/a -lm && bin/a
    hello world
    Heyyou

    Error: buffer is too small. len = 10 but len_required = 12.
    Failed. retcode = -2

    Heyyou
    hello world

    num_bytes_required (not counting null terminator) = 24
    hello world how are you?
    num_bytes_required (not counting null terminator) = 24
    hello world how are you?

    Heyyou
    num_bytes_required (not counting null terminator) = 31
    again: hello world how are you?



OR, in C++:
[DOESN'T COMPILE! NEEDS TO BE FIXED TO BE VALID C++!]

    eRCaGuy_hello_world/c$ g++ -Wall -Wextra -Werror -O3 -std=gnu++17 str_concatenate.c -o bin/a && bin/a
    str_concatenate.c: In function ‘char* str_concat_dynamic(const char*, const char*)’:
    str_concatenate.c:96:32: error: invalid conversion from ‘void*’ to ‘char*’ [-fpermissive]
       96 |     char* str_combined = malloc(len1 + len2 + 1); // +1 for null terminator
          |                          ~~~~~~^~~~~~~~~~~~~~~~~
          |                                |
          |                                void*
    str_concatenate.c: In function ‘char* str_concat_dynamic_multi(const char**, size_t)’:
    str_concatenate.c:185:32: error: invalid conversion from ‘void*’ to ‘char*’ [-fpermissive]
      185 |     char* str_combined = malloc(num_bytes_required + 1); // +1 for null terminator
          |                          ~~~~~~^~~~~~~~~~~~~~~~~~~~~~~~
          |                                |
          |                                void*
    str_concatenate.c: In function ‘int main()’:
    str_concatenate.c:274:33: error: ISO C++ forbids converting a string constant to ‘char*’ [-Werror=write-strings]
      274 |     char* array_of_strings[] = {"hello", " ", "world", " ", "how", " ", "are ", "you?"};
          |                                 ^~~~~~~
    str_concatenate.c:274:42: error: ISO C++ forbids converting a string constant to ‘char*’ [-Werror=write-strings]
      274 |     char* array_of_strings[] = {"hello", " ", "world", " ", "how", " ", "are ", "you?"};
          |                                          ^~~
    str_concatenate.c:274:47: error: ISO C++ forbids converting a string constant to ‘char*’ [-Werror=write-strings]
      274 |     char* array_of_strings[] = {"hello", " ", "world", " ", "how", " ", "are ", "you?"};
          |                                               ^~~~~~~
    str_concatenate.c:274:56: error: ISO C++ forbids converting a string constant to ‘char*’ [-Werror=write-strings]
      274 |     char* array_of_strings[] = {"hello", " ", "world", " ", "how", " ", "are ", "you?"};
          |                                                        ^~~
    str_concatenate.c:274:61: error: ISO C++ forbids converting a string constant to ‘char*’ [-Werror=write-strings]
      274 |     char* array_of_strings[] = {"hello", " ", "world", " ", "how", " ", "are ", "you?"};
          |                                                             ^~~~~
    str_concatenate.c:274:68: error: ISO C++ forbids converting a string constant to ‘char*’ [-Werror=write-strings]
      274 |     char* array_of_strings[] = {"hello", " ", "world", " ", "how", " ", "are ", "you?"};
          |                                                                    ^~~
    str_concatenate.c:274:73: error: ISO C++ forbids converting a string constant to ‘char*’ [-Werror=write-strings]
      274 |     char* array_of_strings[] = {"hello", " ", "world", " ", "how", " ", "are ", "you?"};
          |                                                                         ^~~~~~
    str_concatenate.c:274:81: error: ISO C++ forbids converting a string constant to ‘char*’ [-Werror=write-strings]
      274 |     char* array_of_strings[] = {"hello", " ", "world", " ", "how", " ", "are ", "you?"};
          |                                                                                 ^~~~~~
    str_concatenate.c:307:34: error: ISO C++ forbids converting a string constant to ‘char*’ [-Werror=write-strings]
      307 |     char* array_of_strings2[] = {"again: ", "hello", " ", "world", " ", "how", " ", "are ", "you?"};
          |                                  ^~~~~~~~~
    str_concatenate.c:307:45: error: ISO C++ forbids converting a string constant to ‘char*’ [-Werror=write-strings]
      307 |     char* array_of_strings2[] = {"again: ", "hello", " ", "world", " ", "how", " ", "are ", "you?"};
          |                                             ^~~~~~~
    str_concatenate.c:307:54: error: ISO C++ forbids converting a string constant to ‘char*’ [-Werror=write-strings]
      307 |     char* array_of_strings2[] = {"again: ", "hello", " ", "world", " ", "how", " ", "are ", "you?"};
          |                                                      ^~~
    str_concatenate.c:307:59: error: ISO C++ forbids converting a string constant to ‘char*’ [-Werror=write-strings]
      307 |     char* array_of_strings2[] = {"again: ", "hello", " ", "world", " ", "how", " ", "are ", "you?"};
          |                                                           ^~~~~~~
    str_concatenate.c:307:68: error: ISO C++ forbids converting a string constant to ‘char*’ [-Werror=write-strings]
      307 |     char* array_of_strings2[] = {"again: ", "hello", " ", "world", " ", "how", " ", "are ", "you?"};
          |                                                                    ^~~
    str_concatenate.c:307:73: error: ISO C++ forbids converting a string constant to ‘char*’ [-Werror=write-strings]
      307 |     char* array_of_strings2[] = {"again: ", "hello", " ", "world", " ", "how", " ", "are ", "you?"};
          |                                                                         ^~~~~
    str_concatenate.c:307:80: error: ISO C++ forbids converting a string constant to ‘char*’ [-Werror=write-strings]
      307 |     char* array_of_strings2[] = {"again: ", "hello", " ", "world", " ", "how", " ", "are ", "you?"};
          |                                                                                ^~~
    str_concatenate.c:307:85: error: ISO C++ forbids converting a string constant to ‘char*’ [-Werror=write-strings]
      307 |     char* array_of_strings2[] = {"again: ", "hello", " ", "world", " ", "how", " ", "are ", "you?"};
          |                                                                                     ^~~~~~
    str_concatenate.c:307:93: error: ISO C++ forbids converting a string constant to ‘char*’ [-Werror=write-strings]
      307 |     char* array_of_strings2[] = {"again: ", "hello", " ", "world", " ", "how", " ", "are ", "you?"};
          |                                                                                             ^~~~~~
    cc1plus: all warnings being treated as errors


*/
