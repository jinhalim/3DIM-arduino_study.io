int cnt = 0;

void setup() {
  Serial.begin(9600);
  pinMode(3, OUTPUT);
  pinMode(2, INPUT);
  randomSeed(analogRead(5));
  delay(3000);
}

void loop() {
  // put your main code here, to run repeatedly:
int val =  random(0,1024);
while(digitalRead(2) == LOW);
int num = guessNumber();
}

int guessNumber(){
  if(digitalRead(2) == HIGH){
    while(digitalRead(2) == HIGH);
    cnt++;
    int temp = analogRead(0);
    Serial.println(temp);
    delay(50);
    return temp;
  }
}

