//using DFRobot.com libraries
//Compatible with the Arduino IDE 1.0
//Library version:1.1

#include <Wire.h>
#include <VirtualWire.h>

LiquidCrystal_I2C lcd(0x27,16,2);

void setup(){
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  
  lcd.home();
  
  lcd.setCursor(0, 0);
  lcd.print("Hello world...");
  lcd.setCursor(0, 1);
  lcd.print("this is me!");
  while(1);
}
int backlightState = LOW;
long previousMillis = 0;
long interval = 1000;
  
void loop(){
}

