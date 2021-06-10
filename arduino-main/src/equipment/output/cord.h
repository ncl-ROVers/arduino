#ifndef CORD_H
#define CORD_H

#include <Arduino.h>
#include "output.h"
#include "../../communication/communication.h"
#include "genericEscMotor.h"


/*
  The Cord class represents a BlueRobotics M100 or M200 PWM motor.
  This is similar to most of the other ESC classes
*/
class Cord: public EscMotor {

  protected:

  public:

    Cord (int inputPin, String partID);

    int setValue(int inputValue);

    void turnOff();
};

#endif