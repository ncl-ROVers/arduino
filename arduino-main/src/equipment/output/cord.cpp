#include "cord.h"

Cord::Cord (int inputPin, String partID) : EscMotor(inputPin, partID){
  // Set limit and starting values
  maxValue = 1600;
  minValue = 1400;
  stoppedValue=1500;
  currentValue = stoppedValue;
}

int Cord::setValue(int inputValue) {
  // call parent logic (keeps value within preset boundary)
  int value = EscMotor::setValue(inputValue);
  // Return the set value
  return value;
}

void Cord::turnOff(){
  // Switch off in case of emergency
  setValue(stoppedValue);
}