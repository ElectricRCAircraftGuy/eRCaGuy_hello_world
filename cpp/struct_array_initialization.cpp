/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
Written:          22 Dec. 2020
Added to my repo:  2 Jan. 2023

Demonstrate how to initialize a C-style array of structs in C++.

STATUS: Done and works!

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# NB: you may need to use `-std=gnu++17` instead of `-std=c++17` in order to obtain extra GNU
# gcc features, including gcc extensions, POSIX cmds, and Linux sytem cmds.
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# 1. In C++
time g++ -Wall -Wextra -Werror -O3 -std=c++17 struct_array_initialization.cpp -o bin/a && bin/a
```

References:
1. ***** My answer here, with this code:
   [Arduino Stack Exchange: Initializing Array of structs](https://arduino.stackexchange.com/a/80289/7727)
    1. Run this code on OnlineGDB here: https://onlinegdb.com/MnEOQgCQT


*/


#include <stdint.h>
#include <stdio.h>

// Get the number of elements in a C-style array
#define ARRAY_LEN(array) (sizeof(array)/sizeof(array[0]))

constexpr uint8_t NUM_LEDS = 3;

struct Led {
  uint8_t current;
  uint8_t start;
  uint8_t target;
  uint32_t startTime;
  uint16_t duration;
};

// To initialize once at construction. This form of aggregate initialization
// can be used anywhere: both inside and outside functions.
Led leds[NUM_LEDS] = {
    { 1,  2,  3,  4,  5},
    { 6,  7,  8,  9, 10},
    {11, 12, 13, 14, 15},
};

// Print the full contents of an array of `Led` structs
void printLeds(const Led ledArrayIn[], size_t ledArrayLen)
{
    for (size_t i = 0; i < ledArrayLen; i++)
    {
        printf("ledArrayIn[%lu]\n"
               "current   = %u\n"
               "start     = %u\n"
               "target    = %u\n"
               "startTime = %u\n"
               "duration  = %u\n\n",
               i,
               ledArrayIn[i].current,
               ledArrayIn[i].start,
               ledArrayIn[i].target,
               ledArrayIn[i].startTime,
               ledArrayIn[i].duration);
    }
}

int main()
{
    printf("Hello World\n\n");

    printLeds(leds, ARRAY_LEN(leds));

    printf("==============\n\n");

    // Do this to set or change the structs at any time AFTER construction!
    // This variable (re)assignment is only allowed inside of a function, NOT
    // in the global scope outside of all functions!
    leds[0] = {10, 20,  30,  40,  50};
    leds[1] = {60, 70,  80,  90, 100};
    leds[2] = { 0,  0, 255,   0, 300};

    printLeds(leds, ARRAY_LEN(leds));

    return 0;
}


/*
SAMPLE OUTPUT:

In C++:

    eRCaGuy_hello_world/cpp$ time g++ -Wall -Wextra -Werror -O3 -std=c++17 struct_array_initialization.cpp -o bin/a && bin/a

    real    0m0.424s
    user    0m0.118s
    sys 0m0.080s
    Hello World

    ledArrayIn[0]
    current   = 1
    start     = 2
    target    = 3
    startTime = 4
    duration  = 5

    ledArrayIn[1]
    current   = 6
    start     = 7
    target    = 8
    startTime = 9
    duration  = 10

    ledArrayIn[2]
    current   = 11
    start     = 12
    target    = 13
    startTime = 14
    duration  = 15

    ==============

    ledArrayIn[0]
    current   = 10
    start     = 20
    target    = 30
    startTime = 40
    duration  = 50

    ledArrayIn[1]
    current   = 60
    start     = 70
    target    = 80
    startTime = 90
    duration  = 100

    ledArrayIn[2]
    current   = 0
    start     = 0
    target    = 255
    startTime = 0
    duration  = 300


*/
