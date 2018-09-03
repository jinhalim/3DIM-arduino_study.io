void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(13,OUTPUT);
  pinMode(7,INPUT_PULLUP);
  pinMode(3,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(LOW == digitalRead(7)){
    digitalWrite(13,HIGH);
    digitalWrite(3,LOW);
    delay(300);
  }else{
    digitalWrite(13,LOW);
    digitalWrite(3,HIGH);
  }
}
