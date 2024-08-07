/*
 * Pasos_Vueltas       Pasos_Revolutions
 *
 * Lets change the direction of the motor.
 * Do some revs, change speed and direction,
 * do more revs.
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
  Serial.println("doing 2 revs clock-wise at 7 RPM");
  steps.darVueltas(2, is_clock_wise, RPM_7);
  Serial.println("done...");
  Serial.println();
  delay(1000);
  Serial.println("doing 3 revs counter-clock-wise at 14 RPM");
  steps.darVueltas(3, !is_clock_wise, RPM_14);
  Serial.println("done...");
  Serial.println();
  delay(1000);
}