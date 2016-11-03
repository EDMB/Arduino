/*
  FlowCounters.cpp - Library for multiple flow meters, hall devices, etc.
  Created by turgo.   
*/

#include "FlowCounters.h"

# define cli()  __asm__ __volatile__ ("cli" ::)
# define sei()  __asm__ __volatile__ ("sei" ::)

//#undef DEBUG

/*
 * NOTES
 * This library handles flow meters and hall sensors attached to an Arduino digital input pin.  Analog
 * pins are handled, of course, because the analog pins can be used as digital inputs
 * as well.
 *
 * The library is interrupt-driven and designed to be fast and easy to use.  The interrupt
 * routine is lightweight, and the programmer is then able to read counts
 * at their leisure.
*/

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
// Analog Pins  A8 - A15 [Port K]

// the format is: FlowCounters flowMeterName(arduinoPin, flowConstant, resistor);
// In the equation: Frequency (Hz) = 7.5 * Flow rate (L/min), the flowConstant is 7.5. Omitting flowConstant defaults to -1000.   
//       Then, only readHertz() and readRPM() are meaningful.
// the resistor is HIGH to enable the internal pullup resistor, or Low to disable it.  Omitting resistor defaults to HIGH.


// DEBUG: volatile uint8_t *port;
void FlowCounters::init() {
	volatile uint8_t *port=portInputRegister(digitalPinToPort(_arduinoPin));
	if (port == NOT_A_PIN) { return; }
	pinMode(_arduinoPin, INPUT);
	digitalWrite(_arduinoPin, _resistor);
	// DEBUG: port=portInputRegister(digitalPinToPort(_arduinoPin));

	PCintPort::attachInterrupt(_arduinoPin, this, _trigger);
	flowCountStart=millis();
};

extern volatile unsigned long timer0_millis; // From the Arduino wiring.h file.
unsigned long tigermillis=0;


// Interrupt has been triggered.
//This is the interrupt or ISR().  Because it is an object, it isn't static, and has access to members of the instance.

void FlowCounters::cbmethod() {  
	interruptCount++;
}


/*
 * Returns the counts.  Upon reading, resets to 0.
 */
uint16_t FlowCounters::getCount() {
	uint16_t val;
	val=interruptCount; interruptCount=0;
	return val;
}

/*
 * Returns the counts.
 */
uint16_t FlowCounters::getCountNoReset() {
	return interruptCount;
}

/*
 * Returns the Arduino Pin for this Tigger
 */
uint8_t FlowCounters::getPin() {
	return _arduinoPin;
}

/*
 * startTime is the millis() value when the last switch transition was recorded. 
 * millis() is the Arduino call that returns the number of milliseconds since the Arduino was reset.
 * It is a 32-bit unsigned number.
 */
unsigned long FlowCounters::getStartTime() {
	return _startTime;
}

/*
 * Returns the millis() value when the latest switch transition caused an interrupt, which includes bounces.
 */
unsigned long FlowCounters::getMillis() {
	return tigermillis;
}

float FlowCounters::checkCount() {  //Return the count.
  return (float)interruptCount;
};

float FlowCounters::readHertz() {  //Read the count, reset the counter, restart the sample period, return the frequency in hertz.
  long now, count;
  float flowFrequency = 0;
  if (interruptCount != 0) {
    count = interruptCount;
    interruptCount = 0;
    now = millis();
    flowFrequency=(float)count/((now-flowCountStart)/1000);
    flowCountStart= now;
  }
  return flowFrequency;
};

float FlowCounters::readRPM() {  // Return the RPM (Revolitions Per Minute).
  return readHertz()*60;
};

float FlowCounters::readLitersPerMin() {  // Return the flow in Liters per Minute.
  return readHertz()/_flowConst;
};

float FlowCounters::readGPM() {  // Return the flow in GPM (Gallons per Minute).
  return readLitersPerMin()/3.8;
};