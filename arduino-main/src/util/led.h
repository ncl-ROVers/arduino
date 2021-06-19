#ifndef LED_H
#define LED_H

#define RED 22     
#define BLUE 24     
#define GREEN 23

#include <Arduino.h>

/*
  The Arduino Nano 33 has an on-board RGB LED which can be used for debugging
*/
class LED{

  public:

    LED();

    void red();
    void green();
    void blue();
    void yellow();
    void purple();
    void cyan();
};

//extern LED led;

#endif
