
/*
	MotionSensorGrid
 
	This sketch enables a grid system of PIR motion detectors on two axes
        to output coordinates on the grid defining areas that objects encompass.
 
	The circuit:
	* PIR sensors on each input pin equivalent to total marks on both axes
	* Output to serial monitor (to be later taken in by Processing or by 
          output method of choice)
 
	Created  2014-11-11
	By Tanay Nandgaonkar
 
	Adapted from https://learn.adafruit.com/pir-passive-infrared-proximity-motion-sensor/using-a-pir
 
*/
 
int rowInputPinCount=1;          // the number of row marks 
int columnInputPinCount=2;       // the number of column marks
int rowInputPin[] = {13};        // the ordered row input pins (for PIR sensor)
int columnInputPin[] = {11,9};   // the ordered column input pins (for PIR sensor)
int rowVal[] = {0};              // array for reading the row pins' status
int colVal[] = {0,0};            // array for reading the column pins' status
 
void setup() {
 for (int thisPin = 0; thisPin < rowInputPinCount; thisPin++)  {
    pinMode(rowInputPin[thisPin], INPUT);      
  }
 for (int thisPin = 0; thisPin < columnInputPinCount; thisPin++)  {
    pinMode(columnInputPin[thisPin], INPUT);      
  }
  //each for loop declares all the row and column pins, respectively, as inputs
  Serial.begin(9600);
}
 
void loop(){
  for (int thisPin = 0; thisPin < columnInputPinCount; thisPin++)  {
    colVal[thisPin]=digitalRead(columnInputPin[thisPin]);      
  }
  for (int thisPin = 0; thisPin < rowInputPinCount; thisPin++)  {
    rowVal[thisPin]=digitalRead(rowInputPin[thisPin]);      
  }
  //use for loop to take a reading of each column and row input pin
  for (int thisColPin = 0; thisColPin < columnInputPinCount; thisColPin++)  {
  //this for loop runs through each column pin
    if (colVal[thisColPin]==HIGH) {
    //if motion in the column is detected, then each row in the column is checked
      for (int thisRowPin = 0; thisRowPin < rowInputPinCount; thisRowPin++)  {
      //this for loop runs through each row pin
        if (rowVal[thisRowPin]==HIGH) {
        //if the row pin has detected motion
            //Serial.print("Motion Detected! Column:");
            Serial.print(thisColPin);
            Serial.print( ",");
            //Serial.print("Row: ");
            //Uncomment the serial.print commands for a more human-readable format
            Serial.println(thisRowPin);
            //coordinates of motion are printed out to the serial monitor
        }
      }
    } 
  }
//Uncomment this block of code to see the values of the pins by column and row 
//  Serial.print("Values; Column: ");
//  for (int thisPin = 0; thisPin < columnInputPinCount; thisPin++)  {
//    Serial.print(colVal[thisPin]);
//  }
//  Serial.print(" Row: "); 
//  for (int thisPin = 0; thisPin < rowInputPinCount; thisPin++)  {
//     Serial.println(rowVal[thisPin]);
//  }
 
 delay(1000);
}
