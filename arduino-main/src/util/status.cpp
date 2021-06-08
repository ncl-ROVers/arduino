#include "status.h"

// Normal case
const int NO_ERROR = 0;
const int OUTPUTS_HALTED = 1;
const int ARM_LEFT_LIMIT_ACTIVATED = 2;
const int ARM_RIGHT_LIMIT_ACTIVATED = 3;
const int ARDUINO_BOOTING = 4;
const int HEARTBEAT = 5;

// Error case
const int RECEIVED_VALUE_OUT_OF_RANGE = -1;
const int THIS_ARDUINO_IS_NOT_OUTPUT = -6;
const int THIS_ARDUINO_IS_NOT_INPUT = -7;
const int INVALID_OUTPUT_DEVICE_KEY = -8;
const int INVALID_INPUT_DEVICE_KEY = -9;
const int CANT_STOP_OUTPUTS_ON_INPUT_ARDUINO = -10;
const int JSON_PARSING_FAILED = -11;
const int ARDUINO_ID_NOT_SET_UP = -12;
const int NO_MESSAGES_RECEIVED_OUTPUTS_HALTED = -13;
const int INDEX_NOT_VALID_FOR_SETTING_SENSOR_PARAM = -23;