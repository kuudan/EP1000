const int led=3;
const int pot=A0;
int potv, pwm;
void setup() {
  // put your setup code here, to run once:
 pinMode(led,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  potv=analogRead(pot);
  pwm = map(potv, 0, 1023, 0, 255);
  analogWrite(led,pwm);
}
