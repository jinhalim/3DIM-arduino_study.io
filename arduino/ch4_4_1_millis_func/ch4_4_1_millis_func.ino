unsigned long past = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(myTimer(1000)){
    Serial.print("1초마다 실행됩니다. ");
  }
}

boolean myTmer(int waitTime){
  unsigned long now = millis();
  if(now-past >= waitTime){
    past =  now;
    Serial.println(now/1000);
    return true;
  }
  return false;
}

