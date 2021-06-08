#include "genericEscMotor.h"

/* The following defined constants are based on the servo example provided with the adafruit servo board library */
#define SERVOMIN  150 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // This is the 'maximum' pulse length count (out of 4096)
#define USMIN  600 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX  2400 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

EscMotor::EscMotor (int inputPin, String partID) {
  this->partID = partID;
  // Set limit and starting values
  maxValue = 1900;
  minValue = 1100;
  stoppedValue = 1500;
  currentValue = stoppedValue;

  pin = inputPin; // Record the associated pin
  
  motor.attach(inputPin);
  
  setValue(stoppedValue);
}

int EscMotor::setValue(int inputValue) {
  // call parent logic (keeps value within preset boundary)
  int value = Output::setValue(inputValue);
  // Actually control the device
  motor.writeMicroseconds(inputValue);
  // Return the set value
  return value;
}

void EscMotor::turnOff(){
  // Switch off in case of emergency
  setValue(stoppedValue);
}
