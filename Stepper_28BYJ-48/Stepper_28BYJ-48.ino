/* 
 Stepper Motor Control - one revolution
 This program is an example of how to drive the 28BYJ-48 12VDC unipolar stepper motor using the ULN2003 Stepper Driver Board
 The motor should revolve one revolution in one direction, then
 one revolution in the other direction.
 Modifications to the original program:
  - One complete revolution is 2048 steps for the 28BYJ-48 stepper motor
  - The speed needed to be reduced to 4
 depending on how much voltage you are using or the 
 motor will just vibrate and not move.
 - The sequence wiring sequence has been changed to 8, 10, 9, 11 in order
 to allow a straight connection from the Arduino pins 8, 9, 10, 11 to IN1, IN2, IN3, IN4 respectively.
  
 Created 11 Mar. 2007
 by Tom Igoe
 Modified August 28, 2012
 by Bentley Born
 */

#include <Stepper.h>

const int stepsPerRevolution = 2048; //this has been changed to 2048 for the 28BYJ-48

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8,10,9,11); //note the modified sequence         

void setup() {
  // set the speed (needed to be reduced for the 28BYJ-48):
  myStepper.setSpeed(4);
  // initialize the serial port:
  Serial.begin(9600);
}

void loop() {
  // step one revolution  in one direction:
   Serial.println("clockwise");
  myStepper.step(stepsPerRevolution);
  delay(1000);
  
   // step one revolution in the other direction:
  Serial.println("counterclockwise");
  myStepper.step(-stepsPerRevolution);
  delay(1000); 
}
