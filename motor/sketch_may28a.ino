//간단하게 서브모터 돌리기
#include <Servo.h>

int servoPin = 9; //5V, GND와는 별개로 서브모터에 들어가는 데이터 핀 번호
Servo servo;
int angle = 0;  //각도값

void setup() {
  // put your setup code here, to run once:
  servo.attach(servoPin);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(angle = 0; angle < 180; angle++)
  {
    servo.write(angle);
    delay(15);
  }
  // now scan back from 180 to 0 degrees
  for(angle = 180; angle > 0; angle--)
  {
    servo.write(angle);
    delay(15);
  } 
}
