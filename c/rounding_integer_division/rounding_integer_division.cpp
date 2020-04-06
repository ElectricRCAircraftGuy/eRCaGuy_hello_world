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

Gabriel Staples 
www.ElectricRCAircraftGuy.com 
Started: Oct. 2019 
Last updated: Apr. 2020 
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

#include <stdint.h>
#include <stdio.h>

#define TEST_EQ(num1, num2, line_num) test_eq(num1, num2, __LINE__)

// Function for unit tests
void test_eq(int num1, int num2, int line_num)
{
    printf("Line %i:\t%i == %i\t\t", line_num, num1, num2);

    if (num1 != num2)
    {
        printf("FAIL!\n");
    }
    else
    {
        printf("pass\n");
    }
}

// 1. Macros
// Great for C or C++, but some C++ developers hate them since they may have the multiple evaluation
// problem where you pass in an expression as an input parameter and it gets evaluated multiple 
// times.

/////////
#define DIVIDE_ROUNDUP(numer, denom) (                                                  \
    /* NB: `!=` acts as a logical XOR operator */                                       \
    /* See: https://stackoverflow.com/a/1596681/4561887 */                              \
    ((numer) < 0) != ((denom) < 0) ?                                                    \
    /* numer OR denom, but NOT both, is negative, so do this: */                        \
    (numer) / (denom) :                                                                 \
    /* numer AND denom are either *both positive* OR *both negative*, so do this: */    \
    ((numer) + ((denom) - 1)) / (denom)                                                 \
)

/////
#define DIVIDE_ROUNDDOWN(numer, denom) (                                                \
    /* NB: `!=` acts as a logical XOR operator */                                       \
    /* See: https://stackoverflow.com/a/1596681/4561887 */                              \
    ((numer) < 0) != ((denom) < 0) ?                                                    \
    /* numer OR denom, but NOT both, is negative, so do this: */                        \
    ((numer) - ((denom) - 1)) / (denom) :                                               \
    /* numer AND denom are either *both positive* OR *both negative*, so do this: */    \
    (numer) / (denom)                                                                   \
)

//////////
#define DIVIDE_ROUNDNEAREST(numer, denom) (                                             \
    /* NB: `!=` acts as a logical XOR operator */                                       \
    /* See: https://stackoverflow.com/a/1596681/4561887 */                              \
    ((numer) < 0) != ((denom) < 0) ?                                                    \
    /* numer OR denom, but NOT both, is negative, so do this: */                        \
    ((numer) - ((denom)/2)) / (denom) :                                                 \
    /* numer AND denom are either *both positive* OR *both negative*, so do this: */    \
    ((numer) + ((denom)/2)) / (denom)                                                   \
)


// #define ROUND_DIVISION(numerator, denominator) \
//     ((numerator) + (denominator)/2)/(denominator)


// 2. Statement Expressions
// These solve the multiple evaluation problem of macros perfectly, but are not part of the C or 
// C++ standard. Instead, they are gcc and clang compiler extensions to C and C++. These are safer
// to use than macros, but can still have a name pollution risk because variables created inside
// statement expressions are not in their own scope--rather, they are part of the outer scope.
// Nevertheless, prefer them to macros.

// 3. C++ Templated Functions (AKA: Function Templates)
// Work in C++ only. They solve both problems above, and suffer neither from the multiple evaluation
// problem of macros, nor from the name pollution/variable scope problem of statement expressions.
// Since they work only in C++, I'm going to add type checking here too with a `static_assert()`
// using `std::numeric_limits`, but the truth is this feature could be *easily* added to both
// macros and statement expressions as well so long as you're using C++. Some C++ developers
// feel so hateful towards macros (and are ignorant of statement expressions) that they'd rather
// die than use anything but templates in this case, so for those cases where someone would rather
// die than use one of the above approaches, use templates.



#ifdef __cplusplus
#include <limits>

// Template form for C++
// For *positive* numbers ONLY!
template <typename T>
T round_division(T numerator, T denominator)
{
    // Ensure only integer types are passed in, as this round division technique does NOT work on
    // floating point types since it assumes integer truncation will take place automatically
    // during the division!
    // - The following static assert allows all integer types, including their various `const`,
    //   `volatile`, and `const volatile` variations, but prohibits any floating point type
    //   such as `float`, `double`, and `long double`. 
    // - Reference page: https://en.cppreference.com/w/cpp/types/numeric_limits/is_integer
    static_assert(std::numeric_limits<T>::is_integer, "Only integer types are allowed"); 
    return (numerator + denominator/2)/denominator;
}

#endif

