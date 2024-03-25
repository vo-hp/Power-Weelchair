int xAxis = A0, yAxis = A1;
int up = 2;
int start = 5;
int down = 4;
int stop = 3;
int pwmPinA = A2, pwmPinB = A3;
int out1 = 12, out2 = 11, out3 = 10, out4 = 9;
int x, y;
int speed;

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
  if ( y < 512) {               // backward
    digitalWrite(out1,LOW);
    digitalWrite(out2,HIGH);
    digitalWrite(out3, LOW);
    digitalWrite(out4, HIGH);
    speed = -150./512.*y+150.;
    analogWrite(pwmPinA,speed);
    analogWrite(pwmPinB,speed);
  }
  if( y  >=512) {               // forward
    digitalWrite(out1,HIGH);
    digitalWrite(out2,LOW);
    digitalWrite(out3, HIGH);
    digitalWrite(out4, LOW);
    speed=(150./512.)*y-150.;
    analogWrite(pwmPinA,speed);
    analogWrite(pwmPinB, speed);
  }
}    

void leftAndRight() {
  if ( x < 512) {               //  left
    digitalWrite(out1,LOW);
    digitalWrite(out2,HIGH);
    digitalWrite(out3, HIGH);
    digitalWrite(out4, LOW);
    speed = -150./512.*x+150.;
    analogWrite(pwmPinA,speed);
    analogWrite(pwmPinB,speed);
  }
  if( x  >=512) {               //  right
    digitalWrite(out1,HIGH);
    digitalWrite(out2,LOW);
    digitalWrite(out3, LOW);
    digitalWrite(out4, HIGH);
    speed=(150./512.)*x-150.;
    analogWrite(pwmPinA,speed);
    analogWrite(pwmPinB, speed);
  }
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
  Serial.print("       stop  " + String(B));
  Serial.println("   speed  " + String(speed));
  delay(10);
}