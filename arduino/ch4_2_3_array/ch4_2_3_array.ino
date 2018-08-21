char row1[6] = {' ','/',')',' ','/',')'};
char row2[6] = {40,45,95,45,42,41};
char row3[7] = "(>0<)";
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()){
    Serial.read();
    for(int i =0;i<6;i++){
     Serial.print(row1[i]);
     }
     Serial.print('\n');
     Serial.println(row2);
     Serial.println(row3);
  }
}
