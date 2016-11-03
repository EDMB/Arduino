
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display


volatile unsigned NbTopsFan; //measuring the rising edges of the signal
const int hallsensor = 2;    //The pin location of the sensor

void rpm ()
{
  NbTopsFan++;
}

void setup()
{
  pinMode(hallsensor, INPUT);
  Serial.begin(9600);
  attachInterrupt(0, rpm, RISING); //and the interrupt is attached
  int ticks;
  int temp;
  lcd.init();                      // initialize the lcd 
 
  // Print a message to the LCD.
  lcd.backlight();
  lcd.print("            -----");
  
  temp = NbTopsFan;
  NbTopsFan = 0;
  ticks=ticks+temp;
  
  ticks=ticks+temp;
}

void loop ()   
{
  int temp;
  long Calc; 
  int ticks;  

  delay (1000);
  noInterrupts();
  temp = NbTopsFan;
  NbTopsFan = 0;
  ticks=ticks+temp;
  interrupts();

  Serial.print (temp, DEC);
  Serial.print (" ticks");
  Serial.write( '\t' );

  Calc = (((temp * 60) / 7) / 2);
  Serial.print (Calc, DEC);
  Serial.print (" L/hour");

  Serial.println();
  
  lcd.setCursor(0, 0);
  lcd.print(ticks);
  
  lcd.setCursor(0, 1);
  
  lcd.print(temp);
  lcd.print(" ticks");
  lcd.print("  ");
  lcd.setCursor(8, 1);
  
  lcd.print(Calc);
  lcd.print("L/hour");
  lcd.print("  ");
  lcd.setCursor(0, 0);
  
  //lcd.print(liters); 
  lcd.print(" liters");
  lcd.setCursor(0, 0);
  lcd.print(ticks);
}

