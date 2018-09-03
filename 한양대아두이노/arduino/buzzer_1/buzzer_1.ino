int melody[] = {262,294,330,349,440,494,523};
void setup()
{
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  digitalWrite(11,HIGH);
  digitalWrite(10,LOW);wswsx
  digitalWrite(9,LOW);
  delay(1000);
  for(int i = 0;i<8;i++){
    tone(8,melody[i],250);
    delay(400);
    noTone(8);
  }
  digitalWrite(11,LOW);
}

void loop()
{

}
