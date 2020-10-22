
// This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

/*
onlinegdb--strncmpci.c

Gabriel Staples
www.ElectricRCAircraftGuy.com
Written: 21 Mar. 2019
Updated: 21 Oct. 2020
- moved to this git repo; see `git log` history after that

To compile and run:

    gcc -Wall -Wextra -Werror -ggdb -std=c11 -o bin/tmp onlinegdb--strncmpci.c && ./tmp


References:
1. [my own answer] https://stackoverflow.com/questions/5820810/case-insensitive-string-comp-in-c/55293507#55293507
2. https://en.cppreference.com/w/cpp/string/byte/strncmp
3. http://www.cplusplus.com/reference/cstring/strncmp/

STATUS:
Done. It works!

*/

#include <ctype.h> // for `tolower()`
#include <limits.h> // for `INT_MIN`
#include <stdio.h>
#include <string.h>

/*

Case-insensitive string compare (strncmp case-insensitive)
- Identical to strncmp except case-insensitive. See: http://www.cplusplus.com/reference/cstring/strncmp/
- Aided/inspired, in part, by: https://stackoverflow.com/a/5820991/4561887




return:
(essentially identical to strncmp)
INT_MIN  invalid arguments (one or both of the input strings is a NULL pointer)
<0       the first character that does not match has a lower value in str1 than in str2
 0       the contents of both strings are equal
>0       the first character that does not match has a greater value in str1 than in str2
*/

/// \brief      Perform a case-insensitive string compare (`strncmp()` case-insensitive) to see
///             if two C-strings are equal.
/// \note       1. Identical to `strncmp()` except:
///               1. It is case-insensitive.
///               2. The behavior is NOT undefined (it is well-defined) if either string is a null
///               ptr. Regular `strncmp()` has undefined behavior if either string is a null ptr
///               (see: https://en.cppreference.com/w/cpp/string/byte/strncmp).
///               3. It returns `INT_MIN` as a special sentinel value for certain errors.
///             - Posted as an answer here: https://stackoverflow.com/a/55293507/4561887.
///               - Aided/inspired, in part, by `strcicmp()` here:
///                 https://stackoverflow.com/a/5820991/4561887.
/// \param[in]  str1        C string 1 to be compared.
/// \param[in]  str2        C string 2 to be compared.
/// \param[in]  num         max number of chars to compare
/// \return     A comparison code (identical to `strncmp()`, except with the addition
///             of `INT_MIN` as a special sentinel value):
///
///             INT_MIN  Invalid arguments (one or both of the input strings is a NULL pointer).
///             <0       The first character that does not match has a lower value in str1 than
///                      in str2.
///              0       The contents of both strings are equal.
///             >0       The first character that does not match has a greater value in str1 than
///                      in str2.
int strncmpci(const char * str1, const char * str2, size_t num)
{
    int ret_code = INT_MIN;

    size_t chars_compared = 0;

    // Check for NULL pointers
    if (!str1 || !str2)
    {
        goto done;
    }

    // Continue doing case-insensitive comparisons, one-character-at-a-time, of str1 to str2,
    // as long as at least one of the strings still has more characters in it, and we have
    // not yet compared num chars.
    while ((*str1 || *str2) && (chars_compared < num))
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

done:
    return ret_code;
}

// Added 26 July 2020
// Copied directly from:
// https://stackoverflow.com/questions/5820810/case-insensitive-string-comp-in-c/5820991#5820991
int strcicmp(char const *a, char const *b)
{
    for (;; a++, b++) {
        int d = tolower((unsigned char)*a) - tolower((unsigned char)*b);
        if (d != 0 || !*a)
            return d;
    }
}

int main()
{
    printf("Hello World\n\n");

    const char * str1;
    const char * str2;
    size_t n;

    str1 = "hey";
    str2 = "HEY";
    n = 3;
    printf("strncmpci(%s, %s, %u) = %i\n", str1, str2, n, strncmpci(str1, str2, n));
    printf("strcicmp(%s, %s) = %i\n", str1, str2, strcicmp(str1, str2));
    printf("strncmp(%s, %s, %u) = %i\n", str1, str2, n, strncmp(str1, str2, n));
    printf("\n");

    str1 = "heY";
    str2 = "HeY";
    n = 3;
    printf("strncmpci(%s, %s, %u) = %i\n", str1, str2, n, strncmpci(str1, str2, n));
    printf("strcicmp(%s, %s) = %i\n", str1, str2, strcicmp(str1, str2));
    printf("strncmp(%s, %s, %u) = %i\n", str1, str2, n, strncmp(str1, str2, n));
    printf("\n");

    str1 = "hey";
    str2 = "HEdY";
    n = 3;
    printf("strncmpci(%s, %s, %u) = %i\n", str1, str2, n, strncmpci(str1, str2, n));
    printf("strcicmp(%s, %s) = %i\n", str1, str2, strcicmp(str1, str2));
    printf("strncmp(%s, %s, %u) = %i\n", str1, str2, n, strncmp(str1, str2, n));
    printf("\n");

    str1 = "heY";
    str2 = "HeYd";
    n = 3;
    printf("strncmpci(%s, %s, %u) = %i\n", str1, str2, n, strncmpci(str1, str2, n));
    printf("strcicmp(%s, %s) = %i\n", str1, str2, strcicmp(str1, str2));
    printf("strncmp(%s, %s, %u) = %i\n", str1, str2, n, strncmp(str1, str2, n));
    printf("\n");

    str1 = "heY";
    str2 = "HeYd";
    n = 6;
    printf("strncmpci(%s, %s, %u) = %i\n", str1, str2, n, strncmpci(str1, str2, n));
    printf("strcicmp(%s, %s) = %i\n", str1, str2, strcicmp(str1, str2));
    printf("strncmp(%s, %s, %u) = %i\n", str1, str2, n, strncmp(str1, str2, n));
    printf("\n");

    str1 = "hey";
    str2 = "hey";
    n = 6;
    printf("strncmpci(%s, %s, %u) = %i\n", str1, str2, n, strncmpci(str1, str2, n));
    printf("strcicmp(%s, %s) = %i\n", str1, str2, strcicmp(str1, str2));
    printf("strncmp(%s, %s, %u) = %i\n", str1, str2, n, strncmp(str1, str2, n));
    printf("\n");

    str1 = "hey";
    str2 = "heyd";
    n = 6;
    printf("strncmpci(%s, %s, %u) = %i\n", str1, str2, n, strncmpci(str1, str2, n));
    printf("strcicmp(%s, %s) = %i\n", str1, str2, strcicmp(str1, str2));
    printf("strncmp(%s, %s, %u) = %i\n", str1, str2, n, strncmp(str1, str2, n));
    printf("\n");

    str1 = "hey";
    str2 = "heyd";
    n = 3;
    printf("strncmpci(%s, %s, %u) = %i\n", str1, str2, n, strncmpci(str1, str2, n));
    printf("strcicmp(%s, %s) = %i\n", str1, str2, strcicmp(str1, str2));
    printf("strncmp(%s, %s, %u) = %i\n", str1, str2, n, strncmp(str1, str2, n));
    printf("\n");

    return 0;
}

/*
Sample output:



*/



