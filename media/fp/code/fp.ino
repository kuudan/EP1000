#include <LiquidCrystal_I2C.h>
#include "DHT.h"

//declaration of constant values
const int ledr = A0, ledg = A1, ledb = A2; //output white-orange-red RGB LED R , G , B. pin.
const int pot = A3; //pullup input white POTENTIOMETER. pin
const int but = 3; //pullup input blue-green-orange BUTTON. pin
//lcd sda  A4 output? green for reference
//lcd sdl A5 output? red for reference
const int trig = 5; //   yellow connection TRIG PIN
const int echo = 4; // blue connection ECHO PIN
#define dhtp 2  //pullup input orange of blue-orange-white // DATA PIN DHT11
#define dhtt DHT11 // WHICH DHT MODEL IS USED

//declaration of nonconstant values
double distance; // DISTANCE
int duration; // DURATION
int bstate; //to store button state
int tx=-1,ty=-1, dx=-1,dy=-1, hx=-1,hy=-1; // x lower limit, y upper limit, t = temp h = humid d = dist
int res[3]={0,0,0}; //response values, left to right: t, h, d. 1 means out of range, 0 means within range.
long ti; //internal time comparism
int ur; // potmeter value
int state=0; // range from 0 to 5. 0 n 1 for temp, 2 n 3 for humid, 4 n 5 for dist
float te,hu; // t=temperature, h=humid
bool done=0; //whether set has been done (1) or not done (0)

//declaration of special inputs from libraries
DHT dht(dhtp,dhtt); //DECLARATION OF DHT
LiquidCrystal_I2C lcd(0x27,16,2); //SIZE OF LCD


void ths(){ 
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  hu=h;
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  te=t;
  // Read temperature as Fahrenheit (isFahrenheit = true)
  // float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) /*|| isnan(f)*/) {
    lcd.print(F("Failed to read"));
    lcd.setCursor(0,1);
    lcd.print(F("from DHT sensor"));            
    return;
  }

  // Compute heat index in Fahrenheit (the default)
 // float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);
}

void uss(){ // code for ultrasonic sensor
  
  digitalWrite(trig, LOW);
  delay(5);
  digitalWrite(trig,HIGH);
  delay(10);
  digitalWrite(trig, LOW);

  duration= pulseIn(echo, HIGH);
  distance=(duration/2)*0.0343; // v*t=s, v=343m/s=343x100cm/s=0.0343cm/ms
}

void test(){
  lcd.clear();
  lcd.print("reading current");
  lcd.setCursor(0,1);
  lcd.print("values");
  delay(1000);
  
  lcd.clear();
  ths();
  lcd.print(F("Te: "));
  lcd.print(te);
  lcd.print(F(" deg C"));
  delay(2000);
  lcd.clear();
  lcd.print(F("Hu: "));
  lcd.print(hu);
  lcd.print(" %");
  delay(2000);
  
  lcd.clear();
  uss();
  lcd.print("Distance: ");
  lcd.print(distance);
  delay(2000);
}

void touch(){
  bstate=digitalRead(but);
  if (bstate==1) 
  { 
    debounce(state);
  }
}

void debounce(int val){
  int prevstate = bstate;
  ti=millis();
  while (bstate=1 && prevstate==bstate){
    lcd.clear();
    bstate=digitalRead(but);
    if (millis()-ti>=500) {
      lcd.clear();
      switch (val)
      {
        case 0:{  
          lcd.print("lower temp set @");
          lcd.setCursor(0,1);
          tx=ur;
          lcd.print(tx);
          lcd.print(" deg C");
          delay(1000);
          break;
        }
        case 1:{
          lcd.print("upper temp set @");
          lcd.setCursor(0,1);
          ty=ur;
          lcd.print(ty);
          lcd.print(" deg C");
          delay(1000);
          break;
          }
         case 2:{
          lcd.print("lower humid set @");
          lcd.setCursor(0,1);
          hx=ur;
          lcd.print(hx);
          lcd.print(" %");
          delay(1000);
          break;
          }
         case 3:{
          lcd.print("upper humid set @");
          lcd.setCursor(0,1);
          hy=ur;
          lcd.print(hy);
          lcd.print(" %");
          delay(1000);
          break;
          }
         case 4:{
          lcd.print("lower dist set @");
          lcd.setCursor(0,1);
          dx=ur;
          lcd.print(dx);
          lcd.print(" cm");
          delay(1000);
          break;
          }
         case 5:{
          lcd.print("upper dist set @");
          lcd.setCursor(0,1);
          dy=ur;
          lcd.print(dy);
          lcd.print(" cm");
          delay(1000);
          break;
          }
      }
    }
  }
}

