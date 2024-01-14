#include <LiquidCrystal.h>
LiquidCrystal lcd(7,6,5,4,3,2); 

int cheDo;
int valCD1, valCD2, valCD3;
int bt1 = 8;
int bt2 = 9;
bool preB1 = HIGH;
bool preB2 = HIGH;


void setup() {
  lcd.begin(16,2);
  Serial.begin(9600);
  pinMode(bt1, INPUT);
  pinMode(bt2, INPUT);
  cheDo = 1;
  valCD1 = 0;
  valCD2 = 0;
  valCD3 = 0;
}

void loop() {
  int val1 = digitalRead(bt1);
  int val2 = digitalRead(bt2);
  lcd.setCursor(0,0);
  lcd.print("CHE DO");
  if (val2 == LOW && preB1 == HIGH ) 
  {
    cheDo = cheDo + 1;
    delay(50);
  }
  preB1 = val2;
  if ( cheDo == 4) 
  {
    cheDo = 1;
  }
  if ( cheDo == 1)
  {
    lcd.setCursor(8,0);
    lcd.print("A :");
    if (val1 == LOW && preB2 == HIGH) 
    {
      valCD1++;
      delay(50);
    }
    preB2 = val1;
    lcd.setCursor(12,0);
    lcd.print(valCD1);    
  }
  else if ( cheDo == 2)
  {
    lcd.setCursor(8,0);
    lcd.print("B :");
    if (val1 == LOW && preB2 == HIGH) 
    {
      valCD2++;
      delay(50);
    }
    preB2 = val1;
    lcd.setCursor(12,0);
    lcd.print(valCD2);
  }
  else if ( cheDo == 3)
  {
    lcd.setCursor(8,0);
    lcd.print("C :");
    if (val1 == LOW && preB2 == HIGH) 
    {
      valCD3++;
      delay(50);
    }
    preB2 = val1;
    lcd.setCursor(12,0);
    lcd.print(valCD3);
  }
  Serial.println(cheDo);
}