const int xAxis = A0, yAxis = A1;
const int up = 2;
const int start = 5;
const int down = 4;
const int stop = 3;
const int pwmPinA = A2, pwmPinB = A3;
const int out1 = 12, out2 = 11, out3 = 10, out4 = 9;
int x, y;

void setup() {
  Serial.begin(9600);
  pinMode(up, INPUT);
  pinMode(down, INPUT);
  pinMode(start, INPUT);
  pinMode(stop, INPUT);
  pinMode(xAxis, INPUT);
  pinMode(yAxis, INPUT);
  pinMode(out1, OUTPUT);
  pinMode(out2, OUTPUT);
  pinMode(out3, OUTPUT);
  pinMode(out4, OUTPUT);
  pinMode(pwmPinA, OUTPUT);
  pinMode(pwmPinB, OUTPUT);
  analogWrite(pwmPinA, 0);
  analogWrite(pwmPinB, 0);
}

void forwardAndBackward() {
  int threshold = 512;
  int speed;
  if ( y < threshold) {               // backward
    digitalWrite(out1,LOW);
    digitalWrite(out2,HIGH);
    digitalWrite(out3, LOW);
    digitalWrite(out4, HIGH); //    speed = -150./512.*y+150.;
  }
  else {               // forward
    digitalWrite(out1,HIGH);
    digitalWrite(out2,LOW);
    digitalWrite(out3, HIGH);
    digitalWrite(out4, LOW);
  }
  speed = map(abs(y - threshold), 0, 512, 0, 255);
  analogWrite(pwmPinA,speed);
  analogWrite(pwmPinB,speed);
}    

void leftAndRight() {
  int threshold = 512;
  int speed;
  if ( x < threshold) {               //  left
    digitalWrite(out1,LOW);
    digitalWrite(out2,HIGH);
    digitalWrite(out3, HIGH);
    digitalWrite(out4, LOW);
  }
  else {               //  right
    digitalWrite(out1,HIGH);
    digitalWrite(out2,LOW);
    digitalWrite(out3, LOW);
    digitalWrite(out4, HIGH);
  }
  speed = map(abs(x - threshold), 0, 512, 0, 255);
  analogWrite(pwmPinA,speed);
  analogWrite(pwmPinB,speed);
}

void loop() {
  x = analogRead(xAxis);
  y = analogRead(yAxis);
  Serial.print("X   " + String(x));
  Serial.print("        Y   " + String(y));
  forwardAndBackward();
  leftAndRight();
  int A = digitalRead(up);
  int B = digitalRead(stop);
  int C = digitalRead(down);
  int D = digitalRead(start);
  Serial.print("       up  " + String(A));
  Serial.print("       down  " + String(C));
  Serial.print("       start  " + String(D));
  Serial.println("       stop  " + String(B));
  delay(10);
}