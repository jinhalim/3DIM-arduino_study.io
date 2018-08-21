 void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()){
    Serial.write("Arduino : I'm genius \n");
    int val = Serial.read();
    if(val =='0'){
      Serial.write("Arduino : you say");
      Serial.write(val);
    }else if(val == '1'){
      Serial.write("Arduino : you say");
      Serial.write(val);
    }else{
      Serial.write("Arduino : What? ");
    }
    Serial.write("\n");
  }
}
