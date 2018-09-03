int Sound_sensor = A0;
int Sensor_val;
int count_clap;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Sensor_val = analogRead(Sound_sensor);
  if(Sensor_val>=28){
    count_clap++;
    Serial.println(count_clap);
    delay(20);
  }
}
