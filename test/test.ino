int s1 = 8;
int s2 = 9;
int s3 = 10;
int s4 = 11;
int s5 = 12;

void setup() {
  Serial.begin(9600);
  pinMode(s1 ,INPUT);
  pinMode(s2 ,INPUT);
  pinMode(s3 ,INPUT);
  pinMode(s4 ,INPUT);
  pinMode(s5 ,INPUT);
}

void loop() {
  Serial.println("s1 " + String(digitalRead(s1)));
  Serial.println("s2 " +String(digitalRead(s2)));
  Serial.println("s4 " +String(digitalRead(s3)));
  Serial.println("s3 " +String(digitalRead(s4)));
  Serial.println("s5 " +String(digitalRead(s5)));
  delay(1000);
}
