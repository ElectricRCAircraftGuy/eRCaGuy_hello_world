/*

This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

Gabriel Staples
Written: 8 Nov. 2019 
Updated: 29 Apr. 2020 

struct_initialization
- practice aggregate initialization, default initialization, value initialization, and zero 
  initialization of structs in C++

NB: Not all of these techniques below work or are doing what you might expect. Read the 
comments above each one to see what the expected results are.

To compile and run:
    ./run_struct_initialization.sh

    # OR:

    g++ -Wall -Werror -g3 -std=c++17 -o struct_initialization \
    struct_initialization.cpp && ./struct_initialization

References:  
1. *****[MY OWN Q & ANSWER] "How to initialize a struct to 0 in C++"
   https://stackoverflow.com/questions/61240589/how-to-initialize-a-struct-to-0-in-c/61240590#61240590
1. *****+[MY OWN QUESTION] "Why doesn't initializing a C++ struct to `= {0}` set all of its members to 0?"
   https://stackoverflow.com/questions/61531928/why-doesnt-initializing-a-c-struct-to-0-set-all-of-its-members-to-0
1. Main type of initialization I will be showing below
    1. Default initialization: https://en.cppreference.com/w/cpp/language/default_initialization
    1. Aggregate initialization: https://en.cppreference.com/w/cpp/language/aggregate_initialization
    1. Zero initialization: https://en.cppreference.com/w/cpp/language/zero_initialization
    1. Value initialization: https://en.cppreference.com/w/cpp/language/value_initialization

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
    
    // =============================================================================================
    // SEE MY 2 Q & As on Stack Overflow, in the References above, for a full explanation of 
    // everything below!
    // =============================================================================================


    // 1. Aggregate Initialization??
    // See: https://en.cppreference.com/w/cpp/language/aggregate_initialization
    printf("TEST 1: aggregate initialization??\n\n");
    
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


    // 2. Zero Initialization??
    // See: https://en.cppreference.com/w/cpp/language/zero_initialization
    // NB: Not all of these techniques below work or are doing what you might expect. Read the
    // comments above each one to see what the expected results are.
    printf("TEST 2: zero initialization??\n\n");
    
    // Works! Uses default values.
    data_t d2 = {};
    printf("d2.num1 = %i\nd2.num2 = %i\nd2.num3 = %i\nd2.num4 = %i\n\n",
           d2.num1, d2.num2, d2.num3, d2.num4);
    
    // Does NOT do what I expected! Only sets the FIRST value in the struct to zero! 
    // The rest seem to use default values.
    data_t d3 = {0};
    printf("d3.num1 = %i\nd3.num2 = %i\nd3.num3 = %i\nd3.num4 = %i\n\n",
           d3.num1, d3.num2, d3.num3, d3.num4);
    

    // 3. More Initialization tests
    // See: https://en.cppreference.com/w/cpp/language/zero_initialization
    printf("TEST 3: more initialization tests\n\n");

    // Does NOT do what I expected! Only sets the FIRST value in the struct to this number! 
    // The rest are set to default values.
    data_t d4 = {2};
    printf("d4.num1 = %i\nd4.num2 = %i\nd4.num3 = %i\nd4.num4 = %i\n\n",
           d4.num1, d4.num2, d4.num3, d4.num4);
    
    #ifdef __cplusplus
    printf("The following techniques only are valid in C++, NOT C, so disable them for C:\n{\n\n");

    // Initializes all values which have defult values to their default values, but values which
    // do not have default values are left UNINITIALIZED, and contain whatever data was left over
    // previously in that memory address. For example, d5.num3 might be anything:
    //      d5.num1 = 100
    //      d5.num2 = -100
    //      d5.num3 = 15775231
    //      d5.num4 = 150
    data_t d5;
    printf("d5.num1 = %i\nd5.num2 = %i\nd5.num3 = %i\nd5.num4 = %i\n\n",
           d5.num1, d5.num2, d5.num3, d5.num4);

    // Default initialization of **static** objects forces members without defaults to be zero-
    // initialized, rather than leaving them to be anything (unitialized)
    static data_t d5b;
    printf("d5b.num1 = %i\nd5b.num2 = %i\nd5b.num3 = %i\nd5b.num4 = %i\n\n",
           d5b.num1, d5b.num2, d5b.num3, d5b.num4);

    // Sets all values to their default values, but if a value doesn't have a default, it *APPEARS*
    // to set it to zero. Ex:
    //      d6.num1 = 100
    //      d6.num2 = -100
    //      d6.num3 = 0
    //      d6.num4 = 150
    data_t d6{};
    printf("d6.num1 = %i\nd6.num2 = %i\nd6.num3 = %i\nd6.num4 = %i\n\n",
           d6.num1, d6.num2, d6.num3, d6.num4);

    // Same as d6 above.
    data_t d7 = data_t();
    printf("d7.num1 = %i\nd7.num2 = %i\nd7.num3 = %i\nd7.num4 = %i\n\n",
           d7.num1, d7.num2, d7.num3, d7.num4);

    // // Error: 
    // //      error: no matching function for call to ‘data_t::data_t(int)’
    // data_t d8 = data_t(15);
    // printf("d8.num1 = %i\nd8.num2 = %i\nd8.num3 = %i\nd8.num4 = %i\n\n",
    //        d8.num1, d8.num2, d8.num3, d8.num4);

    printf("}\n\n");
    #endif

    // Works! This seems to be the ONLY way to forcefully set all values in the struct to zero,
    // other than the following d11 way which is extremely explicit.
    data_t d9;
    memset(&d9, 0, sizeof(d9));
    printf("d9.num1 = %i\nd9.num2 = %i\nd9.num3 = %i\nd9.num4 = %i\n\n",
           d9.num1, d9.num2, d9.num3, d9.num4);

    // // Does NOT work
    // // C++17 error:
    // //      error: conversion from ‘int’ to non-scalar type ‘data_t’ requested
    // // C11 error:
    // //      error: invalid initializer
    // data_t d10 = 0;
    // printf("d10.num1 = %i\nd10.num2 = %i\nd10.num3 = %i\nd10.num4 = %i\n\n",
    //        d10.num1, d10.num2, d10.num3, d10.num4);

    // Works! Very explicit.
    data_t d11 = {0, 0, 0, 0};
    printf("d11.num1 = %i\nd11.num2 = %i\nd11.num3 = %i\nd11.num4 = %i\n\n",
           d11.num1, d11.num2, d11.num3, d11.num4);

    // // Nope! Valid only in gcc, and for arrays.
    // // See: https://stackoverflow.com/questions/201101/how-to-initialize-all-members-of-an-array-to-the-same-value/207702#207702
    // data_t d12 = {[0 ... 3] = 0};
    // printf("d12.num1 = %i\nd12.num2 = %i\nd12.num3 = %i\nd12.num4 = %i\n\n",
    //        d12.num1, d12.num2, d12.num3, d12.num4);

    // // Nope! I made this up, and it definitely doesn't work!
    // data_t d13 = {[.num1 ... .num4] = 0};
    // printf("d13.num1 = %i\nd13.num2 = %i\nd13.num3 = %i\nd13.num4 = %i\n\n",
    //        d13.num1, d13.num2, d13.num3, d13.num4);

    return 0;
}

/*
SAMPLE OUTPUT:

    $ cpp/run_struct_initialization.sh 
    ======================
    Running first as C++17
    ======================
    Hello World

    TEST 1: aggregate initialization??

    d1.num1 = 7
    d1.num2 = 8
    d1.num3 = 0
    d1.num4 = 150

    TEST 2: zero initialization??

    d2.num1 = 100
    d2.num2 = -100
    d2.num3 = 0
    d2.num4 = 150

    d3.num1 = 0
    d3.num2 = -100
    d3.num3 = 0
    d3.num4 = 150

    TEST 3: more initialization tests

    d4.num1 = 2
    d4.num2 = -100
    d4.num3 = 0
    d4.num4 = 150

    The following techniques only are valid in C++, NOT C, so disable them for C:
    {

    d5.num1 = 100
    d5.num2 = -100
    d5.num3 = 847115872
    d5.num4 = 150

    d5b.num1 = 100
    d5b.num2 = -100
    d5b.num3 = 0
    d5b.num4 = 150

    d6.num1 = 100
    d6.num2 = -100
    d6.num3 = 0
    d6.num4 = 150

    d7.num1 = 100
    d7.num2 = -100
    d7.num3 = 0
    d7.num4 = 150

    }

    d9.num1 = 0
    d9.num2 = 0
    d9.num3 = 0
    d9.num4 = 0

    d11.num1 = 0
    d11.num2 = 0
    d11.num3 = 0
    d11.num4 = 0

    ======================
    Now running as C11
    ======================
    Hello World

    TEST 1: aggregate initialization??

    d1.num1 = 7
    d1.num2 = 8
    d1.num3 = 0
    d1.num4 = 0

    TEST 2: zero initialization??

    d2.num1 = 0
    d2.num2 = 0
    d2.num3 = 0
    d2.num4 = 0

    d3.num1 = 0
    d3.num2 = 0
    d3.num3 = 0
    d3.num4 = 0

    TEST 3: more initialization tests

    d4.num1 = 2
    d4.num2 = 0
    d4.num3 = 0
    d4.num4 = 0

    d9.num1 = 0
    d9.num2 = 0
    d9.num3 = 0
    d9.num4 = 0

    d11.num1 = 0
    d11.num2 = 0
    d11.num3 = 0
    d11.num4 = 0


*/

