
/*
Pulse Period Measurement of 10 Flow Sensors
-------------------------------------------------------------------------------------
• accurate measurements by using Arduino micros() function
• determines leading edge of pulses without use of iterrupts
• calculates pulse periods, frequencies, flow rates, totalized volumes
• includes pulse generator for testing, simulation and troubleshooting
• easily adapted for testing other sensors and pulse quantities (energy, optic, etc.)
- dlloyd ----------------------------------------------------------------------------*/

// constants
const byte pgenPin = 13;  // PGEN pin number
const byte CLEAR = 12;    // CLEAR pin number
const byte inputs[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11}; // input pins
const double pulseConstant[] = {7.5, 7.5, 7.5, 7.5, 7.5, 7.5, 7.5, 7.5, 7.5, 7.5}; // pulse constants
const byte qty = sizeof(inputs);

//#include <SoftwareSerial.h>

// variables

double pgenFrequency = 7.5;   // pulse generator frequency (Hz)

long previousMillis = 0;
long pgenInterval = 1000000 / (pgenFrequency * 2);
byte pgenState = LOW;
long pgenPreviousMicros = 0;
long startTime[qty];
byte inputsState[qty];
byte inputsPrevious[qty];
double pulsePeriod[qty];
double pulseFrequency[qty];
double pulseMultiplier[qty];
double flowRate[qty];
double pulseVolume[qty];
double totalVolume[qty];

void setup() {
 Serial.begin(115200);
 Serial.print("");
 Serial1.begin(9600);
 Serial1.print("");
 Serial2.begin(9600);
 Serial2.print("");
 
 pinMode(pgenPin, OUTPUT);
 pinMode(CLEAR, INPUT_PULLUP);
 for (int i = 0; i < qty; i++) {
   pinMode(inputs[i], INPUT_PULLUP);
   pulseVolume[i] = 1.0 / (pulseConstant[i] * 60);
   pulseMultiplier[i] = 1.0 / (pulseConstant[i]);
 }
 clr(); // initialize arrays
}

void loop()
{
 pgen();  // run pulse generator

 if (digitalRead (CLEAR) == LOW) {  // check CLEAR push button
   clr();
 }
 pulseMeasure();  // run flow tests, calculations and print results
}


// functions -----------------------------------------------------

void pulseMeasure() {

 for (int i = 0; i < qty; i++) {
   inputsState[i] = digitalRead(inputs[i]);                   // read the inputs

   if ((inputsState[i] == 1) && (inputsPrevious[i] == 0)) {   // if rising
     pulsePeriod[i] = (micros() - startTime[i]) * 0.000001;   // test duration (sec)
     pulseFrequency[i] = 1 / pulsePeriod[i];                  // input frequency (Hz)
     flowRate[i] = pulseFrequency[i] * pulseMultiplier[i];    //  1.0 / pulseConstant[i] (L/min)
     totalVolume[i] = totalVolume[i] + pulseVolume[i];        // totalized volume (L)

     if (millis() - previousMillis > 250) {                   // update interval (milliseconds)
       Serial.print(i); Serial.print(": ");
       Serial.print(pulsePeriod[i], 6); Serial.print(" sec, ");
       Serial.print(pulseFrequency[i], 3); Serial.print(" Hz, ");
       Serial.print(flowRate[i], 3); Serial.print(" L/min, ");
       Serial.print(totalVolume[i], 6); Serial.print(" L");
       Serial.println();
       previousMillis = millis();
     }
     startTime[i] = micros();
   }
   inputsPrevious[i] = inputsState[i];
 }
}

void pgen() {
 // check to see if it's time to pulse the PGEN; that is, if the
 // difference between the current time and last time you pulsed
 // the PGEN is bigger than the interval to changed its output state.
 unsigned long pgenCurrentMicros = micros();

 if (pgenCurrentMicros - pgenPreviousMicros > pgenInterval) {
   // save the last time you pulsed the PGEN
   pgenPreviousMicros = pgenCurrentMicros;

   // if the PGEN output is off turn it on and vice-versa:
   if (pgenState == LOW)
     pgenState = HIGH;
   else
     pgenState = LOW;

   digitalWrite(pgenPin, pgenState);
 }
}

void clr() {
 for (int i = 0; i < qty; i++) {
   startTime[i] = micros();
   inputsState[i] = 0;
   inputsPrevious[i] = 1;
   pulsePeriod[i] = 0;
   pulseFrequency[i] = 0;
   flowRate[i] = 0;
   totalVolume[i] = 0;
 }
}
