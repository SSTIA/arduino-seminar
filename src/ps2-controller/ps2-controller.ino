#include <PS2X_lib.h>

bool routine(const unsigned long int t, const unsigned int i);

PS2X ps2x;

int status = 1;

void setup() {
  Serial.begin(57600);

  delay(1000); // the module needs some time to boot up

  while (status != 0) {
    status = ps2x.config_gamepad(12, 11, 10, 8, true, true);
    delay(300);
  }
  //the clock(7) pin, command(2) pin, attention(6) pin and the data(1) pin
  //pressure and rumble feature enabled

  if (status == 0) { //no error
    Serial.println("Controller found & successfully configured");
  }
  else {
    Serial.println("oooops, something went wrong");
  }
}

void loop() {
  if (status != 0) {
    return; //error occured, skip the loop
  }
  if (!routine(50, 0)) { //returns true every 50 milliseconds
    return;
  }
  ps2x.read_gamepad(false, 0); //changing false to true or 0 to some value may
  //cause the motors to vibrate; try them out for yourselves!

  if (ps2x.Button(PSB_PAD_LEFT)) { //returns true if the left button is held down
    Serial.println("Left button held down");
    Serial.print("Force: ");
    Serial.println(ps2x.Analog(PSAB_PAD_RIGHT), DEC);
  }

  if (ps2x.ButtonPressed(PSB_CROSS) ||
      ps2x.NewButtonState(PSB_R2) ||
      ps2x.ButtonReleased(PSB_SELECT)) {
    Serial.println("R2 or X or SELECT pressed/released");
  }

  if(ps2x.Button(PSB_L3) || ps2x.Button(PSB_R3)) { //joystick is pressed
    Serial.print("Joystick Values(Left Y,X; Right Y,X;):");
    Serial.print(ps2x.Analog(PSS_LX), DEC);
    Serial.print(",");
    Serial.print(ps2x.Analog(PSS_LY), DEC);
    Serial.print(",");
    Serial.print(ps2x.Analog(PSS_RX), DEC);
    Serial.print(",");
    Serial.print(ps2x.Analog(PSS_RY), DEC);
    Serial.print('\n');
  }
}

bool routine(const unsigned long int t, const unsigned int i) {
  static unsigned long int timeOfLast[16] = {0}; //this initializes an array to 0
  if (i >= 16) {
    return false;
  }
  unsigned long int timeNow = millis();
  if (timeNow - timeOfLast[i] >= t) {
    timeOfLast[i] = timeNow;
    return true;
  }
  return false;
}
