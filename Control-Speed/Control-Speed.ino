int number;
int chanPWM = 13, out1 = 11, out2 = 12;
int nut =10;
int pre;

void setup() {
  Serial.begin(9600);
  pinMode(nut, INPUT);
  number = 0;
  pre=HIGH;
  analogWrite(chanPWM, 0);
}

void loop() {
  digitalWrite(out1, HIGH);
  digitalWrite(out2, LOW);
  int docnut=digitalRead(nut);
  if (docnut == LOW && pre==HIGH)
  {
    number++;
    delay(50);
  }
  pre = docnut;
  Serial.println(number);
  if ( number == 6)
  {
    number = 0;
  }
  if ( number == 0)
  {
    analogWrite(chanPWM, 0);
  }
  else if( number == 1)
  {
    analogWrite(chanPWM, 126);
  }
  else if ( number == 2) 
  {
    analogWrite(chanPWM, 153);
  }
  else if ( number == 3) 
  {
    analogWrite(chanPWM, 178);
  }
  else  if ( number == 4) 
  {
    analogWrite(chanPWM, 204);
  }
  else if ( number == 5) 
  {
    analogWrite(chanPWM, 255);
  }
}
