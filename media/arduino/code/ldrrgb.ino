const int vres=A3, led=A0, led1=A1, led3=A2;
int sen=0;

void setup()
{
  pinMode(led, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led3, OUTPUT);
  Serial.begin(9600);
  pinMode(vres,INPUT);
}

void loop()
{
  rbg();
  read();
}

void read(){
sen=analogRead(vres);
Serial.println(sen);
  if(sen < 500){
    analogWrite(led,(1023-sen));
    Serial.println("light up");
  }
  else {
    sen=0;
    Serial.println("no light up");
  }
  delay(100);
}

void rbg()
{
  int red,blue,green;
  red=(100*2+sen*3)/100+sen/4;
  blue=-sen+1023+2*sen;
  green=10+(sen/2)^2;
  limit(red);
  limit(blue);
  limit(green);
  analogWrite(led1,red); //red
  analogWrite(led3,blue); //blue
  analogWrite(led3,green); //green
}

void limit(int i){
  if (i > 1022) i=1023;
  if (i < 1) i=0;
}
