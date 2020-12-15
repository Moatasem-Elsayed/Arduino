/*
---- Transmitter Code ----
Mert Arduino Tutorial & Projects (YouTube)
Please Subscribe for Support
*/
#include <Servo.h>
#include <SPI.h>                      //the communication interface with the modem
#include "RF24.h"        //the library which helps us to control the radio modem

Servo servo1;
Servo servo2;
int msg[1];

//define the flex sensor input pins
int flex_4 = A3;
int flex_3 = A2;
int flex_2 = A1;
int flex_1 = A0;
//int flex_0 = A;

//define variables for flex sensor values
int flex_4_val;
int flex_3_val;
int flex_2_val;
int flex_1_val;
//int flex_0_val;

RF24 radio(7,8);                     //5 and 10 are a digital pin numbers to which signals CE and CSN are connected.
                                      
const uint64_t pipe = 0xE8E8F0F0E1LL; //the address of the modem,that will receive data from the Arduino.

int pot1;
int pot2;
int x=A0;
int y=A5;

void setup(void){
  Serial.begin(9600);
  radio.begin();                      //it activates the modem.
  radio.openWritingPipe(pipe);        //sets the address of the receiver to which the program will send data.
  //pinMode(4,INPUT);

}

void loop(){

 /*flex_0_val = analogRead(flex_0);
                             //175 - 0
  flex_0_val = map(flex_0_val, 1023, 0, 1, 60);
  msg[0] = flex_0_val;
  radio.write(msg, 1);
  Serial.println("sensor 0");
  Serial.println(msg[0]);*/
  //----------------------------------------------------
   if(Serial.available()){
    unsigned char  r=Serial.read();
    switch(r){
      case 'a': 
      msg[0] =120; radio.write(msg, 1); 
   Serial.println("base angle ");
  Serial.println(msg[0]); break;
  case 'b':
   msg[0] =125; radio.write(msg, 1); 
   Serial.println("base angle ");
  Serial.println(msg[0]); break;
  case 'c':
   msg[0] =130; radio.write(msg, 1); 
   Serial.println("base angle ");
  Serial.println(msg[0]); break;
  //----------------------------------------------------------------------------
  case 'd':
   msg[0] =135; radio.write(msg, 1); 
   Serial.println("up angle ");
  Serial.println(msg[0]); break;
    case 'e':
   msg[0] =140; radio.write(msg, 1); 
   Serial.println("up angle ");
  Serial.println(msg[0]); break;   
    case 'f':
   msg[0] =145; radio.write(msg, 1); 
   Serial.println("up angle ");
  Serial.println(msg[0]); break;
//----------------------------------------------------------------------
              case 'k':
   msg[0] =150; radio.write(msg, 1); 
   Serial.println("up angle ");
  Serial.println(msg[0]); break;  

    case 'l':
   msg[0] =155; radio.write(msg, 1); 
   Serial.println("up angle ");
  Serial.println(msg[0]); break;  

    case 'm':
   msg[0] =160; radio.write(msg, 1); 
   Serial.println("up angle ");
  Serial.println(msg[0]); break;  
//----------------------------------------------------------------------------
          case 'x':
   msg[0] =165; radio.write(msg, 1); 
   Serial.println("up angle ");
  Serial.println(msg[0]); break;  
    case 'y':
   msg[0] =170; radio.write(msg, 1); 
   Serial.println("up angle ");
  Serial.println(msg[0]); break;  
    case 'z':
   msg[0] =175; radio.write(msg, 1); 
   Serial.println("up angle ");
  Serial.println(msg[0]); break;  

      }
    }
flex_1_val = analogRead(flex_1);
                             //175 - 0
  flex_1_val = map(flex_1_val, 1023, 0, 20, 40);
  msg[0] = flex_1_val;
  radio.write(msg, 1);
   //Serial.println("sensor 1");
  //Serial.println(msg[0]);
  //--------------------------------------------------------
    flex_2_val = analogRead(flex_2);
                             //175 - 0
  flex_2_val = map(flex_2_val, 1023, 0, 40, 60);
  msg[0] = flex_2_val;
  radio.write(msg, 1);
  //Serial.println("sensor 2");
  //Serial.println(msg[0]);

  //------------------------------------
    flex_3_val = analogRead(flex_3);
                             //175 - 0
  flex_3_val = map(flex_3_val, 1023, 0, 60, 90);
  msg[0] = flex_3_val;
  radio.write(msg, 1);
   //Serial.println("sensor 3");
  //Serial.println(msg[0]);
  
  
  ///--------------------------------------------------
  flex_4_val = analogRead(flex_4);
  flex_4_val = map(flex_4_val, 1023, 0, 90, 110);
  msg[0] = flex_4_val;
  radio.write(msg, 1);
    //Serial.println("sensor 4");
  //Serial.println(msg[0]);
  
  //--------------------------------------------------
  /*pot1=analogRead(x);
  pot1= map (pot1, 1023, 0, 300, 500);
  msg[0]=pot1;
  radio.write(msg,1);
    Serial.println("pot 1");
  Serial.println(msg[0]);
*/
  
  //-------------------------------------------------
 /*pot2=analogRead(y);
  pot2= map (pot2, 1023, 0, 500, 700);
  msg[0]=pot2;
  radio.write(msg,1);
    Serial.println("pot 2");
  Serial.println(msg[0]);*/

  
}
