//YWROBOT
//Compatible with the Arduino IDE 1.0
//Library version:1.1
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  lcd.init();                      // initialize the lcd 
  // Print a message to the LCD.
  lcd.backlight();
  Serial.begin(9600);
}


void loop()
{ 
  lcd.setCursor(0,0);
  lcd.print(millis()/1000);
  Serial.println(millis()/1000);
}
