
// This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world


/*

These are my favorite macros and other utility functions I frequently need in both C and C++.

See also:
1. eRCaGuy_hello_world/c/rounding_integer_division/rounding_integer_division.cpp
2. https://github.com/arduino/ArduinoCore-avr/blob/master/cores/arduino/Arduino.h
3. [my ans] https://stackoverflow.com/questions/3437404/min-and-max-in-c/58532788#58532788

*/


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

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// FROM ARDUINO END
// -------------------------------------------------------------------------------------------------


// See my answer: https://stackoverflow.com/questions/3437404/min-and-max-in-c/58532788#58532788

// Macros
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))

// gcc/clang "statement expressions"
#define max(a,b)             \
({                           \
    __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
    _a > _b ? _a : _b;       \
})
#define min(a,b)             \
({                           \
    __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
    _a < _b ? _a : _b;       \
})

#define MAX max
#define MAX3(a, b, c) MAX(MAX(a, b), c)
