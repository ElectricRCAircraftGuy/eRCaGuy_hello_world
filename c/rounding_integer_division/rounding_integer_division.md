
By Gabriel Staples  
www.ElectricRCAircraftGuy.com  

This answer originally posted [on Stack Overflow here](https://stackoverflow.com/questions/2422712/rounding-integer-division-instead-of-truncating/58568736#58568736).

--------------------------

# Rounding during divion between two integers: `numerator/denominator`

1. **Round down:**

Rounding down during integer division is the natural state of things, because integers automatically truncate anything after the decimal. There's nothing special you have to do. For the sake of completeness, however (to match the macros, statement expressions, and template functions farther below), let's create a macro for it:

    #define DIVIDE_ROUNDDOWN(numer/denom) ((numer)/(denom))

And some examples with both positive and negative inputs (run them [online here](https://onlinegdb.com/BJ2eX9xPE)):

    int numer = 9;
    int denom = 10;
    DIVIDE_ROUNDDOWN(numer, denom);  // 9/10 = 0.9 --> 0
    DIVIDE_ROUNDDOWN(-numer, denom); // -9/10 = -0.9 --> 


## TLDR: Here's a macro; use it!
    
    // To do (numer/denom), rounded to the nearest whole integer, use:
    #define ROUND_DIVIDE(numer, denom) (((numer) + (denom) / 2) / (denom))

Usage example:

    int num = ROUND_DIVIDE(13,7); // 13/7 = 1.857 --> rounds to 2, so num is 2

## Full answer:

Some of these answers are crazy looking! Codeface nailed it though! (See @0xC0DEFACE's [answer here][1]). I really like the type-free macro or gcc statement expression form over the function form, however, so, I wrote this answer with a detailed explanation of what I'm doing (ie: why this mathematically works) and put it into 2 forms:

## 1. Macro form, with detailed commentary to explain the whole thing:

    /// @brief      ROUND_DIVIDE(numerator/denominator): round to the nearest whole integer when doing 
    ///             *integer* division only
    /// @details    This works on *integers only* since it assumes integer truncation will take place automatically
    ///             during the division! 
    /// @notes      The concept is this: add 1/2 to any number to get it to round to the nearest whole integer
    ///             after integer trunction.
    ///             Examples:  2.74 + 0.5 = 3.24 --> 3 when truncated
    ///                        2.99 + 0.5 = 3.49 --> 3 when truncated
    ///                        2.50 + 0.5 = 3.00 --> 3 when truncated
    ///                        2.49 + 0.5 = 2.99 --> 2 when truncated
    ///                        2.00 + 0.5 = 2.50 --> 2 when truncated
    ///                        1.75 + 0.5 = 2.25 --> 2 when truncated
    ///             To add 1/2 in integer terms, you must do it *before* the division. This is achieved by 
    ///             adding 1/2*denominator, which is (denominator/2), to the numerator before the division.
    ///             ie: `rounded_division = (numer + denom/2)/denom`.
    ///             ==Proof==: 1/2 is the same as (denom/2)/denom. Therefore, (numer/denom) + 1/2 becomes 
    ///             (numer/denom) + (denom/2)/denom. They have a common denominator, so combine terms and you get:
    ///             (numer + denom/2)/denom, which is the answer above.
    /// @param[in]  numerator   any integer type numerator; ex: uint8_t, uint16_t, uint32_t, int8_t, int16_t, int32_t, etc
    /// @param[in]  denominator any integer type denominator; ex: uint8_t, uint16_t, uint32_t, int8_t, int16_t, int32_t, etc
    /// @return     The result of the (numerator/denominator) division rounded to the nearest *whole integer*!
    #define ROUND_DIVIDE(numerator, denominator) (((numerator) + (denominator) / 2) / (denominator))

## 2. [GCC Statement Expression][2] form:
*See [a little more on gcc statement expressions here][3].*

    /// @brief      *gcc statement expression* form of the above macro
    #define ROUND_DIVIDE2(numerator, denominator)               \
    ({                                                          \
        __typeof__ (numerator) numerator_ = (numerator);        \
        __typeof__ (denominator) denominator_ = (denominator);  \
        numerator_ + (denominator_ / 2) / denominator_;         \
    })

## 3. C++ Function Template form:
(Added Mar./Apr. 2020)

    #include <limits>

    // Template form for C++ (with type checking to ensure only integer types are passed in!)
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

## Run & test some of this code here:
1. [OnlineGDB: integer rounding during division](https://onlinegdb.com/BJ2eX9xPE)

## Related Answers:
1. https://stackoverflow.com/questions/10067510/fixed-point-arithmetic-in-c-programming/53936802#53936802 - in this answer I go over how to do *integer rounding* to the nearest whole integer, then tenth place (1 decimal digit to the right of the decimal), hundredth place (2 dec digits), thousandth place (3 dec digits), etc. Search the answer for the section in my code comments called `BASE 2 CONCEPT:` for more details!
1. A related answer of mine on gcc's statement expressions: https://stackoverflow.com/questions/3437404/min-and-max-in-c/58532788#58532788
1. The function form of this with fixed types: https://stackoverflow.com/questions/2422712/rounding-integer-division-instead-of-truncating/2422723#2422723
1. https://stackoverflow.com/questions/3602827/what-is-the-behavior-of-integer-division
1. For rounding up instead of to nearest integer, follow this similar pattern: https://stackoverflow.com/questions/2422712/rounding-integer-division-instead-of-truncating/2422722#2422722

## References:
1. https://www.tutorialspoint.com/cplusplus/cpp_templates.htm

  [1]: https://stackoverflow.com/a/2422723/4561887
  [2]: https://gcc.gnu.org/onlinedocs/gcc/Statement-Exprs.html#Statement-Exprs
  [3]: https://stackoverflow.com/questions/3437404/min-and-max-in-c/58532788#58532788

todo: test this for negative inputs & update this answer if it works: 

```
#define ROUND_DIVIDE(numer, denom) ((numer < 0) != (denom < 0) ? ((numer) - (denom) / 2) / (denom) : ((numer) + (denom) / 2) / (denom))
```