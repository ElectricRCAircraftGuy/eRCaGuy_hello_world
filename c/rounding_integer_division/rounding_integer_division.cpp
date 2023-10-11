/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby,
C#, VB, Perl, Swift, Prolog, Javascript, Pascal, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.

OnlineGDB name: integer_rounding_during_division
eRCaGuy_hello_world project name: rounding_integer_division.cpp

Build & run commands:
Note: C files can't end in .cpp or else C compilation fails, so the .c version of this file
for C compilation is simply a symbolic link to the .cpp version of this file. Therefore, they
are the same file. Editing one will edit the other.
1. C:   gcc -Wall -Werror -g3 -std=c11 -o rounding_integer_division rounding_integer_division.c && ./rounding_integer_division
2. C++: g++ -Wall -Werror -g3 -std=c++17 -o rounding_integer_division rounding_integer_division.cpp && ./rounding_integer_division

By Gabriel Staples
www.ElectricRCAircraftGuy.com
Started: Oct. 2019
Updated: Apr. 2020
Most recent update: Oct. 2023
My GitHub project: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world/tree/master/c/rounding_integer_division
My Online answer: https://stackoverflow.com/questions/2422712/rounding-integer-division-instead-of-truncating/58568736#58568736

References:
1. https://stackoverflow.com/questions/2422712/rounding-integer-division-instead-of-truncating/58568736#58568736
1. https://www.tutorialspoint.com/cplusplus/cpp_templates.htm
1. https://stackoverflow.com/questions/4021981/use-static-assert-to-check-types-passed-to-macro/60769143#60769143
1. *****[MY OWN ANS!] https://stackoverflow.com/questions/4021981/use-static-assert-to-check-types-passed-to-macro/60769143#60769143
   - for type-checking in the C++ Template function!
1. *****+https://www.onlinegdb.com/edit/ryZnZ2Sr8
   - thorough C++ type-checking example!
   - online here: https://stackoverflow.com/questions/60611626/how-to-use-static-assert-in-c-to-check-the-types-of-parameters-passed-to-a-macro
1. Google search for "is_integer vs is_integral" - https://www.google.com/search?q=is_integer+vs+is_integral&oq=is_integer+vs+is_integral&aqs=chrome..69i57.7272j0j4&sourceid=chrome&ie=UTF-8
1. != as Logical XOR: https://stackoverflow.com/questions/1596668/logical-xor-operator-in-c/1596681#1596681


*******************************************************************************/

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

// -----------------------------------------------------------------------------
// For unit testing:
// -----------------------------------------------------------------------------

static uint32_t test_fail_cnt = 0; // increment counter each time a test fails

/// @brief  Test if num1 and num2 are equal, automatically passing the line number to the
///         test function.
#define TEST_EQ(num1, num2) test_eq(num1, num2, __LINE__)

/// @brief  Unit test: test if num1 and num2 are equal, and print the line number and whether
///         the test passes or fails.
void test_eq(int num1, int num2, int line_num)
{
    printf("Line %4i:%3i == %3i  ", line_num, num1, num2);

    if (num1 != num2)
    {
        test_fail_cnt++;
        printf("FAIL! <==\n");
    }
    else
    {
        printf("pass\n");
    }
}

// -----------------------------------------------------------------------------
// 1. Macros
// -----------------------------------------------------------------------------
// Great for C or C++, but some C++ developers hate them since they may have the multiple evaluation
// problem where you pass in an expression as an input parameter and it gets evaluated multiple
// times.

/// @brief      A function-like macro to perform integer division of numer/denom, rounding the
///             result UP (AWAY FROM ZERO) to the next whole integer.
/// @note       This works on *integers only* since it assumes integer truncation will take place
///             automatically during the division! It will NOT work properly on floating point
///             types! Valid types are int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t,
///             int64_t, uint64_t, etc.
/// @details    The concept is this:
///             (1) when the division result will be positive, *add*
///             (abs(denom) - 1) to the numerator *prior to* the division, as this is the
///             equivalent of adding a *tiny bit less than 1* to the result, which will always
///             result in a rounding up once integer truncation takes place. Examples:
///             1/4 = 0.25, but we add (abs(denom) - 1) to the numerator --> (1 + (4 - 1))/4 =
///             (1 + 3)/4 = 4/4 = 1.
///             (2) when the division result will be negative, simply truncating the result by
///             performing division as normal results in a rounding-up effect.
/// @param[in]  numer   The numerator in the division: any positive or negative integer
/// @param[in]  denom   The denominator in the division: any positive or negative integer
/// @return     The result of the (numer/denom) division rounded UP to the next *whole integer*!
#define DIVIDE_ROUND_AWAY_FROM_ZERO(numer, denom) DIVIDE_ROUNDUP((numer), (denom))
#define DIVIDE_ROUNDUP(numer, denom) (                                                  \
    /* NB: `!=` acts as a logical XOR operator */                                       \
    /* See: https://stackoverflow.com/a/1596681/4561887 */                              \
    ((numer) < 0) != ((denom) < 0) ?                                                    \
    /* numer OR denom, but NOT both, is negative, so do this: */                        \
    (numer) / (denom) :                                                                 \
    /* numer AND denom are either *both positive* OR *both negative*, so do this, */    \
    /* acting slightly differently if denom is negative: */                             \
    ((numer) + ((denom) < 0 ? (denom) + 1 : (denom) - 1)) / (denom)                     \
)

