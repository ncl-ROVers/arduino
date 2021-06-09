#include "communication.h"

Communication::Communication(){
  // reserve 200 bytes for the inputString:
  //inputString.reserve(200);
  ID idGenerator = ID();
  statusKey = statusKey + idGenerator.getId();
}

void Communication::setStringComplete(bool complete){
  stringComplete = complete;
}

bool Communication::stringIsComplete(){
  return stringComplete;
}

void Communication::recvWithEndMarker() {
    static byte ndx = 0;
    char endMarker = '\n';
    char rc;
    
    while (Serial.available() > 0 && stringComplete == false) {
        rc = Serial.read();

        if (rc != endMarker) {
            receivedChars[ndx] = rc;
            ndx++;
            if (ndx >= numChars) {
                ndx = numChars - 1;
            }
        }
        else {
            receivedChars[ndx] = '\0'; // terminate the string
            ndx = 0;
            stringComplete = true;
        }
    }
}

void Communication::clearInputString(){
  receivedChars[0] = '\0';
}

char* Communication::getInputString(){
  return receivedChars;
}

/* Send response, clear the input buffer and wait for new incoming message */
void Communication::prepareForNewMessage(){
  // Finish by sending all the values
  sendAll();
  // clear the string ready for the next input
  clearInputString();
  setStringComplete(false);
}

void Communication::bufferValue(String device, String incomingValue){
  // buffer a key value pair to be sent with next load
  messageContents+=",\""+device;
  messageContents+="\":\"";
  messageContents+=incomingValue+"\"";
}

void Communication::sendStatus (int status){
  /*MsgPack::Packer p;
  p.to_map(deviceIdKey, arduinoID, statusKey, status);

  Serial.write(p.data(), p.size());*/
  StaticJsonDocument<200> doc;
  doc[deviceIdKey] = arduinoID;
  doc[statusKey] = status;
  serializeMsgPack(doc, Serial);
  Serial.println();
}

void Communication::sendAll(){
  // This is meant to send back data to the Pi

  // TODO actually send back buffered data

  StaticJsonDocument<200> doc;
  doc[deviceIdKey] = arduinoID;
  serializeMsgPack(doc, Serial);
  Serial.println();
}

