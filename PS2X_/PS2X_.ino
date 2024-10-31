#include <PS2X_lib.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include <MPU6050_tockn.h>
#include <SoftwareSerial.h>


MPU6050 mpu6050(Wire);
SoftwareSerial mySerial(1, 0); //SIM800L Tx & Rx is connected to Arduino #3 & #2
const int rs = 14, e = 15, d4 = 16, d5 = 17, d6 = 18, d7 = 19;
LiquidCrystal lcd(rs, e, d4, d5, d6, d7);

/******************************************************************
   select modes of PS2 controller:
     - pressures = analog reading of push-butttons
     - rumble    = motor rumbling
   uncomment 1 of the lines for each mode selection
 ******************************************************************/

#define PS2_DAT 13  //12
#define PS2_CMD 12  //10
#define PS2_SEL 11  //11
#define PS2_CLK 10  //13
#define trigUsA 22
#define echoUsA 24
#define trigUsB 26
#define echoUsB 28
// #define ir1 5
// #define ir2 4
// #define ir3 3
// #define ir4 2
// #define ir5 1
#define buzzerPin A5 
#define vibrationPin A4
//#define pressures   true
#define pressures false
//#define rumble      true
#define rumble false

PS2X ps2x;  // create PS2 Controller Class

int enaAL = 9, enaAR = 8, enaBL = 7, enaBR = 6;
const int pwmAL = 2, pwmAR = 3, pwmBL = 5, pwmBR = 4;
const int vibrationThreshold = 600;
const int angleThreshold = 70;

int leftStickY = 0, rightStickY = 0;
int error = 0;
int countPS2 = 0;
// int countIR = 0;
int vibration;
int obstacleA;
int obstacleB;
// int speedMotorIR;

float angleX;
float angleY;
float angleZ;

byte type = 0;
byte vibrate = 0;

byte ahead[] = {
  B00100,
  B01110,
  B10101,
  B00100,
  B00100,
  B00100,
  B00100,
  B00100,
};

byte behind[] = {
  B00100,
  B00100,
  B00100,
  B00100,
  B00100,
  B10101,
  B01110,
  B00100,
};

bool isPs2ModeChosen(bool L2, bool R2) {
  if (countPS2 == 0 && L2 == true && R2 == true) {
    countPS2 = 1;
    // countIR = 0;
    Serial.println("Mode: PS2");
    clearLCD1();
    return true;
  }
  if (countPS2 == 1 && L2 == true && R2 == true) {
    countPS2 = 0;
    Serial.println("STOP PS2 MODE");
    clearLCD1();
    return false;
  }
  return false;
}

// bool isIrModeChosen(bool L1, bool R1) {
//   if (countIR == 0 && L1 == true && R1 == true) {
//     countIR = 1;
//     countPS2 = 0;
//     Serial.println("Mode: Following line");
//     clearLCD1();
//     return true;
//   }
//   if (countIR == 1 && L1 == true && R1 == true) {
//     countIR = 0;
//     Serial.println("STOP FOLLOWING LINE MODE");
//     clearLCD1();
//     return false;
//   }
//   return false;
// }

// int calculateDistance(const int trig, const int echo) {
//   unsigned long duration;
//   int distance;           
//   digitalWrite(trig,0);   
//   delayMicroseconds(2);
//   digitalWrite(trig,1);  
//   delayMicroseconds(5);   
//   digitalWrite(trig,0);
//   duration = pulseIn(echo,HIGH);  
//   distance = int(duration/2/29.412);
//   Serial.println(distance);
//   return distance
// }

bool isFallen(float x, float y, float z) {
  if (abs(x) > angleThreshold) {
    return true;
  }
  if (abs(y) > angleThreshold) {
    return true;
  }
  // if ( abs(z) > angleThreshold ) {
  //   return true;
  // }
  return false;
}

bool isVibrated(int a) {
  if (a < vibrationThreshold) {
    return true;
  }
  return false;
}

