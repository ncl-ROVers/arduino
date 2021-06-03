#include <EEPROM.h>

void setup() {
  
  // initialize the LED pin as an output.
  pinMode(13, OUTPUT);
  // turn the LED off before success
  digitalWrite(13, LOW);
  // Mark this as Arduino O for Output
  EEPROM.write(0, 'O'); 
  // turn the LED on when we're done
  digitalWrite(13, HIGH);

  Serial.begin(115200);
  Serial.print("ID is ");
  Serial.println(String(char(EEPROM.read(0))));
}

void loop() {
  /** Empty loop. **/
}
