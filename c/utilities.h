
// This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world


/*

These are my favorite macros and other utility functions I frequently need in both C and C++.
THIS FILE ISN'T IN A SHAPE TO JUST INCLUDE AS-IS. INSTEAD, COPY-PASTE WHAT YOU NEED.

TODO(gabriel): CONSIDER CLEANING UP THIS FILE TO MAKE IT SO YOU CAN JUST INCLUDE IT DIRECTLY.

keywords to easily grep or ripgrep in this repo for this program and what it teaches
KEYWORDS: interview prep

See also:
1. eRCaGuy_hello_world/c/rounding_integer_division/rounding_integer_division.cpp
2. https://github.com/arduino/ArduinoCore-avr/blob/master/cores/arduino/Arduino.h
3. [my ans] https://stackoverflow.com/questions/3437404/min-and-max-in-c/58532788#58532788

*/

#pragma once

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/// Debug printf macro (works in both C and C++)
/// See:
/// 1. https://stackoverflow.com/a/1941336/4561887
/// 1. [my answer] https://stackoverflow.com/a/67667132/4561887
/// 1. The fix to make this compatible with C++ too: https://stackoverflow.com/a/72777133/4561887
#ifdef DEBUG
    #define DEBUG_PRINTF(...) printf("DEBUG: " __VA_ARGS__)
#else
    #define DEBUG_PRINTF(...) \
        do                    \
        {                     \
        } while (0)
#endif

/// Get the number of elements in any C array
/// - Usage example: [my own answer]:
///   https://arduino.stackexchange.com/a/80289/7727
#define ARRAY_LEN(array) (sizeof(array) / sizeof((array)[0]))

// Definitions: `rows` = "rows"; `cols` = "columns"
// See usage of the next two macros in "array_2d_practice.c".
/// Get number of rows in a 2D array
#define NUM_ROWS(array_2d) ARRAY_LEN(array_2d)
/// Get number of columns in a 2D array
#define NUM_COLS(array_2d) ARRAY_LEN((array_2d)[0])

// For floating-point comparisons:
// - Modified from: https://docs.microsoft.com/en-us/cpp/build/why-floating-point-numbers-may-lose-precision?view=msvc-160
// - See also the function forms of this in my answer here:
//   https://stackoverflow.com/questions/17333/what-is-the-most-effective-way-for-float-and-double-comparison/65015333#65015333
#define EPSILON 0.0001  // user-defined "small difference" value
#define FLOAT_EQ(x, y) ((((x) - (y)) < EPSILON) && (((y) - (x)) < EPSILON))
#define FLOAT_EQ2(x, y, epsilon) ((((x) - (y)) < (epsilon)) && (((y) - (x)) < (epsilon)))

// GS: even better: use a scaled epsilon, and make it a function.
// See:
// 1. *****[my ans]
//    https://stackoverflow.com/questions/17333/what-is-the-most-effective-way-for-float-and-double-comparison/65015333#65015333
// 2. [this ans]
//    https://stackoverflow.com/questions/17333/what-is-the-most-effective-way-for-float-and-double-comparison/17341#17341
// 3. *****+[this blog post, referenced by the above answer--the secrets revealed here!]
//    http://realtimecollisiondetection.net/blog/?p=89
// Note: the naming conventions of the below functions roughly follow the Google Test (gtest)
// macros `EXPECT_FLOAT_EQ()`, `EXPECT_DOUBLE_EQ`, etc. (see:
// https://github.com/google/googletest/blob/master/googletest/docs/advanced.md), as well as
// `EXPECT_NE()`, `EXPECT_LT()`, `EXPECT_LE()`, etc. (see:
// https://github.com/google/googletest/blob/master/googletest/docs/primer.md#binary-comparison).

/// @brief      Equal: returns true if `a` is approximately == `b`, and false otherwise
bool is_float_eq(float a, float b, float epsilon);
bool is_double_eq(double a, double b, double epsilon);

/// @brief      Not Equal: returns true if `a` is definitely != `b`, and false otherwise
bool is_float_ne(float a, float b, float epsilon);
bool is_double_ne(double a, double b, double epsilon);

/// @brief      Less Than: returns true if `a` is definitively < `b`, and false otherwise
bool is_float_lt(float a, float b, float epsilon);
bool is_double_lt(double a, double b, double epsilon);

