//DFRobot.com
//Compatible with the Arduino IDE 1.0
//Library version:1.1
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
int SENSOR_PIN0 = 0; // center pin of the potentiometer
int SENSOR_PIN1 = 1; // center pin of the potentiometer
int SENSOR_PIN2 = 2; // center pin of the potentiometer
int SENSOR_PIN3 = 3; // center pin of the potentiometer

void setup()
{
  lcd.init();                      // initialize the lcd 
 
  // Print a message to the LCD.
  lcd.backlight();
  lcd.print("        Reader");


 
}

void loop()
{
  float sensorValue0 = analogRead(SENSOR_PIN0);
  float sensorValue1 = analogRead(SENSOR_PIN1);
  float sensorValue2 = analogRead(SENSOR_PIN2);
  float sensorValue3 = analogRead(SENSOR_PIN3);
  
  sensorValue0=(-30+100*sensorValue0/1024);
  sensorValue1=(60*sensorValue1/1024);
  sensorValue2=(255*sensorValue2/1024);
  sensorValue3=(5*sensorValue3/1024);
  
  lcd.setCursor(0, 1);
  
  lcd.print(sensorValue0);
  lcd.print(" C");
  lcd.print("  ");
  lcd.setCursor(8, 1);
  
  lcd.print(sensorValue1);
  lcd.print("Lux");
  lcd.print("  ");
  lcd.setCursor(0, 0);
  
  lcd.print(sensorValue2); 
  lcd.print("kLux");
 
  delay (500);
  
}
