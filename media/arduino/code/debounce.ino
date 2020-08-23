//switching led color via button
//controlling brightness via potential meter (soon tm)
//reset after long press (3000ms)
//13 - red, 12 - orange, 11 - green, 10 - white
// 9 - button, - potential meter

const int R=A0, O=A1,G=A2, B=3; //W=10
//R=red, O=orange,G=green, W=white, B=button
int state, count, prevstate; 
//state= button state, count=tracking button count
const int i=10, a=100; 
// i is for number of loops for flash, a is number of milliseconds delay
int j=0;
// j is the loop counter
 unsigned long prevt; //for timer -> t = time, prev=previous


void setup()
{
  pinMode(R,OUTPUT);
  pinMode(O,OUTPUT);
  pinMode(G,OUTPUT);
  //pinMode(W,OUTPUT); //all these R,O,G,W for led
  pinMode(B,INPUT_PULLUP); //button, input_pulup -> 10k res
  Serial.begin(9600); //records value for monitoring
  prevt=millis();
}

void loop()
{
  state=digitalRead(B);
  if (state==1) 
  { 
    prevstate=state;
    debounce();
    led();
  }
}

void debounce(){
  prevt=millis();
  while (state=1 && prevstate==state){
    Serial.println(state);
    state=digitalRead(B);
    if ((millis()-prevt)>3000){
    Serial.println("restarting");
    count=0;
      analogWrite(R,1023);
      analogWrite(O,1023);
      analogWrite(G,1023);
      Serial.println("restart complete");
      delay(5000);
      
    break;
    }
    else {
      Serial.print(millis());
      Serial.print(" - ");
      Serial.print(prevt);
      Serial.print(" = ");
      Serial.println(millis()-prevt);
      Serial.println("not restart");
      
    }
  }
}

void led() {
  switch (count) {
    case 0:
      analogWrite(R,0);
      analogWrite(O,0);
      analogWrite(G,0);
      delay(a);
      count++;
    break;
    
    case 1:
      while (j<i){
        analogWrite(R,1023);
        delay(a);
        analogWrite(R,0);
        delay(a);
            analogWrite(R,1023);
            delay(a);
          j++;
      }
      j=0;
      count++;
    break;
    
    case 2:
      analogWrite(R,0);
      while (j<i){
        analogWrite(O,1023);
        delay(a);
        analogWrite(O,0);
        delay(a);
            analogWrite(O,1023);
            delay(a);
          j++;
      }
      j=0;
      count++;
    break;
    
    case 3:
      analogWrite(R,0);
      analogWrite(O,0);
      while (j<i){
        analogWrite(G,1023);
        delay(a);
        analogWrite(G,0);
        delay(a);
            analogWrite(G,1023);
            delay(a);
          j++;
      }
      j=0;
      count=0;
    break;
   
    
    default:
      analogWrite(R,0);
      analogWrite(O,0);
      analogWrite(G,0);
      delay(500);
    break;
  }
}

//debug stuff
//for some reason 1023 / 1 = OFF 
//above situation cause: connected to live instead of ground

//might use this link to help for the 3s restart func 
//https://forum.arduino.cc/index.php?topic=420668.0
