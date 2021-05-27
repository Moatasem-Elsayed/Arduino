#include <LiquidCrystal.h>
#include <NewPing.h>
#define ledf    16
#define ledb    17
#define m1f     11
#define m1b     10
#define m2f     9
#define m2b     6
#define buzzer  7
unsigned char speedd,val;
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
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(m1f, OUTPUT);
  pinMode(m1b, OUTPUT);
  pinMode(m2f, OUTPUT);
  pinMode(m2b, OUTPUT);
  pinMode(buzzer, OUTPUT);

}

void loop()
{
  // put your main code here, to run repeatedly:
    if (Serial.available()) //check low fe 7agh gaya 3la bluetooth //value=1
    {
  
      val = Serial.read(); // F
      if (val >= '1' && val <= '9')
      {
        speedd = (val - '0') * 20 + 50;
      }
       switch (val)
      {
        case 'F': forward();  break;
        case 'B': backward();  break;
        case 'L': left();  break;
        case 'R': right();  break;
        case 'G': forwardleft();  break;
        case 'I': forwardright();  break;
        case 'H': backwardleft();  break;
        case 'J': backwardright(); break;
        case 'S': stopp();  break;
        case 'W': ledforwad(); break;
        case 'w': ledforwadoff(); break;
        case 'U': ledbackward(); break;
        case 'u': ledbackwardoff(); break;
        case 'V': buzzeron(); break;
        case 'v': buzzeroff(); break;
        case 'D': stopall(); break;

      }
}
}void forward()
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


