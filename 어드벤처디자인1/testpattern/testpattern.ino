#include <SoftwareSerial.h>
#include<random.h>
SoftwareSerial BTSerial(2,3);

void looppattern(int speed,int count){
  for(int i = 0;i<count;i++){
    analogWrite(A_pin1,0);
    analogWrite(A_pin2,speed);
    analogWrite(B_pin1,0);
    analogWrite(B_pin1,speed);
  }
  delay(450);
}
void setup() {
  // put your setup code here, to run once:
  BTSerial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  char num;
  int count;
  num = BTSerial.read();
  count = random(5,20);
  switch(num){
    case '1':
      looppattern(10,5);
      break;
    case '2':
    case '3':
    case '4':
    
  }
}
