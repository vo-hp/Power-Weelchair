int button1 = 3;
int button2 = 4;
int valuebt1;
int valuebt2;
int interruptPin = 2;  
int a = 0;
int i = 0;

int pwmPin = 12;
int out1 = 11;
int out2 = 10;

bool wasHigh1 = false;
bool wasHigh2 = false;

void emergencyBrake() {
  a = 0;
}

void acceleration() {
  if ( valuebt1 == LOW and !wasHigh1 and valuebt2 == HIGH) {
    for (; i < 255 ; i++) {
      a = a + 1;
      delay(40);
      Serial.println(a);
      if ( i >= 255) {
        break;
      }      
    }  
  }
}

void deceleration() {
  if ( valuebt2 == LOW and !wasHigh2 and valuebt1 == HIGH) {
      for (; i >= 0; i--) {
      a = a - 1;
      delay(40);
      Serial.println(a);
      if ( a <= 0) {
        break;
      }
    }  
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), emergencyBrake, LOW);
}

void loop() {
  valuebt1 = digitalRead(button1);
  valuebt2 = digitalRead(button2);
  acceleration();
  deceleration();
  wasHigh1 = !valuebt1;
  wasHigh2 = !valuebt2;
  Serial.println("1:" + String(valuebt1));
  Serial.println("2:" + String(valuebt2));
}
