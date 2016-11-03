/*
  FlowCounters.h - Library for multiple flow meters, hall devices, etc.
  Created by turgo.   
*/

#ifndef FlowCounters_h
#define FlowCounters_h

#include "stdint.h"

#if defined(ARDUINO) && ARDUINO >= 100
  #include <Arduino.h>
#else
  #include "pins_arduino.h"
  #include "WProgram.h"
  #include "wiring.h"
#endif

#define LIBCALL_OOPINCHANGEINT
#include "../ooPinChangeInt/ooPinChangeInt.h"

#include "../cbiface/cbiface.h"

#undef DEBUG

#define DEFAULTDELAY 10

 // Trigger FALLING for when the pin goes from high to low.

class FlowCounters : public CallBackInterface {
	public:
		FlowCounters(uint8_t arduinoPin) : interruptCount(0), _arduinoPin(arduinoPin), _flowConst(-1000), _trigger(FALLING), _resistor(HIGH), _delay(DEFAULTDELAY), _startTime(0) {
			init();
		}
		FlowCounters(uint8_t arduinoPin, float flowConst) :
			interruptCount(0), _arduinoPin(arduinoPin), _flowConst(flowConst), _trigger(FALLING), _resistor(HIGH), _delay(DEFAULTDELAY), _startTime(0) {
			init();
		}
		FlowCounters(uint8_t arduinoPin, float flowConst, uint8_t resistor) :
			interruptCount(0), _arduinoPin(arduinoPin), _flowConst(flowConst), _trigger(FALLING), _resistor(resistor), _delay(DEFAULTDELAY), _startTime(0) {
			init();
		}
		uint16_t getCount(); // read the number of state changes from the switch.  Reset the count to 0 upon read.
		uint16_t getCountNoReset(); // Do the same, but no reset.
		uint8_t getPin(); // return the arduino pin for this Tigger
		void cbmethod();  // required method for a subclass of CallBackInterface
		unsigned long getStartTime();
		unsigned long getMillis();
		float checkCount();
		float readHertz();
		float readRPM();
		float readLitersPerMin();
		float readGPM();
		
	protected:
		uint8_t _arduinoPin;
		uint8_t _delay;
		uint8_t _resistor;
		uint8_t _trigger;
		long _startTime;
		float _flowConst;
	private:
		void init();
		unsigned long flowCountStart;
		unsigned long interruptCount;
};
#endif
