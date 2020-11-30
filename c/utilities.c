
// This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world


/*

These are my favorite macros and other utility functions I frequently need in both C and C++.

See the .h file for details.

*/

#include "utilities.h"

#include <math.h> // fabs() [for double], fabsf() [for float]


// floating point comparisons

////
// Todo: rename to `get_epsilon_scaled_float()`??
// For background info behind this, see: http://realtimecollisiondetection.net/blog/?p=89
static float scale_float_epsilon(float a, float b, float epsilon)
{
    // For very large `a` and `b`, scale epsilon UP, or else it will eventually become so small
    // relative to `a` and `b` that if falls out in the numerical error.
    float epsilon_scaled = max(fabsf(a), fabsf(b))*epsilon;

    // For very small `a` and `b`, however, ensure `scaled_epsilon` doesn't get too small, or again,
    // it will fall out in numerical error, so let's clip it to be a minimum value of 1.0f.
    epsilon_scaled = max(epsilon_scaled, (float)1.0);

    return epsilon_scaled;
}

// For background info behind this, see: http://realtimecollisiondetection.net/blog/?p=89
static double scale_double_epsilon(double a, double b, double epsilon)
{
    // For very large `a` and `b`, scale epsilon UP, or else it will eventually become so small
    // relative to `a` and `b` that if falls out in the numerical error.
    double epsilon_scaled = max(fabs(a), fabs(b))*epsilon;

    // For very small `a` and `b`, however, ensure `scaled_epsilon` doesn't get too small, or again,
    // it will fall out in numerical error, so let's clip it to be a minimum value of 1.0f.
    epsilon_scaled = max(epsilon_scaled, (double)1.0);

    return epsilon_scaled;
}


bool is_float_eq(float a, float b, float epsilon)
{
    float diff = a - b; // note: `-diff` is the same as `b - a`
    float epsilon_scaled = scale_float_epsilon(a, b, epsilon);

    return diff < epsilon_scaled && -diff < epsilon_scaled;
}
bool is_double_eq(double a, double b, double epsilon)
{

}

bool is_float_ne(float a, float b, float epsilon)
{
    /////
    // float diff = a - b; // note: `-diff` is the same as `b - a`
    // float epsilon_scaled = scale_float_epsilon(a, b, epsilon);

    // return diff >= epsilon_scaled || -diff >= epsilon_scaled;

    return !is_float_eq(a, b, epsilon);
}
bool is_double_ne(double a, double b, double epsilon)
{

}

bool is_float_lt(float a, float b, float epsilon)
{
    return a < b - scale_float_epsilon(a, b, epsilon);
}
bool is_double_lt(double a, double b, double epsilon)
{

}

bool is_float_le(float a, float b, float epsilon)
{
    return a < b + scale_float_epsilon(a, b, epsilon);
}
bool is_double_le(double a, double b, double epsilon)
{

}

bool is_float_gt(float a, float b, float epsilon)
{
    return a > b + scale_float_epsilon(a, b, epsilon);
}
bool is_double_gt(double a, double b, double epsilon)
{

}

bool is_float_ge(float a, float b, float epsilon)
{
    return a > b - scale_float_epsilon(a, b, epsilon);
}
bool is_double_ge(double a, double b, double epsilon)
{

}


// From WMath.cpp:

long map(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
