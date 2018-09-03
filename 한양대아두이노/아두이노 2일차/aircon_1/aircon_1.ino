#include "DHT.h"

#define DHTPIN 3
#define DHTTYPE DHT11

int piezopin  = 2;
int aircon = 9;
int notes[] = {4186,4698,5274,5587,6271};

boolean flag = 0;
DHT dht(DHTPIN,DHTTYPE);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dht.begin();
  pinMode(piezopin,OUTPUT);
  pinMode(aircon,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  if(isnan(humidity)||isnan(temperature)){
    Serial.println("Failed to read from DHT sersor");
    return ;
  }
  float discomfortindex = (1.8*temperature)-(0.55*(1-humidity/100.0)*(1.8*temperature -26))+32;
  Serial.println(discomfortindex);

  if(discomfortindex > 77){
    digitalWrite(aircon,HIGH);
    if(flag ==0){
      for(int i = 0;i<5;i++){
        tone(piezopin,notes[i],300);
        delay(150);
      }
      flag =1;
    }
  }
  else{
    digitalWrite(aircon,LOW);
    flag = 0;
  }
  delay(1500);
}
