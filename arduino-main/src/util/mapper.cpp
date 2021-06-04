#include "mapper.h"

void Mapper::mapA(){

    aObjects[0] = new Thruster(0, aIDs[0]);
    aObjects[1] = new Thruster(1, aIDs[1]);
    aObjects[2] = new Thruster(2, aIDs[2]);
    aObjects[3] = new Thruster(3, aIDs[3]);

    // Delays between each device so they initialise separately. This helps to give an auditory signal that everything is connected properly.
    delay(2000);
    aObjects[4] = new Thruster(4, aIDs[4]);

    delay(2000);
    aObjects[10] = new ArmRotation(10, aIDs[10]); // Micro ROV return cord - TODO: Make new class for this

}

void Mapper::mapB(){
    
    bObjects[0] = new Thruster(0, bIDs[0]);
    bObjects[1] = new Thruster(1, bIDs[1]);
    bObjects[2] = new Thruster(2, bIDs[2]);
    bObjects[3] = new Thruster(3, bIDs[3]);

    // Delays between each device so they initialise separately. This helps to give an auditory signal that everything is connected properly.
    delay(2000);
    bObjects[4] = new ArmGripper(4, bIDs[4],54,55); // Gripper motor for the arm
    // TODO adjust limit switch pins
}

void Mapper::instantiateMap(){
    if(thisIsArduino(A_A)){
        mapA();
    }
    else if(thisIsArduino(A_B)){
        mapB();
    }
    else{
        communication.sendStatus(-12);
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
        communication.sendStatus(-8);
        return new Output();
    }
    else if(thisIsArduino(A_B)){
        for(int i = 0; i < B_COUNT; i++){
            if(jsonID == bIDs[i]){
                return bObjects[i];
            }
        }
        // Send error message saying the device was not found
        communication.sendStatus(-8);
        return new Output();
    }
    else {
        // Send error message saying the Arduino was not found
        communication.sendStatus(-6);
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
        communication.sendStatus(-6);
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
        communication.sendStatus(-6);
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
    //         communication.sendStatus(-9);
    //     }
    // }
    // else{
        // Send error message saying the Arduino was not foun
        communication.sendStatus(-7);
        return new Input();
    //}
}

Input* Mapper::getInputFromIndex(int index){
    // if(thisIsArduino(A_B)){
    //     return bObjects[index];
    // }
    // else{
        // Send error message saying the Arduino was not fou
        communication.sendStatus(-7);
        return new Input();
    // }
    // // Send error message saying the device was not found
    // communication.sendStatus(-9);
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
        communication.sendStatus(0);
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
        communication.sendStatus(-10);
    }
    communication.sendStatus(1);
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