void set() {
if (state==0 || state ==1){ //0 - lower temp limit, 1 - upper temp limit
    while (state==0) {
      lcd.clear();
    lcd.setCursor(0,0);
       lcd.print("lower limit te");
       ur=analogRead(pot);
       ur=map(ur,0,1023,0,40); //sets default lower and upper to 0 and 40
       lcd.setCursor(0,1);
       lcd.print(ur); //outputs pot meter value
       lcd.print(" deg C");
       delay(1000);
       touch();
       if (tx>-1) state++;
       }
  
    while (state==1)
    {
      lcd.clear();
    lcd.setCursor(0,0);
       lcd.print("upper limit te");
       ur=analogRead(pot);
       ur=map(ur,0,1023,0,40); //sets default lower and upper to 0 and 40
       lcd.setCursor(0,1);
       lcd.print(ur); //outputs pot meter value
       lcd.print(" deg C");
       delay(1000);
       touch();
       if (ty>-1) state++;
    }
       if (ty<=tx){
        lcd.clear();
        lcd.print("upper <= lower");
        delay(1000);
        ty=-1;
        tx=-1;
        state=0;
        }
       }
    
  if (state== 2 || state == 3){
    while (state==2) {
      lcd.clear();
    lcd.setCursor(0,0);
       lcd.print("lower limit hu");
       ur=analogRead(pot);
       ur=map(ur,0,1023,0,100); //sets default lower and upper to 0 and 40
       lcd.setCursor(0,1);
       lcd.print(ur);
       lcd.print(" %");
       delay(1000);
       touch();
       if (hx>-1){
        state++;
       }
       }
  
    while (state==3)
    {
      lcd.clear();
    lcd.setCursor(0,0);
       lcd.print("upper limit hu");
       ur=analogRead(pot);
       ur=map(ur,0,1023,0,100); //sets default lower and upper to 0 and 40
       lcd.setCursor(0,1);
       lcd.print(ur);
       lcd.print(" %");
       delay(1000);
       touch();
       if (hy>-1){
          state++;
       }
    }
       if (hy<=hx){
        lcd.clear();
        lcd.print("upper <= lower");
        delay(1000);
        hy=-1;
        hx=-1;
        state=2;
       }
  }
  
  if (state==4 || state == 5){
    while (state==4) {
    lcd.setCursor(0,0);
       lcd.print("lower limit di");
       ur=analogRead(pot);
       ur=map(ur,0,1023,15,300); //sets default lower and upper to 0 and 40
       lcd.setCursor(0,1);
       lcd.print(ur);
       lcd.print(" cm");
       delay(1000);
       touch();
       lcd.clear();
       if (dx>-1){
        state++;
       }
       }
  
    while (state==5) {
    lcd.setCursor(0,0);
       lcd.print("upper limit di");
       ur=analogRead(pot);
       ur=map(ur,0,1023,15,300); //sets default lower and upper to 0 and 40
       lcd.setCursor(0,1);
       lcd.print(ur);
       lcd.print(" cm");
       delay(1000);
       lcd.clear();
       touch();
       if (dy>-1){
          state++;
          done=1;
       }
    }
       if (dy<=dx){
        lcd.clear();
        lcd.print("upper <= lower");
        delay(1000);
        dy=-1;
        dx=-1;
        state=4;
       }
    }   
}

