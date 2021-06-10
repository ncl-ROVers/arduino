#include "id.h"

ID::ID() {
  // set up ID pins
  pinMode(idPin, INPUT_PULLUP);  // sets the digital pin 13 as output
}

String ID::getId() {
  if(digitalRead(idPin) == LOW){
      return "A";
  }
  else{
      return "B";
  }
}
