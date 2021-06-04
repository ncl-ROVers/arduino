#include "mapper.h"

void Mapper::mapO(){
    int numberOfThrusters = 8;
    for ( int i = 0; i < numberOfThrusters; i++) {
        oObjects[i] = new Thruster(i, oIDs[i]); // The 8 movement Thrusters
    }
    // Delays between each device so they initialise separately. This helps to give an auditory signal that everything is connected properly.
    delay(2000);
    oObjects[8] = new ArmGripper(8, oIDs[8],54,55); // Gripper motor for the arm
    delay(2000);
    oObjects[9] = new Thruster(9, oIDs[9]); // The 8 movement Thrusters
    delay(2000);
    oObjects[10] = new ArmRotation(10, oIDs[10]); // Micro ROV return cord - TODO: Make new class for this
}

void Mapper::mapI(){
    // Map and initialise sensors
    // Currently no sensors specified
}

void Mapper::instantiateMap(){
    if(thisIsArduino(A_O)){
        mapO();
    }
    else if(thisIsArduino(A_I)){
        mapI();
    }
    else{
        communication.sendStatus(-12);
    }
}

Output* Mapper::getOutputFromString(String jsonID){
    if(thisIsArduino(A_O)){
        for(int i = 0; i < O_COUNT; i++){
            if(jsonID == oIDs[i]){
                return oObjects[i];
            }
        }
        // Send error message saying the device was not found
        communication.sendStatus(-8);
        return new Output();
    }
    else{
        // Send error message saying the Arduino was not found
        communication.sendStatus(-6);
        return new Output();
    }
}

Output* Mapper::getOutputFromIndex(int index){
    if(thisIsArduino(A_O)){
        return oObjects[index];
    }
    else{
        // Send error message saying the Arduino was not found
        communication.sendStatus(-6);
        return new Output();
    }
}

String Mapper::getOutputString(int index){
    if(thisIsArduino(A_O)){
        return oIDs[index];
    }
    else{
        // Send error message saying the Arduino was not found
        communication.sendStatus(-6);
        return "";
    }
}

Input* Mapper::getInputFromString(String jsonID){
    if(thisIsArduino(A_I)){
        for(int i = 0; i < I_COUNT; i++){
            if(jsonID == iIDs[i]){
                return iObjects[i];
            }
            // Send error message saying the device was not found
            communication.sendStatus(-9);
        }
    }
    else{
        // Send error message saying the Arduino was not foun
        communication.sendStatus(-7);
        return new Input();
    }
}

Input* Mapper::getInputFromIndex(int index){
    if(thisIsArduino(A_I)){
        return iObjects[index];
    }
    else{
        // Send error message saying the Arduino was not fou
        communication.sendStatus(-7);
        return new Input();
    }
    // Send error message saying the device was not found
    communication.sendStatus(-9);
}

int Mapper::getNumberOfInputs(){
    if(thisIsArduino(A_I)){
        return I_COUNT;
    }
    return 0;
}

int Mapper::getNumberOfOutputs(){
    if(thisIsArduino(A_O)){
        return O_COUNT;
    }
    return 0;
}

void Mapper::sendAllSensors(){
    int retcode = 0;
    for(int i = 0; i < I_COUNT; i++){
        if (retcode == 0) {
            retcode = iObjects[i]->getValue();
        } else {
            iObjects[i]->getValue();
        }
    }
    if(retcode == 0) {
        communication.sendStatus(0);
    }
    communication.sendAll();
}

void Mapper::stopOutputs(){
    if(thisIsArduino(A_O)){
        for(int i = 0; i < O_COUNT; i++){
            oObjects[i]->turnOff();
            delay(125); // delay 125ms between each thruster to avoid sudden power halt
        }
    }
    else{
        // Send error message saying the Arduino was not found
        communication.sendStatus(-10);
    }
    communication.sendStatus(1);
}

bool Mapper::thisIsArduino(String arduinoIdToCheck){
    return arduinoID == arduinoIdToCheck;    
}

bool Mapper::thisIsAnOutputArduino(){
    return thisIsArduino(A_O);
}

bool Mapper::thisIsAnInputArduino(){
    return thisIsArduino(A_I);
}