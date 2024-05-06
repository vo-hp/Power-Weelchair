int vibrationSensor = A4;
int led = 13;
int potm = A5;
int buzzer = 3;

void setup() {
  Serial.begin(9600);
  pinMode(vibrationSensor, INPUT);
  pinMode(led, OUTPUT);
  pinMode(potm , INPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  // int value = analogRead(vibrationSensor);
  // Serial.println(value);
  // if ( value <= 100) {
  //   for( int i =0; i <= 10; i++) {
  //     digitalWrite(led, HIGH);
  //     delay(100);
  //     digitalWrite(led, LOW);
  //     delay(100);
  //   }
  // }
  // delay(50);
  int value = analogRead(potm);
  int fre = map(value, 0, 1023, 0, 4000);
  Serial.print(String(value) + "      ");
  Serial.println(fre);
  tone(buzzer, fre);
}
