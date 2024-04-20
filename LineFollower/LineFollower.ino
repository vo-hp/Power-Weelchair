int s1 = 12;
int s2 = 11;
int s3 = 10;
int s4 = 9;
int s5 = 8;
const int enaA = A2, enaB = A3; // enaA and enaB
const int out1 = 7, out2 = 6, out3 = 5, out4 = 4; // const int out1 = 14, out2 = 15, out3 = 16, out4 = 17; for ATMega
int speedMotorA, speedMotorB;

void setup() {
  Serial.begin(9600);
  pinMode(s1 ,INPUT);
  pinMode(s2 ,INPUT);
  pinMode(s3 ,INPUT);
  pinMode(s4 ,INPUT);
  pinMode(s5 ,INPUT);
  pinMode( out1, OUTPUT);
  pinMode(out2, OUTPUT);
  pinMode(out3, OUTPUT);
  pinMode(out4, OUTPUT);
  pinMode(enaA, OUTPUT);
  pinMode(enaB, OUTPUT);
}

void forward() {
  digitalWrite(out1, HIGH);
  digitalWrite(out2, LOW);
  digitalWrite(out3, HIGH);
  digitalWrite(out4, LOW);

}

void backward() {
  digitalWrite(out1, LOW);
  digitalWrite(out2, HIGH);
  digitalWrite(out3, LOW);
  digitalWrite(out4, HIGH);
}

void turnRight() {
  digitalWrite(out1, HIGH);
  digitalWrite(out2, LOW);
  digitalWrite(out3, LOW);
  digitalWrite(out4, LOW);
}

void turnLeft() {
  digitalWrite(out1, LOW);
  digitalWrite(out2, LOW);
  digitalWrite(out3, HIGH);
  digitalWrite(out4, LOW);
}



