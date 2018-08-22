#include <TimerThree.h>

boolean SW = false;
void blinkLED(){
    SW = !SW;
   digitalWrite(3,SW);
  }
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(3,OUTPUT);
  Timer3.initialize(3000000);
  Timer3.attachInterrupt(blinkLED);
  Timer3.pwm(5,10);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("1초마다 실행될 문구");
  delay(1000);
}
