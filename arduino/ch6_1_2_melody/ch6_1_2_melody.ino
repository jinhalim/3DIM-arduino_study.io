#include<TimerThree.h>

const int melody[] = {
  262,294,330,349,392,440,494,523,
  };
void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
for(int i = 0;i<8;i++){
  Timer3.initialize(1000000/melody[i]);
  Timer3.pwm(5,10);
  delay(500);
  }
}
