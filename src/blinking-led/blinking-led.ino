unsigned long int timeOfLastToggle = 0;
bool isOn = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long int timeNow = millis();
  //millis() returns the time elapsed since Arduino was turned on
  //in milliseconds;
  if ( timeNow - timeOfLastToggle >= 1000) {
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
