int s1 = 8;
int s2 = 9;
int s3 = 10;
int s4 = 11;
int s5 = 12;
int out3R;
int out4R;
int out1L;
int out2L;
int pwmPin;

void setup() {
  Serial.begin(9600);
  pinMode(s1 ,INPUT);
  pinMode(s2 ,INPUT);
  pinMode(s3 ,INPUT);
  pinMode(s4 ,INPUT);
  pinMode(s5 ,INPUT);
}

void forward() {
  digitalWrite(out1L, HIGH);
  digitalWrite(out2L, LOW);
  digitalWrite(out3R, HIGH);
  digitalWrite(out4R, LOW);

}

void backward() {
  digitalWrite(out1L, LOW);
  digitalWrite(out2L, HIGH);
  digitalWrite(out3R, LOW);
  digitalWrite(out4R, HIGH);
}

void turnRight() {
  digitalWrite(out1L, HIGH);
  digitalWrite(out2L, LOW);
  digitalWrite(out3R, LOW);
  digitalWrite(out4R, HIGH);
}

void turnLeft() {
  digitalWrite(out1L, LOW);
  digitalWrite(out2L, HIGH);
  digitalWrite(out3R, HIGH);
  digitalWrite(out4R, LOW);
}



void loop() {
  Serial.println("s1 " + String(digitalRead(s1))); 
  Serial.println("s2 " +String(digitalRead(s2)));
  Serial.println("s3 " +String(digitalRead(s3)));
  Serial.println("s4 " +String(digitalRead(s4)));
  Serial.println("s5 " +String(digitalRead(s5))); //analogRead(s5)
  delay(200);
  if ( s5 == 0 or s4 == 0  ) {
    turnLeft();
  }
  if (s1 == 0 or s2 == 0) {
    turnRight();
  }
  if ( s3 == 0 or s3 == 0 and s2 == 0 and s4 ==0 ) {
    forward();
  }
  if ( s1 == 1 and s2 ==1 and s3 == 1 and s4 == 1 and s5 ==1 ){
    backward();
  }
}

// Code cho hệ thống điều khiển xe tự hành theo line
// #define m1 4  //Right Motor MA1
// #define m2 5  //Right Motor MA2
// #define m3 2  //Left Motor MB1
// #define m4 3  //Left Motor MB2
// #define e1 9  //Right Motor Enable Pin EA
// #define e2 10 //Left Motor Enable Pin EB

// //**********5 Channel IR Sensor Connection**********//
// #define ir1 A0
// #define ir2 A1
// #define ir3 A2
// #define ir4 A3
// #define ir5 A4
// //*************************************************//

// void setup() {
//   pinMode(m1, OUTPUT);
//   pinMode(m2, OUTPUT);
//   pinMode(m3, OUTPUT);
//   pinMode(m4, OUTPUT);
//   pinMode(e1, OUTPUT);
//   pinMode(e2, OUTPUT);
//   pinMode(ir1, INPUT);
//   pinMode(ir2, INPUT);
//   pinMode(ir3, INPUT);
//   pinMode(ir4, INPUT);
//   pinMode(ir5, INPUT);
// }

// void loop() {
//   //Reading Sensor Values
//   int s1 = digitalRead(ir1);  //Left Most Sensor
//   int s2 = digitalRead(ir2);  //Left Sensor
//   int s3 = digitalRead(ir3);  //Middle Sensor
//   int s4 = digitalRead(ir4);  //Right Sensor
//   int s5 = digitalRead(ir5);  //Right Most Sensor

//   //if only middle sensor detects black line
//   if((s1 == 1) && (s2 == 1) && (s3 == 0) && (s4 == 1) && (s5 == 1))
//   {
//     //going forward with full speed 
//     analogWrite(e1, 255); //you can adjust the speed of the motors from 0-255
//     analogWrite(e2, 255); //you can adjust the speed of the motors from 0-255
//     digitalWrite(m1, HIGH);
//     digitalWrite(m2, LOW);
//     digitalWrite(m3, HIGH);
//     digitalWrite(m4, LOW);
//   }
  
//   //if only left sensor detects black line
//   if((s1 == 1) && (s2 == 0) && (s3 == 1) && (s4 == 1) && (s5 == 1))
//   {
//     //going right with full speed 
//     analogWrite(e1, 255); //you can adjust the speed of the motors from 0-255
//     analogWrite(e2, 255); //you can adjust the speed of the motors from 0-255
//     digitalWrite(m1, HIGH);
//     digitalWrite(m2, LOW);
//     digitalWrite(m3, LOW);
//     digitalWrite(m4, LOW);
//   }
  
