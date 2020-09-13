/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby,
C#, VB, Perl, Swift, Prolog, Javascript, Pascal, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.

Gabriel Staples
www.ElectricRCAircraftGuy.com
20 Aug. 2020

See also:
1. My "gcc_attribute_cleanup_practice_1" code on onlinegdb: https://www.onlinegdb.com/edit/rJtZoHNb4
2. My Arduino answer here: https://arduino.stackexchange.com/questions/77494/which-arduinos-support-atomic-block/77579#77579.

*******************************************************************************/
#include <stdio.h>

#define ATOMIC_BLOCK_FORCEON AtomicBlockForceOn atomicBlockForceOn_

#define ATOMIC_BLOCK(type) for(type, bool run = true; run; run = false)
#define ATOMIC_FORCEON AtomicBlockForceOn atomicBlockForceOn_

class AtomicBlockForceOn
{
public:
    // Constructor: called when the object is created
    AtomicBlockForceOn()
    {
        printf("noInterrupts()\n"); // turn interrupts OFF
    }

    // Destructor: called when the object is destroyed (ex: goes
    // out-of-scope)
    ~AtomicBlockForceOn()
    {
        printf("interrupts()\n"); // turn interrupts ON
    }
};

int main()
{
    printf("Hello World\n");

    // Option 1: use it like C++'s `std::lock_guard` template type:
    printf("before ATOMIC_BLOCK_FORCEON\n");
    {
        ATOMIC_BLOCK_FORCEON;
        printf("after ATOMIC_BLOCK_FORCEON constructor\n");
        printf("do some stuff here with interrupts off!\n");
    } // the `atomicBlockForceOn_` object's destructor is called here
      // and interrupts are automatically turned back ON!
    printf("after ATOMIC_BLOCK_FORCEON destructor\n");

    // Option 2: use it like avrlibc's `ATOMIC_BLOCK() { }` macro:
    printf("\nbefore ATOMIC_BLOCK(ATOMIC_FORCEON)\n");
    ATOMIC_BLOCK(ATOMIC_FORCEON)
    {
        printf("after AtomicBlockForceOn constructor\n");
        printf("do some stuff here with interrupts off!\n");
    } // the `atomicBlockForceOn_` object's destructor is called here
      // and interrupts are automatically turned back ON!
    printf("after AtomicBlockForceOn destructor\n");

    return 0;
}

/*
SAMPLE OUTPUT:


*/



