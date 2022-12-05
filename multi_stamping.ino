#include <LiquidCrystal.h>//Library of LCD with 12C
#include <Key.h>
#include <Keypad.h>//Library of keypad
#include <Stepper.h>//library of stepper motor
#include <Wire.h> //library that allows you communicate with 12C12C

//stepper motor

const int stepsPerRevolution = 5000;// used in stamp function below.
const int stepsPerRevolution2=1000;
Stepper mystepper(stepsPerRevolution,10, 11);// define stepper motor pins.

//keypad
const byte ROWS = 4; //Declararation the number of rows (four) const byte COLS= 4; //Declararation the number of columns (four)
char keys [ROWS] [COLS] ={
{'1', '2', '3', 'A'},//rowl
{'4', '5', '6', 'B'},//row2
{'7', '8', '9', 'C'},//zow3
{'*','0', '#', 'D'}//row
};
// Keypad Form
byte rowPins [ROWS] = {2,3,4,5}; // Connect keypad ROW1, ROW2, ROW3 and ROW4 to these Arduino pins.
byte colPins [COLS] = {6,7,8,91}; // Connect keypad COLL, COL2, COL3, COL4 to these Arduino pins
//LCD
LiquidCrystal 1cd (0x27, 16, 2);//0x27 stands for the 12C address and 16,2 means that theLCD display 16 characters per line in 2 such lines

//pass
char pass[]={'1', '2', '3', '4', '5', '6'}; // The constant Password char newpass [6]; // New Array That's Carried The typed Password
char newpass[6]; // New Array That's Carried The typed Password
bool check; // variable of type boolean that will store true or 
            //false depended on the comparing password (used in enterpassword function)
int delay1 = 1000; // Delay Value are used (lcd).
int stepperDelay=1500;/Delay Value are used in stepper. int stampDelay-500;//Delay Value are used in stepper (stamping).
int limiting = 0; // used to Limiting The Password Letters in enterpassword function.
int error = 0; // Check if Invalid Password it Reached Specific Value used in enterpassword function.
//PaperNUM
int papercounter = 0;//variable that count number of papers with initial value 0
int paperNum2;// variable that used in pappernumber function.
Keypad keypad = Keypad ( makekeymap(keys), rowPins, colpins, ROWS, COLS);// Create the Keypad

