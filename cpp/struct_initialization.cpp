/*

This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

Gabriel Staples
Written: 8 Nov. 2019 
Updated: 29 Apr. 2020 

struct_initialization
- practice aggregate initialization and zero initialization of structs in C++

******NB: THIS IS A WORK IN PROGRESS! MOST OF THESE ZERO INITIALIZATION TESTS FAIL!******

To compile and run:
    g++ -Wall -Werror -g3 -std=c++17 -o struct_initialization \
    struct_initialization.cpp && ./struct_initialization

References:
1. https://en.cppreference.com/w/cpp/language/aggregate_initialization
1. https://en.cppreference.com/w/cpp/language/zero_initialization

*/

#include <stdio.h>  // printf()
#include <string.h> // memset()

#ifdef __cplusplus
typedef struct
{
    int num1 = 100;
    int num2 = -100;
    int num3;
    int num4 = 150;
} data_t;
#else // For C only, since C doesn't allow default values in structs 
typedef struct
{
    int num1;
    int num2;
    int num3;
    int num4;
} data_t;
#endif 

int main()
{
    printf("Hello World\n\n");
    
    // 1. Aggregate Initialization
    // See: https://en.cppreference.com/w/cpp/language/aggregate_initialization
    printf("TEST 1: aggregate initialization\n\n");
    
    // THIS WORKS IN C! 
    // IT ALSO WORKS IN C++! NOTE, HOWEVER, THAT IN C++ IT *MAY* BE A GCC 
    // EXTENSION, MEANING IT'S NOT PORTABLE C++ CODE. DO SOME CHECKING AND 
    // RESEARCH ONLINE TO FIND OUT! 
    // Update 29 Apr. 2020: yes, it must be a gcc extension, as I'm building 
    // with C++17, yet this reference (https://en.cppreference.com/w/cpp/language/aggregate_initialization)
    // indicates this initialization style is not possible until C++20.
    data_t d1 = 
    {
        .num1 = 7,
        .num2 = 8,
    };
    // WORKS! Any values not explicitly set are left to their default values.
    printf("d1.num1 = %i\nd1.num2 = %i\nd1.num3 = %i\nd1.num4 = %i\n\n",
           d1.num1, d1.num2, d1.num3, d1.num4);


    // 2. Zero Initialization
    // See: https://en.cppreference.com/w/cpp/language/zero_initialization
    // ******NB: THIS IS A WORK IN PROGRESS! MOST OF THESE ZERO INITIALIZATION TESTS FAIL!******
    printf("TEST 2: zero initialization\n\n");
    
    // Works! Uses default values.
    data_t d2 = {};
    printf("d2.num1 = %i\nd2.num2 = %i\nd2.num3 = %i\n\n", d2.num1, d2.num2, d2.num3);
    
    // Only sets the FIRST value in the struct to zero! The rest seem to use default values.
    data_t d3 = {0};
    printf("d3.num1 = %i\nd3.num2 = %i\nd3.num3 = %i\n\n", d3.num1, d3.num2, d3.num3);
    
    // 3. More Initialization tests
    // See: https://en.cppreference.com/w/cpp/language/zero_initialization
    printf("TEST 3: more initialization tests\n\n");

    data_t d4 = {2};
    printf("d4.num1 = %i\nd4.num2 = %i\nd4.num3 = %i\n\n", d4.num1, d4.num2, d4.num3);
    
    #ifdef __cplusplus
    printf("The following techniques only are valid in C++, NOT C, so disable them for C:\n{\n\n");

    data_t d5;
    printf("d5.num1 = %i\nd5.num2 = %i\nd5.num3 = %i\n\n", d5.num1, d5.num2, d5.num3);

    data_t d6{};
    printf("d6.num1 = %i\nd6.num2 = %i\nd6.num3 = %i\n\n", d6.num1, d6.num2, d6.num3);

    data_t d7 = data_t();
    printf("d7.num1 = %i\nd7.num2 = %i\nd7.num3 = %i\n\n", d7.num1, d7.num2, d7.num3);

    // // Error: 
    // //      error: no matching function for call to ‘data_t::data_t(int)’
    // data_t d8 = data_t(15);
    // printf("d8.num1 = %i\nd8.num2 = %i\nd8.num3 = %i\n\n", d8.num1, d8.num2, d8.num3);

    printf("}\n\n");
    #endif

    data_t d9;
    memset(&d9, 0, sizeof(d9));
    printf("d9.num1 = %i\nd9.num2 = %i\nd9.num3 = %i\n\n", d9.num1, d9.num2, d9.num3);

    // // Does NOT work
    // // C++17 error:
    // //      error: conversion from ‘int’ to non-scalar type ‘data_t’ requested
    // // C11 error:
    // //      error: invalid initializer
    // data_t d10 = 0;
    // printf("d10.num1 = %i\nd10.num2 = %i\nd10.num3 = %i\n\n", d10.num1, d10.num2, d10.num3);

    return 0;
}

/*
SAMPLE OUTPUT:

    $ ./run_struct_initialization.sh 
    ======================
    Running first as C++17
    ======================
    Hello World

    TEST 1: aggregate initialization

    d1.num1 = 7
    d1.num2 = 8
    d1.num3 = 0

    TEST 2: zero initialization

    d2.num1 = 100
    d2.num2 = -100
    d2.num3 = 0

    d3.num1 = 0
    d3.num2 = -100
    d3.num3 = 0

    TEST 3: more initialization tests

    d4.num1 = 2
    d4.num2 = -100
    d4.num3 = 0

    The following techniques only are valid in C++, NOT C, so disable them for C:
    {

    d5.num1 = 100
    d5.num2 = -100
    d5.num3 = 0

    d6.num1 = 100
    d6.num2 = -100
    d6.num3 = 0

    d7.num1 = 100
    d7.num2 = -100
    d7.num3 = 0

    }

    ======================
    Now running as C11
    ======================
    Hello World

    TEST 1: aggregate initialization

    d1.num1 = 7
    d1.num2 = 8
    d1.num3 = 0

    TEST 2: zero initialization

    d2.num1 = 0
    d2.num2 = 0
    d2.num3 = 0

    d3.num1 = 0
    d3.num2 = 0
    d3.num3 = 0

    TEST 3: more initialization tests

    d4.num1 = 2
    d4.num2 = 0
    d4.num3 = 0



*/

