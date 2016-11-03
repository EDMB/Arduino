/*
  Adding Strings together

 Examples of how to add strings together
 You can also add several different data types to string, as shown here:
 
 Arduino Atmega 328 UNO

 created 27 July 2010
 modified 2 Apr 2012
 by Tom Igoe

 http://www.arduino.cc/en/Tutorial/StringAdditionOperator

 This example code is in the public domain.
 */

// declare three strings:
String stringOne, stringTwo, stringThree;

#include "DHT.h"
#define DHTPIN 2 // what pin we're connected to

// Uncomment whatever type you're using!
//#define DHTTYPE DHT11 // DHT 11
#define DHTTYPE DHT22 // DHT 22 (AM2302)
//#define DHTTYPE DHT21 // DHT 21 (AM2301)
// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors. This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.

DHT dht(DHTPIN, DHTTYPE);

void rupt() {}





void setup() {
  // initialize serial and wait for port to open:
  Serial.begin(115200);
  
    attachInterrupt (0, rupt, CHANGE);
  dht.begin();
  
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  stringOne = String("stringThree = ");
  stringTwo = String("this string");
  stringThree = String();
  // send an intro:
  //Serial.println("\n\nAdding strings together (concatenation):");
  //Serial.println();
}

void loop() {

  // Wait a few seconds between measurements.

delay(2000);

// Reading temperature or humidity takes about 250 milliseconds!
// Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)

float h = dht.readHumidity();

// Read temperature as Celsius (the default)

float t = dht.readTemperature();

// Read temperature as Fahrenheit (isFahrenheit = true)

float f = dht.readTemperature(true);

// Check if any reads failed and exit early (to try again).

if (isnan(h) || isnan(t) || isnan(f)) {
Serial.println("Failed to read from DHT sensor!");
return;
}

// Compute heat index in Fahrenheit (the default)

// float hif = dht.computeHeatIndex(f, h);

// Compute heat index in Celsius (isFahreheit = false)

//float hic = dht.computeHeatIndex(t, h, false);

//Serial.print("Humidity: ");
Serial.print(h);
//Serial.print(" \t");
//Serial.print("Temperature: ");
Serial.print("-");
Serial.println(t);
//Serial.print(" *C ");
//Serial.print(f);
//Serial.print(" *F\t");
//Serial.print("Heat index: ");
//Serial.print(hic);
//Serial.print(" *C ");
//Serial.print(hif);
//Serial.println(" *F");
  
  
  
  // adding a variable integer to a string:
  int sensorValue00 = 3281;
  int sensorValue0 = analogRead(A0);
  int sensorValue1 = analogRead(A1);
  int sensorValue2 = analogRead(A2);
  int sensorValue3 = analogRead(A3);
  int sensorValue4 = analogRead(A4);
  int sensorValue5 = analogRead(A5);
 
  stringOne = "";
  stringThree =  stringOne + sensorValue00 + "-" + sensorValue0 + "-" + sensorValue1 + "-" + sensorValue2 + "-" + sensorValue3 + "-" + sensorValue4 + "-" + sensorValue5;
  Serial.println(stringThree);    // prints "Sensor Value: 3281-401-..." or whatever value analogRead(A0) has

//Serial.println (" ");
delay (10000);

  // do nothing while true:
  //while (true);
}
