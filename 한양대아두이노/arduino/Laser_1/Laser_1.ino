int SW_pin = 7;
int Laser_pin = 2;

int cot = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode(SW_pin,INPUT_PULLUP);
  pinMode(Laser_pin,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(SW_pin)==LOW){
    cot^=true;
    delay(300);
  }
  if(cot ==true){
    digitalWrite(Laser_pin,HIGH);
    digitalWrite(Laser_pin,LOW);
    digitalWrite(Laser_pin,HIGH);
    digitalWrite(Laser_pin,LOW);
  }else{
    digitalWrite(Laser_pin,LOW);
  }
}
