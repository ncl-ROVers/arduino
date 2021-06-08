#ifndef ID_GEN
#define ID_GEN

#include <Arduino.h>

/*
  Class to identify the current arduino based on a hardware switch
*/
class ID{

  private:

  int idPin = 17;

  public:

    ID();

    String getId();
};

#endif
