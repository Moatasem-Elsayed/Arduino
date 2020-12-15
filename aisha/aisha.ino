void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
int x=Serial.read();
Serial.print(x);
delay(1000);
}
