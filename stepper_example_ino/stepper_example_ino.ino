/*************************
Joel Bartlett
SparkFun Electronics
December 27, 2012

This code controls a stepper motor with the 
EasyDriver board. It spins forwards and backwards
***************************/
#include <Stepper.h>

int dirpin = 7;//2;
int steppin = 4;//3;
const int stepsPerRevolution = 800;  // change this to fit the number of steps per revolution
                                     // for your motor
// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, steppin,dirpin);   

void setup() 
{
pinMode(dirpin, OUTPUT);
pinMode(steppin, OUTPUT);

// set the speed at 120 rpm:
myStepper.setSpeed(120);
}
void loop()
{
/*
  int i;

  digitalWrite(dirpin, LOW);     // Set the direction.
  delay(100);


  for (i = 0; i<4000; i++)       // Iterate for 4000 microsteps.
  {
    digitalWrite(steppin, LOW);  // This LOW to HIGH change is what creates the
    digitalWrite(steppin, HIGH); // "Rising Edge" so the easydriver knows to when to step.
    delay(500);//delayMicroseconds(15000);      // This delay time is close to top speed for this
  }                              // particular motor. Any faster the motor stalls.

  digitalWrite(dirpin, HIGH);    // Change direction.
  delay(100);


  for (i = 0; i<4000; i++)       // Iterate for 4000 microsteps
  {
    digitalWrite(steppin, LOW);  // This LOW to HIGH change is what creates the
    digitalWrite(steppin, HIGH); // "Rising Edge" so the easydriver knows to when to step.
    delay(500);//delayMicroseconds(15000);      // This delay time is close to top speed for this
  }                              // particular motor. Any faster the motor stalls.
*/
  
  myStepper.step(10);
  delay(500);

}
