/* This script is used to make sense of the output from a hall effect water flow meter and make a note of any problems
 
 
Michael Ratcliffe  Mike@MichaelRatcliffe.com
 
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
 
 
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
 
 
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see .
 

    Components:
    See main folder for sensor data sheets, required liabaries and extra information: [can be downloaded via www.michaelratcliffe.com]
 
    All power systems should be powerd of DC voltage of below 48v for safter [water is around] 12v is prefferable and cheapest. 
    As always this is a DIY project and done at your own risk.
  
    >Arduino Mega 2560 [1280 is not sutiable, ram problems and sensor conflict] compiled using Arduino 1:1.0.5
    >Hall Effect Water Flow Meter 5v
 
 
*/
//******************************** User Defined Variables *******************************************************//

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>


#define Meter_power  5
#define Meter_ground 4
#define Water_pin 3

LiquidCrystal_I2C lcd(0x27,16,4);  // set the LCD address to 0x27 for a 16 chars and 4 line display

 
float Click_Per_L = 367; // this depends on your flow meter
String Temp;
  
const float Max_ExpectedFlow =2; //Max flow expected flowrate in L/s, if it is more than this we have a problem
 
 
 
//***************************** End Of User Defined Variables **************************************************//

 
unsigned long PulseCount=0;  //counter for water meter pulses
long Second;
long Last_Reading=0;
int Readings=0;
float Water_Used=0;
float Flow_Rate= 0;
float Max_Flow_Rate= 0;
long Last_Count =0;
 
int BurstPipe=0;

//**************************** Setup Routine , Runs Once and Sets used pins to correct value *******************//
void setup() {

Serial.begin(115200);  
pinMode(Meter_ground, OUTPUT);
digitalWrite(Meter_ground, LOW);
 
pinMode( Meter_power, OUTPUT);
digitalWrite(Meter_power, HIGH);
      
pinMode(Water_pin, INPUT);
digitalWrite(Water_pin, HIGH);// saves having an external pullup
   
//External Interrupts:  3 (interrupt 1),     
attachInterrupt(1, WaterCounter, FALLING);  //watermeter pulse output connected to pin3

lcd.init();                      // initialize the lcd 
 
// Print a message to the LCD.
lcd.backlight();
lcd.print("");
  

};
 
//************************************** Main Loop that will continualy run ******************************************//
void loop(){
 
Second=millis()/1000;
 
 
//************** If Statment that will run every second ******************//
            if (Last_Reading!=Second) {
            Last_Reading=Second; //Makes note of the last second
            Readings=1;          //Tell serial there is data to transmit
            Flow_Rate=((PulseCount-Last_Count)/Click_Per_L);
            if (Flow_Rate>Max_Flow_Rate){
                                                       Max_Flow_Rate=Flow_Rate;
                                                                  };    
         
            Water_Used=(1/(Click_Per_L/PulseCount)); //cant recall why I did it this way, maybe to retain float capabilities
            Last_Count=PulseCount;                   // Makes a note of the last reading
                   
                               //** Checks if there is a problem **//
                                  if(Flow_Rate>=Max_ExpectedFlow){
                                                       BurstPipe=1;
                                                                  };
 
 
                                    };
 
 
 
 
//**** Checks If there is Data To send over Serial- Recomended to be LCD instead ******//
if (Readings==1){
Readings=0;
 
//Temp = "Total Water Used" + Water_Used + " L" + "Current Flow Rate: " + Flow_Rate +" L/s";
//
Serial.println Temp;

lcd.setCursor(0, 0);
lcd.print("Water meter");
  
lcd.setCursor(0, 1);
  
lcd.print(Water_Used);
lcd.print(" liters");  
  
lcd.setCursor(-4, 2);
  
lcd.print(Flow_Rate);
lcd.print(" liter/s");
lcd.print("  ");
lcd.setCursor(-4, 3);
lcd.print(Max_Flow_Rate);
lcd.print(" liter/s"); 
 
if(BurstPipe==1){
            Serial.println("BurstPipe");
            
           
            
          }
     
 
}
 
 
   
delay(10);
};
//*************************************************END OF LOOP ******************************************************//
 
 
//***Interupt routine for water meter readings - Runs everytime sensor has a pulse ***//
 
 
void WaterCounter() {
 
   // Increment the pulse counter
  PulseCount++;
 
};