/// @brief      A function-like macro to perform integer division of numer/denom, rounding the
///             result DOWN (TOWARDS ZERO) to the next whole integer.
/// @note       This works on *integers only* since it assumes integer truncation will take place
///             automatically during the division! It will NOT work properly on floating point
///             types! Valid types are int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t,
///             int64_t, uint64_t, etc.
/// @details    The concept is this:
///             (1) when the division result will be positive, simply truncating the result by
///             performing division as normal results in a rounding-down effect.
///             (2) When the division result will be negative, *subtract*
///             (abs(denom) - 1) from the numerator *prior to* the division, as this is the
///             equivalent of subtracting a *tiny bit less than 1* from the result, which will
///             always result in a rounding down once integer truncation takes place. Examples:
///             -1/4 = -0.25, but we subtract (abs(denom) - 1) from the numerator -->
///             (-1 - (4 - 1))/4 = (-1 - 3)/4 = -4/4 = -1.
/// @param[in]  numer   The numerator in the division: any positive or negative integer
/// @param[in]  denom   The denominator in the division: any positive or negative integer
/// @return     The result of the (numer/denom) division rounded DOWN to the next *whole integer*!
#define DIVIDE_ROUND_TOWARDS_ZERO(numer, denom) DIVIDE_ROUNDDOWN((numer), (denom))
#define DIVIDE_ROUNDDOWN(numer, denom) (                                                \
    /* NB: `!=` acts as a logical XOR operator */                                       \
    /* See: https://stackoverflow.com/a/1596681/4561887 */                              \
    ((numer) < 0) != ((denom) < 0) ?                                                    \
    /* numer OR denom, but NOT both, is negative, so do this, */                        \
    /* acting slightly differently if denom is negative: */                             \
    ((numer) - ((denom) < 0 ? (denom) + 1 : (denom) - 1)) / (denom) :                   \
    /* numer AND denom are either *both positive* OR *both negative*, so do this: */    \
    (numer) / (denom)

/// @brief      A function-like macro to perform integer division of numer/denom, rounding the
///             result TO THE NEAREST whole integer.
/// @note       This works on *integers only* since it assumes integer truncation will take place
///             automatically during the division! It will NOT work properly on floating point
///             types! Valid types are int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t,
///             int64_t, uint64_t, etc.
/// @details    The concept is this:
///             (1) when the division result will be positive, *add* (denom/2) to
///             the numerator *prior to* the division, as this is the equivalent of adding
///             0.5 to the result, which will always result in rounding to the nearest whole
///             integer once integer truncation takes place. Examples:
///             3/4 = 0.75, but we add (denom/2) to the numerator --> (3 + 4/2)/4 =
///             (3 + 2)/4 = 5/4 = 1.25, which truncates to 1.
///             (2) when the division result will be negative, *subtract* (denom/2) from
///             the numerator *prior to* the division, as this is required to grow it by 0.5
///             in the direction *away from zero* (more negative in this case), which is required
///             for rounding to the nearest whole integer. The same principle as in the positive
///             case applies. Example: -3/4 = -0.75, but we subtract (denom/2) from the numerator
///             --> (-3 - 4/2)/4 = (-3 - 2)/4 = -5/4 = -1.25, which truncates to -1.
/// @param[in]  numer   The numerator in the division: any positive or negative integer
/// @param[in]  denom   The denominator in the division: any positive or negative integer
/// @return     The result of the (numer/denom) division rounded TO THE NEAREST *whole integer*!
#define DIVIDE_ROUNDNEAREST(numer, denom) (                                             \
    /* NB: `!=` acts as a logical XOR operator */                                       \
    /* See: https://stackoverflow.com/a/1596681/4561887 */                              \
    ((numer) < 0) != ((denom) < 0) ?                                                    \
    /* numer OR denom, but NOT both, is negative, so do this: */                        \
    ((numer) - ((denom)/2)) / (denom) :                                                 \
    /* numer AND denom are either *both positive* OR *both negative*, so do this: */    \
    ((numer) + ((denom)/2)) / (denom)                                                   \
)


