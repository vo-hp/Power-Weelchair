#include <Servo.h>

Servo myservo;
int bt  = A1;
int servoPin = A0;

void setup() {
  Serial.begin(9600);
  pinMode(bt, INPUT);
  myservo.attach(servoPin);

}

void loop() {
  int value = analogRead(bt);
  int servoD = map(value, 0 , 1023, 0 , 180);
  myservo.write(servoD);
  // Serial.println(servoD);
  Serial.println(value);
}
