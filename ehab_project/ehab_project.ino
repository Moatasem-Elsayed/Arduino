#define ledpin  13
#define ldrpin  11
#define irpin   10
#define gaspin  A0

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(ledpin,OUTPUT);
pinMode(irpin,INPUT);
pinMode(ldrpin,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

int ldrvalue=digitalRead(ldrpin);
int irvalue=digitalRead(irpin);
int gasvalue=analogRead(ldrpin);

  Serial.print("LDR value=");
  Serial.println(ldrvalue);
  Serial.print("IR value ");
  Serial.println(irvalue);
  Serial.print("gas value");
  Serial.println(gasvalue);

  if(ldrvalue==0 ||irvalue==0 ||gasvalue>300)
  {
    digitalWrite(ledpin,HIGH);
  }
  else
  {
    digitalWrite(ledpin,LOW);
    }
  delay(1500);

}
