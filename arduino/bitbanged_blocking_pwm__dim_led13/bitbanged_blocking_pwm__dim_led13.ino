/*
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

Modified by Gabriel Staples & Breck Bendall
23 Apr. 2022
- Modify the built-in blink sketch to dim LED13 a ton using manual, bit-banged, blocking PWM on the
built-in LED 13.


  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink

References:
1. https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink
1. https://www.arduino.cc/reference/en/language/functions/time/delaymicroseconds/

*/

constexpr uint8_t LED = 13;
// constexpr uint8_t LED = LED_BUILTIN; // alternative to the above

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  // dim the LED a ton by manually setting a duty cycle of on_time/(on_time + off_time) =
  // 1/5001 x 100 = 0.02%.
  // NB: to get the **absolute dimmest possible** using this technique, set the HIGH time to 1 us
  // and the LOW time to 16383 us. `delayMicroseconds()` cannot accept values any larger than that.
  // See: https://www.arduino.cc/reference/en/language/functions/time/delaymicroseconds/
  // Of course, you could always just use `delay()` to delay in longer, millisecond values instead,
  // for the LOW time only.

  digitalWrite(LED, HIGH);   // turn the LED on (HIGH is the voltage level)
  delayMicroseconds(1);
  digitalWrite(LED, LOW);    // turn the LED off by making the voltage LOW
  delayMicroseconds(5000);
}
