int button1 = 3;
int button2 = 4;
int interruptPin = 2; 
bool wasHigh1 = false;
bool wasHigh2 = false;
int a = 0;

void emergencyBrake() {
  a = 0;
}

void accleration() {
  
}

void setup() {
  Serial.begin(9600);
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), emergencyBrake, LOW);
}

void loop() {
  int valuebt1 = digitalRead(button1);
  int valuebt2 = digitalRead(button2);
  if ( valuebt1 == LOW and !wasHigh1 and valuebt2 == HIGH) {
    a = a+1;
  }
  if ( valuebt2 == LOW and !wasHigh2 and valuebt1 == HIGH) {
    a = a+1;
  }
  wasHigh1 = !valuebt1;
  wasHigh2 = !valuebt2;
  Serial.println(a);
}
