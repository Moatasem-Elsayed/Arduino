#include "TimerOne.h"

/******************************************************************
 Created with PROGRAMINO IDE for Arduino - 22.04.2020 22:57:31
 Project     :Get Encoder Speed (PPS)
 Libraries   :Timer One - Built In Interrupt
 Author      :Waleed El-Badry
 Description :Calculating Encoder Speed in PPS
******************************************************************/
#include<TimerOne.h>


int interruptPin = 2;
volatile unsigned long counter = 0;
int pps = 0;
long intervalInUS = 500000; 
void countingPulses()
{
  counter ++;
}

void calculateSpeedPPS()
{
    noInterrupts();
    pps = ((counter * 1.0)/(intervalInUS))*(1000000.0);
    Serial.print("Speed (PPS): ");
    Serial.println(pps);
    counter = 0;
    interrupts();
}

void setup()
{
   Serial.begin(9600); 
   attachInterrupt(digitalPinToInterrupt(interruptPin), countingPulses, RISING);
   Timer1.initialize(intervalInUS);
   Timer1.attachInterrupt(calculateSpeedPPS);
}

void loop()
{
}
