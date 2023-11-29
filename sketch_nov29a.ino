#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include "NewPing.h"

Servo myservo;
LiquidCrystal_I2C lcd(0x27,16,2);
NewPing sonar(8, 7);

#define trigPin 8
#define echoPin 7
#define servoPin 9

float duration;
float distance;

void setup() 
{
  myservo.attach(servoPin);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  lcd.init();
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("hyouon dick is");
  
  Serial.begin(9600);
}

void loop()
{
  digitalWrite(trigPin, HIGH);
  delay(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = ((float)(340 * duration) / 10000) / 2;
  
  lcd.setCursor(5,1);
  lcd.print(distance);
  lcd.setCursor(11,1);
  lcd.print("cm");

  Serial.print(distance);
  Serial.println("cm");
 
  if(distance < 15)
  {
    myservo.write(180);
    delay(100);
  }
  else 
  {
    myservo.write(10);
  }
  
  delay(200);
}
