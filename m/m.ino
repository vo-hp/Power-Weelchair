int xAxis = A0;
int yAxis = A1;
int up = 2;
int start = 3;
int down = 4;
int stop = 5;
int pwmPin = 13;
int out1 = 11;
int out2 = 12;
int x;
int y;
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
  pinMode(pwmPin, OUTPUT);
  analogWrite(pwmPin, 0);
}

void tangGiamToc() {
  if ( x < 512){
    digitalWrite(out1,LOW);
    digitalWrite(out2,HIGH);
    speed = -150./512.*x+150.;
    analogWrite(pwmPin,speed);
  }
  if( x  >=512) {
    digitalWrite(out1,HIGH);
    digitalWrite(out2,LOW);
    speed=(150./512.)*x-150.;
    analogWrite(pwmPin,speed);
  }
}    


void loop() {
  x = analogRead(xAxis);
  y = analogRead(yAxis);
  Serial.print("X   " + String(x));
  Serial.print("        Y   " + String(y));
  tangGiamToc();
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