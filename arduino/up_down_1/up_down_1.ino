int cnt = 0;

void setup() {
  Serial.begin(9600);
  pinMode(3, OUTPUT);
  pinMode(2, INPUT);
  randomSeed(analogRead(5));
  delay(3000);
}

void loop() {
  if (digitalRead(2) == HIGH) {
    while(digitalRead(2) == HIGH){
      cnt++;
      int temp = analogRead(0);
      Serial.println(temp);
      delay(50);
    }
//    digitalWrite(3, HIGH);
  } else {
    digitalWrite(3, LOW);
  }
}
