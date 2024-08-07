/*
 * Pasos_Accion       Take_Action_Steps
 *
 * Do a fixed number of steps, take an action, repeat.
 * Lets toggle the Arduino on board Led (pin13) every
 * 8 steps.
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
bool led_state = LOW;
// Create a new object Pasos() and link the arduino pins.
Pasos steps(pin1, pin2, pin3, pin4);

void setup() {
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  Serial.begin(9600);
  delay(1000);
  Serial.println("initialazing motor ...");
  steps.initPasos();
  Serial.println("motor ready to work !!");
  delay(1000);
}

void loop() {
  steps.darPasos(8, is_clock_wise, RPM_14);
  led_state = !led_state;
  digitalWrite(13, led_state);
  Serial.print(steps.getNumeroDePasos());
  Serial.println("  steps");
  delay(1000);
}
