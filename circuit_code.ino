int cnt;	//스위치가 눌린 횟수를 저장

int resistPin = A0;	//가변저항값을 읽을 Pin번호
int photoPin = A1; //조도센서 저항값을 읽을 Pin번호

int sw = 3; //스위치 누름을 판단하기 위한 pin번호

int LED_A = 12;
int LED_B1 = 11;
int LED_B2 = 10;
int LED_B3 = 9;
int LED_C = 8;
//각각의 LED에 대한 pin번호 설정

int getResist(int);	//저항값 읽는 함수
void first();
void second();
void third();
void fourth();		//각각의 루틴에 대한 함수
//함수 선언

void setup()
{
  cnt = 0;
  
  pinMode(resistPin, INPUT);	//A0
  pinMode(photoPin, INPUT);		//A1
  pinMode(sw, INPUT);			//3	(디지털 input)
  
  pinMode(LED_A, OUTPUT);		//12
  pinMode(LED_B1, OUTPUT);		//11
  pinMode(LED_B2, OUTPUT);		//10
  pinMode(LED_B3, OUTPUT);		//9
  pinMode(LED_C, OUTPUT);		//8
}

//아두이노가 아날로그로 읽는 것은 10bit, 아날로그출력(PWM)은 8bit
void loop()
{
  if(digitalRead(sw)!=HIGH){	//스위치가 눌렸다면
    cnt++;	//cnt의 값을 증가시킨다.
    delay(270);	
    //버튼을 누른 순간 cnt가 급격하게 빨리 올라가지 않도록 조정해주는 delay값
    //(3번루틴이 스킵되고 4번으로 바로 넘어가는 경우가 종종 발생)
    
    switch(cnt){	//스위치가 눌린 횟수 각각의 경우에 대하여 각각의 함수 작동
      case 1:
          first();
          break;
      case 2:
          second();
          break;
      case 3:
          third();
          break;
      case 4:
          fourth();
          break;
    }//end switch
  }//endif
  
}//endloop

//함수 정의
int getResist(int pinNum){
  int resist = analogRead(pinNum);	//pinNum에서 저항값을 읽는다. 0 ~ 1023(10비트)
  resist = map(resist, 0, 1023, 0, 255);	//저항값을 8비트 값으로 변환
  resist = constrain(resist, 0, 255); //제한값 설정
  return resist;	//8비트 저항값으로 반환. -> 밝기 등의 설정에 바로 적용 가능
}

void first(){
  int resist = getResist(resistPin);
  if(resist < 127){	//저항값이 127 미만인 경우
  	digitalWrite(LED_A, HIGH);  
  }else{		//127 이상인 경우
   	digitalWrite(LED_A, LOW); 
  }
  delay(3000);
  digitalWrite(LED_A, LOW);	//루틴 종료 후 꺼주기
}

void second(){
  int resist = 0;
  for(int i = 0; i < 3; i++){	//총 3번 실행
    for(int j = LED_B1; j >= LED_B3; j--){
      //B1부터 B3까지 가면서 내부 문장 실행, 11 -> 10 -> 9 (핀번호 순서)
      
      resist = getResist(resistPin);
      //저항값을 매 LED갱신시마다, 반복마다 얻어와서 LED밝기에 반영
      
      analogWrite(j, resist);	//i에 해당하는 핀에 저항값만큼 출력
      delay(1000);	//딜레이
      analogWrite(j, LOW);	//끄기
    }
  }
}

void third(){
  //조도센서는 빛이 밝아질수록 저항은 낮아진다.
  int p_resist = getResist(photoPin);	//cds의 값을 읽는다.
  p_resist = map(p_resist, 0, 255, 255, 0); //재 매핑(역으로)
  
  if(p_resist >= 127){	//저항값이 127 이상이면 -> 빛이 별로 없다 -> LED ON
    digitalWrite(LED_C, HIGH);
  }else{
    digitalWrite(LED_C, LOW);
  }
}

void fourth(){
  cnt = 0;	//푸시버튼 카운터 초기화
  digitalWrite(LED_C, LOW); //네번째 루틴을 실행할 때는 켜져있을지 모르는 LED_C 꺼준다. 
  delay(5000);
}