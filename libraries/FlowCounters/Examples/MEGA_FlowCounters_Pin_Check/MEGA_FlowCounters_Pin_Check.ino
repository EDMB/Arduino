
#include <ooPinChangeInt.h>  // Necessary when including FlowCounters.h. Otherwise we get undefined reference errors.
#include <FlowCounters.h>

// This example demonstrates all possible instances of the FlowCounters class for the MEGA 2560 board.
 
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

FlowCounters flow10(10,.5); 
FlowCounters flow11(11,.5); 
FlowCounters flow12(12,.5); 
FlowCounters flow13(13,.5); 
FlowCounters flow14(14,.5); //didn't work, probably because of the serial connection.
FlowCounters flow15(15,.5);
FlowCounters flow50(50,.5);
FlowCounters flow51(51,.5);
FlowCounters flow52(52,.5);
FlowCounters flow53(53,.5);
FlowCounters flowA6(A6,.5); //Port F didn't work
FlowCounters flowA7(A7,.5); //Port F didn't work
FlowCounters flowA8(A8,.5);
FlowCounters flowA9(A9,.5);
FlowCounters flowA10(A10,.5);
FlowCounters flowA11(A11,.5);
FlowCounters flowA12(A12,.5);
FlowCounters flowA13(A13,.5);
FlowCounters flowA14(A14,.5);
FlowCounters flowA15(A15,.5);

void setup() {
  
  Serial.begin(115200);
  Serial.println("---------------------------------------");
}

void loop() {
  delay(1000);
  //Output options are: readHertz(), readRPM(), readLitersPerMin(), and readGPM().  
  // Calling any of them returns the measurment since the last read and resets the measurment interval 
  // - so calling one immediately after another could result in no counts.
  if (flow10.checkCount()>0) Serial.println(String("pin 10:")+String(flow10.readRPM()));
  if (flow11.checkCount()>0) Serial.println(String("pin 11:")+String(flow11.readRPM()));
  if (flow12.checkCount()>0) Serial.println(String("pin 12:")+String(flow12.readRPM()));
  if (flow13.checkCount()>0) Serial.println(String("pin 13:")+String(flow13.readRPM()));
  if (flow14.checkCount()>0) Serial.println(String("pin 14:")+String(flow14.readRPM()));
  if (flow15.checkCount()>0) Serial.println(String("pin 15:")+String(flow15.readRPM()));
  if (flow50.checkCount()>0) Serial.println(String("pin 50:")+String(flow50.readRPM()));
  if (flow51.checkCount()>0) Serial.println(String("pin 51:")+String(flow51.readRPM()));
  if (flow52.checkCount()>0) Serial.println(String("pin 52:")+String(flow52.readRPM()));
  if (flow53.checkCount()>0) Serial.println(String("pin 53:")+String(flow53.readRPM()));
  if (flowA6.checkCount()>0) Serial.println(String("pin A6:")+String(flowA6.readRPM()));
  if (flowA7.checkCount()>0) Serial.println(String("pin A7:")+String(flowA7.readRPM()));
  if (flowA8.checkCount()>0) Serial.println(String("pin A8:")+String(flowA8.readRPM()));
  if (flowA9.checkCount()>0) Serial.println(String("pin A9:")+String(flowA9.readRPM()));
  if (flowA10.checkCount()>0) Serial.println(String("pin A10:")+String(flowA10.readRPM()));
  if (flowA11.checkCount()>0) Serial.println(String("pin A11:")+String(flowA11.readRPM()));
  if (flowA12.checkCount()>0) Serial.println(String("pin A12:")+String(flowA12.readRPM()));
  if (flowA13.checkCount()>0) Serial.println(String("pin A13:")+String(flowA13.readRPM()));
  if (flowA14.checkCount()>0) Serial.println(String("pin A14:")+String(flowA14.readRPM()));
  if (flowA15.checkCount()>0) Serial.println(String("pin A15:")+String(flowA15.readRPM()));
}

