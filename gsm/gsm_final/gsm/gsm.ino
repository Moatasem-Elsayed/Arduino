
#include <String.h>
#include <DHT.h>

#define DHTPIN A0

DHT dht(DHTPIN, DHT11);
//unsigned int set_point=20;
//char arr[3] = {0};
int x = 0;
unsigned char recv;
unsigned int set_point = 30;
void check_serial();
void setup()
{
  //gprsSerial.begin(9600);  // the GPRS baud rate
  Serial.begin(9600);    // the GPRS baud rate
  dht.begin();
  Serial1.begin(115200);
  delay(1000);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
}

void loop()
{


  float h = dht.readHumidity();
  float t = dht.readTemperature();
  x = t;


  delay(100);
  /*set_point=get_read_from_nodemcu();
    if(t<set_point )
    {
    motor_on();
    }
    else
    {

    }*/
  Serial.println("AT");
  check_serial(100);
  //Serial.write(gprsSerial.read());
  Serial.println("AT+CPIN?");
  check_serial(100);
  Serial.println("AT+CREG?");
  check_serial(100);
  Serial.println("AT+CGATT?");
  check_serial(100);
  Serial.println("AT+CIPSHUT");
  check_serial(100);
  Serial.println("AT+CIPSTATUS");
  check_serial(200);
  Serial.println("AT+CIPMUX=0");
  check_serial(200);
  //ShowSerialData();

  Serial.println("AT+CSTT=\"internet.vodafone.net\"");//start task and setting the APN,
  check_serial(100);
  //ShowSerialData();

  Serial.println("AT+CIICR");//bring up wireless connection
  check_serial(300);
  //ShowSerialData();

  Serial.println("AT+CIFSR");//get local IP adress
  check_serial(200);
  Serial.println("AT+CIPSPRT=0");
  check_serial(300);
  //ShowSerialData();

  Serial.println("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\"");//start up the connection
  check_serial(600);
  //ShowSerialData();

  Serial.println("AT+CIPSEND");//begin send data to remote server
  check_serial(400);
  //ShowSerialData();
  //  GET https://api.thingspeak.com/update?api_key=K7RFJ8YCE0WNB5BW&field1=0

  String str = "GET https://api.thingspeak.com/update?api_key=ZLHI2KVZ37PJZ7SN&field1=" + String(t) + "&field2=" + String(h); //+"&field3="+String(val)
  //Serial.println(str);
  Serial.println(str);//begin send data to remote server
  check_serial(400);
  //ShowSerialData();

  Serial.println((char)26);//sending ctrl +z
  check_serial(500);//waitting for reply, important! the time is base on the condition of internet
  Serial.println();
  // ShowSerialData();

  Serial.println("AT+CIPSHUT");//close the connection
  delay(100);
  //ShowSerialData();
}
/*void ShowSerialData()
  {
  while(gprsSerial.available()!=0)
  Serial.write(gprsSerial.read());
  delay(5000);

  }*/

void check_serial(short int size_ )
{
  for (int i = 0; i < size_; i++)
  {
    recv = Serial1.read();
    if (recv == 12)
    {
       set_point = recv;
      digitalWrite(13, 1);
    }
    else if (recv == 11)
    {
      
      digitalWrite(13, 0);
    }
   if(recv!=255)
   {
    set_point = recv;
   }
   
    if (x <= set_point)
    {
      digitalWrite(12, 1);
    }
    else
    {
      digitalWrite(12, 0);
    }
    delay(10);
  }
}



