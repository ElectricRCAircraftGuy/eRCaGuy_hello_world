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
3. gcc `inline` or `__inline__`, and `static inline` or `static __inline__` rules:
   https://gcc.gnu.org/onlinedocs/gcc/Inline.html

*******************************************************************************/
#include <stdint.h> // for uint8_t
#include <stdio.h>

static __inline__ void cleanup_my_byte(uint8_t *my_byte_p)
{
    printf("my_byte is going out of scope! Its value is %u\n", *my_byte_p);
}

void setup()
{
    printf("entering setup()\n");
    uint8_t my_byte __attribute__((__cleanup__(cleanup_my_byte))) = 7;
    my_byte = 10;
} // The following function call occurs automatically here as `my_byte`
  // exits its scope!:
  //    `cleanup_my_byte(&my_byte);`

int main()
{
    printf("Hello World\n");

    setup();

    return 0;
}

/*
SAMPLE OUTPUT:

    Hello World
    entering setup()
    my_byte is going out of scope! Its value is 10





*/



