int button1 = 3, button2 = 4;
int valuebt1, valuebt2;
int interruptPin = 2;  
int a = 0;
int i;
int pwmPin = 12;
int out1 = 11, out2 = 10;

bool wasHigh1 = false, wasHigh2 = false;

void emergencyBrake() {
  a = 0;
}

void acceleration() {
}

void deceleration() {
}

void setup() {
  Serial.begin(115200);
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(interruptPin, INPUT_PULLUP);
  pinMode(out1, OUTPUT);
  pinMode(out2, OUTPUT);
  pinMode(pwmPin, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPin), emergencyBrake, LOW);
  i = 0;
  analogWrite(pwmPin, 0);
}

void loop() {
  digitalWrite(out1, HIGH);
  digitalWrite(out2, LOW);
  analogWrite(pwmPin, a);
  valuebt1 = digitalRead(button1);
  valuebt2 = digitalRead(button2);
  // acceleration();
  // deceleration();
  if ( valuebt1 == LOW and !wasHigh1 and valuebt2 == HIGH) {
    for (i = 0; i < 255 ; i++) {
      a = a + 1;
      delay(40);
      Serial.println(a);
      if ( a >= 255) {
        break;
      }      
    }  
  }
  if ( valuebt2 == LOW and !wasHigh2 and valuebt1 == HIGH) {
      for (i = 255; i > 0; i--) {
      a = a - 1;
      delay(40);
      Serial.println(a);
      if ( a <= 0) {
        break;
      }
    }  
  }
  wasHigh1 = !valuebt1;
  wasHigh2 = !valuebt2;
  Serial.println("1:" + String(valuebt1));
  Serial.println("2:" + String(valuebt2));
}
