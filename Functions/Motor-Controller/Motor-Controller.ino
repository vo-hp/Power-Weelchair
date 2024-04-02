int nut1 = 10, nut2 = 9;
int number;
int pre1, pre2;

void setup() {
  Serial.begin(9600);
  pinMode(nut1, INPUT);
  pinMode(nut2, INPUT);
  pre1 = HIGH;
  pre2 = HIGH;
  number = 0;
}

void loop() {
  int docnut1 = digitalRead(nut1);
  int docnut2 = digitalRead(nut2);
  if ( number <= 255)
  {
    if (docnut1 == LOW && pre1 == HIGH)
    {
      number = number + 20;
      delay(50);

    }
      pre1 = docnut1;
      Serial.println(number);
  }
  // if ( docnut2 == LOW && pre2 == HIGH)
  // {
  //   number = number - 20;
  //   delay(50);
  // }
  // pre2 = docnut2;

}
