#include <SoftwareSerial.h>

SoftwareSerial BTSerial(4,5);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  BTSerial.begin(9600);
  pinMode(8,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(6,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(BTSerial.available()){
    byte data = BTSerial.read();
    Serial.write(data);
    if(data == '1'){
      digitalWrite(8,HIGH);
    }
    else if(data == '2'){
      digitalWrite(8,LOW);
    }
    else if(data =='3'){
      digitalWrite(7,HIGH);
    }
    else if(data =='4'){
      digitalWrite(7,LOW);
    }
    else if(data =='5'){
      digitalWrite(6,HIGH);
    }
    else if(data =='6'){
      digitalWrite(6,LOW);
    }
  }
  if(Serial.available()){
    BTSerial.write(Serial.read());
  }
}
