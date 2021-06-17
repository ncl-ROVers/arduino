#ifndef MBED_ESC_MOTOR
#define MBED_ESC_MOTOR

#include <Arduino.h>
#include <mbed.h>
#include <pinDefinitions.h>
#include "output.h"
#include "../../communication/communication.h"

/*
  The EscMotor class represents any motor controlled using PWM.
  It takes values between 1100 and 1900 to control the rotation speed and direction of the motor.
*/
class MbedEscMotor: public Output {

  protected:
    // Represents a motor controlled by an ESC
    mbed::PwmOut* pwm;

  public:

    MbedEscMotor (int inputPin, String partID);

    int setValue(int inputValue);

    void turnOff();
};

#endif