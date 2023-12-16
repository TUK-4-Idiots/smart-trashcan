#include <Arduino.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include "NewPing.h"
#include <TimerFreeTone.h>

// 핀 번호 정의
#define BUTTON_PIN 2
#define BUZZER_PIN A0
#define LED_PIN_R 6
#define LED_PIN_G 5
#define LED_PIN_B 4
#define TRIG_PIN 8
#define ECHO_PIN 7
#define SERVO_PIN 10
#define ACCELEROMETER_PIN 6
#define IN1 6
#define IN2 7
#define IN3 3
#define IN4 4



// 모듈 객체 생성
Servo servoMotor;  //서보모터
LiquidCrystal_I2C lcd(0x27, 16, 2);  //lcd
NewPing ultrasonicSensor(TRIG_PIN, ECHO_PIN); //초음파

// 초기 설정
void setup() {
  pinMode(BUTTON_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN_R, OUTPUT);
  pinMode(LED_PIN_G, OUTPUT);
  pinMode(LED_PIN_B, OUTPUT);
  Serial.begin(9600);
  servoMotor.attach(SERVO_PIN);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  
}

// 1번 함수: 수동부저가 "도레미파솔라시도" 라고 울리게 해줍니다.
void playMelody() {
  Serial.println("아아아아아앙");
  int melody[] = {262, 294, 330, 349, 392, 440, 494};  // 도레미파솔라시도 주파수
  int noteDuration = 50;  // 음 길이 설정
  
  for (int i = 0; i < 7; i++) {
    TimerFreeTone(BUZZER_PIN, melody[i], noteDuration);
    delay(noteDuration + 50);  // 음 사이의 간격 설정
  }
}


// 2번 함수: RGB 모듈을 파란색으로 설정해줍니다.
void setBlueColor() {
  analogWrite(LED_PIN_R, 0);
  analogWrite(LED_PIN_G, 0);
  analogWrite(LED_PIN_B, 255);
}

// 3번 함수: 초음파 센서로 15cm 이내에 물체가 감지되면 서보모터를 180도로 빠르게 움직입니다.
void moveServo() {
  int distance = ultrasonicSensor.ping_cm();
  if (distance <= 15) {
    servoMotor.write(180);
    delay(500);
    servoMotor.write(0);
  }
}

// 4번 함수: 수동부저가 "시라솔파미레도" 라고 울리게 해줍니다.
void playScale() {
  int scale[] = {988, 880, 784, 698, 659, 587, 523};  // 시라솔파미레도 주파수
  int noteDuration = 50;  // 음 길이 설정
  
  for (int i = 0; i < 7; i++) {
    TimerFreeTone(BUZZER_PIN, scale[i], noteDuration);
    delay(noteDuration + 50);  // 음 사이의 간격 설정
  }
}

// 5번 함수: RGB 모듈을 빨간색으로 설정해줍니다.
void setRedColor() {
  analogWrite(LED_PIN_R, 255);
  analogWrite(LED_PIN_G, 0);
  analogWrite(LED_PIN_B, 0);
}

// 6번 함수: 일정 간격으로 부저가 "삐삐삐삐" 소리를 내게 해줍니다.
void playBeep() {
  TimerFreeTone(BUZZER_PIN, 1000, 500);  // 1000Hz의 소리를 500ms 동안 울립니다.
  delay(500);  // 소리 사이의 간격을 500ms로 설정합니다.
}

// 7번 함수: 기울기 센서가 기울어질 때 6번 함수를 실행하게 해줍니다.
void checkTilt() {
  int tiltValue = analogRead (ACCELEROMETER_PIN); // 기울기 센서의 값 읽기
  if (tiltValue < 100) { // 기울기 센서의 임계값에 따라 조정
    playBeep(); // 6번 함수 실행
  }
}
// 무한 반복
void loop() {
  if(Serial.available()){
    char command = Serial.read();

    switch(command){
    case 'F': // 전진
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      break;
    case 'B': // 후진
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      break;
    case 'L': // 좌회전
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      break;
    case 'R': // 우회전
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      break;
    case 'S': // 정지
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      break;
    }
  }
}

