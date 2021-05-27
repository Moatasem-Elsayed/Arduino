#define motup    4
#define motdown  5
#define motright 3
#define motleft  2
#define smin 500
#define smax 1024
char flag=0;
char flag2=0;
void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  for (int i = 2; i <= 5; i++)
    pinMode(i, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int topr = analogRead(A0);
  int topl = analogRead(A1);
  int botl = analogRead(A2);
  int botr = analogRead(A3);

  int avgr = (topr + botr) / 2;
  int avgl = ((topl + botl) / 2);
  int avgtop = (topr + topl) / 2;
  int avgbot = (botr + botl) / 2;
  int dvert = avgtop - avgbot; // check the diffirence of up and down
  int dhoriz = avgl - avgr;// check the diffirence og left and rigt

  Serial.println("avgr=");
  Serial.println(avgr);
  Serial.println("avgl=");
  Serial.println(avgl);
  Serial.println("avgtop=");
  Serial.println(avgtop);
  Serial.println("avgbot=");
  Serial.println(avgbot);
  Serial.println("........................");

  Serial.println("dvert=");
  Serial.println(dvert);
Serial.println("........................");

  Serial.println("dhori=");
  Serial.println(dhoriz);

int tol=100;
int tolv=100;

  if (-1 * tolv > dvert || dvert > tolv) // check if the diffirence is in the tolerance else change vertical angle
  {
    flag=1;
    if (avgtop < avgbot)
    {
      digitalWrite(motup, 0);
      digitalWrite(motdown, 1);
     // digitalWrite(motright, 1);
     // digitalWrite(motleft, 1);
//delay(2000);
    }
    else if (avgtop > avgbot)
    {
      digitalWrite(motup, 1);
      digitalWrite(motdown, 0);
      //digitalWrite(motright, 1);
      //digitalWrite(motleft, 1);
//delay(2000);
    }
  }else{flag=0;}
 

  if (-1 * tol > dhoriz || dhoriz > tol) // check if the diffirence is in the tolerance else change horizontal angle
  {
    flag2=1;
    if (avgl > avgr)
    {
      //digitalWrite(motup, 1);
      //digitalWrite(motdown, 1);
      digitalWrite(motright, 1);
      digitalWrite(motleft, 0);
  //delay(1000);

    }
    else if (avgl < avgr)
    {
      //digitalWrite(motup, 1);
      //digitalWrite(motdown, 1);
      digitalWrite(motright, 0);
      digitalWrite(motleft, 1);
    //delay(1000);
    }

  }
  else
  {
    flag2=0;
    }
  if(flag==1||flag2==1)
  {
  }
  else
  {
    
     digitalWrite(motup, 1);
    digitalWrite(motdown, 1);
    digitalWrite(motright, 1);
    digitalWrite(motleft, 1);

  }
//delay(4000);
}



