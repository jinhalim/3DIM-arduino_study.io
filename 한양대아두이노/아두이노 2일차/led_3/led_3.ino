int infrared = 3;
int led =6 ;

void setup() {
  // put your setup code here, to run once:
  pinMode(infrared,INPUT);
  pinMode(led,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int state =digitalRead(infrared);
  Serial.print("Infrared = ");
  Serial.println(state);

  if(state == 0 ){
    digitalWrite(led,HIGH);
    digitalWrite(5,LOW);
    Serial.println("Warning");
    
  }else{
    digitalWrite(led,LOW);
    digitalWrite(5,HIGH);
    Serial.println("safe");
    }
    delay(200);
}
