int cnt = 0; // 스위치 누른횟수

void setup() {
  Serial.begin(9600);
  pinMode(3, OUTPUT);
  pinMode(2, INPUT);
  randomSeed(analogRead(5));
  delay(3000);
}

void loop() {
  int val = random(0, 1024); // val은 정답의 숫자
  cnt = 0;

  Serial.println("Start! Guess (0~1023)");
  Serial.println();

  while(1) {
    while (digitalRead(2) == LOW);
    int guess = guessNumber(); // num은 가변저항 값 (정답 추측값)

    if (guess > val) {
      Serial.println("down");
    } else if (guess < val) {
      Serial.println("up");
    } else {
      Serial.println("You got it !!");
      Serial.print("Your count : ");
      Serial.println(cnt);
      Serial.println();
      delay(2000);
      break;
    }
  }
}

/* 스위치를 한번 누를때, 가변저항값을 읽어서 반환하는 함수 */
int guessNumber() {
  if (digitalRead(2) == HIGH) {
    while (digitalRead(2) == HIGH);
    cnt++;
    int temp = analogRead(0);
    Serial.println(temp);
    delay(50);
    return temp;
  }

}
