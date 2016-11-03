 
/*
Arduino code.
This is for use with the Raspberry Pi through the
I2C. RPi sends a value from 0-255 which is displayed
on the LCD display. Arduino echoes back a response and
the number sent from RPi.

LCD section taken from
http://www.bristolwatch.com/arduino/arduino4a.html

*/

#define Bit_out 12 // Pin 1-2 SN74164
#define CLK 11 // Pin 9 SN74164
#define RS 7  // Pin 4 LCD
#define E 8  // Pin 6 LCD

#define SLAVE_ADDRESS 0x04
int number = 0;
int state = 0;

// location LCD row 0 col 0 or line 1 LCD
#define Line1 0x80  
// location row 1 col 0 or line 2 LCD
#define Line2 0x80 + 0x40  

#include <Wire.h>

void setup() {
  pinMode(Bit_out, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(RS, OUTPUT);
  pinMode(E, OUTPUT);

  digitalWrite(CLK, LOW); 
  // LCD in command mode default
  digitalWrite(RS, LOW); 
  digitalWrite(E, HIGH);
  initLCD(); // se below
  // initialize i2c as slave
  Wire.begin(SLAVE_ADDRESS);

  // define callbacks for i2c communication
  Wire.onReceive(receiveData);
  Wire.onRequest(sendData);
  typeln("Arduino Ready!", Line1);
  typeln("Number = ", Line2);
}

void loop() {
  delay(100);
} // end loop

// location is place on LCD display. 
void typeInt(int k, int location)   {
  char array1[10];
  itoa(k, array1, 10); // int to string
  typeln(array1, location);
}

void typeChar(byte val)   {
  ssrWrite(val);
  digitalWrite(RS, HIGH);
  pulseOut(E);
  digitalWrite(RS, LOW);
}

void writeCommand(byte val)   {

  ssrWrite(val); // send byte to 74164
  digitalWrite(RS, LOW); // make sure RS in Com mode
  pulseOut(E);
}


// Below we pass a pointer to array1[0].
void typeln(char *s, int location)   {
  delayMicroseconds(1000);
  writeCommand(location); // where to begin 
  while (*s)  typeChar(*(s++));
}  // end typeln

// inverts state of pin, delays, then reverts state back
void    pulseOut(byte x)   {
  byte z = digitalRead(x);
  delayMicroseconds(10);
  z = !z; // reverse state
  digitalWrite(x, z);
  z = !z; // return to original state
  digitalWrite(x, z);
} // end pulsout()


void ssrWrite(byte val)  {  // shift data to 74164
  for (int j=1; j<=8; j++)  {   // shift out MSB first
    byte  temp = val & B10000000; // MSB out first
    if (temp == 0x80) digitalWrite(Bit_out, HIGH); 
    else digitalWrite(Bit_out, LOW); 
    pulseOut(CLK); 
    val = val << 1; // shift one place left
  }  // next j
}  // end byteWrite


void initLCD(void)   {

  writeCommand(0x38); // setup for 2 lines
  writeCommand(0x0F); // blinking cursor
  writeCommand(0x01); // clear
  writeCommand(0x02); // home
}


void ClearDisplay(void)   {
  writeCommand(0x01); // clear
  writeCommand(0x02); // home
}



// callback for received data
void receiveData(int byteCount){

  while(Wire.available()) { 
    number = Wire.read();
    typeInt(number, Line2 + 9);


  }
}  // end while

// callback for sending data
void sendData(){
  Wire.write(number);
}

