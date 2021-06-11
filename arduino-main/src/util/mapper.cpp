#include "mapper.h"

void Mapper::mapA(){

    int numberOfThrusters = 4;
    for ( int i = 0; i < numberOfThrusters; i++) {
        aObjects[i] = new Thruster(i + 2, aIDs[i]); // The 8 movement Thrusters
    }

}

void Mapper::mapB(){

    int numberOfThrusters = 4;
    for ( int i = 0; i < numberOfThrusters; i++) {
        bObjects[i] = new Thruster(i + 2, bIDs[i]); // The 8 movement Thrusters
    }

    // Delays between each device so they initialise separately. This helps to give an auditory signal that everything is connected properly.
    delay(2000);

    bObjects[4] = new ArmGripper(6, bIDs[4], 18, 19); // Gripper motor for the arm

    delay(2000);
    
    bObjects[5] = new Cord(7, bIDs[5]); // Micro ROV return cord

    delay(2000);

    bObjects[6] = new Thruster(8, bIDs[6]);

}

void Mapper::instantiateMap(){
    if(thisIsArduino(A_A)){
        mapA();
    }
    else if(thisIsArduino(A_B)){
        mapB();
    }
    else{
        communication.sendStatus(ARDUINO_ID_NOT_SET_UP);
    }
}

Output* Mapper::getOutputFromString(String jsonID){
    if(thisIsArduino(A_A)){
        for(int i = 0; i < A_COUNT; i++){
            if(jsonID == aIDs[i]){
                return aObjects[i];
            }
        }
        // Send error message saying the device was not found
        communication.sendStatus(INVALID_OUTPUT_DEVICE_KEY);
        return new Output();
    }
    else if(thisIsArduino(A_B)){
        for(int i = 0; i < B_COUNT; i++){
            if(jsonID == bIDs[i]){
                return bObjects[i];
            }
        }
        // Send error message saying the device was not found
        communication.sendStatus(INVALID_OUTPUT_DEVICE_KEY);
        return new Output();
    }
    else {
        // Send error message saying the Arduino was not found
        communication.sendStatus(THIS_ARDUINO_IS_NOT_OUTPUT);
        return new Output();
    }
}

Output* Mapper::getOutputFromIndex(int index){
    if(thisIsArduino(A_A)){
        return aObjects[index];
    }
    else if(thisIsArduino(A_B)){
        return bObjects[index];
    }
    else{
        // Send error message saying the Arduino was not found
        communication.sendStatus(THIS_ARDUINO_IS_NOT_OUTPUT);
        return new Output();
    }
}

String Mapper::getOutputString(int index){
    if(thisIsArduino(A_A)){
        return aIDs[index];
    }
    else if(thisIsArduino(A_B)){
        return bIDs[index];
    }
    else{
        // Send error message saying the Arduino was not found
        communication.sendStatus(THIS_ARDUINO_IS_NOT_OUTPUT);
        return "";
    }
}

Input* Mapper::getInputFromString(String jsonID){
    // if(thisIsArduino(A_B)){
    //     for(int i = 0; i < B_COUNT; i++){
    //         if(jsonID == bIDs[i]){
    //             return bObjects[i];
    //         }
    //         // Send error message saying the device was not found
    //         communication.sendStatus(INVALID_INPUT_DEVICE_KEY);
    //     }
    // }
    // else{
        // Send error message saying the Arduino was not foun
        communication.sendStatus(THIS_ARDUINO_IS_NOT_INPUT);
        return new Input();
    //}
}

Input* Mapper::getInputFromIndex(int index){
    // if(thisIsArduino(A_B)){
    //     return bObjects[index];
    // }
    // else{
        // Send error message saying the Arduino was not fou
        communication.sendStatus(THIS_ARDUINO_IS_NOT_INPUT);
        return new Input();
    // }
    // // Send error message saying the device was not found
    // communication.sendStatus(INVALID_INPUT_DEVICE_KEY);
}

int Mapper::getNumberOfInputs(){
    // if(thisIsArduino(A_B)){
    //     return B_COUNT;
    // }
    return 0;
}

int Mapper::getNumberOfOutputs(){
    if(thisIsArduino(A_A)){
        return A_COUNT;
    }
    else if(thisIsArduino(A_B)){
        return B_COUNT;
    }
    return 0;
}

void Mapper::sendAllSensors(){
    int retcode = 0;
    // for(int i = 0; i < B_COUNT; i++){
    //     if (retcode == 0) {
    //         retcode = bObjects[i]->getValue();
    //     } else {
    //         bObjects[i]->getValue();
    //     }
    // }
    if(retcode == 0) {
        communication.sendStatus(NO_ERROR);
    }
    communication.sendAll();
}

void Mapper::stopOutputs(){
    if(thisIsArduino(A_A)){
        for(int i = 0; i < A_COUNT; i++){
            aObjects[i]->turnOff();
            delay(125); // delay 125ms between each thruster to avoid sudden power halt
        }
    }
    else if(thisIsArduino(A_B)){
        for(int i = 0; i < B_COUNT; i++){
            bObjects[i]->turnOff();
            delay(125); // delay 125ms between each thruster to avoid sudden power halt
        }
    }
    else{
        // Send error message saying the Arduino was not found
        communication.sendStatus(CANT_STOP_OUTPUTS_ON_INPUT_ARDUINO);
    }
    communication.sendStatus(OUTPUTS_HALTED);
}

bool Mapper::thisIsArduino(String arduinoIdToCheck){
    return arduinoID == arduinoIdToCheck;
}

bool Mapper::thisIsAnOutputArduino(){
    return thisIsArduino(A_A) || thisIsArduino(A_B);
}

bool Mapper::thisIsAnInputArduino(){
    //return thisIsArduino(A_B);
    return false;
}