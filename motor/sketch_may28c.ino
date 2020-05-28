//사용자 입력값에 따른 각도 변화 
#include <Servo.h>

Servo myservo; 
int servopin = 9; // 서브모터 데이터 핀
int angle;  //각도
int val;    //사용자의 입력값을 읽음
void setup() {
  angle = 0;
  myservo.attach(servopin);
  Serial.begin(9600);
  }
void loop() {
  if(Serial.available()>0){ // 사용자가 값을 입력한 경우
    val = Serial.parseInt();  //그 값을 Int로 파싱하여 저장
    Serial.read();  //개행 제거

    switch(val){
      case 6:
        angle += 30;
      case 5:
        angle += 30;
      case 4:
        angle += 30;
      case 3:
        angle += 30;
      case 2:
        angle += 30;
      case 1:
        angle += 30;
        break;
      default:
        angle = 0;
        break;
    } //6인 경우 180도, 5인 경우 150도... 1인경우 30도 
    Serial.println(angle);  //읽은 각도 값 출력
    myservo.write(angle); //각도 변화
    delay(1000);
    angle = 0;  //0 값으로 다시 돌리기 
    myservo.write(angle); //초기상태 복귀
  }
  
}