int main()
{
    int result;

    printf("Testing Rounding Integer Division\n\n");

    printf("1. Macro Tests\n\n");

    printf("DIVIDE_ROUNDUP():\n\n")
    TEST_EQ(DIVIDE_ROUNDUP(5, 5), 1);   // 5/5   = 1.00 --> 1 
    TEST_EQ(DIVIDE_ROUNDUP(5, 4), 2);   // 5/4   = 1.25 --> 2
    TEST_EQ(DIVIDE_ROUNDUP(6, 4), 2);   // 6/4   = 1.50 --> 2
    TEST_EQ(DIVIDE_ROUNDUP(7, 4), 2);   // 7/4   = 1.75 --> 2
    TEST_EQ(DIVIDE_ROUNDUP(9, 10), 1);  // 9/10  = 0.90 --> 1
    TEST_EQ(DIVIDE_ROUNDUP(3, 4), 1);   // 3/4   = 0.75 --> 1
    TEST_EQ(DIVIDE_ROUNDUP(-3, 4), 0);  // -3/4  = -0.75 --> 0
    TEST_EQ(DIVIDE_ROUNDUP(3, -4), 0);  // 3/-4  = -0.75 --> 0
    TEST_EQ(DIVIDE_ROUNDUP(-3, -4), 1); // -3/-4 = 0.75 --> 1

    printf("DIVIDE_ROUNDDOWN():\n\n")
    TEST_EQ(DIVIDE_ROUNDDOWN(5, 5), 1);   // 5/5   = 1.00 --> 1 
    TEST_EQ(DIVIDE_ROUNDDOWN(5, 4), 1);   // 5/4   = 1.25 --> 1
    TEST_EQ(DIVIDE_ROUNDDOWN(6, 4), 1);   // 6/4   = 1.50 --> 1
    TEST_EQ(DIVIDE_ROUNDDOWN(7, 4), 1);   // 7/4   = 1.75 --> 1
    TEST_EQ(DIVIDE_ROUNDDOWN(9, 10), 0);  // 9/10  = 0.90 --> 0
    TEST_EQ(DIVIDE_ROUNDDOWN(3, 4), 0);   // 3/4   = 0.75 --> 0
    TEST_EQ(DIVIDE_ROUNDDOWN(-3, 4), -1); // -3/4  = -0.75 --> -1
    TEST_EQ(DIVIDE_ROUNDDOWN(3, -4), -1); // 3/-4  = -0.75 --> -1
    TEST_EQ(DIVIDE_ROUNDDOWN(-3, -4), 0); // -3/-4 = 0.75 --> 0
    
    printf("DIVIDE_ROUNDNEAREST():\n\n")
    TEST_EQ(DIVIDE_ROUNDNEAREST(5, 5), 1);   // 5/5   = 1.00 --> 1 
    TEST_EQ(DIVIDE_ROUNDNEAREST(5, 4), 1);   // 5/4   = 1.25 --> 1
    TEST_EQ(DIVIDE_ROUNDNEAREST(6, 4), 2);   // 6/4   = 1.50 --> 2
    TEST_EQ(DIVIDE_ROUNDNEAREST(7, 4), 2);   // 7/4   = 1.75 --> 2
    TEST_EQ(DIVIDE_ROUNDNEAREST(9, 10), 1);  // 9/10  = 0.90 --> 1
    TEST_EQ(DIVIDE_ROUNDNEAREST(3, 4), 1);   // 3/4   = 0.75 --> 1
    TEST_EQ(DIVIDE_ROUNDNEAREST(-3, 4), -1);  // -3/4  = -0.75 --> -1
    TEST_EQ(DIVIDE_ROUNDNEAREST(3, -4), -1);  // 3/-4  = -0.75 --> -1
    TEST_EQ(DIVIDE_ROUNDNEAREST(-3, -4), 1); // -3/-4 = 0.75 --> 1


// #ifdef __cplusplus
//     printf("\nTEMPLATE TESTS:\n");
    
//     i = round_division(5, 4); // 5/4 = 1.25 --> 1
//     printf("%u\n", i);
    
//     i = round_division(6, 4); // 6/4 = 1.5 --> 2
//     printf("%u\n", i);
    
//     i = round_division(7, 4); // 7/4 = 1.75 --> 2
//     printf("%u\n", i);
    
//     i = round_division(9, 5); // 9/5 = 1.8 --> 2
//     printf("%u\n", i);
    
//     i = round_division(4, 4); // 4/4 = 1 --> 1
//     printf("%u\n", i);
    
    
//     // Check the static assert to ensure only integer types are allowed,
//     // including with const or volatile specifiers
    
//     // Float test:
//     // HITS STATIC ASSERT! GOOD!
//     // i = round_division(7.0, 4.0); // 7/4 = 1.75 --> 2
//     // printf("%u\n", i);
    
//     float f = 7.0;
//     // round_division(f, f*2);
//     // round_division(f, 4);
//     uint8_t u8 = 7;
//     uint16_t u16 = 4;
//     // round_division(u8, u16); // error: no matching function for call to ‘round_division(uint8_t&, uint16_t&)’
//     uint16_t u16_2 = round_division((uint16_t)u8, u16);
//     printf("%u\n", u16_2); // 7/4 = 1.75 --> 2 
    
//     const uint16_t u16_3 = 25;
//     volatile uint16_t u16_4 = 7;
//     u16_2 = round_division(u16_3, u16_4);
//     printf("%u\n", u16_2); // 25/7 = 3.57 --> 4
    
//     const volatile uint32_t u32_1 = 25;
//     uint32_t u32_2 = 7;
//     uint32_t u32_result = round_division(u32_1, u32_2);
//     printf("%u\n", u32_result); // 25/7 = 3.57 --> 4
    
    
// #endif
    

    return 0;
}




