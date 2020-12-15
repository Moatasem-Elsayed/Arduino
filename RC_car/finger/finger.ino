#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3);
#define buzzer 12
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
volatile int fingerprintID = 0;
int getFingerprintIDez();

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
 finger.begin(57600);
pinMode(13,OUTPUT);
pinMode(buzzer,OUTPUT);
  
}

void loop() {
  fingerprintID = getFingerprintIDez();
  delay(50);
  Serial.println(fingerprintID);
  if (fingerprintID == 1 || fingerprintID == 2 || fingerprintID == 3 || fingerprintID == 4)
  {
    digitalWrite(13,1);
  }
  else if (fingerprintID == 0 )
  {
     digitalWrite(13,0);
    for (int i = 0; i < 5; i++) {
      digitalWrite(buzzer, 1);
      delay(100 * i);
      digitalWrite(buzzer, 0);
      delay(50 * i);
    }
  }
 
}

int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return 0;

  // found a match!
  /*Serial.print("Found ID #");
    Serial.print(finger.fingerID);
    Serial.print(" with confidence of ");
    Serial.println(finger.confidence);
  */return finger.fingerID;
}

