/*

This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

Gabriel Staples
26 Sept. 2020

template_func.cpp
- See the readme in this folder for a description.
- See also: my code here:
  [function_overloading_on_input_param_array_size](https://onlinegdb.com/Sk3bw8aHD)

To compile and run:

    g++ -Wall -Werror -g3 -O3 -std=c++17 -o template_func \
    template_func.cpp && ./template_func

*/

#include <cstdint>
#include <cstdio>
#include <iostream>

// void print_array_size(uint8_t * byte_array, size_t len)
// {
//     printf("sizeof(byte_array) = %lu\n", len);
// }

template<size_t N>
void print_array_size(uint8_t (&byte_array)[N])
{
    printf("sizeof(byte_array) = %lu\n", N);
}

int main()
{
    printf("Hello World\n");

    // FAILS TO BUILD
    // for (size_t i = 1; i <= 10; i++)
    // {
    //     uint8_t byte_array[i];
    //     print_array_size<i>(byte_array);
    // }

    uint8_t byte_array[10];
    // print_array_size(byte_array);
    // print_array_size((uint8_t (&)[9])byte_array); // works!

    // FAILS TO COMPILE! Again, templates MUST know their parameters STATICALLY, at compile-time!
    // `i` is NOT a compile-time variable, so it doesn't work!
    // for (size_t i = 1; i <= 10; i++)
    // {
    //     print_array_size((uint8_t (&)[i])byte_array);
    // }

#define RUN_100  // set to RUN_1, RUN_10, or RUN_100
#if defined RUN_10 || defined RUN_100
    print_array_size((uint8_t (&)[1])byte_array);
    print_array_size((uint8_t (&)[2])byte_array);
    print_array_size((uint8_t (&)[3])byte_array);
    print_array_size((uint8_t (&)[4])byte_array);
    print_array_size((uint8_t (&)[5])byte_array);
    print_array_size((uint8_t (&)[6])byte_array);
    print_array_size((uint8_t (&)[7])byte_array);
    print_array_size((uint8_t (&)[8])byte_array);
    print_array_size((uint8_t (&)[9])byte_array);
#endif
#if defined RUN_1 || defined RUN_10 || defined RUN_100
    print_array_size(byte_array);
#endif
#if defined RUN_100
    print_array_size((uint8_t (&)[11])byte_array);
    print_array_size((uint8_t (&)[12])byte_array);
    print_array_size((uint8_t (&)[13])byte_array);
    print_array_size((uint8_t (&)[14])byte_array);
    print_array_size((uint8_t (&)[15])byte_array);
    print_array_size((uint8_t (&)[16])byte_array);
    print_array_size((uint8_t (&)[17])byte_array);
    print_array_size((uint8_t (&)[18])byte_array);
    print_array_size((uint8_t (&)[19])byte_array);
    print_array_size((uint8_t (&)[20])byte_array);
    print_array_size((uint8_t (&)[21])byte_array);
    print_array_size((uint8_t (&)[22])byte_array);
    print_array_size((uint8_t (&)[23])byte_array);
    print_array_size((uint8_t (&)[24])byte_array);
    print_array_size((uint8_t (&)[25])byte_array);
    print_array_size((uint8_t (&)[26])byte_array);
    print_array_size((uint8_t (&)[27])byte_array);
    print_array_size((uint8_t (&)[28])byte_array);
    print_array_size((uint8_t (&)[29])byte_array);
    print_array_size((uint8_t (&)[30])byte_array);
    print_array_size((uint8_t (&)[31])byte_array);
    print_array_size((uint8_t (&)[32])byte_array);
    print_array_size((uint8_t (&)[33])byte_array);
    print_array_size((uint8_t (&)[34])byte_array);
    print_array_size((uint8_t (&)[35])byte_array);
    print_array_size((uint8_t (&)[36])byte_array);
    print_array_size((uint8_t (&)[37])byte_array);
    print_array_size((uint8_t (&)[38])byte_array);
    print_array_size((uint8_t (&)[39])byte_array);
    print_array_size((uint8_t (&)[40])byte_array);
    print_array_size((uint8_t (&)[41])byte_array);
    print_array_size((uint8_t (&)[42])byte_array);
    print_array_size((uint8_t (&)[43])byte_array);
    print_array_size((uint8_t (&)[44])byte_array);
    print_array_size((uint8_t (&)[45])byte_array);
    print_array_size((uint8_t (&)[46])byte_array);
    print_array_size((uint8_t (&)[47])byte_array);
    print_array_size((uint8_t (&)[48])byte_array);
    print_array_size((uint8_t (&)[49])byte_array);
    print_array_size((uint8_t (&)[50])byte_array);
    print_array_size((uint8_t (&)[51])byte_array);
    print_array_size((uint8_t (&)[52])byte_array);
    print_array_size((uint8_t (&)[53])byte_array);
    print_array_size((uint8_t (&)[54])byte_array);
    print_array_size((uint8_t (&)[55])byte_array);
    print_array_size((uint8_t (&)[56])byte_array);
    print_array_size((uint8_t (&)[57])byte_array);
    print_array_size((uint8_t (&)[58])byte_array);
    print_array_size((uint8_t (&)[59])byte_array);
    print_array_size((uint8_t (&)[60])byte_array);
    print_array_size((uint8_t (&)[61])byte_array);
    print_array_size((uint8_t (&)[62])byte_array);
    print_array_size((uint8_t (&)[63])byte_array);
    print_array_size((uint8_t (&)[64])byte_array);
    print_array_size((uint8_t (&)[65])byte_array);
    print_array_size((uint8_t (&)[66])byte_array);
    print_array_size((uint8_t (&)[67])byte_array);
    print_array_size((uint8_t (&)[68])byte_array);
    print_array_size((uint8_t (&)[69])byte_array);
    print_array_size((uint8_t (&)[70])byte_array);
    print_array_size((uint8_t (&)[71])byte_array);
    print_array_size((uint8_t (&)[72])byte_array);
    print_array_size((uint8_t (&)[73])byte_array);
    print_array_size((uint8_t (&)[74])byte_array);
    print_array_size((uint8_t (&)[75])byte_array);
    print_array_size((uint8_t (&)[76])byte_array);
    print_array_size((uint8_t (&)[77])byte_array);
    print_array_size((uint8_t (&)[78])byte_array);
    print_array_size((uint8_t (&)[79])byte_array);
    print_array_size((uint8_t (&)[80])byte_array);
    print_array_size((uint8_t (&)[81])byte_array);
    print_array_size((uint8_t (&)[82])byte_array);
    print_array_size((uint8_t (&)[83])byte_array);
    print_array_size((uint8_t (&)[84])byte_array);
    print_array_size((uint8_t (&)[85])byte_array);
    print_array_size((uint8_t (&)[86])byte_array);
    print_array_size((uint8_t (&)[87])byte_array);
    print_array_size((uint8_t (&)[88])byte_array);
    print_array_size((uint8_t (&)[89])byte_array);
    print_array_size((uint8_t (&)[90])byte_array);
    print_array_size((uint8_t (&)[91])byte_array);
    print_array_size((uint8_t (&)[92])byte_array);
    print_array_size((uint8_t (&)[93])byte_array);
    print_array_size((uint8_t (&)[94])byte_array);
    print_array_size((uint8_t (&)[95])byte_array);
    print_array_size((uint8_t (&)[96])byte_array);
    print_array_size((uint8_t (&)[97])byte_array);
    print_array_size((uint8_t (&)[98])byte_array);
    print_array_size((uint8_t (&)[99])byte_array);
    print_array_size((uint8_t (&)[100])byte_array);
#endif

    return 0;
}