// -----------------------------------------------------------------------------
// 2. Statement Expressions
// -----------------------------------------------------------------------------
// These solve the multiple evaluation problem of macros perfectly, but are not part of the C or
// C++ standard. Instead, they are gcc and clang compiler extensions to C and C++. These are safer
// to use than macros, but can still have a name pollution risk because variables created inside
// statement expressions are not in their own scope--rather, they are part of the outer scope.
// Nevertheless, prefer them to macros.

/// @brief  *gcc statement expression* form of the above equivalent macro
#define DIVIDE_ROUND_AWAY_FROM_ZERO2(numer, denom) DIVIDE_ROUNDUP2((numer), (denom))
#define DIVIDE_ROUNDUP2(numer, denom)                                           \
    ({                                                                          \
        __typeof__(numer) numer_ = (numer);                                     \
        __typeof__(denom) denom_ = (denom);                                     \
        ((numer_) < 0) != ((denom_) < 0) ?                                      \
            (numer_) / (denom_) :                                               \
            ((numer_) + ((denom_) < 0 ? (denom_) + 1 : (denom_)-1)) / (denom_); \
    })

/// @brief  *gcc statement expression* form of the above equivalent macro
#define DIVIDE_ROUND_TOWARDS_ZERO2(numer, denom) DIVIDE_ROUNDDOWN2((numer), (denom))
#define DIVIDE_ROUNDDOWN2(numer, denom)                                          \
    ({                                                                           \
        __typeof__(numer) numer_ = (numer);                                      \
        __typeof__(denom) denom_ = (denom);                                      \
        ((numer_) < 0) != ((denom_) < 0) ?                                       \
            ((numer_) - ((denom_) < 0 ? (denom_) + 1 : (denom_)-1)) / (denom_) : \
            (numer_) / (denom_);                                                 \
    })

/// @brief  *gcc statement expression* form of the above equivalent macro
#define DIVIDE_ROUNDNEAREST2(numer, denom)                                              \
({                                                                                      \
    __typeof__ (numer) numer_ = (numer);                                                \
    __typeof__ (denom) denom_ = (denom);                                                \
    ((numer_) < 0) != ((denom_) < 0) ?                                                  \
    ((numer_) - ((denom_)/2)) / (denom_) :                                              \
    ((numer_) + ((denom_)/2)) / (denom_);                                               \
})


// -----------------------------------------------------------------------------
// 3. C++ Templated Functions (AKA: Function Templates)
// -----------------------------------------------------------------------------
// Templates work in C++ only. They solve both problems above, and suffer neither from the multiple
// evaluation problem of macros, nor from the name pollution/variable scope problem of statement
// expressions. Since they work only in C++, I'm going to add type checking here too with a
// `static_assert()` using `std::numeric_limits`, but this feature could be *easily* added to both
// macros and statement expressions as well so long as you're using C++. Some C++ developers feel so
// strongly against macros (and are probably not aware of statement expressions) that they won't let
// you merge the above macro versions into their codebase. If this is the case, use templates.

#ifdef __cplusplus
#include <limits>

/// @brief  C++ function template form of the above equivalent macro
template <typename T>
T divide_roundup(T numer, T denom)
{
    // Ensure only integer types are passed in, as this round division technique does NOT work on
    // floating point types since it assumes integer truncation will take place automatically
    // during the division!
    // - The following static assert allows all integer types, including their various `const`,
    //   `volatile`, and `const volatile` variations, but prohibits any floating point type
    //   such as `float`, `double`, and `long double`.
    // - Reference page: https://en.cppreference.com/w/cpp/types/numeric_limits/is_integer
    static_assert(std::numeric_limits<T>::is_integer, "Only integer types are allowed");

    T result = ((numer) < 0) != ((denom) < 0) ?
        (numer) / (denom) :
        ((numer) + ((denom) < 0 ? (denom) + 1 : (denom) - 1)) / (denom);
    return result;
}

template <typename T>
inline T divide_round_away_from_zero(T numer, T denom)
{
    return divide_roundup(numer, denom);
}

/// @brief  C++ function template form of the above equivalent macro
template <typename T>
T divide_rounddown(T numer, T denom)
{
    // Ensure only integer types are passed in, as this round division technique does NOT work on
    // floating point types since it assumes integer truncation will take place automatically
    // during the division!
    // - The following static assert allows all integer types, including their various `const`,
    //   `volatile`, and `const volatile` variations, but prohibits any floating point type
    //   such as `float`, `double`, and `long double`.
    // - Reference page: https://en.cppreference.com/w/cpp/types/numeric_limits/is_integer
    static_assert(std::numeric_limits<T>::is_integer, "Only integer types are allowed");

    T result = ((numer) < 0) != ((denom) < 0) ?
        ((numer) - ((denom) < 0 ? (denom) + 1 : (denom) - 1)) / (denom) :
        (numer) / (denom);
    return result;
}

