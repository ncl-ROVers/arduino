#include <Arduino.h>

#ifndef STATUS_H
#define STATUS_H

// Normal case
extern const int NO_ERROR;
extern const int OUTPUTS_HALTED;
extern const int ARM_LEFT_LIMIT_ACTIVATED;
extern const int ARM_RIGHT_LIMIT_ACTIVATED;
extern const int ARDUINO_BOOTING;
extern const int HEARTBEAT;

// Error case
extern const int RECEIVED_VALUE_OUT_OF_RANGE;
extern const int THIS_ARDUINO_IS_NOT_OUTPUT;
extern const int THIS_ARDUINO_IS_NOT_INPUT;
extern const int INVALID_OUTPUT_DEVICE_KEY;
extern const int INVALID_INPUT_DEVICE_KEY;
extern const int CANT_STOP_OUTPUTS_ON_INPUT_ARDUINO;
extern const int JSON_PARSING_FAILED;
extern const int ARDUINO_ID_NOT_SET_UP;
extern const int NO_MESSAGES_RECEIVED_OUTPUTS_HALTED;
extern const int INDEX_NOT_VALID_FOR_SETTING_SENSOR_PARAM;

#endif
