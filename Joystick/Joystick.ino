const int xAxis = A0, yAxis = A1;
const int up = 2;
const int start = 5;
const int down = 4;
const int stop = 3;
const int enaA = A2, enaB = A3; // enaA and enaB
const int out1 = 12, out2 = 11, out3 = 10, out4 = 9;
int x, y;
int motorSpeedA, motorSpeedB;

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
  pinMode(enaA, OUTPUT);
  pinMode(enaB, OUTPUT);
  analogWrite(motorSpeedA, 0);
  analogWrite(motorSpeedB, 0);
}

// void forwardAndBackward() {
//   int threshold = 512;
//   if ( y < threshold) {               // backward
//     digitalWrite(out1,LOW);
//     digitalWrite(out2,HIGH);
//     digitalWrite(out3, LOW);
//     digitalWrite(out4, HIGH); //    speed = -150./512.*y+150.;
//   }
//   else {               // forward
//     digitalWrite(out1,HIGH);
//     digitalWrite(out2,LOW);
//     digitalWrite(out3, HIGH);
//     digitalWrite(out4, LOW);
//   }
//   speed = map(abs(y - threshold), 0, 512, 0, 255);
//   analogWrite(pwmPinA,speed);
//   analogWrite(pwmPinB,speed);
// }    

// void leftAndRight() {
//   int threshold = 512;
//   if ( x < threshold) {               //  left
//     digitalWrite(out1,LOW);
//     digitalWrite(out2,HIGH);
//     digitalWrite(out3, HIGH);
//     digitalWrite(out4, LOW);
//   }
//   else {               //  right
//     digitalWrite(out1,HIGH);
//     digitalWrite(out2,LOW);
//     digitalWrite(out3, LOW);
//     digitalWrite(out4, HIGH);
//   }
//   speed = map(abs(x - threshold), 0, 512, 0, 255);
//   analogWrite(pwmPinA,speed);
//   analogWrite(pwmPinB,speed);
// }

  // int A = digitalRead(up);
  // int B = digitalRead(stop);
  // int C = digitalRead(down);
  // int D = digitalRead(start);
  // Serial.print("       up  " + String(A));
  // Serial.print("       down  " + String(C));
  // Serial.print("       start  " + String(D));
  // Serial.println("       stop  " + String(B));

void forward() {
  digitalWrite(out1,HIGH);
  digitalWrite(out2,LOW);
  digitalWrite(out3, HIGH);
  digitalWrite(out4, LOW);
}

void backward() {
  digitalWrite(out1,LOW);
  digitalWrite(out2,HIGH);
  digitalWrite(out3, LOW);
  digitalWrite(out4, HIGH); 
}

void left() {
  digitalWrite(out1,LOW);
  digitalWrite(out2,HIGH);
  digitalWrite(out3, HIGH);
  digitalWrite(out4, LOW);
}

void right() {
  digitalWrite(out1,HIGH);
  digitalWrite(out2,LOW);
  digitalWrite(out3, LOW);
  digitalWrite(out4, HIGH);  
}


void loop() {
  x = analogRead(xAxis);
  y = analogRead(yAxis);
  Serial.print("X   " + String(x));
  Serial.println("        Y   " + String(y));
    motorSpeedA = map(y, 512, 1023, 0, 150);
    motorSpeedB = map(y, 512, 1023, 0, 150);
  }
  if ( x >= 500 and x<= 520 and y < 512  ) { //backward
    backward();
    motorSpeedA = map(y, 511, 0, 0, 150);
    motorSpeedB = map(y, 511, 0, 0, 150);
  }
  if ( y >= 500 and y <= 520 and x >= 512 ) { // right
    right();
    motorSpeedA = map(x, 512, 1023, 0, 150);
    motorSpeedB = map(x, 512, 1023, 0, 150);
  }
  if ( y >= 500 and y <= 520 and x < 512 ) { // left
    left();
    motorSpeedA = map(x, 511, 0, 0, 150);
    motorSpeedB = map(x, 511, 0, 0, 150);
  }
  if ( x > 520 and y> 520  ) { // I
    forward();
    motorSpeedA  = map(x, 521, 1023 , 0, 150);
    motorSpeedB = map(y, 521, 1023, 0, 150);
  }
  if ( x < 500 and y > 520  ) { // II
    forward(); 
    motorSpeedA  = map(y, 521, 1023, 0, 150);
    motorSpeedB = map(x, 499, 0, 0, 150);
  }
  if ( x < 500 and y < 500  ) { // III
    backward(); 
    motorSpeedA  = map(y, 499, 0 , 0, 150);
    motorSpeedB = map(x, 499, 0, 0, 150);
  }
  if ( x > 520 and y < 500  ) { // IV
    backward(); 
    motorSpeedA  = map(y, 521, 1023 , 0, 150);
    motorSpeedB = map(x, 499, 0, 0, 150);
  }
  analogWrite(enaA, motorSpeedA);
  analogWrite(enaB, motorSpeedB);
  delay(10);
}