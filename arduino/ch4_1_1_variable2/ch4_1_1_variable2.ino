void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int val = analogRead(A0);

  if(val >614){
    Serial.println("Arduino : I think HIGH");
  } else if(val < 614 && val >307){
    Serial.println("Arduino : I don't know");
  } else if(val <307){
    Serial.println("Arduino : I think Low");
  }
  delay(500);
}
