// This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

/*
GS
1 Feb. 2021

Raw register-level AVR blocking blink example.

Status:
UNTESTED! THIS CODE IS JUST A QUICK DRAFT--NOT TESTED YET!

References:
1. Arduino pin mapping: https://www.arduino.cc/en/Hacking/PinMapping168
1. See also this early example from 2011 by Ladyada herself!:
   https://www.ladyada.net/learn/proj1/blinky.html

*/

#define __AVR_ATmega328__

#include <avr/io.h>

#include <stdint.h> // uint32_t


int main()
{
    // setup
    DDRB |= 1 << DDB5; // set pinMode to OUTPUT on Arduino LED pin 13

    // loop
    for (;;)
    {
        PORTB |= 1 << PORTB5; // digital write HIGH on Arduino LED pin 13
        for (volatile uint32_t i = 0; i < 100000; i++) {} // delay
        PORTB &= ~(1 << PORTB5); // digital write LOW on Arduino LED pin 13
        for (volatile uint32_t i = 0; i < 100000; i++) {} // delay
    }

    return 0;
}
