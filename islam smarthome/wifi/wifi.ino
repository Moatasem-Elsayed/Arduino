/***************************************************
  Adafruit MQTT Library ESP8266 Example

  Must use ESP8266 Arduino from:
    https://github.com/esp8266/Arduino

  Works great with Adafruit's Huzzah ESP board & Feather
  ----> https://www.adafruit.com/product/2471
  ----> https://www.adafruit.com/products/2821

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Tony DiCola for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/
#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

/************************* WiFi Access Point *********************************/

#define WLAN_SSID       "Gohar"
#define WLAN_PASS       "Gohar101"

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    "Graduation_project"
#define AIO_KEY         "ab345c61bc2e4ff3ac6b94daffeb5c62"

/************ Global State (you don't need to change this!) ******************/

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;
// or... use WiFiFlientSecure for SSL
//WiFiClientSecure client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

/****************************** Feeds ***************************************/

// Setup a feed called 'photocell' for publishing.
// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname>
/*
Adafruit_MQTT_Publish temp = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/Temp");
*/
Adafruit_MQTT_Publish sensors = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/wind");
Adafruit_MQTT_Publish gassensors = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/temp");

// Setup a feed called 'onoff' for subscribing to changes.
Adafruit_MQTT_Subscribe ledred = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/button");
Adafruit_MQTT_Subscribe ledyellow = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/i");
Adafruit_MQTT_Subscribe ledgreen = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/variable");
Adafruit_MQTT_Subscribe lamp = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/hum");

/*************************** Sketch Code ************************************/

// Bug workaround for Arduino 1.6.6, it seems to need a function declaration
// for some reason (only affects ESP8266, likely an arduino-builder bug).
void MQTT_connect();
unsigned char temperture=0;
int humidity=0;
void setup() {
  Serial.begin(115200);
  delay(10);

  Serial.println(F("Adafruit MQTT demo"));
  pinMode(D0,OUTPUT);
  pinMode(D1,OUTPUT);
  pinMode(D2,OUTPUT);
  pinMode(D3,OUTPUT);
  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());

  // Setup MQTT subscription for onoff feed.
  mqtt.subscribe(&ledred);
  mqtt.subscribe(&ledyellow);
  mqtt.subscribe(&ledgreen);
  mqtt.subscribe(&lamp);
}



void loop() {
  // Ensure the connection to the MQTT server is alive (this will make the first
  // connection and automatically reconnect when disconnected).  See the MQTT_connect
  // function definition further below.
  MQTT_connect();

  // this is our 'wait for incoming subscription packets' busy subloop
  // try to spend your time here

  Serial.println("gas");
  Serial.println(digitalRead(D5));
  // Now we can publish stuff!if(digitalRead(D5)==0)
if(digitalRead(D5)==1)
{
  Serial.print("...");
  if (! gassensors.publish(150)) 
  {
    Serial.println(F("Failed"));
  } else {
    Serial.println(F("OK!"));
  }
}else
{
  Serial.print("...");
  if (! gassensors.publish(50)) {
    Serial.println(F("Failed"));
  } else {
    Serial.println(F("OK!"));
  }
  }

  /****************/
  Serial.println("flame=");
  Serial.println(digitalRead(D6));
  
  if(digitalRead(D6)==1)
{
  Serial.print("...");
  if (! sensors.publish(3)) {
    Serial.println(F("Failed"));
  } else {
    Serial.println(F("OK!"));
  }
}
else
{
  Serial.print("...");
  if (! sensors.publish(1)) {
    Serial.println(F("Failed"));
  } else {
    Serial.println(F("OK!"));
  }
  }
  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(1500))) {
    if (subscription == &ledred) {
      Serial.print(F("Got: "));
      Serial.println((char *)ledred.lastread);
    }
  }
  
      if(strcmp( (char *)ledred.lastread,"ON")==0)
      {
        digitalWrite(D0,1);
      }
      else
      {
        digitalWrite(D0,0);
        }
/***************************************************************************/

  Adafruit_MQTT_Subscribe *subscription2;
  while ((subscription2 = mqtt.readSubscription(1500))) {
    if (subscription2 == &ledyellow) {
      Serial.print(F("Got: "));
      Serial.println((char *)ledyellow.lastread);
    }
  }
  
      if(strcmp( (char *)ledyellow.lastread,"ON")==0)
      {
        digitalWrite(D2,1);
      }
      else
      {
        digitalWrite(D2,0);
        }
/***************************************************************************/

  Adafruit_MQTT_Subscribe *subscription3;
  while ((subscription3 = mqtt.readSubscription(1500))) {
    if (subscription3 == &ledgreen) {
      Serial.print(F("Got: "));
      Serial.println((char *)ledgreen.lastread);
    }
  }
  
      if(strcmp( (char *)ledgreen.lastread,"ON")==0)
      {
        digitalWrite(D1,1);
      }
      else
      {
        digitalWrite(D1,0);
        }


/***************************************************************************/

  Adafruit_MQTT_Subscribe *subscription4;
  while ((subscription4 = mqtt.readSubscription(1500))) {
    if (subscription4 == &lamp) {
      Serial.print(F("Got: "));
      Serial.println((char *)lamp.lastread);
    }
  }
  
      if(strcmp( (char *)lamp.lastread,"ON")==0)
      {
        digitalWrite(D3,0);
      }
      else
      {
        digitalWrite(D3,1);
        }

delay(2000);
  // ping the server to keep the mqtt connection alive
  // NOT required if you are publishing once every KEEPALIVE seconds
  /*
  if(! mqtt.ping()) {
    mqtt.disconnect();
  }
  */
}

// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
  Serial.println("MQTT Connected!");
}
