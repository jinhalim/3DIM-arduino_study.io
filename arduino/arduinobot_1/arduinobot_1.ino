void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(3,OUTPUT);
  delay(3000);  
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("input your number");
//  getAnswer2();
Serial.println(getAnswer1());
}

char getAnswer1(){
  while(!Serial.available());
    if(Serial.available()){
      char input  = Serial.read();
      return input;
    }
    return 0;
}
void getAnswer2(){
  while(!Serial.available());
    if(Serial.available()){
      char input  = Serial.read();
      Serial.println(input);
    }
}
