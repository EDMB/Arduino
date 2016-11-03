
#define IRQ_A 0
#define IRQ_B 1
#define FlowA 2
#define FlowB 3

//DFRobot.com
//Compatible with the Arduino IDE 1.0
//Library version:1.1
//same as sketch 17a nov 2015

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

volatile unsigned int countIN = 0;
volatile unsigned int countOUT = 0;
unsigned long oldTime  = 0;

unsigned long totalPulses = 0;

unsigned int circBuf[60];
uint8_t idx = 0;

void setup()
{
  lcd.init();                      // initialize the lcd 
 
  // Print a message to the LCD.
  lcd.backlight();
  lcd.print("            -----");
  
  Serial.begin(57600);

  pinMode(FlowA, INPUT);
  pinMode(FlowB, INPUT);
  digitalWrite(FlowA, HIGH);
  digitalWrite(FlowB, HIGH);

  attachInterrupt(IRQ_A, CounterIN, FALLING);
  attachInterrupt(IRQ_B, CounterOUT, FALLING);
}

void loop()
{
  unsigned long now = millis();
  if(now - oldTime >= 1000)
  {
    unsigned long duration = now - oldTime;
    oldTime = now;

    // store usage of last second in circular buffer
    idx++;
    if (idx == 60) idx = 0;
    // disable interrupts while reading & reset counters.
    cli();
    circBuf[idx] = countIN - countOUT; 
    countIN = 0;
    countOUT = 0;
    sei();

    totalPulses += circBuf[idx];

    long pulsesLastMinute = 0;
    for (uint8_t i=0; i<60; i++) 
    {
      pulsesLastMinute += circBuf[i];
    }
    // LPH based upon last minute
    float LPH_M = pulsesLastMinute/10000.0 * 60;
    // LPH based upon last second
    float LPH_S = circBuf[idx]/10000.0 * 3600;
    // Total Liters since start
    float liters = totalPulses/10000.0;

    // DISPLAY USAGE 
    Serial.print(now);
    Serial.print("\tLPH_M:\t");  
    Serial.print(LPH_M, 3);
    Serial.print("\tLPH_S:\t");
    Serial.print(LPH_S, 3);
    Serial.print("\tLiters:\t");
    Serial.println(liters, 3);
    
  lcd.setCursor(0, 1);
  
  lcd.print(LPH_M);
  lcd.print(" LPH");
  lcd.print("  ");
  lcd.setCursor(8, 1);
  
  lcd.print(LPH_S);
  lcd.print("LPS");
  lcd.print("  ");
  lcd.setCursor(0, 0);
  
  //lcd.print(liters); 
  lcd.print(" liters");
    
    
    
  }
}

void CounterIN()
{
  static unsigned long lastTime = 0;
  if (micros()  - lastTime > 10) // to be adjusted
  {
    lastTime = micros();
    countIN++;
  }
}

void CounterOUT()
{
  static unsigned long lastTime = 0;
  if (micros()  - lastTime > 10) 
  {
    lastTime = micros();
    countOUT++;
  }
}

