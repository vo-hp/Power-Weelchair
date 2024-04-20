int vibrationSensor = A0;
int led = 13;

void setup() {
  Serial.begin(9600);
  pinMode(vibrationSensor, INPUT);
  pinMode(led, OUTPUT);
}

void loop() {
  int value = analogRead(vibrationSensor);
  if ( value <= 800){
    digitalWrite(13, HIGH);
    delay(10000);
    digitalWrite(13, LOW);
  }

  Serial.println(value);
}
