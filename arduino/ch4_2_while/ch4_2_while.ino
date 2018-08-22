int cnt = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(2,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(2) == HIGH){
    cnt++;
    if(cnt>3)cnt = 0;
    while(digitalRead(2) == HIGH){
      Serial.println("버튼이 떨어지길 기다리는 중");
    }
    Serial.print("버튼 눌림 횟수: ");
    Serial.println(cnt);
  }
}
