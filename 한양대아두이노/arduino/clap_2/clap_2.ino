int Sound_sensor = A0;
int Sensor_val;
int count_clap;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(7,OUTPUT);
  pinMode(6,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  Sensor_val = analogRead(Sound_sensor);
  if(Sensor_val>=28){
    count_clap++;
    Serial.println(count_clap);
    digitalWrite(7,HIGH);
    digitalWrite(6,LOW);
    delay(100);
    digitalWrite(6,HIGH);
    digitalWrite(7,LOW);
    delay(20);
  }
}
