//가변저항 이용 각도 변화 
#include <Servo.h>

Servo servo; 
int regiPin =0; // A0 아날로그 (가변저항)
int servopin = 9; // 서브모터 데이터 핀

void setup( ) {
  myservo.attach(servopin);
  Serial.begin(9600);
}
void loop() {
  int vol = analogRead(regiPin); // 0-1023 가변저항 값 읽기
  Serial.println(vol);  //저항 값 출력
  vol = map(vol, 130, 600, 0, 180);
  // vol : 읽은 값
  // 130, 600 : 가변저항의 변화 범위
  // 0, 180 : 서보모터 이동각도
  vol = constrain(vol, 0, 180); //제한

  myservo.write(vol);
  Serial.println(vol);  //각도 값 출력
  delay(15);
}
