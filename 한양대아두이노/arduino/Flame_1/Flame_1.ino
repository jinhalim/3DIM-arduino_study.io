int Flame_sensor = A0;
int Sensor_val;
int G_LED = 6;
int R_LED = 7;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(G_LED,OUTPUT);
  pinMode(R_LED,OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  Sensor_val = analogRead(Flame_sensor);
  if(Sensor_val <= 800){
    digitalWrite(R_LED,HIGH);
    digitalWrite(G_LED,LOW);
  }else{
    digitalWrite(G_LED,HIGH);
    digitalWrite(R_LED,LOW);
  }
}
