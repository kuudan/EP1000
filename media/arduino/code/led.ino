//Example Code of a working LED. 
//Will light up initially, wait for 1s before light is off
//will wait for 1s before light turns on. then the cycle repeats
void setup()
{
  pinMode(2, OUTPUT);
}

void loop()
{
  digitalWrite(2, HIGH);
  delay(1000); // Wait for 1000 millisecond(s)
  digitalWrite(2, LOW);
  delay(1000); // Wait for 1000 millisecond(s)
}
