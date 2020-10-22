
// This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

/*
onlinegdb--strncmpci.c

Gabriel Staples
www.ElectricRCAircraftGuy.com
Written: 21 Mar. 2019
Updated: 21 Oct. 2020
- moved to this git repo; see `git log` history after that

To compile and run:

    gcc -Wall -Wextra -Werror -ggdb -std=c11 -o ./bin/tmp onlinegdb--strncmpci.c && ./bin/tmp


References:
1. [my own answer] https://stackoverflow.com/questions/5820810/case-insensitive-string-comp-in-c/55293507#55293507
2. https://en.cppreference.com/w/cpp/string/byte/strncmp
3. http://www.cplusplus.com/reference/cstring/strncmp/

STATUS:
WORK-IN-PROGRESS!

*/

#include <assert.h>
#include <stdbool.h>
#include <ctype.h> // for `tolower()`
#include <limits.h> // for `INT_MIN`
#include <stdio.h>
#include <string.h>

// For ANSI color codes in a terminal, see my notes to self in my file here:
// https://github.com/ElectricRCAircraftGuy/eRCaGuy_dotfiles/blob/master/useful_scripts/git-diffn.sh
#define ANSI_COLOR_OFF "\033[m"
#define ANSI_COLOR_GRN "\033[32m"
#define ANSI_COLOR_RED "\033[31m"

typedef struct data_s
{
    int error_count;
} data_t;

// Data struct used to safely contain and pass around global data
data_t globals = {
    .error_count = 0,
};

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

// TODO: ADD IN Unit tests to test this function too! Ex: `EXPECT_EQUALS(strcicmp(str1, str2), 0);`

// /// \brief      Alternative approach to test and compare results from.
// /// \note       Copied directly from here:
// ///             https://stackoverflow.com/questions/5820810/case-insensitive-string-comp-in-c/5820991#5820991
// int strcicmp(char const *a, char const *b)
// {
//     for (;; a++, b++) {
//         int d = tolower((unsigned char)*a) - tolower((unsigned char)*b);
//         if (d != 0 || !*a)
//             return d;
//     }
// }

