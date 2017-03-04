void blink_led(unsigned long int timeNow, unsigned long int cycle);

struct Config {
  unsigned long int cycle; //BEST PRACTICE: Put all the things that need to be
  //stored inside a struct!
};

Config config;

#include "EEPROMAnything.h"
void setup() {
  Serial.begin(115200);
  EEPROM_readAnything(0, config); //of course there's a catch here;
  //at the first time there's only garbage in the EEPROM,
  //but we needn't care too much about it.
  pinMode(13, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) { //has input
    char c = (char) Serial.read(); //the input may go in from a Bluetooth module
    // or the Serial Monitor
    switch (c) {
      case 'S': //shorter cycle
      config.cycle = 1000;
      EEPROM_writeAnything(0, config);
      break;
      case 'L': //longer cycle
      config.cycle = 3000;
      EEPROM_writeAnything(0, config);
      break;
    }
  }
  blink_led(millis(), config.cycle);
}

void blink_led(unsigned long int timeNow, unsigned long int cycle)
{
  static unsigned long int timeOfLastToggle = 0; //this works like a global variable
  //it's only set to 0 for once.
  static bool isOn = false;
  if ( timeNow - timeOfLastToggle >= cycle) {
    timeOfLastToggle = timeNow;
    if (isOn) {
      digitalWrite(13, LOW); //turn off the LED
      isOn = false;
    } else {
      digitalWrite(13, HIGH); //turn on the LED
      isOn = true;
    }
  }
}
