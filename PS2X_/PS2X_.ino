#include <PS2X_lib.h>  //for v1.6
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

/******************************************************************
   select modes of PS2 controller:
     - pressures = analog reading of push-butttons
     - rumble    = motor rumbling
   uncomment 1 of the lines for each mode selection
 ******************************************************************/

#define PS2_DAT        12   
#define PS2_CMD        10
#define PS2_SEL        11
#define PS2_CLK        13
#define ir1 8
#define ir2 7
#define ir3 6
#define ir4 5
#define ir5 4
//#define pressures   true
#define pressures   false
//#define rumble      true
#define rumble      false

PS2X ps2x; // create PS2 Controller Class

const int enaA = A0, enaB = A1; // enaA and enaB
const int out1 = 14, out2 = 15, out3 = 16, out4 = 17; //const int out1 = 7, out2 = 6, out3 = 5, out4 = 4;
int speedMotorA, speedMotorB;
int error = 0;
int countIR = 0;
int countPS2 = 0;
byte type = 0;
byte vibrate = 0;

bool isIrModeChosen(bool L1, bool R1) {
  Serial.println(countIR);
  if ( countIR == 0 && L1 == true && R1 == true) {
    countIR = 1;
    Serial.println("Mode: Following line");
    return true;
  }
  if ( countIR == 1 && L1 == true && R1 == true) {
    countIR = 0;
    Serial.println("STOP MODE FOLLOWING LINE");
    return false;
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
  }
  else if (error == 1)
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

void forwardMotor1() {
  digitalWrite(out1, HIGH);
  digitalWrite(out2, LOW);
}

void forwardMotor2() {
  digitalWrite(out3, HIGH);
  digitalWrite(out4, LOW);
}

void backwardMotor1() {
  digitalWrite(out1, LOW);
  digitalWrite(out2, HIGH);
}

void backwardMotor2() {
  digitalWrite(out3, LOW);
  digitalWrite(out4, HIGH);
}

void PS2() {
  int rightStickY = ps2x.Analog(PSS_RY);
  int leftStickY = ps2x.Analog(PSS_LY);
  int rightStickX = ps2x.Analog(PSS_RX);
  int leftStickX =  ps2x.Analog(PSS_LX);
  
  if ( leftStickY <= 127  ) {
    forwardMotor1();
    speedMotorA = map(abs(127-leftStickY), 0, 127, 0, 170);
  }
  
  if ( leftStickY >= 127  ) {
    backwardMotor1();
    speedMotorA = map(abs(127-leftStickY), 0, 127, 0, 170);
  }
  
  if ( rightStickY <= 127) {
    forwardMotor2();
    speedMotorB = map(abs(127-rightStickY), 0, 127, 0, 170);
  }

  if ( rightStickY >= 127  ) {
    backwardMotor2();
    speedMotorB = map(abs(127-rightStickY), 0, 127, 0, 170);
  }

  analogWrite(enaA, speedMotorA);
  analogWrite(enaB, speedMotorB);
  Serial.print("LY:  ");
  Serial.print(ps2x.Analog(PSS_LY), DEC); 
  Serial.print("   LX:  ");
  Serial.print(ps2x.Analog(PSS_LX), DEC);
  Serial.print("   RY:  ");
  Serial.print(ps2x.Analog(PSS_RY), DEC);
  Serial.print("   RX:  ");
  Serial.print(ps2x.Analog(PSS_RX), DEC);
  Serial.print("    A:  " + String(speedMotorA));
  Serial.println("    B:  " + String(speedMotorB));
  delay(50);
}

void IR() {
  int s1 = digitalRead(ir1);
  int s2 = digitalRead(ir2);  
  int s3 = digitalRead(ir3); 
  int s4 = digitalRead(ir4); 
  int s5 = digitalRead(ir5);  

  //if only middle sensor detects black line
  if((s1 == 1) && (s2 == 1) && (s3 == 0) && (s4 == 1) && (s5 == 1))
  {
    analogWrite(enaA, speedMotorA); 
    analogWrite(enaB, speedMotorB);
    digitalWrite(out1, HIGH);
    digitalWrite(out2, LOW);
    digitalWrite(out3, HIGH);
    digitalWrite(out4, LOW);
  }
  
  //if only left sensor detects black line
  if((s1 == 1) && (s2 == 0) && (s3 == 1) && (s4 == 1) && (s5 == 1))
  {
    analogWrite(enaA, speedMotorA); 
    analogWrite(enaB, speedMotorB); 
    digitalWrite(out1, HIGH);
    digitalWrite(out2, LOW);
    digitalWrite(out3, LOW);
    digitalWrite(out4, LOW);
  }
  
  //if only left most sensor detects black line
  if((s1 == 0) && (s2 == 1) && (s3 == 1) && (s4 == 1) && (s5 == 1))
  {
    analogWrite(enaA, speedMotorA);
    analogWrite(enaB, speedMotorB);
    digitalWrite(out1, HIGH);
    digitalWrite(out2, LOW);
    digitalWrite(out3, LOW);
    digitalWrite(out4, HIGH);
  }

  //if only right sensor detects black line
  if((s1 == 1) && (s2 == 1) && (s3 == 1) && (s4 == 0) && (s5 == 1))
  {
    analogWrite(enaA, speedMotorA); 
    analogWrite(enaB, speedMotorB); 
    digitalWrite(out1, LOW);
    digitalWrite(out2, LOW);
    digitalWrite(out3, HIGH);
    digitalWrite(out4, LOW);
  }

  //if only right most sensor detects black line
  if((s1 == 1) && (s2 == 1) && (s3 == 1) && (s4 == 1) && (s5 == 0))
  {
    analogWrite(enaA, speedMotorA); 
    analogWrite(enaB, speedMotorB); 
    digitalWrite(out1, LOW);
    digitalWrite(out2, HIGH);
    digitalWrite(out3, HIGH);
    digitalWrite(out4, LOW);
  }

  //if middle and right sensor detects black line
  if((s1 == 1) && (s2 == 1) && (s3 == 0) && (s4 == 0) && (s5 == 1))
  {
    analogWrite(enaA, speedMotorA); 
    analogWrite(enaB, speedMotorB); 
    digitalWrite(out1, LOW);
    digitalWrite(out2, LOW);
    digitalWrite(out3, HIGH);
    digitalWrite(out4, LOW);
  }

  //if middle and left sensor detects black line
  if((s1 == 1) && (s2 == 0) && (s3 == 0) && (s4 == 1) && (s5 == 1))
  {
    analogWrite(enaA, speedMotorA);
    analogWrite(enaB, speedMotorB);
    digitalWrite(out1, HIGH);
    digitalWrite(out2, LOW);
    digitalWrite(out3, LOW);
    digitalWrite(out4, LOW);
  }

  //if middle, left and left most sensor detects black line
  if((s1 == 0) && (s2 == 0) && (s3 == 0) && (s4 == 1) && (s5 == 1))
  { 
    analogWrite(enaA, speedMotorA);
    analogWrite(enaB, speedMotorB); 
    digitalWrite(out1, HIGH);
    digitalWrite(out2, LOW);
    digitalWrite(out3, LOW);
    digitalWrite(out4, LOW);
  }

  //if middle, right and right most sensor detects black line
  if((s1 == 1) && (s2 == 1) && (s3 == 0) && (s4 == 0) && (s5 == 0))
  {
    analogWrite(enaA, speedMotorA); 
    analogWrite(enaB, speedMotorB); 
    digitalWrite(out1, LOW);
    digitalWrite(out2, LOW);
    digitalWrite(out3, HIGH);
    digitalWrite(out4, LOW);
  }

  //if all sensors are on a black line
  if((s1 == 0) && (s2 == 0) && (s3 == 0) && (s4 == 0) && (s5 == 0))
  {
    //stop
    digitalWrite(out1, LOW);
    digitalWrite(out2, LOW);
    digitalWrite(out3, LOW);
    digitalWrite(out4, LOW);
  }
}

void setup() {

  Serial.begin(115200);
  lcd.init();
  lcd.backlight();
  pinMode(out1, OUTPUT);
  pinMode(out2, OUTPUT);
  pinMode(out3, OUTPUT);
  pinMode(out4, OUTPUT);
  pinMode(enaA, OUTPUT);
  pinMode(enaB, OUTPUT);
  analogWrite(speedMotorA, 0);
  analogWrite(speedMotorB, 0);
  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
  pinMode(ir3, INPUT);
  pinMode(ir4, INPUT);
  pinMode(ir5, INPUT);
  delay(300);  
  error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);
  checkError();
}

