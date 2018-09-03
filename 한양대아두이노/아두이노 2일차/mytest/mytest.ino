#include "DHT.h"
#include <LiquidCrystal_I2C.h>
#define DHTPIN 3
#define DHTTYPE DHT11

LiquidCrystal_I2C lcd(0x27,16,2);

int piezopin  = 2;
int aircon = 9;
int notes[] = {4186,4698,5274,5587,6271};
int buttonpin = A0;

int button = 0;
int flag2 = 0;

float discomfortindex;
boolean flag = 0;
DHT dht(DHTPIN,DHTTYPE);

void auto_d(){
  if(discomfortindex > 80){
    digitalWrite(aircon,HIGH);
    if(flag ==0){
      for(int i = 0;i<5;i++){
        tone(piezopin,notes[i],300);
        delay(150);
      }
      lcd.clear();
      lcd.print("aircon:");
      lcd.print("ON");
      lcd.print("(auto)");
        lcd.setCursor(0,1);
      lcd.print("index:");
  lcd.print(discomfortindex);
  
      flag =1;
    }
  }
  else{
    digitalWrite(aircon,LOW);
   if(flag == 1){
      for(int i = 5;i>0;i--){
        tone(piezopin,notes[i],300);
        delay(150);
      }
    }
    lcd.clear();
    lcd.print("aircon:");
    lcd.print("OFF");
    lcd.print("(auto)");
      lcd.setCursor(0,1);
    lcd.print("index:");
  lcd.print(discomfortindex);
    flag = 0;
  }
  delay(1500);
}

void noauto(){
   if(analogRead(A0) == 0){
    digitalWrite(aircon,HIGH);
    if(flag ==0){
      for(int i = 0;i<5;i++){
        tone(piezopin,notes[i],300);
        delay(150);
      }
      lcd.clear();
      lcd.print("aircon:");
      lcd.print("ON");
 
        lcd.setCursor(0,1);
        lcd.print("index:");
       lcd.print(discomfortindex);
  
      flag =1;
    }
    }
    else{
    digitalWrite(aircon,LOW);
    if(flag == 1){
      for(int i = 5;i>0;i--){
        tone(piezopin,notes[i],300);
        delay(150);
      }
    }

    lcd.clear();
    lcd.print("aircon:");
    lcd.print("OFF");

      lcd.setCursor(0,1);
    lcd.print("index:");
  lcd.print(discomfortindex);
    flag = 0;
  }
  delay(1500);
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dht.begin();
  pinMode(piezopin,OUTPUT);
  pinMode(aircon,OUTPUT);
  lcd.init();
  
  
}

void loop() {
  
  lcd.backlight();
  lcd.setCursor(0,0);
  
  // put your main code here, to run repeatedly:
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  if(isnan(humidity)||isnan(temperature)){
    Serial.println("Failed to read from DHT sersor");
    return ;
  }
   discomfortindex = (1.8*temperature)-(0.55*(1-humidity/100.0)*(1.8*temperature -26))+32;
  Serial.println(discomfortindex);
  Serial.println(analogRead(buttonpin));
  if(analogRead(buttonpin) > 0 && button == 0 ){
    auto_d();
  }
  else if(analogRead(buttonpin) == 0 && button == 0){ 
    noauto();
    button = 1;
  }
  else if(analogRead(buttonpin) == 0 && button == 1){
    noauto();
    button=0;
  }else{
    noauto();
  }
  }
  
