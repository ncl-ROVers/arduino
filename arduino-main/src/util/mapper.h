#define A_COUNT 4 // Number of devices attached to Arduino A
#define B_COUNT 7 // Number of devices attached to Arduino B

#ifndef MAPPER_H
#define MAPPER_H

#include <Arduino.h>
#include "../equipment/input/input.h"
#include "../equipment/output/output.h"
#include "../equipment/output/thruster.h"
#include "../equipment/output/armgripper.h"
#include "../equipment/output/armrotation.h"
#include "../equipment/output/cord.h"
#include "../equipment/output/mbedEsc.h"


/* ==========================Mapper========================== */
/*
  The Mapper class is a lightweight replacement for a map/dictionary structure.
  Each Arduino ID has its own array of Strings for JSON IDs, which correspond to Input or Output objects to control devices.
*/
class Mapper {
  private:

    // Enclosure 1
    Output* aObjects[A_COUNT];
    String aIDs[A_COUNT] = {
      "T_VFP", "T_VFS", "T_VAP", "T_VAS"
      };

    // Enclosure 2
    Output* bObjects[B_COUNT];
    String bIDs[B_COUNT] = {
      "T_HFP", "T_HFS", "T_HAP", "T_HAS", 
      "M_G", "M_C", "T_M"
      };

    /*
      Assign JSON IDs to devices on this Arduino
    */
    void mapA();

    /*
      Assign JSON IDs to sensors on this Arduino
    */
    void mapB();

  public:

    /*
      Assign JSON IDs to devices on this Arduino
    */
    void instantiateMap();

    /*
      Get the object representing an output device connected to this Arduino with the specified JSON ID
     */
    Output* getOutputFromString(String jsonID);

    /*
      Get the object representing an output device connected to this Arduino with the index of its position within the output array
    */
    Output* getOutputFromIndex(int index);

    /*
      Get the string associated with the output from a given index
      */
    String getOutputString(int index);

    /*
      Get the object representing a senor connected to this Arduino with the specified JSON ID
     */
    Input* getInputFromString(String jsonID);

    /*
      Get the object representing a sensor connected to this Arduino with the index of its position within the input array
    */
    Input* getInputFromIndex(int index);



    /*
      Get the number of sensors
     */
    int getNumberOfInputs();

    /*
      Get the number of output devices connected to this Arduino
     */
    int getNumberOfOutputs();

    /*
      Read data from all sensors and send this to the Pi
     */
    void sendAllSensors();

    /*
      Switch off all devices attached to this Arduino.
      This is primarily a safety feature to be used if no control signals are being received.
     */
    void stopOutputs();

    /*
      Returns whether this is an output-only Arduino
    */
    bool thisIsAnOutputArduino();

    /*
      Returns whether this is an input-only Arduino
    */
    bool thisIsAnInputArduino();

    /*
      Returns whether this is a specified Arduino
    */
    bool thisIsArduino(String arduinoIdToCheck);

};

#endif /* MAPPER_H */
