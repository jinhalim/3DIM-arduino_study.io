int pushValue = 0;
int cnt = 3;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(3,OUTPUT);
  pinMode(2, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(2) == HIGH && cnt <5){
    pushValue += cnt;
    if(pushValue > 255 ) pushValue = 0;
    Serial.println(pushValue);
  }
  delay(10);
  analogWrite(3,pushValue);
}
