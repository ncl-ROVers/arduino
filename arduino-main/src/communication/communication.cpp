#include "communication.h"

#include <MsgPack.h>

Communication::Communication(){
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
}

void Communication::setStringComplete(bool complete){
  stringComplete = complete;
}

bool Communication::stringIsComplete(){
  return stringComplete;
}

void Communication::setInputString(String inputStr){
  inputString = inputStr;
}

String Communication::getInputString(){
  return inputString;
}

void Communication::bufferValue(String device, String incomingValue){
  // buffer a key value pair to be sent with next load
  messageContents+=",\""+device;
  messageContents+="\":\"";
  messageContents+=incomingValue+"\"";
}

void Communication::sendStatus (int status){
  MsgPack::Packer p;
  p.to_map(deviceIdKey, arduinoID, statusKey, status);

  Serial.write(p.data(), p.size());
}

void Communication::sendAll(){
  // This is meant to send back data to the Pi
  // Disabled for 2021 as no sensor data is expected

  /*Serial.print("{\""+deviceIdKey+"\":\"");
  Serial.print(arduinoID);
  Serial.print("\"");
  Serial.print(messageContents);
  Serial.println("}");
  messageContents="";*/
}