void RGB() {
  //problem: can only display 4 colors
  //fix: use only 5 responses.
  // {0,0,0} = no light
  // {1,0,0} = cyan, temperature
  // {0,1,0} = blue, humid
  // {0,0,1} = green, distance
  // {1,1,1} = red, all 3.
  const int high=1023, low=0;
  if (res[0]==1 && res[1]==1 && res[2]==1) {
      analogWrite(ledr,high);
      analogWrite(ledb,low);
      analogWrite(ledg,low);
    }
   else {
     if (res[0]==1){ 
         analogWrite(ledr,low);
         analogWrite(ledb,high);
         analogWrite(ledg,high);
         delay(500);
       }
     if (res[1]==1){
         analogWrite(ledr,low);
         analogWrite(ledb,high);
         analogWrite(ledg,low);
         delay(500);
       }
     if (res[2]==1){
         analogWrite(ledr,low);
         analogWrite(ledb,low);
         analogWrite(ledg,high);
         delay(500);
       }
    if (res[0]==0 && res[1]==0 && res[2]==0){ 
         analogWrite(ledr,low);
         analogWrite(ledb,low);
         analogWrite(ledg,low);
      }
   }
  /*
   * reference:
   * RGB_color(255, 0, 0); // Red
   * RGB_color(0, 255, 0); // Green
   * RGB_color(0, 0, 255); // Blue
   * RGB_color(255, 255, 125); // Raspberry
   * RGB_color(0, 255, 255); // Cyan
   * RGB_color(255, 0, 255); // Magenta
   * RGB_color(255, 255, 0); // Yellow
   RGB_color(255, 255, 255); // White
   */
}

void mainprog() {
  if (millis()-ti>2000){
    ths();
    if (te<tx || te>ty){
      lcd.clear();
      lcd.print("too hot or cold"); 
      lcd.setCursor(0,1);
      lcd.print(te);
      lcd.print(" deg C");
      delay(1000);
      res[0]=1;//1234567890123456
    }
    else res[0]=0;
    if (hu<hx || hu>hy){
      lcd.clear();
      lcd.print("too dry or humid"); 
      lcd.setCursor(0,1);
      lcd.print(hu);
      lcd.print(" % humid");
      delay(1000);
      res[1]=1;//1234567890123456
    }
    else res[1]=0;
    uss();
    if (distance<dx || distance>dy){
      lcd.clear();
      lcd.print("too far or near"); 
      lcd.setCursor(0,1);
      lcd.print(distance);
      lcd.print(" cm");
      delay(1000);
      res[2]=1;//1234567890123456
    }
    else res[2]=0;
    if (res[0]==0 && res[1]==0 && res[2]==0){
      lcd.clear();
      lcd.print("all clear");
      delay(1000);
    }
    RGB();
    ti=millis();
  }
}



void setup() {
  // put your setup code here, to run once:
  pinMode(ledr,OUTPUT);
  pinMode(ledb,OUTPUT);
  pinMode(ledg,OUTPUT);
  pinMode(pot,INPUT_PULLUP);
  pinMode(but,INPUT_PULLUP);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  lcd.init(); //starts the lcd
  lcd.backlight(); // not sure if needed, but lights up the backlight. probably to indicate working condition
  lcd.setCursor(0,0); // sets cursor to 0,0 (top left corner, max is 16,2 for this lcd. in coordinate terms, that is (15,1)
  lcd.clear(); //clear screen
  delay(1000); // give time to refresh
  lcd.print("Startup Complete");
  delay(1000); // allows user to comprehend startup
  dht.begin(); //begins measuring (when called out)
  test(); // displays current parameters (temp, humid, dist). also checks if error in dht.
  ti=millis(); // starts timer
  done=0; // to indicate that set() has not been done
  //Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (done==0)  set(); //set is the setup for tolerances for the program to activate RGB LED
  else {
    lcd.clear();
    mainprog(); // calls out main program, which is the actual mood lamp part (lol)
    RGB(); //calls out RGB, which will compute the measurement to RGB LED accordingly
    touch();
    }
  }
  /*
  flow: 
  ---------------------------------
  check surroundings (via test(); ) [o]
  ---------------------------------
  setup (via set(); )
    - temperature [o]
    - humidity [o]
    - distance [o]
  ---------------------------------
  main program (via prog(); )
    checking
      - check temperature every 2s [1] [o]
      - check humidity every 2s [2] [o]
      - check distance every 2s [3] [o]
    RGB LED
      - output according to [1][2][3]
  ---------------------------------
   reset (why would it be needed, i dont know. you can unplug the usb, since it technically resets variables for you.)
  ---------------------------------
  */
