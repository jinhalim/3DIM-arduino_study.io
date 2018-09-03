#include<Servo.h>
Servo myservo;
int sw =5;
int angle =0;
long bounceStartTime = 0;
long debounce = 50;

void setup() {
  // put your setup code here, to run once:
  pinMode(sw,INPUT_PULLUP);
  myservo.attach(A3);
//  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(sw)  ==  LOW){
    if(bounceStartTime == 0 ){
      bounceStartTime = millis();
    }
    if(millis() - bounceStartTime > debounce){
      angle +=15;
      if(angle >180){
        angle = 0;
      }
      myservo.write(angle);
      bounceStartTime = 0;
      delay(100);
    }
  }
 
}
