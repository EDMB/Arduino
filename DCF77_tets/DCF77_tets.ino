#include "DCF77.h" #include <Time.h> #include <TimeLib.h>
#define DCF_PIN 2 // Connection pin to DCF 77 device
#define DCF_INTERRUPT 0 // Interrupt number associated with pin #define POWER 7
time_t time;
DCF77 DCF = DCF77(DCF_PIN,DCF_INTERRUPT);
void setup() {
Serial.begin(9600);
pinMode(7, OUTPUT);
digitalWrite(7, LOW);
DCF.Start();
Serial.println("warte auf DCF77 zeit ... ");
Serial.println("Es kann bis zu 2 Minuten dauern, bi sein Signal vollständig erfasst wurde.");
}
void loop() {
delay(1000);
time_t DCFtime = DCF.getTime(); // ist eine neue DCF77 Zeit vorhanden if (DCFtime!=0)
{
Serial.println("Zeit wurde aktuallisiert");
setTime(DCFtime); }
digitalClockDisplay(); }
void digitalClockDisplay(){
// Serielle Ausgabe der Zeit Serial.print(hour()); printDigits(minute()); printDigits(second()); Serial.print(" "); Serial.print(day()); Serial.print(" "); Serial.print(month()); Serial.print(" "); Serial.print(year()); Serial.println();
}
void printDigits(int digits){ // Ausgabe Serial.print(":");
if(digits < 10)
Serial.print('0'); Serial.print(digits);
}
