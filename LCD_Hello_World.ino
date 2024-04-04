#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd1(0x26,20,4);  // set the LCD address to 0x26 for a 20 chars and 4 line display

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

const int resetTarget1 = 42;
const int resetTarget2 = 43;
const int resetTarget3 = 44;
const int resetTarget4 = 45;
const int resetTarget5 = 46;
const int resetTarget6 = 47;

void setup() {
  lcd1.init();
  lcd1.clear();         
  lcd1.backlight();      // Make sure backlight is on
  
  lcd1.setCursor(0,0);   //Set cursor to character 0 on line 0
  lcd1.print("Target 1");
  
  lcd1.setCursor(0,1);   //Move cursor to character 0 on line 1
  lcd1.print("Target 2");
  lcd1.setCursor(0,2);   //Move cursor to character 0 on line 2
  lcd1.print("Target 3");
}

void loop() {
}
