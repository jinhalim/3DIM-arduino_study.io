#include <SoftwareSerial.h>

SoftwareSerial BTSerial(4,5);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  BTSerial.begin(9600);
  Serial.println("ATcommand");
}

void loop() {
  // put your main code here, to run repeatedly:
  if(BTSerial.available()){
    Serial.write(BTSerial.read());
  }
  if(Serial.available()){
    BTSerial.write(Serial.read());
  }
}
