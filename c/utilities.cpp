
// This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world


/*

These are my favorite macros and other utility functions I frequently need in both C and C++.

See also:
1. eRCaGuy_hello_world/c/rounding_integer_division/rounding_integer_division.cpp
2.https://github.com/arduino/ArduinoCore-avr/blob/master/cores/arduino/Arduino.h

*/


// From WMath.cpp:

long map(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