void chooseMode() {
  if ( isIrModeChosen(ps2x.Button(PSB_L1), ps2x.Button(PSB_R1))) {
    IR();
  }
}

void loop() {
  /* You must Read Gamepad to get new values and set vibration values
     ps2x.read_gamepad(small motor on/off, larger motor strenght from 0-255)
     if you don't enable the rumble, use ps2x.read_gamepad(); with no values
     You should call this at least once a second
  */
  if (error == 1) //skip loop if no controller found
    return;

  if (type == 2) { //Guitar Hero Controller
    ps2x.read_gamepad();          //read controller

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

    if (ps2x.Button(UP_STRUM))         //will be TRUE as long as button is pressed
      Serial.println("Up Strum");
    if (ps2x.Button(DOWN_STRUM))
      Serial.println("DOWN Strum");

    if (ps2x.Button(PSB_START))        //will be TRUE as long as button is pressed
      Serial.println("Start is being held");
    if (ps2x.Button(PSB_SELECT))
      Serial.println("Select is being held");

    if (ps2x.Button(ORANGE_FRET)) {    // print stick value IF TRUE
      Serial.print("Wammy Bar Position:");
      Serial.println(ps2x.Analog(WHAMMY_BAR), DEC);
    }
  }
  else { //DualShock Controller
    ps2x.read_gamepad(false, vibrate); //read controller and set large motor to spin at 'vibrate' speed

    if (ps2x.Button(PSB_START))        //will be TRUE as long as button is pressed
      Serial.println("Start is being held");
    if (ps2x.Button(PSB_SELECT))
      Serial.println("Select is being held");

    if (ps2x.Button(PSB_PAD_UP)) {     //will be TRUE as long as button is pressed
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

    if (ps2x.ButtonPressed(PSB_CIRCLE))              //will be TRUE if button was JUST pressed
      Serial.println("Circle just pressed");
    if (ps2x.NewButtonState(PSB_CROSS))              //will be TRUE if button was JUST pressed OR released
      Serial.println("X just changed");
    if (ps2x.ButtonReleased(PSB_SQUARE))             //will be TRUE if button was JUST released
      Serial.println("Square just released");

    if (ps2x.Button(PSB_L3) || ps2x.Button(PSB_R3)) { //print stick values if either is TRUE
      Serial.print("Stick Values:");
      Serial.print("LY:  ");
      Serial.print(ps2x.Analog(PSS_LY), DEC); //Left stick, Y axis. Other options: LX, RY, RX
      Serial.print("   LX:  ");
      Serial.print(ps2x.Analog(PSS_LX), DEC);
      Serial.print("   RY:  ");
      Serial.print(ps2x.Analog(PSS_RY), DEC);
      Serial.print("   RX:  ");
      Serial.println(ps2x.Analog(PSS_RX), DEC);
    }
  }
  chooseMode();
  delay(100);
}
