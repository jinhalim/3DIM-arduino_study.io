#include <Wire.h>
#include <Mouse.h>

const int MPU_ADDRESS = 0x68; // 센서 주소값
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ; //가속도, 자이로,온도값을 받을 변수


void setup() {
  Wire.begin();//I2C 실행
  Wire.beginTransmission(MPU_ADDRESS); // 센서 주소 설정
  Wire.write(0x6B); // 보내 데이터 저장
  Wire.write(0); // 보낼 데이터
  Wire.endTransmission(true);
  Serial.begin(115200);
  pinMode(5,OUTPUT);

  Mouse.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  Wire.beginTransmission(MPU_ADDRESS);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDRESS, 14, true);

  AcX = Wire.read() << 8 | Wire.read();
  AcY = Wire.read() << 8 | Wire.read();
  AcZ = Wire.read() << 8 | Wire.read();
  Tmp = Wire.read() << 8 | Wire.read();
  GyX = Wire.read() << 8 | Wire.read();
  GyY = Wire.read() << 8 | Wire.read();
  GyZ = Wire.read() << 8 | Wire.read();

  Serial.print("AcX = "); Serial.println(AcX);
  Serial.print("AcY = "); Serial.println(AcY);
  Serial.print("AcZ = "); Serial.println(AcZ);
  
  Serial.print("Tmp = ");
  Serial.println(Tmp/340.00 + 36.53);

  Serial.print("GyX = "); Serial.println(GyX);
  Serial.print("GyY = "); Serial.println(GyY);
  Serial.print("GyZ = "); Serial.println(GyZ);

  if(AcX < -8000){
    Mouse.move(5,0,0);
  }else if(AcX > 8000){
    Mouse.move(-5,0,0);
  }
}
