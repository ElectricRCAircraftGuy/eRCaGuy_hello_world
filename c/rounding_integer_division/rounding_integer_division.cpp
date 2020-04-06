/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
C#, VB, Perl, Swift, Prolog, Javascript, Pascal, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.

integer_rounding_during_division

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

// Works in C perfectly! (for POSITIVE numbers only!)
#define ROUND_DIVISION(numerator, denominator) \
    ((numerator) + (denominator)/2)/(denominator)

// TODO: THIS LOOKS LIKE A CORRECT ANSWER; TEST IT! https://stackoverflow.com/a/18067292/4561887

// // For positive OR negative numbers!
// #define ROUND_DIVISION2(numerator, denominator) \
//     do {
//         bool numer_is_negative = false;
//         bool denom_is_negative = false;
//         // Don't use `abs()`, as it only handles `int` in C
//         if ((numerator) < 0)
//         {
//             numer_is_negative = true;
//             numerator = -(numerator);
//         }
//         if ((denominator) < 0)
//         {
//             denom_is_negative = true;
//             denominator = -(denominator);
//         }
//         // The `!=` acts as a logical XOR here; 
//         // see: https://stackoverflow.com/a/1596681/4561887
//         bool answer_is_negative = numer_is_negative != denom_is_negative;
        
//         ((numerator) + (denominator)/2)/(denominator)
//     } while (0)

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

// For positive OR negative numbers
// TODO 

#endif

int main()
{
    printf("Hello World\n");
    
    int i;
    
    
    printf("\nMACRO TESTS:\n");
    
    i = ROUND_DIVISION(5, 4); // 5/4 = 1.25 --> 1
    printf("%u\n", i);
    
    i = ROUND_DIVISION(6, 4); // 6/4 = 1.5 --> 2
    printf("%u\n", i);
    
    i = ROUND_DIVISION(7, 4); // 7/4 = 1.75 --> 2
    printf("%u\n", i);
    
    i = ROUND_DIVISION(9, 5); // 9/5 = 1.8 --> 2
    printf("%u\n", i);
    
    i = ROUND_DIVISION(4, 4); // 4/4 = 1 --> 1
    printf("%u\n", i);
    
    i = ROUND_DIVISION(3, 4); // 3/4 = 0.75 --> 1
    printf("%u\n", i);
    
    // TRY IT ON NEGATIVE NUMBERS (WILL FAIL!)
    printf("negative numbers:\n");
    i = ROUND_DIVISION(-3, 4); // -3/4 = -0.75 --> 0 FAILED!
    printf("%u\n", i);
    i = ROUND_DIVISION(3, -4); // 3/-4 = -0.75 --> 0 FAILED!
    printf("%u\n", i);
    i = ROUND_DIVISION(-3, -4); // -3/-4 = 0.75 --> 1 PASSED!
    printf("%u\n", i);
    // Now try the new negative-capable statement expression version here 
    // todo 


#ifdef __cplusplus
    printf("\nTEMPLATE TESTS:\n");
    
    i = round_division(5, 4); // 5/4 = 1.25 --> 1
    printf("%u\n", i);
    
    i = round_division(6, 4); // 6/4 = 1.5 --> 2
    printf("%u\n", i);
    
    i = round_division(7, 4); // 7/4 = 1.75 --> 2
    printf("%u\n", i);
    
    i = round_division(9, 5); // 9/5 = 1.8 --> 2
    printf("%u\n", i);
    
    i = round_division(4, 4); // 4/4 = 1 --> 1
    printf("%u\n", i);
    
    
    // Check the static assert to ensure only integer types are allowed,
    // including with const or volatile specifiers
    
    // Float test:
    // HITS STATIC ASSERT! GOOD!
    // i = round_division(7.0, 4.0); // 7/4 = 1.75 --> 2
    // printf("%u\n", i);
    
    float f = 7.0;
    // round_division(f, f*2);
    // round_division(f, 4);
    uint8_t u8 = 7;
    uint16_t u16 = 4;
    // round_division(u8, u16); // error: no matching function for call to ‘round_division(uint8_t&, uint16_t&)’
    uint16_t u16_2 = round_division((uint16_t)u8, u16);
    printf("%u\n", u16_2); // 7/4 = 1.75 --> 2 
    
    const uint16_t u16_3 = 25;
    volatile uint16_t u16_4 = 7;
    u16_2 = round_division(u16_3, u16_4);
    printf("%u\n", u16_2); // 25/7 = 3.57 --> 4
    
    const volatile uint32_t u32_1 = 25;
    uint32_t u32_2 = 7;
    uint32_t u32_result = round_division(u32_1, u32_2);
    printf("%u\n", u32_result); // 25/7 = 3.57 --> 4
    
    
#endif
    

    return 0;
}




