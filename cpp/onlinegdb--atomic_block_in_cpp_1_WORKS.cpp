/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby,
C#, VB, Perl, Swift, Prolog, Javascript, Pascal, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.

Gabriel Staples
www.ElectricRCAircraftGuy.com
20 Aug. 2020

To run locally:

    g++ -Wall -Werror -ggdb -std=c++17 -o temp onlinegdb--atomic_block_in_cpp.cpp && ./temp

See also:
1. My "gcc_attribute_cleanup_practice_1" code on onlinegdb: https://www.onlinegdb.com/edit/rJtZoHNb4
2. My Arduino answer here: https://arduino.stackexchange.com/questions/77494/which-arduinos-support-atomic-block/77579#77579.
3. In C++ can constructor and destructor be inline functions?:
   https://stackoverflow.com/questions/21303/in-c-can-constructor-and-destructor-be-inline-functions

*******************************************************************************/
#include <stdio.h>

#define ATOMIC_BLOCK_FORCEON AtomicBlockForceOn atomicBlockForceOn_

class AtomicBlockForceOn
{
public:
    // Constructor: called when the object is created
    inline AtomicBlockForceOn()
    {
        printf("noInterrupts()\n"); // turn interrupts OFF
    }

    // Destructor: called when the object is destroyed (ex: goes
    // out-of-scope)
    inline ~AtomicBlockForceOn()
    {
        printf("interrupts()\n"); // turn interrupts ON
    }
};

int main()
{
    printf("Hello World\n");

    printf("before ATOMIC_BLOCK_FORCEON\n");
    {
        ATOMIC_BLOCK_FORCEON;
        printf("after ATOMIC_BLOCK_FORCEON constructor\n");
        printf("do some stuff here with interrupts off!\n");
    } // the `atomicBlockForceOn_` object's destructor is called here
      // and interrupts are automatically turned back ON!
    printf("after ATOMIC_BLOCK_FORCEON destructor\n");

    return 0;
}

/*
SAMPLE OUTPUT:

    Hello World
    before ATOMIC_BLOCK_FORCEON
    noInterrupts()
    after ATOMIC_BLOCK_FORCEON constructor
    do some stuff here with interrupts off!
    interrupts()
    after ATOMIC_BLOCK_FORCEON destructor

*/



