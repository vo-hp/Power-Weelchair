const int trigPin =8 ;
const int echoPin = 7;
float duration, distance;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = (duration * 0.0343)/2;
  if ( distance <= 100)
  {
    Serial.println("Phat hien vat the");
  }
  else 
  {
    Serial.println("Xe duoc di thang");
  }
  Serial.print("distance: ");
  Serial.println(distance);
  delay(1000);
}