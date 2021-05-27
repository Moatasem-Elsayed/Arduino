#include <LiquidCrystal.h>

LiquidCrystal lcd(5, 6, 7, 8, 9, 10);

int pin1 = 2;
int pin2 = 3;

int Pos = 0; 
int State;
int LastState;  

const float pi = 3.14;

const int R = 7;
const int N = 22;

float distance = 0;

void setup() { 
  pinMode (pin1 ,INPUT);
  pinMode (pin2 ,INPUT);

  lcd.begin(16, 2);
  lcd.print("SURVEYOR'S WHEEL");
  
  LastState = digitalRead(pin1);    
} 

void loop() { 
  State = digitalRead(pin1);
   if (State != LastState){     
     if (digitalRead(pin2) != State) { 
       Pos ++;
     } 
     
     else {
       Pos --;
     }
   } 

  distance = (2*pi*R)/N;

  lcd.setCursor(0, 1);
  lcd.print( distance);

  lcd.setCursor(3, 1);
  lcd.print("cm  ");
   
  LastState = State;
 }
