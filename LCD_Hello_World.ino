/*
Originally developed by Jackson McMillen and Garrett Cline
For use by Newton's Attic

Required Libraries to dowload:
LiquidCrystal I2C library by Marco Schwartz

*/

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd1(0x26,20,4);  // set the LCD address to 0x26 for a 20 chars and 4 line display
LiquidCrystal_I2C lcd2(0x27,20,4);  // set the LCD address to 0x26 for a 20 chars and 4 line display
LiquidCrystal_I2C lcd3(0x25,20,4);  // set the LCD address to 0x26 for a 20 chars and 4 line display

const int lockTarget1 = 22;
const int lockTarget2 = 23;
const int lockTarget3 = 24;
const int lockTarget4 = 25;
const int lockTarget5 = 26;
const int lockTarget6 = 27;

const int motorTarget1 = 28;
const int motorTarget2 = 29;
const int motorTarget3 = 30;
const int motorTarget4 = 31;
const int motorTarget5 = 32;
const int motorTarget6 = 33;

const int sensorTarget1 = 48;
const int sensorTarget2 = 49;
const int sensorTarget3 = 50;
const int sensorTarget4 = 51;
const int sensorTarget5 = 52;
const int sensorTarget6 = 53;

const int resetTargetButton1 = 42;
const int resetTargetButton2 = 43;
const int resetTargetButton3 = 44;
const int resetTargetButton4 = 45;
const int resetTargetButton5 = 46;
const int resetTargetButton6 = 47;

const int resetTargetAllButton = 41;

const int randomLockButton = 40; 

const int incrTime5Button = 36;
const int incrTime30Button = 37;
const int decrTime5Button = 38;
const int decrTime30Button = 39;

const int startStopButton = 35;


void setup() {
  lcd1.init();
  lcd1.clear();         
  lcd1.backlight();      // Make sure backlight is on
  lcd2.init();
  lcd2.clear();         
  lcd2.backlight();      // Make sure backlight is on
  lcd3.init();
  lcd3.clear();         
  lcd3.backlight();      // Make sure backlight is on
  
  lcd1.setCursor(0,0);   //Set cursor to character 0 on line 0
  lcd1.print("Target 1");
  
  lcd1.setCursor(0,1);   //Move cursor to character 0 on line 1
  lcd1.print("Target 2");
  lcd1.setCursor(0,2);   //Move cursor to character 0 on line 2
  lcd1.print("Target 3");

  lcd2.setCursor(0,0);   //Set cursor to character 0 on line 0
  lcd2.print("Target 4");
  
  lcd2.setCursor(0,1);   //Move cursor to character 0 on line 1
  lcd2.print("Target 5");
  lcd2.setCursor(0,2);   //Move cursor to character 0 on line 2
  lcd2.print("Target 6");

  pinMode(lockTarget1, OUTPUT);
  pinMode(lockTarget2, OUTPUT);
  pinMode(lockTarget3, OUTPUT);
  pinMode(lockTarget4, OUTPUT);
  pinMode(lockTarget5, OUTPUT);
  pinMode(lockTarget6, OUTPUT);

  pinMode(motorTarget1, OUTPUT);
  pinMode(motorTarget2, OUTPUT);
  pinMode(motorTarget3, OUTPUT);
  pinMode(motorTarget4, OUTPUT);
  pinMode(motorTarget5, OUTPUT);
  pinMode(motorTarget6, OUTPUT);

  pinMode(sensorTarget1, INPUT);
  pinMode(sensorTarget2, INPUT);
  pinMode(sensorTarget3, INPUT);
  pinMode(sensorTarget4, INPUT);
  pinMode(sensorTarget5, INPUT);
  pinMode(sensorTarget6, INPUT);

  pinMode(resetTargetButton1, INPUT);
  pinMode(resetTargetButton2, INPUT);
  pinMode(resetTargetButton3, INPUT);
  pinMode(resetTargetButton4, INPUT);
  pinMode(resetTargetButton5, INPUT);
  pinMode(resetTargetButton6, INPUT);

  pinMode(resetTargetAllButton, INPUT);

  pinMode(randomLockButton, INPUT);

  pinMode(incrTime5Button, INPUT);
  pinMode(incrTime30Button, INPUT);
  pinMode(decrTime5Button, INPUT);
  pinMode(decrTime30Button, INPUT);

  pinMode(startStopButton, INPUT);
}

void loop() {
}
