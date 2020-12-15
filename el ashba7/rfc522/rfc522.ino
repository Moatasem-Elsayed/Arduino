#include <Servo.h>
#include <SPI.h> // serial protocol interface
#include <MFRC522.h> // bta3 el mfrc
#define SS_PIN 53 // rgole el 
#define RST_PIN 49 
int id[4] = {0x5b, 0xfd, 0xc4, 0x59}; // d el2raiat
int flag = 0;
typedef enum {ledr1=7, ledg1=4, ledr2=6, ledg2=3, ledr3=5, ledg3=2} ledpins;// red 3la odd & green 3la even
typedef enum {sw1=13, sw2=12, sw3=11, sw4=10} swpins; // awel 3 ll entrance w el 4 ll exit

char led_pins[6] = {ledr1, ledg1, ledr2, ledg2, ledr3, ledg3};
char sw_pins[4] = {sw1, sw2, sw3, sw4};
//servo motor
Servo servo;

void house_door();
void zo7leka();
MFRC522 mfrc522(SS_PIN, RST_PIN); // Instance of the class
void setup() {
  Serial.begin(9600);
  SPI.begin();       // Init SPI bus
  mfrc522.PCD_Init(); // Init MFRC522
  Serial.println("RFID reading UID");

  for (int i = 0; i < 6; i++)
  {
    pinMode(led_pins[i], OUTPUT);
  }
  for (int i = 0; i < 4; i++)
  {
    pinMode(sw_pins[i], INPUT);
  }
  servo.attach(8);
  servo.write(0);
}
void loop() {
  house_door();
  zo7leka();
}
void zo7leka()
{
  char sw_val[4];
  for (int i = 0; i < 4; i++)
  {
    sw_val[i] = digitalRead(sw_pins[i]);
  }
  for (int i = 0; i < 3; i++)
  {`
    if (sw_val[i] == 1)
    {
       for (int j = 1; j < 6; j = j + 2)
      {
        digitalWrite(led_pins[j], 0);
      }
      for (int j = 0; j < 6; j = j + 2)
      {
        digitalWrite(led_pins[j], 1);
      }//for
    }
    }//for
    if(sw_val[3]==1)
    {
      
      for (int j = 0; j < 6; j = j + 2)
      {
        digitalWrite(led_pins[j], 0);
      }//for
      for (int j = 1; j < 6; j = j + 2)
      {
        digitalWrite(led_pins[j], 1);
      }
      }
  }



void house_door() {
  if ( mfrc522.PICC_IsNewCardPresent())
  {
    if ( mfrc522.PICC_ReadCardSerial())
    {
      Serial.print("Tag UID:");
      for (byte i = 0; i < mfrc522.uid.size; i++) {
        //    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
        Serial.print(mfrc522.uid.uidByte[i], HEX);
      }
      for (int i = 0; i < 4; i++) {
        if (mfrc522.uid.uidByte[i] == id[i])
          flag++;
      }
      if (flag == 4) {
        Serial.println("nour");
        servo.write(180);
        delay(2000);
        servo.write(0);
        flag = 0;
      }
      else {
        Serial.println("error");
        servo.write(0);
      }
      Serial.println();
      mfrc522.PICC_HaltA();
    }
  }
}
