/*
---- Receiver Code ----
Mert Arduino Tutorial & Projects (YouTube)
Please Subscribe for Support
*/


#include <SPI.h>      //the communication interface with the modem
#include "RF24.h"     //the library which helps us to control the radio modem
#include <Servo.h>
Servo mbase;
Servo mup;
Servo mext;
Servo mgp;


RF24 radio(7,8);     /*This object represents a modem connected to the Arduino. 
                      Arguments 5 and 10 are a digital pin numbers to which signals 
                      CE and CSN are connected.*/

const uint64_t pipe = 0xE8E8F0F0E1LL; //the address of the modem,that will receive data from the Arduino.

int msg[1];

int data; //data variable
int pos; //position variable
const int m1f=6;
const int m1b=5;
const int m2f=4;
const int m2b=3;

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

mbase.attach(9);
mup.attach(2);
mext.attach(10);
mgp.attach(14);  
  }


//You don't need to make changes in this section
void loop(){

  
  while((radio.available())){

  
    radio.read(msg, 1);
      Serial.println(msg[0]); 
if(msg[0]==120){mbase.write(0);delay(1500);  Serial.println("angle 1");Serial.println(msg[0]);}
if(msg[0]==125){mbase.write(45);delay(1500);Serial.println("angle 1");Serial.println(msg[0]);}      
if(msg[0]==130){mbase.write(90);delay(1500);Serial.println("angle 1");Serial.println(msg[0]);} 
if(msg[0]==135){mup.write(0);delay(1500);Serial.println("angle 1");Serial.println(msg[0]);} 
if(msg[0]==140){mup.write(45);delay(1500);Serial.println("angle 1");Serial.println(msg[0]);} 
if(msg[0]==145){mup.write(90);delay(1500);Serial.println("angle 1");Serial.println(msg[0]);} 
if(msg[0]==150){mext.write(0);delay(1500);Serial.println("angle 1");Serial.println(msg[0]);} 
if(msg[0]==155){mext.write(45);delay(1500);Serial.println("angle 1");Serial.println(msg[0]);} 
if(msg[0]==160){mext.write(75);delay(1500);Serial.println("angle 1");Serial.println(msg[0]);} 
if(msg[0]==165){mext.write(90);delay(1500);Serial.println("angle 1");Serial.println(msg[0]);} 
if(msg[0]==170){mgp.write(0);delay(1500);Serial.println("angle 1");Serial.println(msg[0]);} 
if(msg[0]==175){mgp.write(90);delay(1500);Serial.println("angle 1");Serial.println(msg[0]);} 
 
 if(msg[0]>22 && msg[0]<40){
      Serial.println("sensor 1");
  Serial.println(msg[0]);
     digitalWrite(m1f,1);
digitalWrite(m1b,0);
digitalWrite(m2f,1);
digitalWrite(m2b,0);
    
    } 
  
       if(msg[0]>45 && msg[0]<60){
      Serial.println("sensor 2");
  Serial.println(msg[0]);
     digitalWrite(m1f,0);
digitalWrite(m1b,1);
digitalWrite(m2f,0);
digitalWrite(m2b,1);
    
    }
      if(msg[0]>63 && msg[0]<90){
      Serial.println("sensor 3");
  Serial.println(msg[0]);
     digitalWrite(m1f,0);
digitalWrite(m1b,1);
digitalWrite(m2f,1);
digitalWrite(m2b,0);
    
    }
           if(msg[0]>94 && msg[0]<110){
      Serial.println("sensor 4");
  Serial.println(msg[0]);
     digitalWrite(m1f,0);
digitalWrite(m1b,0);
digitalWrite(m2f,0);
digitalWrite(m2b,0);}
    
      

    
}}
