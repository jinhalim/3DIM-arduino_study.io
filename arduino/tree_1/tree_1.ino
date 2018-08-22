int height = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(3, OUTPUT);
  pinMode(2,INPUT);
  delay(3000);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("insert height of tree");
  height = getNumber() -'0';
  Serial.println(height);
}

char getNumber(){
  while(!Serial.available()){
    if(Serial.available()){
      char input = Serial.read();
      return input;     
    }
    return 0;
  }
}