void loop() {
  int v1 = digitalRead(s1);
  int v2 = digitalRead(s2);
  int v3 = digitalRead(s3);
  int v4 = digitalRead(s4);
  int v5 = digitalRead(s5);
  Serial.print("s1 " + String(v1)); 
  Serial.print("   s2 " + String(v2));
  Serial.print("   s3 " +String(v3));
  Serial.print("   s4 " +String(v4));
  Serial.println("   s5 " +String(v5)); //analogRead(s5)
  middle detects line
  if ( (( v1 == 1) and ( v2 == 1) and ( v3 == 0 ) and ( v4 == 1) and ( v5 == 1)) or ( v1 == 1  and v2 == 0 and v3 == 0 and v4 == 0 and v5 == 1))  {
    forward();
    analogWrite(enaA, 70);
    analogWrite(enaB, 70);
  }
  // far left detect line
  if (( v1 == 0) and ( v2 == 1) and ( v3 == 1) and ( v4 == 1) and ( v5 == 1)) {
    turnRight();
    analogWrite(enaA, 70);
    analogWrite(enaB, 70);
  }
  //  left detects line
  if (( v1 == 0) and ( v2 == 0) and ( v3 == 1) and ( v4 == 1) and ( v5 == 1)) {
    turnRight();
    analogWrite(enaA, 70);
    analogWrite(enaB, 70);
  }
  //far right detects line
  if (( v1 == 1) and ( v2 == 1) and ( v3 == 1) and ( v4 == 1) and ( v5 == 0)) {
    turnLeft();
    analogWrite(enaA, 70);
    analogWrite(enaB, 70);
  }
    // right detects line
  if (( v1 == 1) and ( v2 == 1) and ( v3 == 1) and ( v4 == 0) and ( v5 == 0)) {
    turnLeft();
    analogWrite(enaA, 70);
    analogWrite(enaB, 70);
  }
  // no line detection
  if (( v1 == 1) and ( v2 == 1) and ( v3 == 1) and ( v4 == 1) and ( v5 == 1)) {
    digitalWrite(out1, LOW);
    digitalWrite(out2, LOW);
    digitalWrite(out4, LOW);
    digitalWrite(out3, LOW);
    analogWrite(enaA, 0);
    analogWrite(enaB, 0);
  }

}
/*
  //if only middle sensor detects black line
  if((s1 == 1) && (s2 == 1) && (s3 == 0) && (s4 == 1) && (s5 == 1))
  {
    //going forward with full speed 
    analogWrite(e1, 255); //you can adjust the speed of the motors from 0-255
    analogWrite(e2, 255); //you can adjust the speed of the motors from 0-255
    digitalWrite(m1, HIGH);
    digitalWrite(m2, LOW);
    digitalWrite(m3, HIGH);
    digitalWrite(m4, LOW);
  }
  
  //if only left sensor detects black line
  if((s1 == 1) && (s2 == 0) && (s3 == 1) && (s4 == 1) && (s5 == 1))
  {
    //going right with full speed 
    analogWrite(e1, 255); //you can adjust the speed of the motors from 0-255
    analogWrite(e2, 255); //you can adjust the speed of the motors from 0-255
    digitalWrite(m1, HIGH);
    digitalWrite(m2, LOW);
    digitalWrite(m3, LOW);
    digitalWrite(m4, LOW);
  }
  
  //if only left most sensor detects black line
  if((s1 == 0) && (s2 == 1) && (s3 == 1) && (s4 == 1) && (s5 == 1))
  {
    //going right with full speed 
    analogWrite(e1, 255); //you can adjust the speed of the motors from 0-255
    analogWrite(e2, 255); //you can adjust the speed of the motors from 0-255
    digitalWrite(m1, HIGH);
    digitalWrite(m2, LOW);
    digitalWrite(m3, LOW);
    digitalWrite(m4, HIGH);
  }

  //if only right sensor detects black line
  if((s1 == 1) && (s2 == 1) && (s3 == 1) && (s4 == 0) && (s5 == 1))
  {  
    //going left with full speed 
    analogWrite(e1, 255); //you can adjust the speed of the motors from 0-255
    analogWrite(e2, 255); //you can adjust the speed of the motors from 0-255
    digitalWrite(m1, LOW);
    digitalWrite(m2, LOW);
    digitalWrite(m3, HIGH);
    digitalWrite(m4, LOW);
  }

  //if only right most sensor detects black line
  if((s1 == 1) && (s2 == 1) && (s3 == 1) && (s4 == 1) && (s5 == 0))
  {
    //going left with full speed 
    analogWrite(e1, 255); //you can adjust the speed of the motors from 0-255
    analogWrite(e2, 255); //you can adjust the speed of the motors from 0-255
    digitalWrite(m1, LOW);
    digitalWrite(m2, HIGH);
    digitalWrite(m3, HIGH);
    digitalWrite(m4, LOW);
  }

  //if middle and right sensor detects black line
  if((s1 == 1) && (s2 == 1) && (s3 == 0) && (s4 == 0) && (s5 == 1))
  {
    //going left with full speed 
    analogWrite(e1, 255); //you can adjust the speed of the motors from 0-255
    analogWrite(e2, 255); //you can adjust the speed of the motors from 0-255
    digitalWrite(m1, LOW);
    digitalWrite(m2, LOW);
    digitalWrite(m3, HIGH);
    digitalWrite(m4, LOW);
  }

  //if middle and left sensor detects black line
  if((s1 == 1) && (s2 == 0) && (s3 == 0) && (s4 == 1) && (s5 == 1))
  {
    //going right with full speed 
    analogWrite(e1, 255); //you can adjust the speed of the motors from 0-255
    analogWrite(e2, 255); //you can adjust the speed of the motors from 0-255
    digitalWrite(m1, HIGH);
    digitalWrite(m2, LOW);
    digitalWrite(m3, LOW);
    digitalWrite(m4, LOW);
  }

  //if middle, left and left most sensor detects black line
  if((s1 == 0) && (s2 == 0) && (s3 == 0) && (s4 == 1) && (s5 == 1))
  {
    //going right with full speed 
    analogWrite(e1, 255); //you can adjust the speed of the motors from 0-255
    analogWrite(e2, 255); //you can adjust the speed of the motors from 0-255
    digitalWrite(m1, HIGH);
    digitalWrite(m2, LOW);
    digitalWrite(m3, LOW);
    digitalWrite(m4, LOW);
  }

  //if middle, right and right most sensor detects black line
  if((s1 == 1) && (s2 == 1) && (s3 == 0) && (s4 == 0) && (s5 == 0))
  {
    //going left with full speed 
    analogWrite(e1, 255); //you can adjust the speed of the motors from 0-255
    analogWrite(e2, 255); //you can adjust the speed of the motors from 0-255
    digitalWrite(m1, LOW);
    digitalWrite(m2, LOW);
    digitalWrite(m3, HIGH);
    digitalWrite(m4, LOW);
  }

  //if all sensors are on a black line
  if((s1 == 0) && (s2 == 0) && (s3 == 0) && (s4 == 0) && (s5 == 0))
  {
    //stop
    digitalWrite(m1, LOW);
    digitalWrite(m2, LOW);
    digitalWrite(m3, LOW);
    digitalWrite(m4, LOW);
  }
}
*/