void setup()
{
  pinMode (12, INPUT);// assign IR pin 12 as input
  Wire.begin();
  Serial.begin(9600);// initialize the serial portu
  lcd.init(); // initialize the serial port:
  lcd.backlight ();// Turn on the backligt (try led.noBaklight () to turn it off)
  introMessage(); // Intro Message
  enter thepassword();//user enters password then check it.
  pappernumber(check);//user enter paper number
}
//enter password function returns boolean value if the password that the user enters correct or not. 
bool enter_thepassword () [
lcd.setCursor(0, 0);
lcd.print("enter the pass");
while (true) [
  char key = keypad.getKey(); if (key) (
  if (key=='A'){
    int cursorMinusOne=limiting -1;
    lcd.setCursor(cursorMinusOne, 1);
    lcd.print (" ");
    limiting = cursorMinusOne:
    continue;
  }
  lcd.setCursor (limiting, 1);
  lcd.print (key);
  newpass [limiting] = key;
  limiting++;
  if (limiting == 6){
    check = checkequality (newpass, pass, 6);
    lcd.clear();
    delay (delay1);
    if (check == true){
      //if check is true the LCD will print the following message
        lcd.setCursor(0, 0);
        lcd.print ("your pass is ");
        lcd.setCursor (0, 1);
        lcd.print ("correct! ");
        delay(delay1);
        intiaMotor();
        break; //exit of if statement
    }
else{
    if (error ==2){
      //if check is false and error 2 the LCD will print the following message
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print ("disconnected!!");
      delay (delay1);
      return false;
    }
        lcd.setCursor(0, 0);
        lcd.print ("your pass is ");
        lcd.setCursor(0, 1);
        lcd.print ("wrong!");
        delay(delay1);
        lcd.clear();
        delay (500);
        lcd.print ("try agian!");
        limiting = 0;
        error += 1;
        continue;
      }
    }
  }
}

return true;
}
void loop(){
  stamp (paperNum2, check); // start stamping in certain condetion.
//Functions
//show intro message
void introMessage(){
  lcd.setCursor(0, 0); //Setting cursor position to index 0,0, Means Top left of LCD lcd.setCursor (column, row) LCD
  lcd.print(" Hint: If you ");
  lcd.setCursor(0, 1); //Setting cursor position to index 0,1, Means Bottom left of LCD lcd.setCursor (column, row)
  lcd.println("Enter Wrong Pass");
  delay(delay1);
  lcd.clear();/*Clears the LCD screen and positions the cursor in the upper-left corner (first row and first column) of the display. You can use this function to display different words in a loop. */
  lcd.setCursor (0, 0);
  lcd.print (" After 5 Times ");
  lcd.setCursor(0, 1);
  lcd.println("Wt 5s to Retries");
  delay(delay1);
  lcd.clear();
}
// check equality between two character arrays. 
bool checkequality (char *arr, char *arr2, int arrsize) {
  for (int i = 0; i < arrsize; i++){
    if (arr[i] == arr2 [i]){
      continue;
      }
      else{
        return false;
        }
       }
       return true;
}
// convert string to integer. 
int stringToint (String str){
  int num str.toInt();
  return num;
}

//function to check if the password is true allow to enter the paper number 
// ask the user to enter papper number to stamp.
int papparnumber(bool x) {
  if (x = true){
    lcd.clear();
    lcd.setCursor (0, 0);
    lcd.print("enter paper ");
    lcd.setCursor (0, 1);
    lcd.print ("number please");
    delay (delay1);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print ("enter : ");
    char paperArr[10];
    while (true){
      //if the password is true go read the keypad
      char key = keypad.getKey(); // reading the keypad
      if (key){
        if (key== 'D') {
      //paperatr is faction to convert char from keypad to string from paperArr
      String paperstr= charTostring(paperArr, 6);
      paperNum2 stringToint (paperstr);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print ("done");
      delay (delay1);
      lcd.clear();
      papercounter = 0;
      break;
        }
// stepper motor
//start stamp if password is true and IR is reading low.
void stamp (int x, bool y) {
  int paperCounter = 0;
  if (y == true){
    while (papperCounter < x) {
      lcd.clear();
      lcd.setCursor (0, 0);
      lcd.print("paper done :");
      lcd.setCursor(0, 1);
      lcd.print (papperCounter);
      delay (500);
      if (digitalRead(12) == LOW){
        delay(stepperDelay);
        myStepper.setSpeed (250);
        myStepper.step(-stepsPerRevolution); // step one revolution in the other direction:
        delay (stampDelay);
        myStepper.setSpeed (80);
        myStepper.step(-3500);
        delay(delay1);
        // step one revolution in the other direction:
        myStepper.setSpeed(60);
        mystepper.step(stepsPerRevolution);
        delay(stampDelay);
        paperCounter++;}
        else{
          continue;
          }
if(key='A'){
  int cursorMinusOne = papercounter - 1;
  lcd.setCursor (cursorMinusOne, 1);
  lcd.print (" ");
  papercounter = cursorMinusOne;
  continue;
}
lcd.setCursor(papercounter, 1); // (0,1) this is the beginig then the increment will replace the cursor to the second colum and second row (1,1 lcd.print (key);//print the key that we will enter with the keypad
paperArr[papercounter] = key;
papercounter++;
    }
  }
return paperNum2;
}
}
// change character array to a whole string. 
String chartostring (char *arr, int size){
  String s=" ";
  for (int i = 0; i < size; i++) {
    s = s+arr[i];
  }
return s;
}
//if stamping ends 
lcd.clear();
lcd.setCursor(0, 0);
lcd.print ("finished");
delay (delay1);
pappernumber (check);
}
else {
lcd.setCursor (0, 1);
lcd.print("calling the police");
  }
}

// make stepper motor move clockwise in the beggening 
void intiatMotor(){
  myStepper.setSpeed(55); //speed 60 
  myStepper.step(stepsPerRevolution2);
  delay(stepperDelay);
}
