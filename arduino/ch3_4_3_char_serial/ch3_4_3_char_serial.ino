void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(3,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()){
    char data = Serial.read();
    if(data == 97) digitalWrite(3,HIGH);
    else digitalWrite(3,LOW);
    int data2 = data;
    Serial.println(data2);
    Serial.write(data2);
    Serial.println();
  }
}
