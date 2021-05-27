unsigned char flag=0;
void setup() {
  // put your setup code here, to run once:
  for (int i = 30; i < 0; i++)
  {
    pinMode(i, OUTPUT);
  }
  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);
  pinMode(A4, INPUT_PULLUP);
  pinMode(A14, INPUT_PULLUP);
  pinMode(A15, INPUT_PULLUP);

}

void loop() {
  // put your main code here, to run repeatedly:
 if(digitalRead(A15)==0)
 {
  flag=1;
  }
  if(digitalRead(A14)==0)
 {
  flag=0;
  }
  if(flag==1)
  {
  if (digitalRead(A0) == 1&&digitalRead(A14)==1)
  {
    motor_CW(1);
  }
  else
  {
    motor_stop(1);
  }
  if (digitalRead(A1) == 1&&digitalRead(A14)==1)
  {
    motor_CW(2);
  }
  else
  {
    motor_stop(2);
  }

  if (digitalRead(A2) == 1&&digitalRead(A14)==1)
  {
    motor_CW(3);
  }
  else
  {
    motor_stop(3);
  }
    if (digitalRead(A3) == 1&&digitalRead(A14)==1)
  {
    motor_CW(4);
  }
  else
  {
    motor_stop(4);
  }
    if (digitalRead(A4) == 1&&digitalRead(A14)==1)
  {
    motor_CW(5);
  }
  else
  {
    motor_stop(5);
  }
  
  }
}
void motor_CCW( short int no_motor)
{
  switch (no_motor)
  { case 1:
      PORTB = 0x09 << 4; delay(50); PORTB = 0x0C << 4; delay(50);
      PORTB = 0x06 << 4; delay(50); PORTB = 0x03 << 4; delay(50);
      PORTB = 0x09 << 4;  /* Last step to initial position */
      delay(50);
      break;

    case 2:
      PORTH = 0x09 << 3; delay(50); PORTH = 0x0C << 3; delay(50);
      PORTH = 0x06 << 3; delay(50); PORTH = 0x03 << 3; delay(50);
      PORTH = 0x09 << 3;  /* Last step to initial position */
      delay(50);
      break;
    case 3:
      PORTD = 0x09 ; delay(50); PORTD = 0x0C ; delay(50);
      PORTD = 0x06 ; delay(50); PORTD = 0x03 ; delay(50);
      PORTD = 0x09 ;  /* Last step to initial position */
      delay(50); break;
    case 4:
      PORTA = 0x09 ; delay(50); PORTA = 0x0C ; delay(50);
      PORTA = 0x06 ; delay(50); PORTA = 0x03 ; delay(50);
      PORTA = 0x09 ;  /* Last step to initial position */
      delay(50); break;
    case 5:
      PORTA = 0x09 << 4; delay(50); PORTA = 0x0C << 4; delay(50);
      PORTA = 0x06 << 4; delay(50); PORTA = 0x03 << 4; delay(50);
      PORTA = 0x09 << 4;  /* Last step to initial position */
      delay(50);
      break;
  }
}
void motor_CW(short int no_motor)
{
  switch (no_motor)
  { case 1:
      PORTB = 0x09 << 4; delay(50); PORTB = 0x03 << 4; delay(50); PORTB = 0x06 << 4; delay(50);
      PORTB = 0x0C << 4; delay(50); PORTB = 0x09 << 4;
      delay(50);
      break;
    case 2:
      PORTH = 0x09 << 3; delay(50); PORTH = 0x03 << 3; delay(50);
      PORTH = 0x06 << 3; delay(50); PORTH = 0x0C << 3; delay(50);
      PORTH = 0x09 << 3;  /* Last step to initial position */
      delay(50);
      break;
    case 3:
      PORTD = 0x09 ; delay(50); PORTD = 0x03 ; delay(50);
      PORTD = 0x06 ; delay(50); PORTD = 0x0C ; delay(50);
      PORTD = 0x09 ;  /* Last step to initial position */
      delay(50);
      break;
    case 4:
      PORTA = 0x09 ; delay(50); PORTA = 0x03 ; delay(50);
      PORTA = 0x06 ; delay(50); PORTA = 0x0C ; delay(50);
      PORTA = 0x09 ;  /* Last step to initial position */
      delay(50);
      break;
    case 5:
      PORTA = 0x09 << 4; delay(50); PORTA = 0x03 << 4; delay(50); PORTA = 0x06 << 4; delay(50);
      PORTA = 0x0C << 4; delay(50); PORTA = 0x09 << 4;
      delay(50);
      break;
  }
}
void motor_stop(short int no_motor)
{
  switch (no_motor)
  { case 1:
      PORTB = 0x00 << 4;
      delay(50);
      break;
    case 2:
      PORTH = 0x00 << 3;   /* Last step to initial position */
      delay(50);
      break;
    case 3:
      PORTD = 0x00 ; /* Last step to initial position */
      delay(50);
      break;
    case 4:
      PORTA = 0x00 ; ;  /* Last step to initial position */
      delay(50);
      break;
    case 5:
      PORTA = 0x00 << 4; delay(50);
      delay(50);
      break;
  }
}
//motor_CCW(1);
  /*motor_CW(2);
    motor_CW(2);
    motor_CW(2);

    //motor_CCW(2);
    motor_CW(3);
    motor_CW(3);
    motor_CW(3);
    //motor_CCW(3);

    motor_CW(4);
    motor_CW(4);
    motor_CW(4);
    //motor_CCW(4);

    motor_CW(5);
    motor_CW(5);
    motor_CW(5);
    //motor_CCW(5);

  */
