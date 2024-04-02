int irPin = 10;
bool isThereObstacle = false;

void setup() {
  Serial.begin(9600);
  pinMode(irPin, INPUT);
}

void loop() {
  int value = digitalRead(irPin);
  if ( value  == LOW) {
    Serial.println("detect obstacle");
  }
  else  if ( value  == HIGH) {
    Serial.println("no obstacle");
  }
}
