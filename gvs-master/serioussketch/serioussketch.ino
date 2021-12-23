#include <DueTimer.h>
// #include <MPU9250.>




void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial3.begin(115200);
  

}

void loop() {

  if (Serial.available()) 
  {

    Serial.println(Serial.read());
  }

}