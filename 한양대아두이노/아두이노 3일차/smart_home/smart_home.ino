
#include <SoftwareSerial.h>
#include<Servo.h>
#include<Wire.h>
#include<LiquidCrystal_I2C.h>
#include<Adafruit_Sensor.h>
#include<DHT.h>
#include<DHT_U.h>

byte temp[] = {
  B00100,
  B01010,
  B01010,
  B01110,
  B01110,
  B11111,
  B11111,
  B01110
};

byte humi[] = {
  B00100,
  B00100,
  B01010,
  B01010,
  B10001,
  B11111,
  B11111,
  B01110
};
byte C[] = {
  B10000,
  B00110,
  B01001,
  B01000,
  B01000,
  B01001,
  B00110,
  B00000
};

int DHTpin = 3;
DHT_Unified dht(3, DHT11);
uint32_t delayMS;

SoftwareSerial BTSerial(4,5);
LiquidCrystal_I2C  TV(0x27,16,2);

Servo blind;

boolean ledR = false;
boolean ledG = false;
boolean ledB = false;
boolean led1R = false;
boolean led1G = false;
boolean led1B = false;
boolean ledGAS = false;
boolean blindOpen = false;
boolean LCD1= false;
boolean LCD2 = false;

byte temperature = 0;
byte humidity  = 0;

int notes[] = {4186,6271};
int tempo = 200;

void setup() {
  // put your setup code here, to run once:
  pinMode(2,OUTPUT);
  blind.attach(6);
  dht.begin();

  for(int i = 7;i<=13;i++){
    pinMode(i,OUTPUT);
  }
  TV.init();
  Serial.begin(9600);
  BTSerial.begin(9600);

  
  TV.createChar((byte)0,temp);
  TV.createChar(1, humi);
  TV.createChar(2,C);
}

void loop() {
  // put your main code here, to run repeatedly:
  int cdsVal = analogRead(A0);
  Serial.println(cdsVal);

  if(BTSerial.available()){
    char c = BTSerial.read();
    if(c == 'a'){
      setLED(8,ledR);
    }
    else if(c == 'b'){
      setLED(9,ledG);
    }
    else if(c == 'c'){
      setLED(10,ledB);
    }
    else if(c == 'd'){
      setLED(7,ledGAS);
    }
    else if(c == 'e'){
      if(!LCD1){
        TV.backlight();
      }
      else{
        TV.noBacklight();
        TV.clear();
      }
      LCD1 = !LCD1;
    }
    else if(c == 'f'){
      TV.clear();
      LCD2 = !LCD2;
    }
     else if(c == 'g'){
      setLED(11,led1R);
    }
     else if(c == 'h'){
      setLED(12,led1G);
    }
     else if(c == 'i'){
      setLED(13,led1B);
    }
  }
  sensors_event_t event;
  dht.temperature().getEvent(&event);

  if(isnan(event.temperature)){
    Serial.println("Error reading temperature!");
  }
  if(LCD2){
    TV.setCursor(0,0);
    TV.print("Today's weather");

    TV.setCursor(0,1);
    TV.write((byte)0);
    TV.print(" ");
    TV.print(event.temperature);
    TV.write(2);
     dht.humidity().getEvent(&event);
     if(isnan(event.relative_humidity)){
      Serial.println("Error reading humidity!");
     }
     TV.setCursor(6,1);
     TV.write(1);
     TV.print(" ");
     TV.print(event.relative_humidity);
     TV.print("%");
     delay(100);
  }
  else{
    TV.clear();
    if(cdsVal >200){
      TV.print("blind open!");
    }
    else{
      TV.print("blind close");
    }
    delay(100);
  }

  if(cdsVal > 450 && !blindOpen){
    blind.attach(6);
    TV.setCursor(0,0);
    blind.write(80);
    for(int i = 0;i<2;i++){
      tone(2, notes[i],tempo);
      delay(100);
    }
    blindOpen = !blindOpen;
    blind.detach();
  }
  else if(cdsVal < 450 && blindOpen){
    blind.attach(6);
    TV.setCursor(0,0);
    blind.write(180);
     blindOpen = !blindOpen;
     delay(200);
    blind.detach();
  }
}

void setLED(int pin, boolean &LED){
  if(!LED){
    digitalWrite(pin,HIGH);
  }
  else{
    digitalWrite(pin,LOW);
  }
  LED = !LED;
}