void checkError() {
  if (error == 0) {
    Serial.print("Found Controller, configured successful ");
    Serial.print("pressures = ");
    if (pressures)
      Serial.println("true ");
    else
      Serial.println("false");
    Serial.print("rumble = ");
    if (rumble)
      Serial.println("true)");
    else
      Serial.println("false");
    Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
    Serial.println("holding L1 or R1 will print out the analog stick values.");
    Serial.println("Note: Go to www.billporter.info for updates and to report bugs.");
  } else if (error == 1)
    Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");

  else if (error == 2)
    Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");

  else if (error == 3)
    Serial.println("Controller refusing to enter Pressures mode, may not support it. ");

  //  Serial.print(ps2x.Analog(1), HEX);

  type = ps2x.readType();
  switch (type) {
    case 0:
      Serial.print("Unknown Controller type found ");
      break;
    case 1:
      Serial.print("DualShock Controller found ");
      break;
    case 2:
      Serial.print("GuitarHero Controller found ");
      break;
    case 3:
      Serial.print("Wireless Sony DualShock Controller found ");
      break;
  }
}

void clearLCD1() {
  lcd.setCursor(0,0);
  lcd.print("                 ");
}

void clearLCD2() {
  lcd.setCursor(0,1);
  lcd.print("                 ");
}

void enaMotor() {
  digitalWrite(enaAL, HIGH);
  digitalWrite(enaAR, HIGH);
  digitalWrite(enaBL, HIGH);
  digitalWrite(enaBR, HIGH);
}

void PS2() {
  rightStickY = map(abs(127 - ps2x.Analog(PSS_RY)), 0, 127, 0, 200);  //150
  leftStickY = map(abs(127 - ps2x.Analog(PSS_LY)), 0, 127, 0, 200);   //150
  
  if (ps2x.Analog(PSS_LY) < 120) {
    analogWrite(pwmAL, leftStickY);
    analogWrite(pwmAR, 0);
  }
  if (ps2x.Analog(PSS_LY) > 135) {
    analogWrite(pwmAL, 0);
    analogWrite(pwmAR, leftStickY);
  }
  if (ps2x.Analog(PSS_LY) >= 120 && ps2x.Analog(PSS_LY) <= 135) {
    analogWrite(pwmAL, 0);
    analogWrite(pwmAR, 0);
  }

  if (ps2x.Analog(PSS_RY) < 120) {
    analogWrite(pwmBL, rightStickY);
    analogWrite(pwmBR, 0);
  }
  if (ps2x.Analog(PSS_RY) > 135) {
    analogWrite(pwmBL, 0);
    analogWrite(pwmBR, rightStickY);
  }
  if (ps2x.Analog(PSS_RY) >= 120 && ps2x.Analog(PSS_RY) <= 135) {
    analogWrite(pwmBL, 0);
    analogWrite(pwmBR, 0);
  }

  Serial.print("LY:  ");
  Serial.print(ps2x.Analog(PSS_LY), DEC);
  Serial.print("   LX:  ");
  Serial.print(ps2x.Analog(PSS_LX), DEC);
  Serial.print("   RY:  ");
  Serial.print(ps2x.Analog(PSS_RY), DEC);
  Serial.print("   RX:  ");
  Serial.print(ps2x.Analog(PSS_RX), DEC);
  Serial.print("    A:  " + String(leftStickY));
  Serial.println("    B:  " + String(rightStickY));
}
/*
void IR() {
  int s1 = digitalRead(ir1);
  int s2 = digitalRead(ir2);
  int s3 = digitalRead(ir3);
  int s4 = digitalRead(ir4);
  int s5 = digitalRead(ir5);

  // create a mode to increase and decrease the chosen speed from 0 - 50%
  if ( ps2x.Button(PSB_PAD_UP) ) {
    speedMotorIR = speedMotorIR + 1;
  }
  if ( ps2x.Button(PSB_PAD_DOWN )) {
    speedMotorIR = speedMotorIR - 1;
  }

  if (speedMotorIR < 0) {
    speedMotorIR = 0;
  } 
  if (speedMotorIR > 50) {
    speedMotorIR = 50;
  }

  Serial.println("irSpeed" + String(speedMotorIR));
  //if only middle sensor detects black line
  if ((s1 == 1) && (s2 == 1) && (s3 == 0) && (s4 == 1) && (s5 == 1)) {
    analogWrite(pwmAL, 0);
    analogWrite(pwmAR, speedMotorIR);
    analogWrite(pwmBL, 0);
    analogWrite(pwmBR, speedMotorIR);
  }

  //if only left sensor detects black line
  if ((s1 == 1) && (s2 == 0) && (s3 == 1) && (s4 == 1) && (s5 == 1)) {
    analogWrite(pwmAL, speedMotorIR);
    analogWrite(pwmAR, 0);
    analogWrite(pwmBL, 0);
    analogWrite(pwmBR, 0);
  }

  //if only left most sensor detects black line
  if ((s1 == 0) && (s2 == 1) && (s3 == 1) && (s4 == 1) && (s5 == 1)) {
    analogWrite(pwmAL, speedMotorIR);
    analogWrite(pwmAR, 0);
    analogWrite(pwmBL, 0);
    analogWrite(pwmBR, speedMotorIR);
  }

  //if only right sensor detects black line
  if ((s1 == 1) && (s2 == 1) && (s3 == 1) && (s4 == 0) && (s5 == 1)) {
    analogWrite(pwmAL, 0);
    analogWrite(pwmAR, 0);
    analogWrite(pwmBL, speedMotorIR);
    analogWrite(pwmBR, 0);
  }

  //if only right most sensor detects black line
  if ((s1 == 1) && (s2 == 1) && (s3 == 1) && (s4 == 1) && (s5 == 0)) {
    analogWrite(pwmAL, 0);
    analogWrite(pwmAR, speedMotorIR);
    analogWrite(pwmBL, speedMotorIR);
    analogWrite(pwmBR, 0);
    }

  //if middle and right sensor detects black line
  if ((s1 == 1) && (s2 == 1) && (s3 == 0) && (s4 == 0) && (s5 == 1)) {
    analogWrite(pwmAL, 0);
    analogWrite(pwmAR, 0);
    analogWrite(pwmBL, speedMotorIR);
    analogWrite(pwmBR, 0);
  }

  //if middle and left sensor detects black line
  if ((s1 == 1) && (s2 == 0) && (s3 == 0) && (s4 == 1) && (s5 == 1)) {
    analogWrite(pwmAL, speedMotorIR);
    analogWrite(pwmAR, 0);
    analogWrite(pwmBL, 0);
    analogWrite(pwmBR, 0);
  }

  //if middle, left and left most sensor detects black line
  if ((s1 == 0) && (s2 == 0) && (s3 == 0) && (s4 == 1) && (s5 == 1)) {
    analogWrite(pwmAL, speedMotorIR);
    analogWrite(pwmAR, 0);
    analogWrite(pwmBL, 0);
    analogWrite(pwmBR, 0);
  }

  //if middle, right and right most sensor detects black line
  if ((s1 == 1) && (s2 == 1) && (s3 == 0) && (s4 == 0) && (s5 == 0)) {
    analogWrite(pwmAL, 0);
    analogWrite(pwmAR, 0);
    analogWrite(pwmBL, speedMotorIR);
    analogWrite(pwmBR, 0);
  }
  //if all sensors are on a black line
  if ((s1 == 0) && (s2 == 0) && (s3 == 0) && (s4 == 0) && (s5 == 0)) {
    //stop
    analogWrite(pwmAL, 0);
    analogWrite(pwmAR, 0);
    analogWrite(pwmBL, 0);
    analogWrite(pwmBR, 0);
  }
}   
*/

