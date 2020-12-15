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

#define WLAN_SSID       "Moatasm"
#define WLAN_PASS       "junction1234"

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    "moatasem_elsayed"
#define AIO_KEY         "aio_PTiY19oKoiM1nXTri5rC69pD9cDb"

/************ Global State (you don't need to change this!) ******************/

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;
// or... use WiFiFlientSecure for SSL
//WiFiClientSecure client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

/****************************** Feeds ***************************************/

/**/
//Adafruit_MQTT_Publish gassensor = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/humidity");


// Setup a feed called 'onoff' for subscribing to changes.
Adafruit_MQTT_Subscribe lamp = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/lamp1");
Adafruit_MQTT_Subscribe fan = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/fan");
Adafruit_MQTT_Subscribe led = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/keypad");

/*************************** pin diagram  ************************************/
#define lamp_pin          D0
#define fan_pin           D1
/*******************************************************************/
// Bug workaround for Arduino 1.6.6, it seems to need a function declaration
// for some reason (only affects ESP8266, likely an arduino-builder bug).
static char set_point[3];
static char val_set_point=0;
static char cnt=0;
void MQTT_connect();

void setup() {
    Serial.begin(115200);
  /***********************************************************************/
  pinMode(lamp_pin, OUTPUT);
  pinMode(fan_pin, OUTPUT);
  /************************************************************************/
  Serial.println(); Serial.println(); Serial.print("Connecting to "); Serial.println(WLAN_SSID);
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(); Serial.println("WiFi connected"); Serial.println("IP address: "); Serial.println(WiFi.localIP());
  // Setup MQTT subscription for onoff feed.
  mqtt.subscribe(&lamp);
  mqtt.subscribe(&fan);
   mqtt.subscribe(&led);
}



void loop() {
  MQTT_connect();
 
  /********************************************************************/
 /* Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(1000))) {
    if (subscription == &lamp) {
      Serial.print(F("Got: ")); Serial.println((char *)lamp.lastread);
    }
  }

  if (strcmp( (char *)lamp.lastread, "1") == 0)
  {
    digitalWrite(lamp_pin, 0);
  }
  else
  {
    digitalWrite(lamp_pin, 1);
  }*/
  /***************************************************************************/
/*
  Adafruit_MQTT_Subscribe *subscription2;
  while ((subscription2 = mqtt.readSubscription(1000))) {
    if (subscription2 == &fan) {
      Serial.print(F("Got: "));
      Serial.println((char *)fan.lastread);
    }
  }

  if (strcmp( (char *)fan.lastread, "1") == 0)
  {
    digitalWrite(fan_pin, 0);
  }
  else
  {
    digitalWrite(fan_pin, 1);
  }
*/  /***************************************************************************/

  Adafruit_MQTT_Subscribe *subscription3;
  while ((subscription3 = mqtt.readSubscription(1000))) {
    if (subscription3 == &led) {
      Serial.print(F("Got: "));
      Serial.println((char *)led.lastread);
      set_point[cnt]=*(led.lastread);
      cnt++;
      set_point[cnt]=0;
      cnt=cnt%2;
      
    }
  }

  if (strcmp( set_point, "12") == 0)
  {
    digitalWrite(fan_pin, 0);
  }
  else if(strcmp( set_point, "13") == 0)
  {
    digitalWrite(lamp_pin, 0);
  }
  else if(strcmp( set_point, "14") == 0)
  {
      digitalWrite(lamp_pin, 1);
  
    }
    else if(strcmp( set_point, "15") == 0)
    {
        digitalWrite(fan_pin, 1);
  
      }
  /***************************************************************************/
 
  delay(1000);
  // ping the server to keep the mqtt connection alive
  // NOT required if you are publishing once every KEEPALIVE seconds
  /*ء
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

