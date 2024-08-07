/*
 * Pasos_Cuenta_Vueltas     Pasos_Revs_Count
 *
 * Lets do revs forever and count them.
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

int revs = 0;
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
  revs++;
  steps.darPasos(STEPS_P_REV, is_clock_wise, RPM_14);
  Serial.print(revs);
  Serial.println("  rev");
}
