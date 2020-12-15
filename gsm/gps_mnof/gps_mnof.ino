#include <SoftwareSerial.h>

//Create software serial object to communicate with SIM800L
SoftwareSerial mySerial(7, 8); //SIM800L Tx & Rx is connected to Arduino #3 & #2

void setup()
{
  //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);
  Serial1.begin(9600);

  Serial.println("AT"); //Once the handshake test is successful, it will back to OK 
  Serial1.println(Serial.read());
  delay(4000);
  Serial.println("AT+CMGF=1"); // Configuring TEXT mode
  Serial1.println(Serial.read());
  delay(4000);
  Serial.println("AT+CNMI=1,2,0,0,0"); // Decides how newly arrived SMS messages should be handle
  Serial1.println(Serial.read());
  delay(4000);
}

void loop()
{
 if(Serial.available())
    Serial1.println(Serial.read());
  
}

void updateSerial()
{
  delay(500);
 
  if(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }}
