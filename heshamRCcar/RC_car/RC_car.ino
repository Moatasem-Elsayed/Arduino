#include <LiquidCrystal.h>
#include <NewPing.h>
#define ledf    16
#define ledb    17
#define m1f     11
#define m1b     10
#define m2f     9
#define m2b     6
#define buzzer  7
#define rs      5
#define en      4
#define d4      3
#define d5      2
#define d6      14
#define d7      15
#define trig    13
#define echo    12

#define trig2    8
#define echo2    18


/**************************************************/
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
NewPing ultrafront(trig, echo,400);
NewPing ultraback(trig2, echo2,400);
/**************************************************/
void forward();
void forwardleft();
void forwardright();
void backward();
void backwardleft();
void backwardright();
void right();
void left();
void stopp();
void ledforwad();
void ledforwadoff();
void ledbackward();
void ledbackwardoff();
void ledsoff();
void buzzeron();
void buzzeroff();
void stopall();
/**************************************************/
int speedd;
int dist,dist2;
int flag2;
char val;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(m1f, OUTPUT);
  pinMode(m1b, OUTPUT);
  pinMode(m2f, OUTPUT);
  pinMode(m2b, OUTPUT);
  pinMode(ledf, OUTPUT);
  pinMode(ledb, OUTPUT);
  pinMode(buzzer, OUTPUT);
 lcd.setCursor(0, 0);
 lcd.print("distance= ");
 lcd.setCursor(0, 1);
 lcd.print("distance2= ");

}

void loop()
{
  dist = ultrafront.ping_cm();
  dist2 = ultraback.ping_cm();
  
  lcd.setCursor(11, 0);
  lcd.print("    ");
  lcd.setCursor(10, 0);
  lcd.print(String(dist)); 
  
  lcd.setCursor(11, 1);
  lcd.print("    ");
  lcd.setCursor(10, 1);
  lcd.print(String(dist2)); 
  
 
   
   /*lcd.setCursor(0, 1);
  lcd.print("distance=");
  lcd.print(String(dist2));
 */ 
  // put your main code here, to run repeatedly:
  if (distance_check() == 1)
  {
    stopp();
    ledbackward();
    ledforwadoff();
    buzzeron();
    flag2=1;
    if(Serial.read()=='B')
    {
      backward();
      
      }
      else if (Serial.read()=='F')
      {
        forward();
        }

  }
  else
  {
    buzzeroff();
    ledbackwardoff();

    if (Serial.available()) //check low fe 7agh gaya 3la bluetooth //value=1
    {
      while(flag2==1){if(Serial.read()!='S'){stopp();}else flag2=0;}

      val = Serial.read(); // F
      Serial.println(val);
      if (val >= '1' && val <= '9')
      {
        speedd = (val - '0') * 20 + 50;
      }
      switch (val)
      {
        case 'F': forward(); ledforwad(); break;
        case 'B': backward(); ledforwad(); break;
        case 'L': left(); ledforwad(); break;
        case 'R': right(); ledforwad(); break;
        case 'G': forwardleft(); ledforwad(); break;
        case 'I': forwardright(); ledforwad(); break;
        case 'H': backwardleft(); ledforwad(); break;
        case 'J': backwardright(); ledforwad(); break;
        case 'S': stopp(); stopall(); break;
        case 'W': ledforwad(); break;
        case 'w': ledforwadoff(); break;
        case 'U': ledbackward(); break;
        case 'u': ledbackwardoff(); break;
        case 'V': buzzeron(); break;
        case 'v': buzzeroff(); break;
        case 'D': stopall(); break;

      }
    }
  }
}
void forward()
{
  analogWrite(m1f, speedd);
  analogWrite(m1b, 0);
  analogWrite(m2f, speedd);
  analogWrite(m1b, 0);
}
void backward()
{
  analogWrite(m1f, 0);
  analogWrite(m1b, speedd);
  analogWrite(m2f, 0);
  analogWrite(m2b, speedd);
}

void left()
{
  analogWrite(m1f, speedd);
  analogWrite(m1b, 0);
  analogWrite(m2f, 0);
  analogWrite(m2b, speedd);
}

void right()
{
  analogWrite(m1f, 0);
  analogWrite(m1b, speedd);
  analogWrite(m2f, speedd);
  analogWrite(m2b, 0);
}
void forwardleft()
{
  analogWrite(m1f, speedd);
  analogWrite(m1b, 0);
  analogWrite(m2f, speedd / 2);
  analogWrite(m2b, 0);
}

void forwardright()
{
  analogWrite(m1f, speedd / 2);
  analogWrite(m1b, 0);
  analogWrite(m2f, speedd);
  analogWrite(m2b, 0);
}


void backwardleft()
{
  analogWrite(m1f, 0);
  analogWrite(m1b, speedd);
  analogWrite(m2f, 0);
  analogWrite(m2b, speedd / 2);
}

void backwardright()
{
  analogWrite(m1f, 0);
  analogWrite(m1b, speedd / 2);
  analogWrite(m2f, 0);
  analogWrite(m2b, speedd);
}

void stopp()
{
  analogWrite(m1f, 0);
  analogWrite(m1b, 0);
  analogWrite(m2f, 0);
  analogWrite(m2b, 0);
}
void ledforwad()
{
  digitalWrite(ledf, 1);
}
void ledforwadoff()
{
  digitalWrite(ledf, 0);
}

void ledbackward()
{
  digitalWrite(ledb, 1);
}

void ledbackwardoff()
{
  digitalWrite(ledb, 0);
}
void ledsoff()
{
  digitalWrite(ledf, 0);
  digitalWrite(ledb, 0);
}
void stopall()
{
  ledsoff();
  stopp();
}
void buzzeron() {
  digitalWrite(buzzer, 1);
}

void buzzeroff() {
  digitalWrite(buzzer, 0);
}

char distance_check()
{
  char flag = 0;
  dist = ultrafront.ping_cm();
  //dist2 = ultraback.ping_cm();
  if (dist <= 15&&dist!=0||dist2<=15&&dist2!=0) {
    flag = 1;
  }
  else
  {
    flag = 0;
  }
  return flag;
}
