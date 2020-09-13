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

#define ATOMIC_BLOCK(type) for(type; type##_OBJECT_NAME.run(); \
    type##_OBJECT_NAME.stop())
#define ATOMIC_FORCEON_OBJECT_NAME atomicBlockForceOn_
#define ATOMIC_FORCEON AtomicBlockForceOn ATOMIC_FORCEON_OBJECT_NAME

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

    // Can we run? Returns true to run the `for` loop or
    // `false` to stop it.
    inline bool run()
    {
        return run_now;
    }

    // Tell the `for` loop to stop
    inline void stop()
    {
        run_now = false;
    }

private:
    bool run_now = true;
};

int main()
{
    printf("Hello World\n");

    // use it like avrlibc's `ATOMIC_BLOCK() { }` macro:
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

    Hello World

    before ATOMIC_BLOCK(ATOMIC_FORCEON)
    noInterrupts()
    after AtomicBlockForceOn constructor
    do some stuff here with interrupts off!
    interrupts()
    after AtomicBlockForceOn destructor




*/




