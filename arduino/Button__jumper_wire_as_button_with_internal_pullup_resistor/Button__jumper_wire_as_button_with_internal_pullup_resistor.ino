/*
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

Modified by Gabriel Staples & Breck Bendall
23 Apr. 2022

- Modify the built-in button sketch to use a standard jumper wire as a button by using an internal
  pull-up resistor on a digital input pin. You then plug one one end of a jumper wire into GND, and
  touch the other end of the jumper wire to the digital input pin (pin 2, defined below) to
  simulate a button press. The way this works is that the internal pull-up resistor pulls up the pin
  to 5V through an internal ~20K resistor. When you ground the input pin with the jumper wire, it
  pulls the pin LOW to GND safely because the internal 5V driving force is going through the
  internal 20K current-limiting resistor to prevent you from frying the pin. It's NOT a direct
  short of 5V to GND, which would fry the pin. Rather, it's through a safe 20K internal resistor.
- OPEN UP THE SERIAL MONITOR (Tools --> Serial Monitor) or the SERIAL PLOTTER (Tools --> Serial
  Plotter) to view the button state as a 0 or 1 in the Serial Monitor or in a live graphical plot
  in the Serial Plotter!


ORIGINAL ARDUINO "BUTTON" EXAMPLE DESCRIPTION:

  Button

  Turns on and off a light emitting diode(LED) connected to digital pin 13,
  when pressing a pushbutton attached to pin 2.

  The circuit:
  - LED attached from pin 13 to ground through 220 ohm resistor
  - pushbutton attached to pin 2 from +5V
  - 10K resistor attached to pin 2 from ground

  - Note: on most Arduinos there is already an LED on the board
    attached to pin 13.

  created 2005
  by DojoDave <http://www.0j0.org>
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Button


References:
1. https://www.arduino.cc/en/Tutorial/BuiltInExamples/Button
1. https://www.arduino.cc/reference/en/language/functions/digital-io/pinmode/
1. *****https://docs.arduino.cc/learn/microcontrollers/digital-pins - see especially the section
titled "Properties of Pins Configured as INPUT_PULLUP"

*/

// constants won't change. They're used here to set pin numbers:
constexpr uint8_t buttonPin = 2;     // the number of the pushbutton pin
constexpr uint8_t ledPin =  13;      // the number of the LED pin

// variables will change:
bool buttonState = 0;         // variable for reading the pushbutton status

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input, also enabling the internal ~20KOhm pull-up resistor.
  // See: https://docs.arduino.cc/learn/microcontrollers/digital-pins --> see the section
  // titled "Properties of Pins Configured as INPUT_PULLUP"
  pinMode(buttonPin, INPUT_PULLUP);

  Serial.begin(115200);
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
//  Serial.print("state = ");
  Serial.println(buttonState);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
    digitalWrite(ledPin, HIGH);
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
  }

  // This limits the max sample rate to <= 10 Hz (100 ms or greater sample periods) so that the
  // serial prints won't be too fast.
  delay(100);
}
