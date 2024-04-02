int s1 = 8;
int s2 = 9;
int s3 = 10;
int s4 = 11;
int s5 = 12;
int out3R;
int out4R;
int out1L;
int out2L;
int pwmPin;

void setup() {
  Serial.begin(9600);
  pinMode(s1 ,INPUT);
  pinMode(s2 ,INPUT);
  pinMode(s3 ,INPUT);
  pinMode(s4 ,INPUT);
  pinMode(s5 ,INPUT);
}

void forward() {
  digitalWrite(out1L, HIGH);
  digitalWrite(out2L, LOW);
  digitalWrite(out3R, HIGH);
  digitalWrite(out4R, LOW);

}

void backward() {
  digitalWrite(out1L, LOW);
  digitalWrite(out2L, HIGH);
  digitalWrite(out3R, LOW);
  digitalWrite(out4R, HIGH);
}

void turnRight() {
  digitalWrite(out1L, HIGH);
  digitalWrite(out2L, LOW);
  digitalWrite(out3R, LOW);
  digitalWrite(out4R, HIGH);
}

void turnLeft() {
  digitalWrite(out1L, LOW);
  digitalWrite(out2L, HIGH);
  digitalWrite(out3R, HIGH);
  digitalWrite(out4R, LOW);
}



void loop() {
  Serial.println("s1 " + String(digitalRead(s1))); 
  Serial.println("s2 " +String(digitalRead(s2)));
  Serial.println("s3 " +String(digitalRead(s3)));
  Serial.println("s4 " +String(digitalRead(s4)));
  Serial.println("s5 " +String(digitalRead(s5))); //analogRead(s5)
  delay(200);
  if ( s5 == 0 or s4 == 0  ) {
    turnLeft();
  }
  if (s1 == 0 or s2 == 0) {
    turnRight();
  }
  if ( s3 == 0 or s3 == 0 and s2 == 0 and s4 ==0 ) {
    forward();
  }
  if ( s1 == 1 and s2 ==1 and s3 == 1 and s4 == 1 and s5 ==1 ){
    backward();
  }
}
