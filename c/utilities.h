
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


// -------------------------------------------------------------------------------------------------
// FROM ARDUINO START (GNU LGPL v2.1 or later License)
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