template <typename T>
inline T divide_round_towards_zero(T numer, T denom)
{
    return divide_rounddown(numer, denom);
}

/// @brief  C++ function template form of the above equivalent macro
template <typename T>
T divide_roundnearest(T numer, T denom)
{
    // Ensure only integer types are passed in, as this round division technique does NOT work on
    // floating point types since it assumes integer truncation will take place automatically
    // during the division!
    // - The following static assert allows all integer types, including their various `const`,
    //   `volatile`, and `const volatile` variations, but prohibits any floating point type
    //   such as `float`, `double`, and `long double`.
    // - Reference page: https://en.cppreference.com/w/cpp/types/numeric_limits/is_integer
    static_assert(std::numeric_limits<T>::is_integer, "Only integer types are allowed");

    T result = ((numer) < 0) != ((denom) < 0) ?
        ((numer) - ((denom)/2)) / (denom) :
        ((numer) + ((denom)/2)) / (denom);
    return result;
}

#endif


// -----------------------------------------------------------------------------
// main
// -----------------------------------------------------------------------------
int main()
{
    printf("Testing Rounding Integer Division\n\n");


    printf("1. Macro Tests\n\n");

    printf("DIVIDE_ROUNDUP():\n");
    TEST_EQ(DIVIDE_ROUNDUP(5, 5), 1);   // 5/5   = 1.00 --> 1
    TEST_EQ(DIVIDE_ROUNDUP(5, 4), 2);   // 5/4   = 1.25 --> 2
    TEST_EQ(DIVIDE_ROUNDUP(6, 4), 2);   // 6/4   = 1.50 --> 2
    TEST_EQ(DIVIDE_ROUNDUP(7, 4), 2);   // 7/4   = 1.75 --> 2
    TEST_EQ(DIVIDE_ROUNDUP(9, 10), 1);  // 9/10  = 0.90 --> 1
    TEST_EQ(DIVIDE_ROUNDUP(3, 4), 1);   // 3/4   = 0.75 --> 1
    TEST_EQ(DIVIDE_ROUNDUP(-3, 4), 0);  // -3/4  = -0.75 --> 0
    TEST_EQ(DIVIDE_ROUNDUP(3, -4), 0);  // 3/-4  = -0.75 --> 0
    TEST_EQ(DIVIDE_ROUNDUP(-3, -4), 1); // -3/-4 = 0.75 --> 1
    TEST_EQ(DIVIDE_ROUNDUP(999, 1000), 1);   // 999/1000    = 0.999 --> 1
    TEST_EQ(DIVIDE_ROUNDUP(-999, 1000), 0);  // -999/1000   = -0.999 --> 0
    TEST_EQ(DIVIDE_ROUNDUP(999, -1000), 0);  // 999/-1000   = -0.999 --> 0
    TEST_EQ(DIVIDE_ROUNDUP(-999, -1000), 1); // -999/-1000  = 0.999 --> 1

    printf("\nDIVIDE_ROUND_AWAY_FROM_ZERO():\n");
    TEST_EQ(DIVIDE_ROUND_AWAY_FROM_ZERO(5, 5), 1);         // 5/5   = 1.00 --> 1
    TEST_EQ(DIVIDE_ROUND_AWAY_FROM_ZERO(5, 4), 2);         // 5/4   = 1.25 --> 2
    TEST_EQ(DIVIDE_ROUND_AWAY_FROM_ZERO(6, 4), 2);         // 6/4   = 1.50 --> 2
    TEST_EQ(DIVIDE_ROUND_AWAY_FROM_ZERO(7, 4), 2);         // 7/4   = 1.75 --> 2
    TEST_EQ(DIVIDE_ROUND_AWAY_FROM_ZERO(9, 10), 1);        // 9/10  = 0.90 --> 1
    TEST_EQ(DIVIDE_ROUND_AWAY_FROM_ZERO(3, 4), 1);         // 3/4   = 0.75 --> 1
    TEST_EQ(DIVIDE_ROUND_AWAY_FROM_ZERO(-3, 4), 0);        // -3/4  = -0.75 --> 0
    TEST_EQ(DIVIDE_ROUND_AWAY_FROM_ZERO(3, -4), 0);        // 3/-4  = -0.75 --> 0
    TEST_EQ(DIVIDE_ROUND_AWAY_FROM_ZERO(-3, -4), 1);       // -3/-4 = 0.75 --> 1
    TEST_EQ(DIVIDE_ROUND_AWAY_FROM_ZERO(999, 1000), 1);    // 999/1000    = 0.999 --> 1
    TEST_EQ(DIVIDE_ROUND_AWAY_FROM_ZERO(-999, 1000), 0);   // -999/1000   = -0.999 --> 0
    TEST_EQ(DIVIDE_ROUND_AWAY_FROM_ZERO(999, -1000), 0);   // 999/-1000   = -0.999 --> 0
    TEST_EQ(DIVIDE_ROUND_AWAY_FROM_ZERO(-999, -1000), 1);  // -999/-1000  = 0.999 --> 1

    printf("\nDIVIDE_ROUNDDOWN():\n");
    TEST_EQ(DIVIDE_ROUNDDOWN(5, 5), 1);   // 5/5   = 1.00 --> 1
    TEST_EQ(DIVIDE_ROUNDDOWN(5, 4), 1);   // 5/4   = 1.25 --> 1
    TEST_EQ(DIVIDE_ROUNDDOWN(6, 4), 1);   // 6/4   = 1.50 --> 1
    TEST_EQ(DIVIDE_ROUNDDOWN(7, 4), 1);   // 7/4   = 1.75 --> 1
    TEST_EQ(DIVIDE_ROUNDDOWN(9, 10), 0);  // 9/10  = 0.90 --> 0
    TEST_EQ(DIVIDE_ROUNDDOWN(3, 4), 0);   // 3/4   = 0.75 --> 0
    TEST_EQ(DIVIDE_ROUNDDOWN(-3, 4), -1); // -3/4  = -0.75 --> -1
    TEST_EQ(DIVIDE_ROUNDDOWN(3, -4), -1); // 3/-4  = -0.75 --> -1
    TEST_EQ(DIVIDE_ROUNDDOWN(-3, -4), 0); // -3/-4 = 0.75 --> 0
    TEST_EQ(DIVIDE_ROUNDDOWN(999, 1000), 0);   // 999/1000    = 0.999 --> 0
    TEST_EQ(DIVIDE_ROUNDDOWN(-999, 1000), -1);  // -999/1000   = -0.999 --> -1
    TEST_EQ(DIVIDE_ROUNDDOWN(999, -1000), -1);  // 999/-1000   = -0.999 --> -1
    TEST_EQ(DIVIDE_ROUNDDOWN(-999, -1000), 0); // -999/-1000  = 0.999 --> 0

    printf("\nDIVIDE_ROUND_TOWARDS_ZERO():\n");
    TEST_EQ(DIVIDE_ROUND_TOWARDS_ZERO(5, 5), 1);         // 5/5   = 1.00 --> 1
    TEST_EQ(DIVIDE_ROUND_TOWARDS_ZERO(5, 4), 1);         // 5/4   = 1.25 --> 1
    TEST_EQ(DIVIDE_ROUND_TOWARDS_ZERO(6, 4), 1);         // 6/4   = 1.50 --> 1
    TEST_EQ(DIVIDE_ROUND_TOWARDS_ZERO(7, 4), 1);         // 7/4   = 1.75 --> 1
    TEST_EQ(DIVIDE_ROUND_TOWARDS_ZERO(9, 10), 0);        // 9/10  = 0.90 --> 0
    TEST_EQ(DIVIDE_ROUND_TOWARDS_ZERO(3, 4), 0);         // 3/4   = 0.75 --> 0
    TEST_EQ(DIVIDE_ROUND_TOWARDS_ZERO(-3, 4), -1);       // -3/4  = -0.75 --> -1
    TEST_EQ(DIVIDE_ROUND_TOWARDS_ZERO(3, -4), -1);       // 3/-4  = -0.75 --> -1
    TEST_EQ(DIVIDE_ROUND_TOWARDS_ZERO(-3, -4), 0);       // -3/-4 = 0.75 --> 0
    TEST_EQ(DIVIDE_ROUND_TOWARDS_ZERO(999, 1000), 0);    // 999/1000    = 0.999 --> 0
    TEST_EQ(DIVIDE_ROUND_TOWARDS_ZERO(-999, 1000), -1);  // -999/1000   = -0.999 --> -1
    TEST_EQ(DIVIDE_ROUND_TOWARDS_ZERO(999, -1000), -1);  // 999/-1000   = -0.999 --> -1
    TEST_EQ(DIVIDE_ROUND_TOWARDS_ZERO(-999, -1000), 0);  // -999/-1000  = 0.999 --> 0

    printf("\nDIVIDE_ROUNDNEAREST():\n");
    TEST_EQ(DIVIDE_ROUNDNEAREST(5, 5), 1);   // 5/5   = 1.00 --> 1
    TEST_EQ(DIVIDE_ROUNDNEAREST(5, 4), 1);   // 5/4   = 1.25 --> 1
    TEST_EQ(DIVIDE_ROUNDNEAREST(6, 4), 2);   // 6/4   = 1.50 --> 2
    TEST_EQ(DIVIDE_ROUNDNEAREST(7, 4), 2);   // 7/4   = 1.75 --> 2
    TEST_EQ(DIVIDE_ROUNDNEAREST(9, 10), 1);  // 9/10  = 0.90 --> 1
    TEST_EQ(DIVIDE_ROUNDNEAREST(3, 4), 1);   // 3/4   = 0.75 --> 1
    TEST_EQ(DIVIDE_ROUNDNEAREST(-3, 4), -1);  // -3/4  = -0.75 --> -1
    TEST_EQ(DIVIDE_ROUNDNEAREST(3, -4), -1);  // 3/-4  = -0.75 --> -1
    TEST_EQ(DIVIDE_ROUNDNEAREST(-3, -4), 1); // -3/-4 = 0.75 --> 1
    TEST_EQ(DIVIDE_ROUNDNEAREST(999, 1000), 1);   // 999/1000    = 0.999 --> 1
    TEST_EQ(DIVIDE_ROUNDNEAREST(-999, 1000), -1);  // -999/1000   = -0.999 --> -1
    TEST_EQ(DIVIDE_ROUNDNEAREST(999, -1000), -1);  // 999/-1000   = -0.999 --> -1
    TEST_EQ(DIVIDE_ROUNDNEAREST(-999, -1000), 1); // -999/-1000  = 0.999 --> 1

    // Add a few extras with some unsigned types
    TEST_EQ(DIVIDE_ROUNDNEAREST((uint8_t)5, 5), 1);   // 5/5   = 1.00 --> 1
    TEST_EQ(DIVIDE_ROUNDNEAREST(5, (uint64_t)4), 1);   // 5/4   = 1.25 --> 1


    printf("\n\n2. Statement Expression Tests\n\n");

    printf("DIVIDE_ROUNDUP2():\n");
    TEST_EQ(DIVIDE_ROUNDUP2(5, 5), 1);   // 5/5   = 1.00 --> 1
    TEST_EQ(DIVIDE_ROUNDUP2(5, 4), 2);   // 5/4   = 1.25 --> 2
    TEST_EQ(DIVIDE_ROUNDUP2(6, 4), 2);   // 6/4   = 1.50 --> 2
    TEST_EQ(DIVIDE_ROUNDUP2(7, 4), 2);   // 7/4   = 1.75 --> 2
    TEST_EQ(DIVIDE_ROUNDUP2(9, 10), 1);  // 9/10  = 0.90 --> 1
    TEST_EQ(DIVIDE_ROUNDUP2(3, 4), 1);   // 3/4   = 0.75 --> 1
    TEST_EQ(DIVIDE_ROUNDUP2(-3, 4), 0);  // -3/4  = -0.75 --> 0
    TEST_EQ(DIVIDE_ROUNDUP2(3, -4), 0);  // 3/-4  = -0.75 --> 0
    TEST_EQ(DIVIDE_ROUNDUP2(-3, -4), 1); // -3/-4 = 0.75 --> 1
    TEST_EQ(DIVIDE_ROUNDUP2(999, 1000), 1);   // 999/1000    = 0.999 --> 1
    TEST_EQ(DIVIDE_ROUNDUP2(-999, 1000), 0);  // -999/1000   = -0.999 --> 0
    TEST_EQ(DIVIDE_ROUNDUP2(999, -1000), 0);  // 999/-1000   = -0.999 --> 0
    TEST_EQ(DIVIDE_ROUNDUP2(-999, -1000), 1); // -999/-1000  = 0.999 --> 1

    printf("\nDIVIDE_ROUNDDOWN2():\n");
    TEST_EQ(DIVIDE_ROUNDDOWN2(5, 5), 1);   // 5/5   = 1.00 --> 1
    TEST_EQ(DIVIDE_ROUNDDOWN2(5, 4), 1);   // 5/4   = 1.25 --> 1
    TEST_EQ(DIVIDE_ROUNDDOWN2(6, 4), 1);   // 6/4   = 1.50 --> 1
    TEST_EQ(DIVIDE_ROUNDDOWN2(7, 4), 1);   // 7/4   = 1.75 --> 1
    TEST_EQ(DIVIDE_ROUNDDOWN2(9, 10), 0);  // 9/10  = 0.90 --> 0
    TEST_EQ(DIVIDE_ROUNDDOWN2(3, 4), 0);   // 3/4   = 0.75 --> 0
    TEST_EQ(DIVIDE_ROUNDDOWN2(-3, 4), -1); // -3/4  = -0.75 --> -1
    TEST_EQ(DIVIDE_ROUNDDOWN2(3, -4), -1); // 3/-4  = -0.75 --> -1
    TEST_EQ(DIVIDE_ROUNDDOWN2(-3, -4), 0); // -3/-4 = 0.75 --> 0
    TEST_EQ(DIVIDE_ROUNDDOWN2(999, 1000), 0);   // 999/1000    = 0.999 --> 0
    TEST_EQ(DIVIDE_ROUNDDOWN2(-999, 1000), -1);  // -999/1000   = -0.999 --> -1
    TEST_EQ(DIVIDE_ROUNDDOWN2(999, -1000), -1);  // 999/-1000   = -0.999 --> -1
    TEST_EQ(DIVIDE_ROUNDDOWN2(-999, -1000), 0); // -999/-1000  = 0.999 --> 0

    printf("\nDIVIDE_ROUNDNEAREST2():\n");
    TEST_EQ(DIVIDE_ROUNDNEAREST2(5, 5), 1);   // 5/5   = 1.00 --> 1
    TEST_EQ(DIVIDE_ROUNDNEAREST2(5, 4), 1);   // 5/4   = 1.25 --> 1
    TEST_EQ(DIVIDE_ROUNDNEAREST2(6, 4), 2);   // 6/4   = 1.50 --> 2
    TEST_EQ(DIVIDE_ROUNDNEAREST2(7, 4), 2);   // 7/4   = 1.75 --> 2
    TEST_EQ(DIVIDE_ROUNDNEAREST2(9, 10), 1);  // 9/10  = 0.90 --> 1
    TEST_EQ(DIVIDE_ROUNDNEAREST2(3, 4), 1);   // 3/4   = 0.75 --> 1
    TEST_EQ(DIVIDE_ROUNDNEAREST2(-3, 4), -1);  // -3/4  = -0.75 --> -1
    TEST_EQ(DIVIDE_ROUNDNEAREST2(3, -4), -1);  // 3/-4  = -0.75 --> -1
    TEST_EQ(DIVIDE_ROUNDNEAREST2(-3, -4), 1); // -3/-4 = 0.75 --> 1
    TEST_EQ(DIVIDE_ROUNDNEAREST2(999, 1000), 1);   // 999/1000    = 0.999 --> 1
    TEST_EQ(DIVIDE_ROUNDNEAREST2(-999, 1000), -1);  // -999/1000   = -0.999 --> -1
    TEST_EQ(DIVIDE_ROUNDNEAREST2(999, -1000), -1);  // 999/-1000   = -0.999 --> -1
    TEST_EQ(DIVIDE_ROUNDNEAREST2(-999, -1000), 1); // -999/-1000  = 0.999 --> 1


#ifdef __cplusplus
    printf("\n\n3. Function Template Tests\n\n");

    printf("divide_roundup():\n");
    TEST_EQ(divide_roundup(5, 5), 1);   // 5/5   = 1.00 --> 1
    TEST_EQ(divide_roundup(5, 4), 2);   // 5/4   = 1.25 --> 2
    TEST_EQ(divide_roundup(6, 4), 2);   // 6/4   = 1.50 --> 2
    TEST_EQ(divide_roundup(7, 4), 2);   // 7/4   = 1.75 --> 2
    TEST_EQ(divide_roundup(9, 10), 1);  // 9/10  = 0.90 --> 1
    TEST_EQ(divide_roundup(3, 4), 1);   // 3/4   = 0.75 --> 1
    TEST_EQ(divide_roundup(-3, 4), 0);  // -3/4  = -0.75 --> 0
    TEST_EQ(divide_roundup(3, -4), 0);  // 3/-4  = -0.75 --> 0
    TEST_EQ(divide_roundup(-3, -4), 1); // -3/-4 = 0.75 --> 1
    TEST_EQ(divide_roundup(999, 1000), 1);   // 999/1000    = 0.999 --> 1
    TEST_EQ(divide_roundup(-999, 1000), 0);  // -999/1000   = -0.999 --> 0
    TEST_EQ(divide_roundup(999, -1000), 0);  // 999/-1000   = -0.999 --> 0
    TEST_EQ(divide_roundup(-999, -1000), 1); // -999/-1000  = 0.999 --> 1

    printf("\ndivide_rounddown():\n");
    TEST_EQ(divide_rounddown(5, 5), 1);   // 5/5   = 1.00 --> 1
    TEST_EQ(divide_rounddown(5, 4), 1);   // 5/4   = 1.25 --> 1
    TEST_EQ(divide_rounddown(6, 4), 1);   // 6/4   = 1.50 --> 1
    TEST_EQ(divide_rounddown(7, 4), 1);   // 7/4   = 1.75 --> 1
    TEST_EQ(divide_rounddown(9, 10), 0);  // 9/10  = 0.90 --> 0
    TEST_EQ(divide_rounddown(3, 4), 0);   // 3/4   = 0.75 --> 0
    TEST_EQ(divide_rounddown(-3, 4), -1); // -3/4  = -0.75 --> -1
    TEST_EQ(divide_rounddown(3, -4), -1); // 3/-4  = -0.75 --> -1
    TEST_EQ(divide_rounddown(-3, -4), 0); // -3/-4 = 0.75 --> 0
    TEST_EQ(divide_rounddown(999, 1000), 0);   // 999/1000    = 0.999 --> 0
    TEST_EQ(divide_rounddown(-999, 1000), -1);  // -999/1000   = -0.999 --> -1
    TEST_EQ(divide_rounddown(999, -1000), -1);  // 999/-1000   = -0.999 --> -1
    TEST_EQ(divide_rounddown(-999, -1000), 0); // -999/-1000  = 0.999 --> 0

    printf("\ndivide_roundnearest():\n");
    TEST_EQ(divide_roundnearest(5, 5), 1);   // 5/5   = 1.00 --> 1
    TEST_EQ(divide_roundnearest(5, 4), 1);   // 5/4   = 1.25 --> 1
    TEST_EQ(divide_roundnearest(6, 4), 2);   // 6/4   = 1.50 --> 2
    TEST_EQ(divide_roundnearest(7, 4), 2);   // 7/4   = 1.75 --> 2
    TEST_EQ(divide_roundnearest(9, 10), 1);  // 9/10  = 0.90 --> 1
    TEST_EQ(divide_roundnearest(3, 4), 1);   // 3/4   = 0.75 --> 1
    TEST_EQ(divide_roundnearest(-3, 4), -1);  // -3/4  = -0.75 --> -1
    TEST_EQ(divide_roundnearest(3, -4), -1);  // 3/-4  = -0.75 --> -1
    TEST_EQ(divide_roundnearest(-3, -4), 1); // -3/-4 = 0.75 --> 1
    TEST_EQ(divide_roundnearest(999, 1000), 1);   // 999/1000    = 0.999 --> 1
    TEST_EQ(divide_roundnearest(-999, 1000), -1);  // -999/1000   = -0.999 --> -1
    TEST_EQ(divide_roundnearest(999, -1000), -1);  // 999/-1000   = -0.999 --> -1
    TEST_EQ(divide_roundnearest(-999, -1000), 1); // -999/-1000  = 0.999 --> 1

    // Check the static assert to ensure only integer types are allowed,
    // including with const or volatile specifiers

    // Float test:
    // HITS STATIC ASSERT! GOOD!
    //      error: static assertion failed: Only integer types are allowed
    //              static_assert(std::numeric_limits<T>::is_integer, "Only integer types are allowed");
    //              ^~~~~~~~~~~~~
    // TEST_EQ(divide_roundnearest(7.0, 4.0), 2); // 7/4 = 1.75

    // Check differing types; this should NOT work since I wrote the template to expect two inputs
    // of the EXACT SAME TYPE!
    // FAILS TO COMPILE! GOOD!
    //      rounding_integer_division.cpp:451:56: error: no matching function for call to ‘divide_roundnearest(uint32_t, int32_t)’
    //              TEST_EQ(divide_roundnearest((uint32_t)7, (int32_t)4), 2); // 7/4 = 1.75 --> 2
    //                                                                 ^
    // TEST_EQ(divide_roundnearest((uint32_t)7, (int32_t)4), 2); // 7/4 = 1.75 --> 2

    // Try a few as uint8_t for kicks:
    TEST_EQ(divide_roundnearest((uint8_t)5, (uint8_t)4), 1);   // 5/4   = 1.25 --> 1
    TEST_EQ(divide_roundnearest((uint8_t)6, (uint8_t)4), 2);   // 6/4   = 1.50 --> 2
    TEST_EQ(divide_roundnearest((uint8_t)7, (uint8_t)4), 2);   // 7/4   = 1.75 --> 2

    // Try some explicit template types using the <> operator:
    /////////////// TODO
    // TEST_EQ(divide_roundnearest<7>(5, 4), 1);   // 5/4   = 1.25 --> 1

#endif

    printf("\nTest failure count = %u\n\n", test_fail_cnt);
    assert(test_fail_cnt == 0);

    return 0;
} // main