//   //if only left most sensor detects black line
//   if((s1 == 0) && (s2 == 1) && (s3 == 1) && (s4 == 1) && (s5 == 1))
//   {
//     //going right with full speed 
//     analogWrite(e1, 255); //you can adjust the speed of the motors from 0-255
//     analogWrite(e2, 255); //you can adjust the speed of the motors from 0-255
//     digitalWrite(m1, HIGH);
//     digitalWrite(m2, LOW);
//     digitalWrite(m3, LOW);
//     digitalWrite(m4, HIGH);
//   }

//   //if only right sensor detects black line
//   if((s1 == 1) && (s2 == 1) && (s3 == 1) && (s4 == 0) && (s5 == 1))
//   {
//     //going left with full speed 
//     analogWrite(e1, 255); //you can adjust the speed of the motors from 0-255
//     analogWrite(e2, 255); //you can adjust the speed of the motors from 0-255
//     digitalWrite(m1, LOW);
//     digitalWrite(m2, LOW);
//     digitalWrite(m3, HIGH);
//     digitalWrite(m4, LOW);
//   }

//   //if only right most sensor detects black line
//   if((s1 == 1) && (s2 == 1) && (s3 == 1) && (s4 == 1) && (s5 == 0))
//   {
//     //going left with full speed 
//     analogWrite(e1, 255); //you can adjust the speed of the motors from 0-255
//     analogWrite(e2, 255); //you can adjust the speed of the motors from 0-255
//     digitalWrite(m1, LOW);
//     digitalWrite(m2, HIGH);
//     digitalWrite(m3, HIGH);
//     digitalWrite(m4, LOW);
//   }

//   //if middle and right sensor detects black line
//   if((s1 == 1) && (s2 == 1) && (s3 == 0) && (s4 == 0) && (s5 == 1))
//   {
//     //going left with full speed 
//     analogWrite(e1, 255); //you can adjust the speed of the motors from 0-255
//     analogWrite(e2, 255); //you can adjust the speed of the motors from 0-255
//     digitalWrite(m1, LOW);
//     digitalWrite(m2, LOW);
//     digitalWrite(m3, HIGH);
//     digitalWrite(m4, LOW);
//   }

//   //if middle and left sensor detects black line
//   if((s1 == 1) && (s2 == 0) && (s3 == 0) && (s4 == 1) && (s5 == 1))
//   {
//     //going right with full speed 
//     analogWrite(e1, 255); //you can adjust the speed of the motors from 0-255
//     analogWrite(e2, 255); //you can adjust the speed of the motors from 0-255
//     digitalWrite(m1, HIGH);
//     digitalWrite(m2, LOW);
//     digitalWrite(m3, LOW);
//     digitalWrite(m4, LOW);
//   }

//   //if middle, left and left most sensor detects black line
//   if((s1 == 0) && (s2 == 0) && (s3 == 0) && (s4 == 1) && (s5 == 1))
//   {
//     //going right with full speed 
//     analogWrite(e1, 255); //you can adjust the speed of the motors from 0-255
//     analogWrite(e2, 255); //you can adjust the speed of the motors from 0-255
//     digitalWrite(m1, HIGH);
//     digitalWrite(m2, LOW);
//     digitalWrite(m3, LOW);
//     digitalWrite(m4, LOW);
//   }

//   //if middle, right and right most sensor detects black line
//   if((s1 == 1) && (s2 == 1) && (s3 == 0) && (s4 == 0) && (s5 == 0))
//   {
//     //going left with full speed 
//     analogWrite(e1, 255); //you can adjust the speed of the motors from 0-255
//     analogWrite(e2, 255); //you can adjust the speed of the motors from 0-255
//     digitalWrite(m1, LOW);
//     digitalWrite(m2, LOW);
//     digitalWrite(m3, HIGH);
//     digitalWrite(m4, LOW);
//   }

//   //if all sensors are on a black line
//   if((s1 == 0) && (s2 == 0) && (s3 == 0) && (s4 == 0) && (s5 == 0))
//   {
//     //stop
//     digitalWrite(m1, LOW);
//     digitalWrite(m2, LOW);
//     digitalWrite(m3, LOW);
//     digitalWrite(m4, LOW);
//   }
// }

