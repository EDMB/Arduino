/* Define the DIO pins used for the RTC module */
#define SCK_PIN 4
#define IO_PIN 3
#define RST_PIN 2

/* Include the DS1302 library */
#include <DS1302.h>

/* Initialise the DS1302 library */
DS1302 rtc(RST_PIN, IO_PIN, SCK_PIN);

void setup()
{
  /* Clear the 1302's halt flag */
  rtc.halt(false);
  /* And disable write protection */
  rtc.writeProtect(false);
 
  /* Initialise the serial port */
  Serial.begin(9600);
}

/* Main program */
void loop()
{
  
  /* Set the time and date to 16:30 on the 3rd of September 2013 */
  rtc.setDOW(MONDAY);
  rtc.setTime(16,30,0);
  rtc.setDate(3, 9, 2013); 
  
  /* Read the time and date once every second */
  while(1)
  {
    Serial.print("It is ");
    Serial.print(rtc.getDOWStr());
    Serial.print(" ");
    Serial.print(rtc.getDateStr());
    Serial.print(" ");
    Serial.print("and the time is: ");
    Serial.println(rtc.getTimeStr());

    /* Wait before reading again */
    delay (1000);
  }
}

  
