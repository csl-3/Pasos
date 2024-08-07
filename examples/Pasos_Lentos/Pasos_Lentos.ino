/*
 * Pasos_Lentos       Slow_Steps
 *
 * A super long delay to able you to see the sequences
 * when you read them on board leds on the ULN2003A.
 *
 * jazzlutty@gmail.com
 * This example code is in the public domain.
 */
#include "Pasos.h"

// Your arduino pins selected.
#define pin1   8
#define pin2   9
#define pin3  10
#define pin4  11

bool is_clock_wise = CLOCKWISE;
// Create a new object Pasos() and link the arduino pins.
Pasos steps(pin1, pin2, pin3, pin4);

void setup() {
  Serial.begin(9600);
  delay(1000);
  Serial.println("initialazing motor ...");
  steps.initPasos();
  Serial.println("motor ready to work !!");
  delay(1000);
}

void loop() {
  Serial.println();
  Serial.println("BEHOLD !!!     the magnetic sequence");
  Serial.println("dont look at me, look at the ULN2003A");
  Serial.println("lets see 10 steps clock-wise");
  steps.darPasos(10, is_clock_wise, RPM_DEBUG);
  Serial.println("and now 10 steps back counter-clock-wise");
  steps.darPasos(10, !is_clock_wise, RPM_DEBUG);
}
