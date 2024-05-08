const int trigPin =22 ;
const int echoPin = 23;
float duration, distance;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(4, OUTPUT);
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
    tone(4, 2000,2000);
  }
  else 
  {
    Serial.println("Xe duoc di thang");
  }
  Serial.print("distance: ");
  Serial.println(distance);
  delay(1000);
}