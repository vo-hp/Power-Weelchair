int nut1 = 2, nut2 = 3;
int out1 = 11, out2 = 12;
int chanPWM = 13;
int i;


void setup() {
  Serial.begin(9600);
  pinMode(nut1, INPUT);
  pinMode(nut2, INPUT);
  pinMode(out1, OUTPUT);
  pinMode(out2 , OUTPUT);
  pinMode(chanPWM, OUTPUT);
  analogWrite(chanPWM, 0);
  attachInterrupt(1, tangToc, LOW);
  attachInterrupt(2, giamToc, LOW);
}

void tangToc() 
{
  for ( i = 0; i <= 255; i++) 
  {
    analogWrite(chanPWM , i);
    delay(40);
  }
}
void giamToc() 
{
  for ( i = 255; i >= 0; i--) 
  {
    analogWrite(chanPWM , i);
    delay(40);
  }
}


void loop() {
  int value1 = digitalRead(nut1);
  int value2  =digitalRead(nut2);
  digitalWrite(out1, HIGH);
  digitalWrite(out2, LOW);
  // Serial.println(i);
  if ( value1 == LOW )
  {
    tangToc();
  }
  else if ( value2 == LOW)
  {
    giamToc();
  }
  Serial.println(value1);
  Serial.println(value2);
}
