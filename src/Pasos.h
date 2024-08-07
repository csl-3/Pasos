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

// ensure this library description is only included once.
#ifndef _Pasos_h
#define _Pasos_h

#include <Arduino.h>
// total steps per revolution for the model 28BYJ-48.
#define STEPS_P_REV 512
// definitions of directions
#define CLOCKWISE          HIGH
#define COUNTERCLOCKWISE   LOW
// definitions of motor speeds expresed on RPMs.
#define RPM_14      1
#define RPM_7       2
#define RPM_5       3
#define RPM_4       4
#define RPM_3       5
#define RPM_DEBUG   125

// library interface description.
class Pasos {
  public:
    // Constructors:
    Pasos(void);
    Pasos(int blue, int pink, int yellow, int orange);

    // void initSteps();
    // initialize digital pins to handle the motor.
    void initPasos(void);

    // void doSteps();
    // funtion to implement a some steps at a given direction and speed.
    void darPasos(int steps_to_do, bool is_clock_wise, int speed);

    // void oneRev();
    // function to performe 1 single revolution at a given direction and
    // speed.
    void unaVuelta(bool is_clock_wise, int speed);

    // void doRevs();
    // function to give some revolutions at a given direction and speed.
    void darVueltas(int revs_to_do, bool is_clock_wise, int speed);

    // int get_Steps_Count();
    // function to get the actual count value from a private variable.
    int getNumeroDePasos(void);

  private:
    // internal function to implement a single step clock-wise.
    void singleStep_CW(void);
    // internal function to implement a single step counter-clock-wise.
    void singleStep_CCW(void);

    // it's a binary one: Either ClockWise or against it.
    bool is_clock_wise;
    // Speed of rotation in Revolutions per Minute [RPM].
    int speed;
    // number of motor steps required per revolution.
    int steps_per_rev;
    // a simple count on how many spets until now.
    int steps_count;

    int blue;    // 1. First wire from ULN2003A to motor 28BYJ-48, BLUE
    int pink;    // 2. Second              "                 "     PINK
    int yellow;  // 3. Third               "                 "     YELLOW
    int orange;  // 4. Forth wire from ULN2003A to motor 28BYJ-48, ORANGE
};

#endif
