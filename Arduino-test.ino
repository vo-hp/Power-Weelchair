int i;
int nut1 = 2, nut2 = 3; 
int chanPWM = 13, out1 = 11, out2 = 12;

void setup() 
{
  Serial.begin(9600)
  pinMode(nut1, INPUT);
  pinMode(nut2, INPUT);
  pinMode(chanPWM, OUTPUT);
  pinMode(out1, OUTPUT);
  pinMode(out2, OUTPUT);
  analogWrite(chanPWM, 0);
}
// void tangToc() 
// {
//   for (i = 0; i < 255; i++)
//   {
//     analogWrite(chanPWM , i);
//     delay(40);
//   }
// }

// void giamToc() 
// {
//   for (i = 255; i >= 0; i--)
//   {
//     analogWrite(chanPWM , i);
//     delay(40);
//   }
// }

void loop() 
{
  int doc1 = digitalRead(nut1);
  // Serial.println(doc1);
  int doc2 = digitalRead(nut2);
  // Serial.println(doc2);
  digitalWrite(out1, HIGH);
  digitalWrite(out2, LOW);
  if ( doc1 == LOW) 
  {
    for (i = 0; i < 255; i++)
    {
      analogWrite(chanPWM , i);
      delay(40);
    }
  }
  else if( doc2 == LOW)
  {
    for (i = 255; i >= 0; i--)
    {
      analogWrite(chanPWM , i);
      delay(40);
    }
  }
  Serial.println(i);
}
