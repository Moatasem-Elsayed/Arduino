#include <LiquidCrystal.h>
#include <Keypad.h>
#include <NewPing.h>

//password check
struct data {
  char password1[3] = {'1', '2', '3'};
  char password2[3] = {'4', '5', '6'};
} pass;

// Lcd defintions
enum {
  rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8
} lcdpins;

//keypad definetions pins
enum {
  rw1 = 52, rw2 = 50, rw3 = 48, rw4 = 46,
  col = 44, col2 = 42, col3 = 40,
} keypadpins;
const byte ROW = 4; //four rows
const byte COL = 3; //three columns
byte rowPins[ROW] = {rw1, rw2, rw3, rw4};
byte colPins[COL] = {col, col2, col3};
//ultrasonic definations pins
enum {
  trg = 31,
  echo = 33,
} ultrapins;
//buzzer defintion pin
#define buz 30
//led defintion pin
#define led 7
#define fan 7
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
NewPing ultrasonic (trg, echo);

char keys[ROW][COL] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

Keypad mykeypad = Keypad( makeKeymap(keys), rowPins, colPins, ROW, COL );
/* prototypes*/
int coming();
int check_pass();
void mobile_control();
int the_home(int decision);
void reading_sensors() ;
void automatic_system();
int fola();
/*end of prototypes*/

int tr = 0;
/*sensors pins*/
enum {
  flamepin = 4,
  pirpin = 5,
  gaspin = 6,
  soilpin = A0,
  temppin = A2,
} sensorspins;

/*sensors variables */
int gas, temp, flame, soil, pir;

/* statring code*/

//homeflag
int home_flag = 0;
int decide_flag;
void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(led, OUTPUT);
  pinMode(fan, OUTPUT);
  pinMode(buz, OUTPUT);
  pinMode(flamepin, INPUT);
  pinMode(pirpin, INPUT);
  pinMode(gaspin, INPUT);
  pinMode(soilpin, INPUT);
  pinMode(temppin, INPUT);
  lcd.clear();
}//void setup

void loop() {
  if (home_flag == 0) {
    decide_flag = fola();
    home_flag = the_home(decide_flag); //case 1 automatic return 1 case 13 reutrn 0
  }//if
  else {
    home_flag = the_home(decide_flag);
  }//else
}//viod loop
int fola() {
  int human = coming();// case 0 return 1 some one come and 13 for no any body  and case 1 return 13
  int d = check_pass(human); //case 1:return 6 dr,7 nour,5 wrong ,case 13 reutrn 13
  int decide_flag = decide(d);//case 5 wrong r and case 6 welcome abbas case 7 nour return 1 case 13 reutrn 13
  return decide_flag;
}//fola

/* the home function */

int the_home(int decision) {
  switch (decision) {
    case 1:
      reading_sensors();
      automatic_system();
      mobile_control();
      return 1;
      break;
    case 13: return 0; break;
  }//switch
}//the home
/*  mobile control the home */
void mobile_control() {
  if (Serial.available())
  {
    char x = Serial.read();
    switch (x)
    {
      case 'l':
      case 'L':
        digitalWrite(led, 1);
        Serial.println("led is on");
        break;
      case 'f':
      case 'F':
        digitalWrite(fan, 1);
        Serial.println("fan is on");
        break;
      case 'o':
      case 'O': digitalWrite(led, 0); digitalWrite(fan, 0); Serial.println("led and fan is off"); break;
    }//switch(x)
  }//if serial avialble
}//mobile control


/* decide function */
void reading_sensors() {
  temp = analogRead(temppin);
  temp = temp * ((5 / 1023.0) * 100);
  soil = analogRead(soilpin);
  flame = digitalRead(flamepin);
  gas = digitalRead(gaspin);
  pir = digitalRead(pirpin);

  Serial. print("temp=");
  Serial.println(temp);
  delay(500);
  Serial. print("soil=");
  Serial.println(soil);
  delay(500);
  Serial. print("flame=");
  Serial.println(flame);
  delay(500);
  Serial. print("gas=");
  Serial.println(gas);

  delay(500);
  Serial. print("pir=");
  Serial.println(pir);
  delay(500);
}
/*end of decide function*/

/*automatic system  */
void automatic_system() {
  if (gas == 0 || flame == 1 || temp > 35)
  {
    digitalWrite(fan, 1);
  }//if
  else
  {
    digitalWrite(fan, 0);
  }//else
  if (pir == 1)
  {
    digitalWrite(led, 1);
  }//if
  else
  {
    digitalWrite(led, 0);
  }//else
}//automatic system
/*end of system*/
int  decide(int d) {
  switch (d) {
    case 6:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Dr abassy");
      Serial.println("welcome Dr.abassy");
      delay(1000);
      return 1;
      // phase 2 and send welcome through mobile
      break;
    case 7:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("nour");
      Serial.println("welcome miss nour");
      delay(1000);
      return 1;
      // phase 2 and send welcome through mobile
      break;
    case 5:
      tr++;
      if (tr == 3) {
        digitalWrite(buz, 1);
        while (1);
      }//if
      return 0;
      break;
    case 13: lcd.clear(); return 13; break;
  }//switch
}//decide                                                                                                                                                                                                                  / void decide
/* the end of decide function */

//using ultrasonic in enetring to light the led
int coming() {
  int dis = ultrasonic.ping_cm();
  if (dis < 30 && dis > 0)
  {
    digitalWrite(led, 1);
    return 1;
  }//if
  else {
    digitalWrite(led, 0);
    return 13;
  }//else
}//comming

//checking password
int check_pass(int x)
{
  int i;
  int pass_val[3] = {0};
  int flag1 = 0, flag2 = 0;
  switch (x) {
    case 1:
      // entering values from user
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("enter password");
      delay(500);
      for (int i = 0; i < 3; i++)
      {
        pass_val[i] = mykeypad.waitForKey();
        lcd.setCursor(i, 1);
        lcd.print("*");
        delay(500);
      }

      //check the value from the user

      for ( i = 0; i < 3; i++)
      {
        if (pass_val[i] == pass.password1[i])
        {
          flag1++;
        }//if
      }//for

      for ( i = 0; i < 3; i++)
      {
        if (pass_val[i] == pass.password2[i])
        {
          flag2++;
        }//if
      }//for

      /*** end the check ***/

      if (flag1 == 3) {
        return 6;
      }
      if (flag2 == 3)
      {
        return 7;
      }
      else
      {
        return 5;
      }
      break;
    case 13: lcd.clear(); return 13; break;
  }
}//check_pass
