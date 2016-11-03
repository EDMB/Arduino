/* FILE:    ARD_1302_RTC_Example_Sketch_HCMODU0035
   DATE:    03/09/13
   VERSION: 0.1
   
REVISIONS:

20/09/13 Created version 0.1

This is an example of how to use the Hobby Components 1302 Real Time Clock
module (HCMODU0035). This example uses the RTC library written by Henning Karlsen 
(http://www.henningkarlsen.com/electronics/). This example sketch demonstrates 
how to read and write to the RTC module. To connect the module to your Arduino 
please see the following pinout:

PINOUT:

MODULE    ARDUINO
GND       GND             
VCC       +5V              
SCK       D4
I/O       D3
RST(CS)   D2


You may copy, alter and reuse this code in any way you like, but please leave
reference to HobbyComponents.com in your comments if you redistribute this code.
This software may not be used for the purpose of premoting or selling products 
that directly compete with Hobby Components Ltd's own range of products.

THIS SOFTWARE IS PROVIDED "AS IS". HOBBY COMPONENTS MAKES NO WARRANTIES, WHETHER
EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE, ACCURACY OR LACK OF NEGLIGENCE.
HOBBY COMPONENTS SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR ANY DAMAGES,
INCLUDING, BUT NOT LIMITED TO, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY
REASON WHATSOEVER. */

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
