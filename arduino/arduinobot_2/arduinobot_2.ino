String fruits[8] = {"apple","tomato","strawberry","pepper","orange","lemon","banana","cucumber"};
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(3,OUTPUT);
  delay(3000);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("think about your fruits and vegetables, Don't talk!!");
  Serial.println("apple, tomato, straberry, pepper,orange,lemon, banana,cucumber");
  Serial.println();
  Serial.println("Is it red? answer y or n");
  if(getAnswer() == 'y'){
    Serial.println("Is it circle? answer y or n");
    if(getAnswer() == 'y'){
      Serial.println("Is it sweet? answer y or n");
      if(getAnswer() == 'y'){
        Serial.print("I got it!,it is");
        Serial.println(fruits[0]);
      }else{
        Serial.print(i got it!);
        Serial.println(fruits[1]);
        }
      }else{
        Serial.println("Is it sweet? answer y or n");
        Serial.println("Is it sweet? answer y or n");
      if(getAnswer() == 'y'){
        Serial.print("I got it!,it is");
        Serial.println(fruits[2]);
      }else{
        Serial.print(i got it!);
        Serial.println(fruits[3]);
        }
        }
    
  }
}
