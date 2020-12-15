/*
---- Transmitter Code ----
Mert Arduino Tutorial & Projects (YouTube)
Please Subscribe for Support
*/

#include <SPI.h>                      //the communication interface with the modem
#include "RF24.h"                     //the library which helps us to control the radio modem

int msg[1];

//define the flex sensor input pins
int flex_4 = A4;
int flex_3 = A3;
int flex_2 = A2;
int flex_1 = A1;
int flex_0 = A0;

//define variables for flex sensor values
int flex_4_val;
int flex_3_val;
int flex_2_val;
int flex_1_val;
int flex_0_val;

RF24 radio(7,8);                     //5 and 10 are a digital pin numbers to which signals CE and CSN are connected.
                                      
const uint64_t pipe = 0xE8E8F0F0E1LL; //the address of the modem, that will receive data from Arduino.


void setup(void){
  Serial.begin(9600);
  radio.begin();                      //it activates the modem.
  radio.openWritingPipe(pipe);        //sets the address of the receiver to which the program will send data.
  //pinMode(2,INPUT);
 
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
flex_1_val = analogRead(flex_1);
                             //175 - 0
  flex_1_val = map(flex_1_val, 1023, 0, 20, 40);
  msg[0] = flex_1_val;
  radio.write(msg, 1);
   Serial.println("sensor 1");
  Serial.println(msg[0]);
  //--------------------------------------------------------
    flex_2_val = analogRead(flex_2);
                             //175 - 0
  flex_2_val = map(flex_2_val, 1023, 0, 40, 60);
  msg[0] = flex_2_val;
  radio.write(msg, 1);
  Serial.println("sensor 2");
  Serial.println(msg[0]);

  //------------------------------------
    flex_3_val = analogRead(flex_3);
                             //175 - 0
  flex_3_val = map(flex_3_val, 1023, 0, 60, 90);
  msg[0] = flex_3_val;
  radio.write(msg, 1);
   Serial.println("sensor 3");
  Serial.println(msg[0]);
  
  
  ///--------------------------------------------------
  flex_4_val = analogRead(flex_4);
  flex_4_val = map(flex_4_val, 1023, 0, 90, 250);
  msg[0] = flex_4_val;
  radio.write(msg, 1);
    Serial.println("sensor 4");
  Serial.println(msg[0]);
  
  
  
  //delay(500);
  //delay(500);


  /*
   * 
   *   
  delay(500);
0
   * 
 
                             //175 - 0
                              delay(500);
  flex_4_val = analogRead(flex_4);
  flex_4_val = map(flex_4_val, 1023, 0, 0, 10);
  msg[0] = flex_4_val;
  radio.write(msg, 1);

  flex_3_val = analogRead(flex_3);
                             //175 - 0
  flex_3_val = map(flex_3_val, 1023, 0, 11, 20);
  msg[0] = flex_3_val;
  radio.write(msg, 1);

  flex_2_val = analogRead(flex_2);
                             //175 - 0
  flex_2_val = map(flex_2_val, 1023, 0, 21, 30);
  msg[0] = flex_2_val;
  radio.write(msg, 1);

  flex_1_val = analogRead(flex_1);
                             //175 - 0
  flex_1_val = map(flex_1_val, 1023, 0, 31, 40);
  msg[0] = flex_1_val;
  radio.write(msg, 1);

  flex_0_val = analogRead(flex_0);
                             //175 - 0
  flex_0_val = map(flex_0_val, 1023, 0, 41, 50);
  msg[0] = flex_0_val;
  radio.write(msg, 1);*/
  
}
