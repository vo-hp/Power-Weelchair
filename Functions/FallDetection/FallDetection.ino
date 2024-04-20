int vibrationSensor = A3;
int led = 13;

void setup() {
  Serial.begin(9600);
  pinMode(vibrationSensor, INPUT);
  pinMode(led, OUTPUT);
}

void loop() {
  int value = analogRead(vibrationSensor);
  Serial.println(value);
  delay(dlay1dela0dela0deladedel
}
