unsigned long past = 0;
const int MY_DELAY_TIME = 1000;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long now = millis();
  if(now - past >= MY_DELAY_TIME){
    past = now;
    Serial.print("Time is gone ");
    Serial.println(now/100);
  }
}
