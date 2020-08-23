// #include <NewPing.h>
const int trig=5, echo=4;
double duration, distance;
// NewPing sonar(trig, echo, 250); //max dist=250cm (aka 3rd variable)

void setup() {
  // put your setup code here, to run once:
pinMode(trig, OUTPUT); 
pinMode(echo, INPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
// val = sonar.ping_cm(); // reads sonar cm thingy and asigns value to val

digitalWrite(trig, LOW);
delay(5);
digitalWrite(trig,HIGH);
delay(10);
digitalWrite(trig, LOW);

duration= pulseIn(echo, HIGH);
distance=(duration/2)*0.0343; // v*t=s, v=343m/s=343x100cm/s=0.0343cm/ms
Serial.print("\ndistance in cm:");
Serial.print(distance);
}
