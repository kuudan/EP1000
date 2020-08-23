#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#define dhtp 7
#define dhtt DHT11

DHT dht(dhtp,dhtt);
LiquidCrystal_I2C lcd(0x27,16,2);

const int a=2000;

void setup() {
  // put your setup code here, to run once:
  pinMode(dhtp,INPUT_PULLUP);
  //Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  dht.begin();
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  // float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) /*|| isnan(f)*/) {
    lcd.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
 // float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(F("Hu: "));
  lcd.print(h);
  lcd.print(F("%"));
  lcd.setCursor(0,1);
  lcd.print(F("Te: "));
  lcd.print(t);
  lcd.print(F("°C"));
}