/// \brief      Wrapper around the below unit test function.
/// \details    Sample usage:
///                 EXPECT_EQUALS(strncmpci(str1, str2, n), 1);
///             Sample output:
///                 FAILED at line 173 in function main! strncmpci(str1, str2, n) != 1
///                   a: strncmpci(str1, str2, n) is 0
///                   b: 1 is 1
#define EXPECT_EQUALS(int_a, int_b) \
    do { \
        expect_equals(int_a, int_b, &globals.error_count, #int_a, #int_b, __LINE__, __func__); \
    } while (false)

/// \brief      Perform a simple unit test to see if int a == int b.
/// \param[in]      a            the first integer to compare
/// \param[in]      b            the second integer to compare
/// \param[in,out]  error_count  (Optional) a total error counter which will be incremented in the
///                     event a != b. Pass in NULL to not use.
/// \param[in]      a_str        (Optional) a string to print to represent what was passed in for
///                              `a`. Pass in NULL to not use.
/// \param[in]      b_str        (Optional) a string to print to represent what was passed in for
///                              `b`. Pass in NULL to not use.
/// \param[in]      line         The line number of the call site; pass in `__LINE__`. See:
///                              https://gcc.gnu.org/onlinedocs/cpp/Standard-Predefined-Macros.html.
/// \param[in]      func         The function of the call site; pass in `__func__`. See:
///                              https://gcc.gnu.org/onlinedocs/gcc/Function-Names.html.
/// \return     true if a == b, and false otherwise
bool expect_equals(int a, int b, int * error_count, char * a_str, char * b_str, int line,
    const char * func)
{
    if (a == b)
    {
        return true;
    }

    if (error_count != NULL)
    {
        (*error_count)++;
    }

    if (a_str == NULL || b_str == NULL)
    {
        printf("FAILED at line %i in function %s! a != b\n"
               "  a is %i\n"
               "  b is %i\n\n",
               line, func, a, b);
    }
    else
    {
        // both a_str and b_str are NOT null ptrs
        printf("FAILED at line %i in function %s! %s != %s\n"
               "  a: %s is %i\n"
               "  b: %s is %i\n\n",
               line, func, a_str, b_str, a_str, a, b_str, b);
    }

    return false;
}

int main()
{
    printf("-----------------------\n"
           "String Comparison Tests\n"
           "-----------------------\n\n");

    int num_failures_expected = 0;

    printf("INTENTIONAL UNIT TEST FAILURE to show what a unit test failure looks like!\n");
    EXPECT_EQUALS(strncmpci("hey", "HEY", 3), 1);
    num_failures_expected++;
    printf("------ beginning ------\n\n");


    const char * str1;
    const char * str2;
    size_t n;

    str1 = "hey";
    str2 = "HEY";
    n = 3;
    EXPECT_EQUALS(strncmpci(str1, str2, n), 0);
    EXPECT_EQUALS(strncmp(str1, str2, n), 'h' - 'H');

    str1 = "heY";
    str2 = "HeY";
    n = 3;
    EXPECT_EQUALS(strncmpci(str1, str2, n), 0);
    EXPECT_EQUALS(strncmp(str1, str2, n), 'h' - 'H');

    str1 = "hey";
    str2 = "HEdY";
    n = 3;
    EXPECT_EQUALS(strncmpci(str1, str2, n), 'y' - 'd');
    EXPECT_EQUALS(strncmp(str1, str2, n), 'h' - 'H');

    str1 = "heY";
    str2 = "hEYd";
    n = 3;
    EXPECT_EQUALS(strncmpci(str1, str2, n), 0);
    EXPECT_EQUALS(strncmp(str1, str2, n), 'e' - 'E');

    str1 = "heY";
    str2 = "heyd";
    n = 6;
    EXPECT_EQUALS(strncmpci(str1, str2, n), -'d');
    EXPECT_EQUALS(strncmp(str1, str2, n), 'Y' - 'y');

    str1 = "hey";
    str2 = "hey";
    n = 6;
    EXPECT_EQUALS(strncmpci(str1, str2, n), 0);
    EXPECT_EQUALS(strncmp(str1, str2, n), 0);

    str1 = "hey";
    str2 = "heyd";
    n = 6;
    EXPECT_EQUALS(strncmpci(str1, str2, n), -'d');
    EXPECT_EQUALS(strncmp(str1, str2, n), -'d');

    str1 = "hey";
    str2 = "heyd";
    n = 3;
    EXPECT_EQUALS(strncmpci(str1, str2, n), 0);
    EXPECT_EQUALS(strncmp(str1, str2, n), 0);

    str1 = "hEY";
    str2 = "heyYOU";
    n = 3;
    EXPECT_EQUALS(strncmpci(str1, str2, n), 0);
    EXPECT_EQUALS(strncmp(str1, str2, n), 'E' - 'e');

    str1 = "hEY";
    str2 = "heyYOU";
    n = 10;
    EXPECT_EQUALS(strncmpci(str1, str2, n), -'y');
    EXPECT_EQUALS(strncmp(str1, str2, n), 'E' - 'e');

    str1 = "hEYHowAre";
    str2 = "heyYOU";
    n = 10;
    EXPECT_EQUALS(strncmpci(str1, str2, n), 'h' - 'y');
    EXPECT_EQUALS(strncmp(str1, str2, n), 'E' - 'e');


    if (globals.error_count == num_failures_expected)
    {
        printf(ANSI_COLOR_GRN "All unit tests passed!" ANSI_COLOR_OFF "\n");
    }
    else
    {
        printf(ANSI_COLOR_RED "FAILED UNIT TESTS! NUMBER OF UNEXPECTED FAILURES = %i"
            ANSI_COLOR_OFF "\n", globals.error_count - num_failures_expected);
    }

    assert(globals.error_count == num_failures_expected);
    return globals.error_count;
}

/*
Sample output:



*/



