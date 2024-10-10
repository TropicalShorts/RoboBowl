/*
Originally developed by Jackson McMillen and Garrett Cline
For use by Newton's Attic

Required Libraries to dowload:
LiquidCrystal I2C library by Marco Schwartz

*/

#include <LiquidCrystal_I2C.h>
#include <YetAnotherPcInt.h>

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

const int sensorTarget1 = 10;
const int sensorTarget2 = 11;
const int sensorTarget3 = 12;
const int sensorTarget4 = 13;
const int sensorTarget5 = 14;
const int sensorTarget6 = 15;

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

unsigned long startTime = 0;
unsigned long state3time = 0;
unsigned long elapsedTime = 0;
unsigned long elapsedTimePause = 0;
unsigned long pauseStartTime = 0;
unsigned long secondTime = 0;

int i = 0;
int team1Score = 0;
int team2Score = 0;

bool paused = false;
bool firstCheckDispalyState1 = true;
bool firstCheckDisplaySecond = true;
bool needToResetTime = false;
int currentState = 0;

static unsigned long lastSecondPrinted = 0;  // Variable to store the last time a second was printed
static int remainingSeconds = 10;            // Variable to store the remaining seconds

bool pinState1 = true;
bool pinState2 = true;
bool pinState3 = true;
bool pinState4 = true;
bool pinState5 = true;
bool pinState6 = true;

void pinChange1(){
  Serial.println("Pin 1 knocked down");
  pinState1 = !pinState1;
}
void pinChange2(){
  Serial.println("Pin 2 knocked down");
  pinState2 = !pinState2;
}
void pinChange3(){
  Serial.println("Pin 3 knocked down");
  pinState3 = !pinState3;
}
void pinChange4(){
  Serial.println("Pin 4 knocked down");
  pinState4 = !pinState4;
}
void pinChange5(){
  Serial.println("Pin 5 knocked down");
  pinState5 = !pinState5;
}
void pinChange6(){
  Serial.println("Pin 6 knocked down");
  pinState6 = !pinState6;
}

