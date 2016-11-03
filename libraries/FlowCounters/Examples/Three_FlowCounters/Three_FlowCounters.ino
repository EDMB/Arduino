
#include <ooPinChangeInt.h>  // Necessary when including FlowCounters.h. Otherwise we get undefined reference errors.
#include <FlowCounters.h>

// This example demonstrates three instances of the FlowCounters class.
 
// Add more instances and Pins at your leisure.  
// Only certain pins with the hardware Pin change Interrupt feature will work.
// On the Mega 2560:
// For the Analog Input pins used as digital input pins, you can use 62-69 etc.
// or you can use A8- A15 [Port K]  (the Arduino code comes with #define's
// for the Analog Input pins and will properly recognize e.g., pinMode(A8, INPUT);
//
// On the Mega2560, the available Pin Change Interrupt (PCINT) pins are:
//    Arduino Pin   [Port]              AVR Pin Name
// Digital Pin 10  [Port B]           PB4 (OC2A/PCINT4)
// Digital Pin 11  [Port B]           PB5 (OC1A/PCINT5)
// Digital Pin 12  [Port B]           PB6 (OC1B/PCINT6)
// Digital Pin 13  [Port B]           PB7 (OC0A/OC1C/PCINT7)
// Digital Pin 50-53 [Port B]
// Digital Pin 14-15 [Port J]
// Analog Pins  A8 - A15 [Port K]
// Analog Pins  A6 - A7 [Port F] //Port F didn't work

// the format is: FlowCounters flowMeterName(arduinoPin, flowConstant, resistor);
// In the equation: Frequency (Hz) = 7.5 * Flow rate (L/min), the flowConstant is 7.5. Omitting flowConstant defaults to -1000.   
//       Then, only readHertz() and readRPM() are meaningful.
// the resistor is HIGH to enable the internal pullup resistor, or Low to disable it.  Omitting resistor defaults to HIGH.

FlowCounters hydroFlow(11,.5); //Half inch plastic flow meter Sea YF 5201
FlowCounters hotWaterFlow(12,7.5); //Half inch plastic flow meter Sea YF 5201
//4.8 for One inch plastic flow meter FS400A G1
FlowCounters hydronicWaterFlow(13,.53); //.53 actual 4.5 official for 1 1/4 SEA flow meter

void setup() {
  
  Serial.begin(115200);
  Serial.println("---------------------------------------");
}

void loop() {
  delay(1000);
  //Output options are: readHertz(), readRPM(), readLitersPerMin(), and readGPM().  
  // Calling any of them returns the measurment since the last read and resets the measurment interval 
  // - so calling one immediately after another could result in no counts.
  Serial.print("Hydro count: ");
  Serial.print(hydroFlow.checkCount());
  Serial.print("  Hydro RPM: ");
  Serial.println(hydroFlow.readRPM());
  //Serial.print("Hydro hertz: ");
  //Serial.println(hydroFlow.readHertz());

  Serial.print("Hot Water count: ");
  Serial.print(hotWaterFlow.checkCount());
  Serial.print("  Hot Water GPM: ");
  Serial.println(hotWaterFlow.readGPM());
  
  Serial.print("Hydronic count: ");
  Serial.print(hydronicWaterFlow.checkCount());
  Serial.print("  Hydronic GPM: ");
  Serial.println(hydronicWaterFlow.readGPM());
}

