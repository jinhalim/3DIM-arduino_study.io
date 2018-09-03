#include<Servo.h>

int servo =6;
int piezopin = 2;
int notes[] = {4186,6271};
int tempo =200;
int flag  = 1;

Servo blind;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(piezopin,OUTPUT);
  blind.attach(servo);
  blind.write(80);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  int cdsVal = analogRead(A0);
  Serial.println(cdsVal);
  if(cdsVal <400){
    if(flag==0){
      for(int i =0 ;i<2;i++){
        tone(piezopin,notes[i],tempo);
        delay(100);
      }
      blind.write(180);
      flag = 1;
    }
  }
    else{
      if(flag == 1){
        blind.write(80);
        flag = 0;
      }
    }
    delay(100);
  }