void buzzer() {
  tone(buzzerPin, 2000, 2000);
}

// void ultraSonic() {
//     unsigned long duration;
//     int distance;           
//     digitalWrite(trig,0);   
//     delayMicroseconds(2);
//     digitalWrite(trig,1);   
//     delayMicroseconds(5);   
//     digitalWrite(trig,0);   
//     duration = pulseIn(echo,HIGH);  
//     distance = int(duration/2/29.412);
//     Serial.print(distance);
//     Serial.println("cm");
// }

void chooseMode() {
  // if (isIrModeChosen(ps2x.Button(PSB_L1), ps2x.Button(PSB_R1))) {
  //   IR();
  // }
  // else if (isPs2ModeChosen(ps2x.Button(PSB_L2), ps2x.Button(PSB_R2))) {
  if (isPs2ModeChosen(ps2x.Button(PSB_L2), ps2x.Button(PSB_R2))) {
    PS2();
  }
}

void startMode() {
  // if (countPS2 == 1 && countIR == 0) {
  if (countPS2 == 1) {
    PS2();
    lcd.setCursor(0, 0);
    lcd.print("PS2");
    lcd.setCursor(8, 0);
    lcd.print(leftStickY);
    lcd.setCursor(12, 0);
    lcd.print(rightStickY);
  }

  // if (countPS2 == 0 && countIR == 1) {
  //   IR();
  //   int count = 0;
  //   // lcd.clear();
  //   lcd.setCursor(0, 0);
  //   lcd.print("IR");
  //   lcd.setCursor(8, 0);
  //   lcd.print(speedMotorIR);
  //   lcd.setCursor(12, 0);
  //   lcd.print(speedMotorIR);
  // }
  // if (countPS2 == 0 && countIR == 0) {
  if (countPS2 == 0 ) {
    lcd.setCursor(0, 0);
    lcd.print("Mode: MANUAL");
    digitalWrite(pwmAL, 0);
    digitalWrite(pwmAR, 0);
    digitalWrite(pwmBL, 0);
    digitalWrite(pwmBR, 0);
  }
}