/// @brief      Less Than or Equal: returns true if `a` is definitively <= `b`, and false otherwise
bool is_float_le(float a, float b, float epsilon);
bool is_double_le(double a, double b, double epsilon);

/// @brief      Greater Than: returns true if `a` is definitively > `b`, and false otherwise
bool is_float_gt(float a, float b, float epsilon);
bool is_double_gt(double a, double b, double epsilon);

/// @brief      Greater Than or Equal: returns true if `a` is definitively >= `b`, and false
///             otherwise
bool is_float_ge(float a, float b, float epsilon);
bool is_double_ge(double a, double b, double epsilon);


// -------------------------------------------------------------------------------------------------
// FROM ARDUINO START (GNU LGPL v2.1 or later License)
///////// TODO: FOR LICENSING REASONS, just break out this Arduino section into a totally separate
// file named "utilities_arduino.h" or something.
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// From Arduino.h:
// See: https://github.com/arduino/ArduinoCore-avr/blob/master/cores/arduino/Arduino.h

#define HIGH 0x1
#define LOW  0x0

#define PI 3.1415926535897932384626433832795
#define HALF_PI 1.5707963267948966192313216916398
#define TWO_PI 6.283185307179586476925286766559
#define DEG_TO_RAD 0.017453292519943295769236907684886
#define RAD_TO_DEG 57.295779513082320876798154814105
#define EULER 2.718281828459045235360287471352

#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define abs(x) ((x)>0?(x):-(x))
#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
#define round(x)     ((x)>=0?(long)((x)+0.5):(long)((x)-0.5))
#define radians(deg) ((deg)*DEG_TO_RAD)
#define degrees(rad) ((rad)*RAD_TO_DEG)
#define sq(x) ((x)*(x))

#define interrupts() sei()
#define noInterrupts() cli()

#define clockCyclesPerMicrosecond() ( F_CPU / 1000000L )
#define clockCyclesToMicroseconds(a) ( (a) / clockCyclesPerMicrosecond() )
#define microsecondsToClockCycles(a) ( (a) * clockCyclesPerMicrosecond() )

#define lowByte(w) ((uint8_t) ((w) & 0xff))
#define highByte(w) ((uint8_t) ((w) >> 8))

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitToggle(value, bit) ((value) ^= (1UL << (bit)))
#define bitWrite(value, bit, bitvalue) ((bitvalue) ? bitSet(value, bit) : bitClear(value, bit))

long map(long, long, long, long, long);

/// Perform linear interpolation on x to scale it from an input range between in_min and in_max
/// to an output range between out_min and out_max. This is similar to Arduino's `map`
/// function found in Arduino's WMath.cpp.
#define SCALE(x, in_min, in_max, out_min, out_max)  \
    (((x) - (in_min)) * ((out_max) - (out_min)) / ((in_max) - (in_min)) + (out_min))

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// FROM ARDUINO END
// -------------------------------------------------------------------------------------------------

/// \brief  Get `uint8_t` byte number `byte_num` from variable `value`, where `byte_num` 0 is
///         the least-significant byte.
///         See my answer here: https://stackoverflow.com/a/67206563/4561887
/// \example
///         ```
///         uint32_t value = 1234;
///
///         uint8_t byte0 = READ_BYTE(value, 0),
///         uint8_t byte1 = READ_BYTE(value, 1),
///         uint8_t byte2 = READ_BYTE(value, 2),
///         uint8_t byte3 = READ_BYTE(value, 3),
///
///         // OR
///
///         uint8_t bytes[] = {
///             READ_BYTE(value, 0),
///             READ_BYTE(value, 1),
///             READ_BYTE(value, 2),
///             READ_BYTE(value, 3),
///         };
///         ```
/// \details  Similar to Arduino's `lowByte()` and `highByte()` macros just above, where `byte_num`
///         is 0 for `lowByte()` and 1 for `highByte()`--thereby assuming a 2-byte `uint16_t` type.
#define READ_BYTE(value, byte_num) ((uint8_t)(((value) >> (8*(byte_num))) & 0xff))


// See my answer: https://stackoverflow.com/questions/3437404/min-and-max-in-c/58532788#58532788

// Macros
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))

