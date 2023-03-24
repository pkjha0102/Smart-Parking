#include <Servo.h>  //includes the servo library
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);

Servo myservo;

#define enter 7
#define back 9

#define car1 10
#define car2 11
#define car3 12
#define car4 13

int S1 = 0, S2 = 0, S3 = 0, S4 = 0;
int flag1 = 0, flag2 = 0;
int slot = 4;

void setup() {
  Serial.begin(9600);

  pinMode(car1, INPUT);
  pinMode(car2, INPUT);
  pinMode(car3, INPUT);
  pinMode(car4, INPUT);

  pinMode(enter, INPUT);
  pinMode(back, INPUT);

  myservo.attach(8);
  myservo.write(90);

  lcd.begin(20, 4, 80);
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("      Welcome!      ");
  lcd.setCursor(0, 1);
  lcd.print("    Car  parking  ");
  lcd.setCursor(0, 2);
  lcd.print("       System     ");
  delay(2000);
  lcd.clear();

  Read_Sensor();

  int total = S1 + S2 + S3 + S4;
  slot = slot - total;
}

void loop() {

  Read_Sensor();

  if(slot != 0)
  {
    lcd.setCursor(0, 0);
    lcd.print("      Welcome!      ");
  }
  else
  {
    lcd.setCursor(0, 0);
    lcd.print("       Sorry!       ");
  }
  lcd.setCursor(0, 1);
  lcd.print("    Slots  left: ");
  lcd.print(slot);
 

  lcd.setCursor(0, 2);
  if (S1 == 1) {
    lcd.print("S1:Full ");
  } else {
    lcd.print("S1:Empty");
  }

  lcd.setCursor(10, 2);
  if (S2 == 1) {
    lcd.print("S2:Full ");
  } else {
    lcd.print("S2:Empty");
  }

  lcd.setCursor(0, 3);
  if (S3 == 1) {
    lcd.print("S3:Full ");
  } else {
    lcd.print("S3:Empty");
  }

  lcd.setCursor(10, 3);
  if (S4 == 1) {
    lcd.print("S4:Full ");
  } else {
    lcd.print("S4:Empty");
  }


  if (digitalRead(enter) == 0 && flag1 == 0) {
    if (slot > 0) {
      flag1 = 1;
      if (flag2 == 0) {
        myservo.write(180);
        slot = slot - 1;
      }
    } else {
      lcd.clear();
       lcd.setCursor(0, 0);
       lcd.print("     Hard Luck     ");
       lcd.setCursor(0, 1);
       lcd.print("   Couldn't  find   ");
       lcd.setCursor(0, 2);
       lcd.print("   empty   slot!    ");
       delay(1500);
    }
  }

  if (digitalRead(back) == 0 && flag2 == 0) {
    flag2 = 1;
    if (flag1 == 0) {
      myservo.write(180);
      slot = slot + 1;
    }
  }

  if (flag1 == 1 && flag2 == 1) {
    delay(1000);
    myservo.write(90);
    flag1 = 0, flag2 = 0;
  }

  delay(1);
}

void Read_Sensor() {
  S1 = 0, S2 = 0, S3 = 0, S4 = 0;

  if (digitalRead(car1) == 0) { S1 = 1; }
  if (digitalRead(car2) == 0) { S2 = 1; }
  if (digitalRead(car3) == 0) { S3 = 1; }
  if (digitalRead(car4) == 0) { S4 = 1; }
}