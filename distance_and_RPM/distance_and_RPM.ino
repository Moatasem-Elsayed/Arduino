#include <LiquidCrystal.h>
#include <TimerOne.h>

LiquidCrystal lcd(5, 6, 7, 8, 9, 10);
int buttonPin = 2;

#define  pi  3.14
#define  Radius  0.5            //lets asume radius of wheel 0.5 
#define Rotation_pulses  720    // 360 slot channel a and channel b 360 a xor b  it increase resolution 720 (0.5)deg 

float distance_per_1rotation = 0;
float distance=0;
volatile unsigned long pulses=0;
volatile unsigned long PPS;       //pulses per second to get the speed 
volatile unsigned long RPM;       // rotate per minuits

void setup() { 
pinMode(13,OUTPUT);
pinMode(12,OUTPUT);
pinMode(1,OUTPUT);
digitalWrite(1,1);
  lcd.begin(16, 2);
   Timer1.initialize(1000000);
  Timer1.attachInterrupt(timer_function);
 attachInterrupt(digitalPinToInterrupt(2), ISR_button, FALLING );  
} 

void loop() { 
  distance_per_1rotation = (2*pi*Radius);
  distance=(distance_per_1rotation*((float)pulses/Rotation_pulses))*100;
  RPM=PPS*60*(0.5/360);
   
  lcd.setCursor(0, 0);
  lcd.print( "dist=");
  lcd.print( distance);
  lcd.print("cm ");
  lcd.setCursor(1, 1);
  lcd.print( "speed=");
  lcd.print( RPM);
  lcd.print("RPM ");
  if(digitalRead(3)==0)
  {
    digitalWrite(1,1);
    digitalWrite(13,1);
   }
   else
   {digitalWrite(1,0);
    digitalWrite(13,0);
    }
    if(digitalRead(4)==0)
  {
    digitalWrite(1,1);
    digitalWrite(12,1);
   }
   else
   {digitalWrite(1,0);
    digitalWrite(12,0);
    }
 }

 void ISR_button()
 {
  pulses++;
 }

 void timer_function()
 {
  static volatile unsigned int pulses_laststate=0;
  static volatile unsigned int time_val=0;
  static volatile unsigned int time_laststate=0;
  time_val++;
  PPS=pulses-pulses_laststate/(time_val-time_laststate);
  if(pulses!=pulses_laststate)
  {
  pulses_laststate=pulses;
  }
  if(time_val!=time_laststate)
  {
  time_laststate=time_val;
  }
  
 }
