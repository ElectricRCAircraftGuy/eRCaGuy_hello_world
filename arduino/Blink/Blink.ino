/*
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

Modified by Gabriel Staples
Jan. 2022
- demonstrate manual "big-banging" PWM on built-in LED 13, and also show how to use the
Serial Monitor and Serial Plotter. The code as written right now will print two opposing
sawtooth waves when viewed through the Arduino Serial Plotter.


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

  http://www.arduino.cc/en/Tutorial/Blink
*/

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  Serial.println("i, 256-i");  // create a header in the Serial Plotter
}

// the loop function runs over and over again forever
void loop() {
  // Dim LED (manual "bit-banging" PWM)
//  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
//  delayMicroseconds(10);                       // wait for a second
//  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
//  delayMicroseconds(1000);                       // wait for a second

  // Sawtooth waves (view in the Serial Plotter)
  static uint8_t i = 0;
  Serial.print(i);
  Serial.print(",");
  Serial.println(256-i);
  delay(10);
  i++;
}
