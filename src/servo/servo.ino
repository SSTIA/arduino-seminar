#include <Servo.h>
Servo myServo; //create an object;

unsigned long int timeOfLastToggle = 0;
bool isOn = false;

void setup() {
  // put your setup code here, to run once:
  myServo.attach(9);
  Serial.begin(115200); //The baud rate must match!
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long int timeNow = millis();
  //millis() returns the time elapsed since Arduino was turned on
  //in milliseconds;
  if ( timeNow - timeOfLastToggle >= 1000) {
    timeOfLastToggle = timeNow;
    if (isOn) {
      myServo.write(45);
      Serial.println("45 degrees;");
      isOn = false;
    } else {
      myServo.write(135);
      Serial.println("135 degrees;");
      isOn = true;
    }
  }
}
