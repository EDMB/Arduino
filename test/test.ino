/*
  Adding Strings together

 Examples of how to add strings together
 You can also add several different data types to string, as shown here:

 created 27 July 2010
 modified 2 Apr 2012
 by Tom Igoe

 http://www.arduino.cc/en/Tutorial/StringAdditionOperator

 This example code is in the public domain.
 */

// declare three strings:
String stringOne, stringTwo, stringThree;

void setup() {
  // initialize serial and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  stringOne = String("stringThree = ");
  stringTwo = String("this string");
  stringThree = String();
  // send an intro:
  Serial.println("\n\nAdding strings together (concatenation):");
  Serial.println();
}

void loop() {



  // adding a variable integer to a string:
  int sensorValue0 = analogRead(A0);
  int sensorValue1 = analogRead(A1);
  int sensorValue2 = analogRead(A2);
  int sensorValue3 = analogRead(A3);
  int sensorValue4 = analogRead(A4);
  int sensorValue5 = analogRead(A5);
  int sensorValue6 = analogRead(A6);
 
  stringOne = "";
  stringThree =  stringOne + sensorValue0 + "-" + sensorValue1 + "-" + sensorValue2 + "-" + sensorValue3 + "-" + sensorValue4 + "-" + sensorValue5 + "-" + sensorValue6;
  Serial.println(stringThree);    // prints "Sensor Value: 401" or whatever value analogRead(A0) has



Serial.println (" ");
delay (5000);

  // do nothing while true:
  //while (true);
}
