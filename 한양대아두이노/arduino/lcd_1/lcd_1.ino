#include<Wire.h>
#include<LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);
void setup() {
  // put your setup code here, to run once:
  
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Hello, everyone");
  lcd.setCursor(0,1);
  lcd.print("Enjoy Day");
  delay(500);
  lcd.scrollDisplayRight();
  delay(100);
  lcd.scrollDisplayRight();
  delay(200);
  lcd.scrollDisplayRight();
  delay(200);
  lcd.scrollDisplayRight();
  delay(200);
  lcd.scrollDisplayRight();
  delay(200);
  lcd.scrollDisplayRight();
  delay(200);
  lcd.scrollDisplayRight();
  delay(200);
  lcd.scrollDisplayRight();
  delay(200);
  lcd.scrollDisplayRight();
  delay(200);
  lcd.scrollDisplayRight();
  delay(200);
  lcd.scrollDisplayRight();
  delay(200);
  lcd.scrollDisplayRight();
  delay(200);
  lcd.scrollDisplayRight();
  delay(200);
  lcd.scrollDisplayRight();
  delay(200);
  lcd.scrollDisplayRight();
  delay(200);
  lcd.scrollDisplayRight();
  delay(200);
  lcd.scrollDisplayRight();
}
