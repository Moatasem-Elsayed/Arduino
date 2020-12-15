/*
---- Receiver Code ----
Mert Arduino Tutorial & Projects (YouTube)
Please Subscribe for Support
*/


#include <SPI.h>      //the communication interface with the modem
#include "RF24.h"     //the library which helps us to control the radio modem


RF24 radio(7,8);     /*This object represents a modem connected to the Arduino. 
                      Arguments 5 and 10 are a digital pin numbers to which signals 
                      CE and CSN are connected.*/

const uint64_t pipe = 0xE8E8F0F0E1LL; //the address of the modem,that will receive data from the Arduino.

int msg[1];

int data; //data variable
int pos; //position variable
const int m1f=2;
const int m1b=3;
const int m2f=4;
const int m2b=5;
void setup(){
Serial.begin(9600);
  //define the servo input pins
pinMode(m1f,OUTPUT);
pinMode(m1b,OUTPUT);
pinMode(m2f,OUTPUT);
pinMode(m2b,OUTPUT);;
  
  radio.begin();                    //it activates the modem.
  radio.openReadingPipe(1, pipe);   //determines the address of our modem which receive data.
  radio.startListening();           //enable receiving data via modem
  }


//You don't need to make changes in this section
void loop(){

  
  while((radio.available())){
   
    radio.read(msg, 1);
  
   /*if (msg[0]==1 ||msg[0]==2)
   {
      Serial.println("sensor 1");
  Serial.println(msg[0]);
     digitalWrite(m1f,1);
digitalWrite(m1b,0);
digitalWrite(m2f,1);
digitalWrite(m2b,0);
    
   }*/
   if((msg[0]==22)||msg[0]==23){
      Serial.println("sensor 1");
  Serial.println(msg[0]);
     digitalWrite(m1f,1);
digitalWrite(m1b,0);
digitalWrite(m2f,1);
digitalWrite(m2b,0);
    
    } 
  
     if((msg[0]==42)||msg[0]==43||msg[0]==44){
      Serial.println("sensor 2");
  Serial.println(msg[0]);
     digitalWrite(m1f,0);
digitalWrite(m1b,1);
digitalWrite(m2f,0);
digitalWrite(m2b,1);
    
    }
       if(msg[0]==73 || msg[0]==72 || msg[0]==71){
      Serial.println("sensor 3");
  Serial.println(msg[0]);
     digitalWrite(m1f,0);
digitalWrite(m1b,1);
digitalWrite(m2f,1);
digitalWrite(m2b,0);
    
    }
         if(  msg[0]==92){
      Serial.println("sensor 4");
  Serial.println(msg[0]);
     digitalWrite(m1f,0);
digitalWrite(m1b,0);
digitalWrite(m2f,0);
digitalWrite(m2b,0);
    
    }    
    }
   

   


   
    
  
    
   /* if(msg[0] <21 && msg[0]>10){
      data = msg[0], pos=map(data, 11, 20, 175, 0);
      myServo3.write(pos);
    }
    if(msg[0] <31 && msg[0]>20){
      data = msg[0], pos=map(data, 21, 30, 175, 0);
      myServo4.write(pos);
    }
    if(msg[0] <41 && msg[0]>30){
      data = msg[0], pos=map(data, 31, 40, 175, 0);
      myServo2.write(pos);
    }
    if(msg[0] <51 && msg[0]>40){
      data = msg[0], pos=map(data, 41, 50, 175, 0);
      myServo5.write(pos);
    }
  }*/
}
