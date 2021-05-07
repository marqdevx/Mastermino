// -----
// SimplePollRotator.ino - Example for the RotaryEncoder library.
// This class is implemented for use with the Arduino environment.
//
// Copyright (c) by Matthias Hertel, http://www.mathertel.de
// This work is licensed under a BSD 3-Clause License. See http://www.mathertel.de/License.aspx
// More information on: http://www.mathertel.de/Arduino
// -----
// 18.01.2014 created by Matthias Hertel
// 04.02.2021 conditions and settings added for ESP8266
// -----

// This example checks the state of the rotary encoder using interrupts and in the loop() function.
// The current position and direction is printed on output when changed.

// Hardware setup:
// Attach a rotary encoder with output pins to
// * 2 and 3 on Arduino UNO. (supported by attachInterrupt)
// * A2 and A3 can be used when directly using the ISR interrupts, see comments below.
// * D5 and D6 on ESP8266 board (e.g. NodeMCU).
// Swap the pins when direction is detected wrong.
// The common contact should be attached to ground.
//
// Hints for using attachinterrupt see https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/

#include <Arduino.h>
#include <RotaryEncoder.h>
#include "matrix.h"

// Example for Arduino UNO with input signals on pin 2 and 3
#define PIN_IN1 0
#define PIN_IN2 1



// Setup a RotaryEncoder with 4 steps per latch for the 2 signal input pins:
// RotaryEncoder encoder(PIN_IN1, PIN_IN2, RotaryEncoder::LatchMode::FOUR3);

// Setup a RotaryEncoder with 2 steps per latch for the 2 signal input pins:
RotaryEncoder encoder(PIN_IN1, PIN_IN2, RotaryEncoder::LatchMode::TWO03);

void rotationCallback();
bool bounceBlock = false;

// This interrupt routine will be called on any change of one of the input signals
void checkPosition()
{
  encoder.tick(); // just call tick() to check the state.
  rotationCallback();
}

void rotarySetup()
{
  attachInterrupt(PIN_IN1, checkPosition, CHANGE);
  attachInterrupt(PIN_IN2, checkPosition, CHANGE);
} // setup()


// Read the current position of the encoder and print out when changed.
void encoderUpdate()
{


  static int pos = 0;
  encoder.tick();

  int newPos = pos + (int)encoder.getDirection();

  if (newPos > COLORS_SIZE - 1) newPos = 0;
  if (newPos < 0) newPos = COLORS_SIZE - 1;

  if (pos != newPos) {

    Serial.print("pos:");
    Serial.print(newPos);
    Serial.print(" dir:");
    Serial.println((int)(encoder.getDirection()));
    pos = newPos;




    setpixel(mastermino.turnCount, mastermino.guessCount, pos);


  }
  if (mastermino.entryAvailable()) {
    if (!digitalRead(7) && !bounceBlock) {
      if (pos <= 0) return;
      mastermino.newEntry(pos);
      bounceBlock = true;
      setpixel(mastermino.turnCount, mastermino.guessCount, 0);
      pos = 0;

    } else if (digitalRead(7) && bounceBlock) {
      bounceBlock = false;
    }

  } else {
    mastermino.finishGuess();
    mastermino.getChecks();
    updateMatrix();
    setpixel(mastermino.turnCount, mastermino.guessCount, pos);
    pos = 0;
  }
}