/// Max and min gcc/clang **statement expressions** (safer than macros) for C. By Gabriel Staples.
/// See: https://stackoverflow.com/a/58532788/4561887
#define MAX(a, b)               \
    ({                          \
        __typeof__(a) _a = (a); \
        __typeof__(b) _b = (b); \
        _a > _b ? _a : _b;      \
    })
#define MIN(a, b)               \
    ({                          \
        __typeof__(a) _a = (a); \
        __typeof__(b) _b = (b); \
        _a < _b ? _a : _b;      \
    })

#define MAX max
#define MAX3(a, b, c) MAX(MAX(a, b), c)

/// Get the next `alignment`-aligned address starting from address `base_addr.
void* utils_get_aligned_address(void* base_addr, size_t alignment);

// For the time macros and functions below, see my (Gabriel Staples's) answer here:
// https://stackoverflow.com/a/67731965/4561887

/// Convert seconds to milliseconds
#define SEC_TO_MS(sec) ((sec)*1000)
/// Convert seconds to microseconds
#define SEC_TO_US(sec) ((sec)*1000000)
/// Convert seconds to nanoseconds
#define SEC_TO_NS(sec) ((sec)*1000000000)

/// Convert nanoseconds to seconds
#define NS_TO_SEC(ns) ((ns) / 1000000000)
/// Convert nanoseconds to milliseconds
#define NS_TO_MS(ns) ((ns) / 1000000)
/// Convert nanoseconds to microseconds
#define NS_TO_US(ns) ((ns) / 1000)

// NB: for all 3 timestamp functions below: gcc defines the type of the internal
// `tv_sec` seconds value inside the `struct timespec`, which is used
// internally in these functions, as a signed `long int`. For architectures
// where `long int` is 64 bits, that means it will have undefined
// (signed) overflow in 2^64 sec = 5.8455 x 10^11 years. For architectures
// where this type is 32 bits, it will occur in 2^32 sec = 136 years. If the
// implementation-defined epoch for the timespec is 1970, then your program
// could have undefined behavior signed time rollover in as little as
// 136 years - (year 2021 - year 1970) = 136 - 51 = 85 years. If the epoch
// was 1900 then it could be as short as 136 - (2021 - 1900) = 136 - 121 =
// 15 years. Hopefully your program won't need to run that long. :). To see,
// by inspection, what your system's epoch is, simply print out a timestamp and
// calculate how far back a timestamp of 0 would have occurred. Ex: convert
// the timestamp to years and subtract that number of years from the present
// year.

/// Get a time stamp in milliseconds.
uint64_t millis();
/// Get a time stamp in microseconds.
uint64_t micros();
/// Get a time stamp in nanoseconds.
uint64_t nanos();


/// \brief      Use linear interpolation to rescale, or "map" value `val` from range
///             `in_min` to `in_max`, inclusive, to range `out_min` to `out_max`, inclusive.
/// \details    Similar to Arduino's ingenious `map()` function:
///             https://www.arduino.cc/reference/en/language/functions/math/map/
///
/// TODO(gabriel): turn this into a gcc statement expression instead to prevent the potential for
/// the "double evaluation" bug. See `MIN()` and `MAX()` above.
#define UTILS_MAP(val, in_min, in_max, out_min, out_max) \
    (((val) - (in_min)) * ((out_max) - (out_min)) / ((in_max) - (in_min)) + (out_min))

/// \brief      Obtain a pseudo-random integer value between `min` and `max`, **inclusive**.
/// \details    1. If `(max - min + 1) > RAND_MAX`, then the range of values returned will be
///             **scaled** to the range `max - min + 1`, and centered over the center of the
///             range at `(min + max)/2`. Scaling the numbers means that in the case of scaling,
///             not all numbers can even be reached. However, you will still be assured to have
///             a random distribution of numbers across the full range.
///             2. Also, the first time per program run that you call this function, it will
///             automatically seed the pseudo-random number generator with your system's
///             current time in seconds.
///             3. Source: Gabriel Staples: https://stackoverflow.com/a/67746081/4561887
/// \param[in]  min         The minimum pseudo-random number you'd like, inclusive. Can be positive
///                         OR negative.
/// \param[in]  max         The maximum pseudo-random number you'd like, inclusive. Can be positive
///                         OR negative.
/// \return     A pseudo-random integer value between `min` and `max`, **inclusive**.
int utils_rand(int min, int max);