void setup() {
  Serial.begin(9600);
  Serial.println("Check 1");
  
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
  lcd1.print("Target 1: UP");
  
  lcd1.setCursor(0,1);   //Move cursor to character 0 on line 1
  lcd1.print("Target 2: UP");
  lcd1.setCursor(0,2);   //Move cursor to character 0 on line 2
  lcd1.print("Target 3: UP");

  lcd2.setCursor(0,0);   //Set cursor to character 0 on line 0
  lcd2.print("Target 4: UP");
  
  lcd2.setCursor(0,1);   //Move cursor to character 0 on line 1
  lcd2.print("Target 5: UP");
  lcd2.setCursor(0,2);   //Move cursor to character 0 on line 2
  lcd2.print("Target 6: UP");
  

  Serial.println("Check 2");

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

  //PCMSK0 |= (1 << PCINT4);//pin 10 - B4 - Rx Channel 5
  PcInt::attachInterrupt(sensorTarget1, pinChange1, CHANGE);
  PcInt::attachInterrupt(sensorTarget2, pinChange2, CHANGE);
  PcInt::attachInterrupt(sensorTarget3, pinChange3, CHANGE);
  PcInt::attachInterrupt(sensorTarget4, pinChange4, CHANGE);
  PcInt::attachInterrupt(sensorTarget5, pinChange5, CHANGE);
  PcInt::attachInterrupt(sensorTarget6, pinChange6, CHANGE);

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
  switch(currentState) {
    case 0:                                         // Waiting for button input to begin the game
      if (firstCheckDispalyState1){
        Serial.println("In state 0");
        firstCheckDispalyState1 = false;
      }

      lcd3.setCursor(0,0);
      lcd3.print("Waiting to begin");

      if (digitalRead(startStopButton) == HIGH) {   // If button is pressed
        Serial.println("Start button pressed");
        lcd3.clear();
        lcd3.print("Begining round!");
        currentState = 1;  
        startTime = millis();
        delay(1000);
        lcd3.clear();
        lcd3.print("Game on!");
      }
      break;
      
    case 1:  // State 1: Wait for a minute

      static unsigned long previousMillis = 0;
      static int countdown = 31;

      if(needToResetTime){
        countdown = 31;
        needToResetTime = false;
      }

      while (countdown > 0 && !paused) {

        if(digitalRead(startStopButton)==HIGH || digitalRead(incrTime5Button)==HIGH){
        Serial.println("Pause started");
        lcd3.setCursor(0,2);
        lcd3.print("Paused");
        currentState = 2;
        pauseStartTime = millis();
        paused = true;
        }

        if(pinState1 == false){
          lcd1.setCursor(0,0);
          lcd1.print("Target 1: DOWN");
        }
        if(pinState2 == false){
          lcd1.setCursor(0,1);
          lcd1.print("Target 2: DOWN");
        }
        if(pinState3 == false){
          lcd1.setCursor(0,2);
          lcd1.print("Target 3: DOWN");
        }
        if(pinState4 == false){
          lcd2.setCursor(0,0);
          lcd2.print("Target 4: DOWN");
        }
        if(pinState5 == false){
          lcd2.setCursor(0,1);
          lcd2.print("Target 5: DOWN");
        }
        if(pinState6 == false){
          lcd2.setCursor(0,2);
          lcd2.print("Target 6: DOWN");
        }

        if(pinState1 == false && pinState2 == false && pinState3 == false){
          currentState = 3;
          state3time = millis();
          countdown = 0;
          needToResetTime = true;
          Serial.println("Team 1 wins!");
          lcd3.clear();
          lcd3.print("Round over!");
          lcd3.setCursor(0,1);
          lcd3.print("Team 1 wins!!!");
          team1Score++;
          lcd3.setCursor(0,2);
          lcd3.print(team1Score);
          delay(5000);
        }

        unsigned long currentMillis = millis();
        if (currentMillis - previousMillis >= 1000 && !paused) { // Check if 1 second has passed
            previousMillis = currentMillis;
            Serial.println(countdown-1);
            lcd3.clear();
            lcd3.setCursor(0,0);
            lcd3.print("Game on!");
            lcd3.setCursor(0,1);
            lcd3.print(countdown - 1);
            countdown--; // Decrement countdown
        }
      }

      elapsedTime = millis() - startTime; 

      if (elapsedTime >= 30000 && !paused) {                   // If 1 minute (60000) has passed
          Serial.println("Round over!!!");

          lcd3.clear();
          lcd3.print("Round over!");

          currentState = 3;                         // Move to state 2
          state3time = millis();                     // Record the start time for the next state
          countdown = 31;
      }

      break;
      
    case 2:

      Serial.println("Paused");
      if(digitalRead(incrTime5Button)==HIGH){
        paused = false;
        currentState = 1;
        delay(1000);
      }

      break;

    case 3: 
      lcd3.setCursor(0,2);
      lcd3.print("Reseting pins");

      digitalWrite(motorTarget1, HIGH);               // Set pin high for 5 seconds
      digitalWrite(motorTarget2, HIGH);
      digitalWrite(motorTarget3, HIGH);
      digitalWrite(motorTarget4, HIGH);
      digitalWrite(motorTarget5, HIGH);
      digitalWrite(motorTarget6, HIGH);

      if (millis() - state3time >= 10000) {           // If 5 seconds have passed
        Serial.println("Pins reset");
        currentState = 0;                           // Return to state 0

        lcd3.setCursor(0,2);
        lcd3.clear();
        lcd3.print("Pins reset");

        lcd1.clear();
        lcd2.clear();
        lcd1.setCursor(0,0);   //Set cursor to character 0 on line 0
        lcd1.print("Target 1: UP");
        lcd1.setCursor(0,1);   //Move cursor to character 0 on line 1
        lcd1.print("Target 2: UP");
        lcd1.setCursor(0,2);   //Move cursor to character 0 on line 2
        lcd1.print("Target 3: UP");
        lcd2.setCursor(0,0);   //Set cursor to character 0 on line 0
        lcd2.print("Target 4: UP");
        lcd2.setCursor(0,1);   //Move cursor to character 0 on line 1
        lcd2.print("Target 5: UP");
        lcd2.setCursor(0,2);   //Move cursor to character 0 on line 2
        lcd2.print("Target 6: UP");

        digitalWrite(motorTarget1, LOW);            // Disengage motors
        digitalWrite(motorTarget2, LOW);
        digitalWrite(motorTarget3, LOW);
        digitalWrite(motorTarget4, LOW);
        digitalWrite(motorTarget5, LOW);
        digitalWrite(motorTarget6, LOW);

        delay(5000);
      }
      break;
  }
}
