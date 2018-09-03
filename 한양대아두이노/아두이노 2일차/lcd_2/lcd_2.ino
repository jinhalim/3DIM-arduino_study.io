#include<Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C TV(0x27,16,2);
int piezopin = 2;
int irpin = 9;
int flag;
int notes[]={6900,4906,6900,4906,6900};
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(piezopin,OUTPUT);
  pinMode(irpin,INPUT);

  TV.init();
  TV.backlight();
  TV.setCursor(0,0);
  TV.print("Looking TV...........");
}

void loop() {
  // put your main code here, to run repeatedly:
  int IRVal = digitalRead(irpin);
  Serial.println(IRVal);

  if(IRVal == 0){
    if(flag == 0 ){
      for(int i =0;i<5;i++){
        tone(piezopin, notes[i],150);
        delay(150);
      }
      flag = 1;
    }
    TV.noBacklight();
  }
  else{
    TV.backlight();
    flag = 0;
  }
  delay(100);
  }
