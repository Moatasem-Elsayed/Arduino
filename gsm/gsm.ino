String number ="01112932885";
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  //Begin serial communication with Arduino and SIM800L

  Serial.println("AT"); //Once the handshake test is successful, i t will back to OK
  Serial.println("ATD+ +01112932885;"); //  change ZZ with country code and xxxxxxxxxxx with phone number to dial
  
  delay(20000); // wait for 20 seconds...
  Serial.println("ATH"); //hang up
  /*Serial.begin(9600);
  Serial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);
  //Serial.println ("Set SMS Number");
  //Serial.println("AT+CMGS=\"" + number + "\"\r"); //Mobile phone number to send message
    Serial.println("AT+CMGS=\"01112932885\"\r"); //Mobile phone number to send message
  delay(1000);
  String SMS = "iam Moatasem Robot hello";
  Serial.println(SMS);
  delay(100);
  Serial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
 */
}

void loop() {
  // put your main code here, to run repeatedly:

}
