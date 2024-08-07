/*
 * Pasos_Velocidad       Pasos_Speed
 *
 * Compare diferent motor speeds.
 * Do 1 revolution, change speed, more Revs.
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
  Serial.println("enjoy 1 leap at 3 RPM");
  steps.unaVuelta(is_clock_wise, RPM_3);
  delay(1000);
  Serial.println("have a good one at 14 RPM");
  steps.unaVuelta(is_clock_wise, RPM_14);
  delay(1000);
}