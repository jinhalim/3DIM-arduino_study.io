int cnt = 0;
int num[3] = {0,0,0};
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(3,OUTPUT);
  pinMode(2,INPUT);
  randomSeed(analogRead(5));
}

void loop() {
  // put your main code here, to run repeatedly:
  saveNumber();
  printNumber();
  if(num[1] == 7 && num[2]==7 && num[3] == 7 && cnt ==3){
    Serial.println("!!!!!!!JACKPOT!!!!!");
    digitalWrite(3,HIGH);
  }
}
void saveNumber(){
  if(digitalRead(2) == HIGH){
    while(digitalRead(2) == HIGH){
      cnt++;
      if(cnt >3) cnt=0;
      num[cnt] = random(1,10);
      delay(50);
    }
  }
}

void printNumber(){
  if(cnt == 0){
  Serial.println(num[0]);
  Serial.println(num[1]);
  Serial.println(num[2]);
 }
 }