void getAngleAndVibration() {
  mpu6050.update();
  Serial.print("angleX : ");
  angleX = mpu6050.getAngleX();
  Serial.print(angleX);
  Serial.print("\tangleY : ");
  angleY = mpu6050.getAngleY();
  Serial.print(angleY);
  Serial.print("\tangleZ : ");
  angleZ = mpu6050.getAngleZ();
  Serial.println(angleZ);
  // Serial.print("  accX : ");Serial.print(mpu6050.getAccX());
  // Serial.print("  accY : ");Serial.print(mpu6050.getAccY());
  // Serial.println(" taccZ : ");Serial.println(mpu6050.getAccZ());
  vibration = analogRead(vibrationPin);
  Serial.println("vibration: " + String(vibration));
  if (isFallen(angleX, angleY, angleZ) && isVibrated(vibration)) {
    buzzer();
    updateSerial();
  }
}

void SIM()
{
  mySerial.begin(9600);
  Serial.println("Initializing...");
  delay(1000);

  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();

  mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();
  mySerial.println("AT+CMGS=\"+84326510251\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
  updateSerial();
  mySerial.write(26);
}

void updateSerial()
{
  Serial.write("Xe bi lat");
}


void setup() {
  Serial.begin(115200);
  Wire.begin();
  lcd.begin(16, 2);
  lcd.setCursor(4, 0);
  lcd.print("Starting");
  lcd.setCursor(1, 1);
  lcd.print("Please Waiting");
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
  // SIM();
  pinMode(enaAL, OUTPUT);
  pinMode(enaAR, OUTPUT);
  pinMode(pwmAL, OUTPUT);
  pinMode(pwmAR, OUTPUT);
  pinMode(enaBL, OUTPUT);
  pinMode(enaBR, OUTPUT);
  pinMode(pwmBL, OUTPUT);
  pinMode(pwmBR, OUTPUT);
  pinMode(trigUsA, OUTPUT);
  pinMode(echoUsA, INPUT);
  pinMode(trigUsB, OUTPUT);
  pinMode(echoUsB, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(vibrationPin, INPUT);
  digitalWrite(enaAL, 0);
  digitalWrite(enaAR, 0);
  digitalWrite(enaBL, 0);
  digitalWrite(enaBR, 0);
  // pinMode(ir1, INPUT);
  // pinMode(ir2, INPUT);
  // pinMode(ir3, INPUT);
  // pinMode(ir4, INPUT);
  // pinMode(ir5, INPUT);
  // lcd.createChar(0, ahead);
  // lcd.createChar(1, behind);
  error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);
  checkError();
  delay(300);
  lcd.clear();
  // countIR = 0;
  countPS2 = 0;

  if (error == 0) {
    lcd.setCursor(4, 0);
    lcd.print("WELCOME");
    delay(2000);
  }

  if (error != 0) {
    lcd.setCursor(3, 0);
    lcd.print("TRY AGAIN");
    delay(2000);
  }
}

void loop() {
  /* You must Read Gamepad to get new values and set vibration values
     ps2x.read_gamepad(small motor on/off, larger motor strenght from 0-255)
     if you don't enable the rumble, use ps2x.read_gamepad(); with no values
     You should call this at least once a second
  */

  if (error == 1)  //skip loop if no controller found
    return;

  if (type == 2) {        //Guitar Hero Controller
    ps2x.read_gamepad();  //read controller

    if (ps2x.ButtonPressed(GREEN_FRET))
      Serial.println("Green Fret Pressed");
    if (ps2x.ButtonPressed(RED_FRET))
      Serial.println("Red Fret Pressed");
    if (ps2x.ButtonPressed(YELLOW_FRET))
      Serial.println("Yellow Fret Pressed");
    if (ps2x.ButtonPressed(BLUE_FRET))
      Serial.println("Blue Fret Pressed");
    if (ps2x.ButtonPressed(ORANGE_FRET))
      Serial.println("Orange Fret Pressed");

    if (ps2x.ButtonPressed(STAR_POWER))
      Serial.println("Star Power Command");

    if (ps2x.Button(UP_STRUM))  //will be TRUE as long as button is pressed
      Serial.println("Up Strum");
    if (ps2x.Button(DOWN_STRUM))
      Serial.println("DOWN Strum");

    if (ps2x.Button(PSB_START))  //will be TRUE as long as button is pressed
      Serial.println("Start is being held");
    if (ps2x.Button(PSB_SELECT))
      Serial.println("Select is being held");

    if (ps2x.Button(ORANGE_FRET)) {  // print stick value IF TRUE
      Serial.print("Wammy Bar Position:");
      Serial.println(ps2x.Analog(WHAMMY_BAR), DEC);
    }
  } else {                              //DualShock Controller
    ps2x.read_gamepad(false, vibrate);  //read controller and set large motor to spin at 'vibrate' speed

    if (ps2x.Button(PSB_START))  //will be TRUE as long as button is pressed
      Serial.println("Start is being held");
    if (ps2x.Button(PSB_SELECT))
      Serial.println("Select is being held");

    if (ps2x.Button(PSB_PAD_UP)) {  //will be TRUE as long as button is pressed
      Serial.print("Up held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_UP), DEC);
    }
    if (ps2x.Button(PSB_PAD_RIGHT)) {
      Serial.print("Right held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_RIGHT), DEC);
    }
    if (ps2x.Button(PSB_PAD_LEFT)) {
      Serial.print("LEFT held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_LEFT), DEC);
    }
    if (ps2x.Button(PSB_PAD_DOWN)) {
      Serial.print("DOWN held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_DOWN), DEC);
    }

    vibrate = ps2x.Analog(PSAB_CROSS);  //this will set the large motor vibrate speed based on how hard you press the blue (X) button
    if (ps2x.NewButtonState()) {        //will be TRUE if any button changes state (on to off, or off to on)
      if (ps2x.Button(PSB_L3))
        Serial.println("L3 pressed");
      if (ps2x.Button(PSB_R3))
        Serial.println("R3 pressed");
      if (ps2x.Button(PSB_L2))
        Serial.println("L2 pressed");
      if (ps2x.Button(PSB_R2))
        Serial.println("R2 pressed");
      if (ps2x.Button(PSB_L1))
        Serial.println("L1 pressed");
      if (ps2x.Button(PSB_R1))
        Serial.println("R1 pressed");
      if (ps2x.Button(PSB_TRIANGLE))
        Serial.println("Triangle pressed");
    }

    if (ps2x.ButtonPressed(PSB_CIRCLE))  //will be TRUE if button was JUST pressed
      Serial.println("Circle just pressed");
    if (ps2x.NewButtonState(PSB_CROSS))  //will be TRUE if button was JUST pressed OR released
      Serial.println("X just changed");
    if (ps2x.ButtonReleased(PSB_SQUARE))  //will be TRUE if button was JUST released
      Serial.println("Square just released");

    if (ps2x.Button(PSB_L3) || ps2x.Button(PSB_R3)) {  //print stick values if either is TRUE
      Serial.print("Stick Values:");
      Serial.print("LY:  ");
      Serial.print(ps2x.Analog(PSS_LY), DEC);  //Left stick, Y axis. Other options: LX, RY, RX
      Serial.print("   LX:  ");
      Serial.print(ps2x.Analog(PSS_LX), DEC);
      Serial.print("   RY:  ");
      Serial.print(ps2x.Analog(PSS_RY), DEC);
      Serial.print("   RX:  ");
      Serial.println(ps2x.Analog(PSS_RX), DEC);
    }
  }
  
  enaMotor();
  chooseMode();
  startMode();
  // ultraSonic();
  getAngleAndVibration();
  delay(70);
  lcd.clear();
}
