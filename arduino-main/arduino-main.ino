/**
 * @file    arduino-main
 *
 * @brief   Embedded software for a marine ROV
 *
 * @author  Antoine Petty, Joe Smith
 *          Adapted from arduino-main-2019 by Antoine Petty, Mark Hazell, Adam Foy, Paweł Czaplewski
 *          
 * Contact: antoine@antoinepetty.co.uk
 *
 */

/* ============================================================ */
/* ======================Import libraries====================== */
/* ============================================================ */
#include <ArduinoJson.h> // JSON encoding and decoding
#include <MsgPack.h> // Msgpack packing and unpacking

// Custom ROV Libaries
#include "./src/util/status.h"
#include "./src/communication/communication.h"
#include "./src/util/constants.h"
#include "./src/equipment/input/input.h"
#include "./src/equipment/output/output.h"
#include "./src/util/mapper.h"
#include "./src/util/id.h"
#include "./src/util/led.h"

/* ============================================================ */
/* ==================Set up global variables=================== */
/* ============================================================ */


unsigned long lastMessage; // The timestamp of when the last message was received
unsigned long lastHB; // The timestamp of when the last heartbeat was sent
bool safetyActive = false; // Whether output devices are stopped because no data was received

Mapper mapper; // Lightweight replacement for a map/dictionary structure to map JSON IDs to objects representing devices.

Communication communication; // Object to allow for communication with the Raspberry Pi over UART

LED led; // Object to allow for communication with the Raspberry Pi over UART

/* ============================================================ */
/* =======================Setup function======================= */
/* =============Runs once when Arduino is turned on============ */
void setup() {
  led.red();
  
  // Wait for serial connection before starting
  while (!Serial);
  led.yellow();
  
  ID idGenerator = ID();
  arduinoID = "A_" + idGenerator.getId();

  // initialize serial:
  Serial.begin(115200);
  communication.sendStatus(ARDUINO_BOOTING);
  led.purple();
  // Map inputs and outputs based on which Arduino this is
  mapper.instantiateMap();

  communication.sendAll();
  communication.sendStatus(NO_ERROR);
  led.green();
}

/* ============================================================ */
/* =======================Loop function======================== */
/* ======Runs continuously after setup function finishes======= */
void loop() {
  // parse the string when a newline arrives:
  if (communication.stringIsComplete()) {
    led.purple();
    StaticJsonDocument<200> root;
    DeserializationError err = deserializeMsgPack(root, communication.getInputString());
    // Test if parsing succeeds.
    if (err) {
      communication.sendStatus(JSON_PARSING_FAILED);
      communication.prepareForNewMessage();
      return;
    }

    safetyActive = false; // Switch off auto-off because valid message received

    // Act on incoming message accordingly
    if(mapper.thisIsAnOutputArduino()){
      handleOutputCommands(root);
    }
    else if (mapper.thisIsAnInputArduino()){
      handleSensorCommands(root);
    }
    else{
      communication.sendStatus(ARDUINO_ID_NOT_SET_UP);
    }
    communication.prepareForNewMessage();

    updateMostRecentMessageTime();
    led.green();
  }

  // Code to run all the time goes here:

  if(mapper.thisIsAnOutputArduino()){
    // This Arduino is for outputting
    disableOutputsIfNoMessageReceived(safetyShutoffTimeMs);
  }
  else if(mapper.thisIsAnInputArduino()){
    // Output all sensor data
      mapper.sendAllSensors();
  }

  // Heartbeat if no message recieved in this time
  if(millis() - lastMessage > heartbeatTimeMs && millis() - lastHB > heartbeatTimeMs){ //timeout to trigger heartbeat to be sent
    lastHB = millis();
    communication.sendStatus(HEARTBEAT);
    if(!safetyActive){
      led.yellow();
    }
    
  }
  else{
    communication.sendStatus(NO_ERROR);
  }

  // Call this method to process incoming serial data.
  // On Arduino Mega this is called by default each loop, but on Arduino Nano 33 you have to call it manually.
  //serialEvent();
  communication.recvWithEndMarker();

}

/* Handle each control value from the incoming JSON message */
void handleOutputCommands(StaticJsonDocument<200> doc){

  JsonObject obj = doc.as<JsonObject>();
  for (JsonPair p : obj) {
    mapper.getOutputFromString(p.key().c_str())->setValue(p.value().as<int>());
  }

}

/* Handle each control value from the incoming JSON message (Ard_I Only) */
void handleSensorCommands(StaticJsonDocument<200> root){
  // TODO replace this?
  /*
  for(int i = 0; i < root.length(); i++){
    JSONVar current = root[i];
    int setValue = mapper.getInputFromIndex(i)->setValue(current.value);
    
    // Sonar has custom range settings.
    if(current.keys == "Sen_Sonar_Start"){
      setValue = mapper.getInputFromString("Sen_Sonar")->setParam(1,current.value);
    }
    else if(current.keys == "Sen_Sonar_Len"){
      setValue = mapper.getInputFromString("Sen_Sonar")->setParam(2,current.value);
    }

    if(setValue == current.value) {
      communication.sendStatus(NO_ERROR);
    }
  }
  */
}

/* If no valid message has been received within a sensible amount of time, switch all devices off for safety */
void disableOutputsIfNoMessageReceived(int timeInMs){
  if(timeSinceLastMessageExceeds(timeInMs) && !safetyActive){ // 1 second limit
    led.red();
    mapper.stopOutputs();
    safetyActive = true; //activate safety
    communication.sendStatus(NO_MESSAGES_RECEIVED_OUTPUTS_HALTED);
    communication.sendAll();
  }
}

/* Check if it's been a certain amount of time since the last valid message was received */
bool timeSinceLastMessageExceeds(int timeInMs){
  return millis() - lastMessage > timeInMs;
}

/* Update time last valid message received */
void updateMostRecentMessageTime(){
  lastMessage = millis();
}
