/*
#include <LiquidCrystal.h>
enum{
  rs=13,en=12,d4=11,d5=10,d6=9,d7=8
  }lcdpins;
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);
#include <Keypad.h>
#include <NewPing.h>
NewPing ultrasonic (31,33);
const byte ROW = 4; //four rows
const byte COL = 3; //three columns
char keys[ROW][COL] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROW] = {52, 50, 48, 46}; //connect to the row pinouts of the keypad
byte colPins[COL] = {44, 42, 40}; //connect to the column pinouts of the keypad

Keypad mykeypad = Keypad( makeKeymap(keys), rowPins, colPins, ROW, COL );

*/
void setup() {
  // put your setup code here, to run once:

/*lcd.begin(16,2);

Serial.begin(9600);

*/
pinMode(6,INPUT);
pinMode(5,INPUT);
pinMode(30,OUTPUT);
pinMode(7,OUTPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
int x=analogRead(A0);
delay(500);
Serial.println(String(x));

/*if(digitalRead(6)==0){
  int x=digitalRead(6);
  digitalWrite(30,1);
 Serial.println("gan sensor");
 Serial.println(x);
  }
  else{
    digitalWrite(30,0);
    }

    if(digitalRead(5)==1){
  int y=digitalRead(5);
  digitalWrite(7,1);
  
 Serial.println("pir sensor");
 Serial.println(y);
  }
  else{
    digitalWrite(7,0);
    
    }*/
/*
Serial.println("hello");
delay(1000);
char x=Serial.read();
Serial.print(x);
delay(1000);
/*
lcd.setCursor(0,0);
lcd.print("el ashba7");
 
int x=ultrasonic.ping_cm();
  lcd.setCursor(5,1);
  lcd.print(String(x));
  delay(1000);
  lcd.clear();
 char value = mykeypad.getKey();
  if (value != NO_KEY){
   
    lcd.setCursor(0,1);
    lcd.print(value);
 digitalWrite(30,1);   
  delay(1000);
  }
  else{
    digitalWrite(30,0);
  }*/
}
