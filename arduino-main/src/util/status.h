#include <Arduino.h>

#ifndef STATUS_H
#define STATUS_H

// Normal case
extern const int NO_ERROR = 0;
extern const int OUTPUTS_HALTED = 1;
extern const int ARM_LEFT_LIMIT_ACTIVATED = 2;
extern const int ARM_RIGHT_LIMIT_ACTIVATED = 3;
extern const int ARDUINO_BOOTING = 4;
extern const int HEARTBEAT = 5;

// Error case
extern const int RECEIVED_VALUE_OUT_OF_RANGE = -1;
extern const int THIS_ARDUINO_IS_NOT_OUTPUT = -6;
extern const int THIS_ARDUINO_IS_NOT_INPUT = -7;
extern const int INVALID_OUTPUT_DEVICE_KEY = -8;
extern const int INVALID_INPUT_DEVICE_KEY = -9;
extern const int CANT_STOP_OUTPUTS_ON_INPUT_ARDUINO = -10;
extern const int JSON_PARSING_FAILED = -11;
extern const int ARDUINO_ID_NOT_SET_UP = -12;
extern const int NO_MESSAGES_RECEIVED_OUTPUTS_HALTED = -13;
extern const int INDEX_NOT_VALID_FOR_SETTING_SENSOR_PARAM = -23;

#endif
