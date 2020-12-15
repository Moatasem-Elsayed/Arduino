#include <LiquidCrystal.h>
#include <Servo.h>
#include <NewPing.h>

enum {trig = 13, echo = 12} ultrapin;
NewPing ultrasonic(trig, echo);


Servo motor_out;
Servo motor_in;
enum {
  motor_in_pin = 4,
  motor_out_pin = 5,
} servopins;

/* lcd initilizations */
enum {
  rs = 11, en = 10, d4 = 9, d5 = 8, d6 = 7, d7 = 6
} lcdpins;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
/* IR LEDS*/
enum {space1 = 3, space2 = 2, space3 = 14, space4 = 15};
struct park {
  int space_vaule;
};

/* global vairables */
int found;
char pass[3];
char client_pass[3] = {'1', '2', '3'};
/* prototypes*/
void check_park();
void outdoor();
void check_client();
/*end of prototypes*/
char flag_functions = 0;
void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  Serial.begin(9600);
  pinMode(space1, INPUT);
  pinMode(space2, INPUT);
  pinMode(space3, INPUT);
  pinMode(space4, INPUT);
  motor_out.attach(motor_out_pin);
  motor_in.attach(motor_in_pin);
  motor_in.write(0);
  motor_out.write(0);


}

void loop() {
  // put your main code here, to run repeatedly:
  check_park();
  if (flag_functions == 0) {
    outdoor();
    check_client();
  }
  else {
    check_client();
    }
}
void check_client()
{
  int  flg = 0;
  while (found == 1) {

    for (int j = 0; j < 3; j++) {
      do {
        pass[j] = Serial.read();
        if (flag_functions == 0) {
          outdoor();
          check_park();
        }
      } while (pass[j] == -1);
    }
    Serial.println("finish login");
    /* check passowrd */
    for (int j = 0; j < 3; j++)
    {
      if (client_pass[j] == pass[j]) {
        flg++;
      }
      else
        flg = 0;
    }
    /*decide if correct*/
    Serial.println("finish check");
    if (flg == 3)
    {
      Serial.println("correct");
      if(flag_functions==1){
      motor_out.write(90);
      delay(2000);
      motor_out.write(0);/* ir led check car get inside or not */
        
        }
      motor_in.write(90);
      delay(1000);
      motor_in.write(0);
      delay(1000);
      
      flg = 0;
      found = 0;
    }
    else {
      Serial.println("incorrect");
      motor_in.write(0);
    }
  }
}
void outdoor() {
  outside_door_check();
  decide_outdoor();
}
void outside_door_check()
{
  int distance = ultrasonic.ping_cm();

  if (distance > 0 && distance < 30)
  {
    found = 1;
  }
  else {
    found = 0;
  }

}

void decide_outdoor()
{
  switch (found) {
    case 1:
      motor_out.write(90);
      delay(2000);
      motor_out.write(0);/* ir led check car get inside or not */
      break;
    case 0:
      motor_out.write(0);
      break;
    default: /* nothing to do */break;
  }
}

void check_park()
{
  struct park parking_values[4];
  unsigned char cnt1 = 0 ;
  lcd.setCursor(0, 0);
  lcd.print("welcome");
  parking_values[0].space_vaule = digitalRead(space1);
  parking_values[1].space_vaule = digitalRead(space2);
  parking_values[2].space_vaule = digitalRead(space3);
  parking_values[3].space_vaule = digitalRead(space4);
  /*
    Serial.print("space1=");
    Serial.println(String (parking_values[0].space_vaule));

    Serial.print("space2=");
    Serial.println(parking_values[1].space_vaule);
    Serial.print("space3=");
    Serial.println(parking_values[2].space_vaule);
    Serial.print("space4=");
    Serial.println(parking_values[3].space_vaule);
    delay(1000);*/
  for (int i = 0; i < 4; i++)
  {
    if (parking_values[i].space_vaule == 1)
    {
      cnt1++;
    }

  }
  if (cnt1 == 0)
  {
    lcd.setCursor(1, 1);
    lcd.print("no available cars");
    cnt1 = 0;
    flag_functions = 1;
  }
  else

  {
    lcd.setCursor(1, 1);
    lcd.print(String(cnt1));
    lcd.print(" ");
    lcd.print("available cars");
    flag_functions = 0;
    cnt1 = 0;
  }
}
