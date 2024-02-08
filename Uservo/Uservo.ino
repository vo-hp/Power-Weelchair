#include <Servo.h>

Servo myservo;
int bt  = 11;
int servoPin = 10;

void setup() {
  Serial.begin(9600);
  pinMode(bt, INPUT);
  myservo.attach(servoPin);

}

void loop() {
  int value = analogRead(bt);
  int servoD = map(value, 0 , 1023, 0 , 100);
  myservo.write(servoD);
  // Serial.println(servoD);
  Serial.println(value);
}
