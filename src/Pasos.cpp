/*************************************************************************
 * Class::Pasos(); was created for you to be able to handle a step by    *
 *                 step motor model 28BYJ-48 with your Arduino board.    *
 *************************************************************************
 * Original library        (1.0)   by Carlos Silva (jazzlutty@gmail.com) *
 *                                                                       *
 * This library is free software; you can redistribute it and/or modify  *
 * it under the terms of the GNU Lesser General PublicLicense as         *
 * by the Free Software Foundation; eitherversion 2.1 of the License, or *
 * (at your option) any later version.                                   *
 *                                                                       *
 * This library is distributed in the hope that it will be useful, but   *
 * WITHOUT ANY WARRANTY; without even the implied warranty of            *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU      *
 * Lesser General Public License for more details.                       *
 *                                                                       *
 * You should have received a copy of the GNU Lesser General Public      *
 * License along with this library; if not, write to the Free Software   *
 * Foundation, Inc, 51 Franklin St, 5th Floor, Boston, MA 02110-1301 USA *
 *************************************************************************
 *  you should use the class Pasos() in a way to connect as follows:     *
 *                                                                       *
 ********************************************************************    *
 * -----------------------------------  * DO NOT CONNECT ARDUINO+5V *    *
 * -ext_5V- Arduino   bridge   motor -  * TO MOTOR ******************    *
 * -----------------------------------  * external 5V dc to avoid   *    *
 * -      - Pin8 ---> IN1 ---> blue  -  * damage to your Arduino    *    *
 * -      - Pin9 ---> IN2 ---> pink  -  * board. (a must) !!!       *    *
 * -      - Pin10 --> IN3 ---> yellow-  *****************************    *
 * -      - Pin11 --> IN4 ---> orange-  * Remember to connect the   *    *
 * - + 5V -  *nc      +5V ---> red   -  * external Ground with your *    *
 * - -gnd - GND  ---> -0V --->  *nc  -  * Arduino GND. **************    *
 * -----------------------------------  *         *nc: Not Connected*    *
 *                                      *****************************    *
 *  In other words, from the Arduino board point of view, as a example   *
 *  pin 10 is connected to IN3. Then any changes on your software via    *
 *  pin 10 will force a change in the yellow wire to the motor, after    *
 *  the 250 ns delay from the ULN2003A gate average response time. take  *
 *  this nano-delay into consideration, because an Arduino instruction   *
 *  is about 65 ns, so you dont want to change your digital pin state    *
 *  before the motor was able in time to response. Lets asume a minimal   *
 *  time of 1 ms to be sure. Again, you need to thing a single motor     *
 *  step like an equivalency with a single 8-times magnetic sequence.    *
 *                                                                       *
 *  Since the source energy to unlock the gear in the motor is magnetic, *
 *  every single step given by the motor, regardless on directions or    *
 *  speeds, should be designed thinking in a magnetic pattern. The motor *
 *  model 28BYJ-48 has a 5ft red wire, connected to an external +5V dc   *
 *  source to avoiding damage or inductive malfunction on your Arduino   *
 *  board. This Class implements the 8-times magnetic sequence to unlock *
 *  one single step on the motor. The total number of single steps to    *
 *  take one turn is 512 steps. (512 steps per revolution)               *
 *                                                                       *
 ************************************************************            *
 *  pins  *      8-time-secuense      *    4-time-secuense  *            *
 ************************************************************            *
 * pin 8  *   11111000     00111110      1 1 1 0    0 1 1 1 *    blue    *
 * pin 9  *   11100011     10001111      1 1 0 1    1 0 1 1 *    pink    *
 * pin 10 *   10001111     11100011      1 0 1 1    1 1 0 1 *    yellow  *
 * pin 11 *   00111110     11111000      0 1 1 1    1 1 1 0 *    orange  *
 ************************************************************            *
 *              CCW           CW           CCW        CW    *            *
 ************************************************************************/

