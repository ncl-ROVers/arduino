#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <Arduino.h>
#include <ArduinoJson.h> // JSON encoding and decoding
#include <MsgPack.h>
#include "../util/constants.h"
#include "../util/id.h"

#define ELEMENTCOUNT 20
#define MSGPACK_DEBUGLOG_ENABLE // Enables debugging to the serial port

/* ==========================Communication========================== */

/*
  The communication class is the implementation of the method of communicating with the Raspberry Pi.
  External methods can buffer data to be sent to the Pi, and this class will handle conversion to JSON and other formatting.
*/
class Communication{
  private:
    String key[ELEMENTCOUNT];
    String value[ELEMENTCOUNT];
    bool stringComplete = false;  // whether a full JSON string has been received
    //String inputString = "";         // a String to hold incoming data
    static const byte numChars = 200; // Only expecting 200 input chars
    char receivedChars[numChars];   // an array to store the received data
    String statusKey = "S";
    String deviceIdKey = "ID";
    String messageContents = "";

  public:
    Communication();

    /*
      Whether full string had been received
    */
    void setStringComplete(bool complete);

    /*
      Whether full string had been received
    */
    bool stringIsComplete();

    /*
      The latest JSON string read from the serial port
      Source: https://forum.arduino.cc/t/serial-input-basics-updated/382007
    */
    void recvWithEndMarker();

    /*
      Clear input string ready to receive new one
    */
    void clearInputString();

    /*
      The latest JSON string read from the serial port
    */
    char* getInputString();

    /*
      Clear input string etc in anticipation of new incoming message
    */
    void prepareForNewMessage();

    /*
      Buffer a key:value pair to be sent to the Pi
    */
    void bufferValue(String device, String incomingValue);

    /*
      Send the current status of this Arduino (e.g. booting)
    */
    void sendStatus (int status);

    /*
      Send all buffered values to the Pi
    */
    void sendAll();
};

extern Communication communication; // Object to handle communication between Arduino and Pi

#endif /* COMMUNICATION_H */