/*
Size (`size <executable>`):

1. `#define RUN_1`:

        $ size template_func
           text    data     bss     dec     hex filename
           2007     648       8    2663     a67 template_func


2. `#define RUN_10`:

        $ size template_func
           text    data     bss     dec     hex filename
           2223     648       8    2879     b3f template_func

Increase in size of (2879 - 2663)/9 added = 24 bytes per new (array size) function call.


3. `#define RUN_100`:

        $ size template_func
           text    data     bss     dec     hex filename
           4383     648       8    5039    13af template_func

Increase in size of (5039 - 2663)/99 added = 24 bytes per new (array size) function call.



Sample Output:

1. `#define RUN_1`:

        $ g++ -Wall -Werror -g3 -O3 -std=c++17 -o template_func     template_func.cpp && ./template_func
        Hello World
        sizeof(byte_array) = 10


2. `#define RUN_10`:

        $ g++ -Wall -Werror -g3 -O3 -std=c++17 -o template_func     template_func.cpp && ./template_func
        Hello World
        sizeof(byte_array) = 1
        sizeof(byte_array) = 2
        sizeof(byte_array) = 3
        sizeof(byte_array) = 4
        sizeof(byte_array) = 5
        sizeof(byte_array) = 6
        sizeof(byte_array) = 7
        sizeof(byte_array) = 8
        sizeof(byte_array) = 9
        sizeof(byte_array) = 10


3. `#define RUN_100`:

        $ g++ -Wall -Werror -g3 -O3 -std=c++17 -o template_func     template_func.cpp && ./template_func
        Hello World
        sizeof(byte_array) = 1
        sizeof(byte_array) = 2
        sizeof(byte_array) = 3
        sizeof(byte_array) = 4
        sizeof(byte_array) = 5
        sizeof(byte_array) = 6
        sizeof(byte_array) = 7
        sizeof(byte_array) = 8
        sizeof(byte_array) = 9
        sizeof(byte_array) = 10
        sizeof(byte_array) = 11
        sizeof(byte_array) = 12
        sizeof(byte_array) = 13
        sizeof(byte_array) = 14
        sizeof(byte_array) = 15
        sizeof(byte_array) = 16
        sizeof(byte_array) = 17
        sizeof(byte_array) = 18
        sizeof(byte_array) = 19
        sizeof(byte_array) = 20
        sizeof(byte_array) = 21
        sizeof(byte_array) = 22
        sizeof(byte_array) = 23
        sizeof(byte_array) = 24
        sizeof(byte_array) = 25
        sizeof(byte_array) = 26
        sizeof(byte_array) = 27
        sizeof(byte_array) = 28
        sizeof(byte_array) = 29
        sizeof(byte_array) = 30
        sizeof(byte_array) = 31
        sizeof(byte_array) = 32
        sizeof(byte_array) = 33
        sizeof(byte_array) = 34
        sizeof(byte_array) = 35
        sizeof(byte_array) = 36
        sizeof(byte_array) = 37
        sizeof(byte_array) = 38
        sizeof(byte_array) = 39
        sizeof(byte_array) = 40
        sizeof(byte_array) = 41
        sizeof(byte_array) = 42
        sizeof(byte_array) = 43
        sizeof(byte_array) = 44
        sizeof(byte_array) = 45
        sizeof(byte_array) = 46
        sizeof(byte_array) = 47
        sizeof(byte_array) = 48
        sizeof(byte_array) = 49
        sizeof(byte_array) = 50
        sizeof(byte_array) = 51
        sizeof(byte_array) = 52
        sizeof(byte_array) = 53
        sizeof(byte_array) = 54
        sizeof(byte_array) = 55
        sizeof(byte_array) = 56
        sizeof(byte_array) = 57
        sizeof(byte_array) = 58
        sizeof(byte_array) = 59
        sizeof(byte_array) = 60
        sizeof(byte_array) = 61
        sizeof(byte_array) = 62
        sizeof(byte_array) = 63
        sizeof(byte_array) = 64
        sizeof(byte_array) = 65
        sizeof(byte_array) = 66
        sizeof(byte_array) = 67
        sizeof(byte_array) = 68
        sizeof(byte_array) = 69
        sizeof(byte_array) = 70
        sizeof(byte_array) = 71
        sizeof(byte_array) = 72
        sizeof(byte_array) = 73
        sizeof(byte_array) = 74
        sizeof(byte_array) = 75
        sizeof(byte_array) = 76
        sizeof(byte_array) = 77
        sizeof(byte_array) = 78
        sizeof(byte_array) = 79
        sizeof(byte_array) = 80
        sizeof(byte_array) = 81
        sizeof(byte_array) = 82
        sizeof(byte_array) = 83
        sizeof(byte_array) = 84
        sizeof(byte_array) = 85
        sizeof(byte_array) = 86
        sizeof(byte_array) = 87
        sizeof(byte_array) = 88
        sizeof(byte_array) = 89
        sizeof(byte_array) = 90
        sizeof(byte_array) = 91
        sizeof(byte_array) = 92
        sizeof(byte_array) = 93
        sizeof(byte_array) = 94
        sizeof(byte_array) = 95
        sizeof(byte_array) = 96
        sizeof(byte_array) = 97
        sizeof(byte_array) = 98
        sizeof(byte_array) = 99
        sizeof(byte_array) = 100


*/





