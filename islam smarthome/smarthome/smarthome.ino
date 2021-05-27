/** inputs variable**/
int soil_value,flame_value,gas_value;
int flame_pin=12;
int gas_pin=11;
/** output variable**/
int pump = 13;
int fan=10;
int ledred=9,ledgreen=8,ledyellow=7;
int buzzer=9;
void garden();
void sensor_home();
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pump, OUTPUT);
  pinMode(fan, OUTPUT);
  pinMode(ledred, OUTPUT);
  pinMode(ledgreen, OUTPUT);
  pinMode(ledyellow, OUTPUT);
  pinMode(buzzer, OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  garden();
  sensor_home();
}

void garden()
{
  soil_value = analogRead(A0);
  Serial.println(soil_value);
  delay(1000);
  if (soil_value < 450) //water 
  {
    digitalWrite( pump, 1); // turn it off
  }
  else if (soil_value < 1000)//dry
  {
    digitalWrite( pump, 0); // turn it on
  }
  else //air
  {
  digitalWrite( pump, 1); // turn it off
  Serial.println("take care it is in air");
  }
}

void sensor_home()
{
  gas_value=digitalRead(gas_pin);
  flame_value=digitalRead(flame_pin);
  Serial.println("flame ");
  Serial.print(flame_value);
  Serial.println("gas ");
  Serial.println(gas_value);
  delay(1000);

  if(flame_value==1)
  {
    digitalWrite(fan,0); //turn it on
     digitalWrite(buzzer,1); //turn it on
  }
  else
  {
    digitalWrite(fan,1); //turn it off
    digitalWrite(buzzer,0); //turn it on
   }
  
}