#include "Pasos.h"
// Constructors:
Pasos::Pasos() {
  this->blue = 8;
  this->pink = 9;
  this->yellow = 10;
  this->orange = 11;
}
// Constructors:
Pasos::Pasos(int blue, int pink, int yellow, int orange) {
  this->blue = blue;
  this->pink = pink;
  this->yellow = yellow;
  this->orange = orange;
}
// initialize digital pins to handle the motor.
void Pasos::initPasos(void) {
  this->is_clock_wise = COUNTERCLOCKWISE;
  this->speed = RPM_14;
  this->steps_per_rev = STEPS_P_REV;
  this->steps_count = 0;

  pinMode(this->blue, OUTPUT);
  pinMode(this->pink, OUTPUT);
  pinMode(this->yellow, OUTPUT);
  pinMode(this->orange, OUTPUT);
  // initial state for sequence.
  digitalWrite(this->blue, LOW);
  digitalWrite(this->pink, HIGH);
  digitalWrite(this->yellow, HIGH);
  digitalWrite(this->orange, LOW);
}
// function to get the actual count value from a private variable.
int Pasos::getNumeroDePasos(void) {
  return this->steps_count;
}
// funtion to implement a some steps at a given direction and speed.
void Pasos::darPasos(int steps_to_do, bool is_clock_wise, int speed) {
  this->is_clock_wise = is_clock_wise;
  this->speed = speed;
  for (int j=0; j<steps_to_do; j++) {
    if (this->is_clock_wise) singleStep_CW();
    else singleStep_CCW();
    this->steps_count++;
//    Serial.println(this->steps_count);
    if (this->steps_count == this->steps_per_rev) this->steps_count = 0;
  }
}
// function to performe 1 single revolution at a given direction and speed.
void Pasos::unaVuelta(bool is_clock_wise, int speed) {
  darPasos(STEPS_P_REV, is_clock_wise, speed);
}
// function to give some revolutions at a given direction and speed.
void Pasos::darVueltas(int revs_to_do, bool is_clock_wise, int speed) {
  for(int k=0; k<revs_to_do; k++) {
    unaVuelta(is_clock_wise, speed);
  }
}
// internal function to implement a single step clock-wise.
void Pasos::singleStep_CW(void) {
                // 0110 <--- initial state.
  for(int i=0; i<8; i++) {
    switch (i) {
      case 0:   // 0111
      digitalWrite(this->orange, HIGH);
      break;
      case 1:   // 0011
      digitalWrite(this->pink, LOW);
      break;
      case 2:   // 1011
      digitalWrite(this->blue, HIGH);
      break;
      case 3:   // 1001
      digitalWrite(this->yellow, LOW);
      break;
      case 4:   // 1101
      digitalWrite(this->pink, HIGH);
      break;
      case 5:   // 1100
      digitalWrite(this->orange, LOW);
      break;
      case 6:   // 1110
      digitalWrite(this->yellow, HIGH);
      break;
      case 7:   // 0110
      digitalWrite(this->blue, LOW);
      break;
    }
    delay(this->speed);
  }
}
// internal function to implement a single step counter-clock-wise.
void Pasos::singleStep_CCW(void) {
                // 0110 <--- initial state.
  for(int i=0; i<8; i++) {
    switch (i) {
      case 0:   // 1110
      digitalWrite(this->blue, HIGH);
      break;
      case 1:   // 1100
      digitalWrite(this->yellow, LOW);
      break;
      case 2:   // 1101
      digitalWrite(this->orange, HIGH);
      break;
      case 3:   // 1001
      digitalWrite(this->pink, LOW);
      break;
      case 4:   // 1011
      digitalWrite(this->yellow, HIGH);
      break;
      case 5:   // 0011
      digitalWrite(this->blue, LOW);
      break;
      case 6:   // 0111
      digitalWrite(this->pink, HIGH);
      break;
      case 7:   // 0110
      digitalWrite(this->orange, LOW);
      break;
    }
    delay(this->speed);
  }
}
