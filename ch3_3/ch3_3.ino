void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()){
    Serial.write("arduino : Hi, I'm Arduino");
    Serial.write("\n");

    Serial.write("you : ");
    Serial.write(Serial.read());
    Serial.write("\n");
    }
}
