/* YourDuino.com Example Software Sketch
16 character 2 line I2C Display
NEW TYPE Marked "Arduino-IIC-LCD GY-LCD-V1"
terry@yourduino.com */
/*-----( Import needed libraries )-----*/ 
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>  // F Malpartida's NewLiquidCrystal library

/*-----( Declare Constants )-----*/
#define I2C_ADDR    0x20  // Define I2C Address for the PCF8574A 
//---(Following are the PCF8574 pin assignments to LCD connections )----
// This are different than earlier/different I2C LCD displays
#define BACKLIGHT_PIN  7
#define En_pin  4
#define Rw_pin  5
#define Rs_pin  6
#define D4_pin  0
#define D5_pin  1
#define D6_pin  2
#define D7_pin  3

#define  LED_OFF  0
#define  LED_ON  1

/*-----( Declare objects )-----*/  
LiquidCrystal_I2C  lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

void setup()   /*----( SETUP: RUNS ONCE )----*/
{
 lcd.begin (16,2);  // initialize the lcd 
// Switch on the backlight
 lcd.setBacklightPin(BACKLIGHT_PIN,NEGATIVE);
 lcd.setBacklight(LED_ON);
}// END Setup

void loop()   /*----( LOOP: RUNS OVER AND OVER AGAIN )----*/
{

// Reset the display  
 lcd.clear();
 delay(1000);
 lcd.home();
 
// Print our characters on the LCD
 lcd.backlight();  //Backlight ON if under program control
 lcd.setCursor(0,0); //Start at character 0 on line 0
 lcd.print("Hello, world!");
 delay(1000);
 lcd.setCursor(0,1); //Start at character 0 on line 1
 lcd.print("16 by 2 Display");
 delay(8000);
} // END Loop

