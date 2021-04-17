/*
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

Arduino Leonardo code to press the zero ("0") key once per second.

Compatible Boards:
For use with:
    - Arduino Leonardo
    - Arduino Micro
    - Arduino Pro Micro
    - Arduino Due

By Gabriel Staples
https://www.ElectricRCAircraftGuy.com
https://gabrielstaples.com

If this is useful, consider a donation via PayPal here:
https://www.electricrcaircraftguy.com/2016/01/contribute.html
OR (even better) a monthly GitHub sponsorship here:
==> https://github.com/sponsors/ElectricRCAircraftGuy <==

References:
1. www.arduino.cc/en/Tutorial/BuiltInExamples/KeyboardMessage
1. www.arduino.cc/en/Tutorial/BuiltInExamples/KeyboardAndMouseControl
1. https://www.arduino.cc/reference/en/language/functions/usb/keyboard/
    1. https://www.arduino.cc/reference/en/language/functions/usb/keyboard/keyboardprint/

*/

#include "Keyboard.h"

/// This runs once at program startup
void setup()
{
    // initialize control over the keyboard:
    Keyboard.begin();

    pinMode(10, INPUT_PULLUP);
    // Do NOT go to the `loop()` code if you have a jumper wire from pin 10 to
    // GND. This way, to reprogram the Leonardo without having it typing
    // constantly and interfering with you uploading new code, you can just
    // disable the typing by putting a jumper wire from pin 10 to GND.
    if (digitalRead(10) == LOW)
    {
        while (true) {} // empty, infinite while loop (ie: do nothing, forever)
    }
}

/// This loop runs continually, forever, once `setup()` is complete.
void loop()
{
    // Press the zero (0) key once per second, forever.
    // Change what is in quotes to ANY TEXT or characters you want the
    // Arduino to print out as a USB keyboard!
    Keyboard.print("0");
    delay(1000); // wait 1000ms before looping back around and repeating
}
