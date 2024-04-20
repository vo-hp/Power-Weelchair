int vibrationSensor = A4;
int led = 13;

void setup() {
  Serial.begin(9600);
  pinMode(vibrationSensor, INPUT);
  pinMode(led, OUTPUT);
}

void loop() {
  int value = analogRead(vibrationSensor);
  Serial.println(value);
  if ( value <= 100) {
    for( int i =0; i <= 10; i++) {
      digitalWrite(led, HIGH);
      delay(100);
      digitalWrite(led, LOW);
      delay(100);
    }
  }
  delay(50);
}
