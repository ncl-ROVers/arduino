#include "genericEscMotor.h"

EscMotor::EscMotor (int inputPin, String partID) {
  this->partID = partID;
  // Set limit and starting values
  maxValue = 1900;
  minValue = 1100;
  stoppedValue = 1500;
  currentValue = stoppedValue;

  pin = inputPin; // Record the associated pin

  pwm = new mbed::PwmOut(digitalPinToPinName(pin));
  
  pwm->period_ms(200);
  
  setValue(stoppedValue);
}

int EscMotor::setValue(int inputValue) {
  // call parent logic (keeps value within preset boundary)
  int value = Output::setValue(inputValue);
  // Actually control the device
  pwm->pulsewidth_us(value);
  // Return the set value
  return value;
}

void EscMotor::turnOff(){
  // Switch off in case of emergency
  setValue(stoppedValue);
}
