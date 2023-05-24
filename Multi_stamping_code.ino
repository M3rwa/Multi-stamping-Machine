#include <LiquidCrystal.h>
#include <Key.h>
#include <Keypad.h>
#include <Stepper.h>
#include <Wire.h>

const int stepsPerRevolution = 5000;
const int stepsPerRevolution2 = 1000;
Stepper mystepper(stepsPerRevolution, 10, 11);

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {2, 3, 4, 5};
byte colPins[COLS] = {6, 7, 8, 9};

LiquidCrystal lcd(0x27, 16, 2);

char pass[] = {'1', '2', '3', '4', '5', '6'};
char newpass[6];
bool check;
int delay1 = 1000;
int stepperDelay = 1500;
int stampDelay = 500;
int limiting = 0;
int error = 0;
int papercounter = 0;
int paperNum2;

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  pinMode(12, INPUT);
  Wire.begin();
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  introMessage();
  enterThePassword();
  paperNumber(check);
}

bool enterThePassword() {
  lcd.setCursor(0, 0);
  lcd.print("Enter the pass");
  
  while (true) {
    char key = keypad.getKey();
    if (key) {
      if (key == 'A') {
        int cursorMinusOne = limiting - 1;
        lcd.setCursor(cursorMinusOne, 1);
        lcd.print(" ");
        limiting = cursorMinusOne;
        continue;
      }
      
      lcd.setCursor(limiting, 1);
      lcd.print(key);
      newpass[limiting] = key;
      limiting++;
      
      if (limiting == 6) {
        check = checkEquality(newpass, pass, 6);
        lcd.clear();
        delay(delay1);
        
        if (check == true) {
          lcd.setCursor(0, 0);
          lcd.print("Your pass is ");
          lcd.setCursor(0, 1);
          lcd.print("correct! ");
          delay(delay1);
          initMotor();
          break;
        } else {
          if (error == 2) {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Disconnected!!");
            delay(delay1);
            return false;
          }
          
          lcd.setCursor(0, 0);
          lcd.print("Your pass is ");
          lcd.setCursor(0, 1);
          lcd.print("wrong!");
          delay(delay1);
          lcd.clear();
          delay(500);
          lcd.print("Try again!");
          limiting = 0;
          error += 1;
          continue;
        }
      }
    }
  }

  return true;
}

void loop() {
  stamp(paperNum2, check);
}

void introMessage() {
  lcd.setCursor(0, 0);
  lcd.print("Hint: If you ");
  lcd.setCursor(0, 1);
  lcd.println("Enter Wrong Pass");
  delay(delay1);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("After 5 Times ");
  lcd.setCursor(0, 1);
  lcd.println("Wait 5s to Retries");
  delay(delay1);
  lcd.clear();
}

bool checkEquality(char* arr, char* arr2, int arrsize) {
  for (int i = 0; i < arrsize; i++) {
    if (arr[i] != arr2[i]) {
      return false;
    }
  }
  
  return true;
}

int stringToInt(String str) {
  int num = str.toInt();
  return num;
}

int paperNumber(bool x) {
  if (x == true) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Enter paper ");
    lcd.setCursor(0, 1);
    lcd.print("number please");
    delay(delay1);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Enter: ");
    char paperArr[10];
    
    while (true) {
      char key = keypad.getKey();
      
      if (key) {
        if (key == 'D') {
          String paperStr = charToString(paperArr, 6);
          paperNum2 = stringToInt(paperStr);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Done");
          delay(delay1);
          lcd.clear();
          papercounter = 0;
          break;
        }
        
        if (key == 'A') {
          int cursorMinusOne = papercounter - 1;
          lcd.setCursor(cursorMinusOne, 1);
          lcd.print(" ");
          papercounter = cursorMinusOne;
          continue;
        }
        
        lcd.setCursor(papercounter, 1);
        lcd.print(key);
        paperArr[papercounter] = key;
        papercounter++;
      }
    }
  }
  
  return paperNum2;
}

void stamp(int x, bool y) {
  int paperCounter = 0;
  
  if (y == true) {
    while (paperCounter < x) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Paper done: ");
      lcd.setCursor(0, 1);
      lcd.print(paperCounter);
      delay(500);
      
      if (digitalRead(12) == LOW) {
        delay(stepperDelay);
        mystepper.setSpeed(250);
        mystepper.step(-stepsPerRevolution);
        delay(stampDelay);
        mystepper.setSpeed(80);
        mystepper.step(-3500);
        delay(delay1);
        mystepper.setSpeed(60);
        mystepper.step(stepsPerRevolution);
        delay(stampDelay);
        paperCounter++;
      } else {
        continue;
      }
    }
  }
  
  if (key == 'A') {
    int cursorMinusOne = papercounter - 1;
    lcd.setCursor(cursorMinusOne, 1);
    lcd.print(" ");
    papercounter = cursorMinusOne;
    continue;
  }
  
  lcd.setCursor(papercounter, 1);
  lcd.print(key);
  paperArr[papercounter] = key;
  papercounter++;
  }
}

String charToString(char* arr, int size) {
  String s = "";
  
  for (int i = 0; i < size; i++) {
    s += arr[i];
  }
  
  return s;
}

void initMotor() {
  mystepper.setSpeed(55);
  mystepper.step(stepsPerRevolution2);
  delay(stepperDelay);
}
