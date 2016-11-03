// Program: Display 7 segments - 8 digit MAX7219 
// Load the LedControl library 
#include "LedControl.h"

// Definitions pins and number of modules in the circuit 
LedControl lc = LedControl ( 7 , 6 , 5 , 1 );

void setup ()
{
  // Initialize the module 
  lc.shutdown ( 0 , false);
   // display brightness adjustment 
  lc.setIntensity ( 0 , 3 );
   // Delete the display 
  lc.clearDisplay ( 0 );
}

void loop ()
{
  // Send Arduino for display
  writeArduinoOn7Segment ();
  // Countdown
  countdown();

  // Init counter 0 1 million 
  for ( long i = 0 ; i < 1000000 ; i ++)
  {
    printNumber (i);
  }
  delay ( 500 );
}
void printNumber ( long v)
{
  // Variable value digit 
  int digito1;
   int digito2;
   int digito3;
   int digito4;
   int digito5;
   int digito6;
   int digito7;
   int digito8;

  // Calculate the value of each digit 
  digito1 v =% 10 ;
  digito2 = (V / 10 )% 10 ;
  digito3 = (V / 100 )% 10 ;  
  digito4 = (V / 1000 )% 10 ;
  digito5 = (V / 10000 )% 10 ;
  digito6 = (v / 100000 )% 10 ;
  digito7 = (v / 1000000 )% 10 ;
  digito8 = (v / 10000000 )% 10 ;
  
  // Display the value of each digit in the display 
  lc.setDigit ( 0 , 7 , (byte) digito8, false);
  lc.setDigit ( 0 , 6 , (byte) digito7, false);
  lc.setDigit ( 0 , 5 , (byte) digito6, false);
  lc.setDigit ( 0 , 4 , (byte) digito5, false);
  lc.setDigit ( 0 , 3 , (byte) digito4, false);
  lc.setDigit ( 0 , 2 , (byte) digito3, false);
  lc.setDigit ( 0 , 1 , (byte) digito2, false);
  lc.setDigit ( 0 , 0 , (byte) digito1, false);
  delay ( 00 );
}

void writeArduinoOn7Segment ()
{
  // Arduino on the display 
  for ( int i = 0 ; i < 21 ; i ++)
  {
    lc.setChar ( 0 , i, 'a' , false);
    lc.setRow ( 0 , i 1 , 0x05 );
    lc.setChar ( 0 , i- 2 , 'd' , false);
    lc.setRow ( 0 , i- 3 , 0x1c );
    lc.setRow ( 0 , i- 4 , B00010000);
    lc.setRow ( 0 , i 5 , 0x15 );
    lc.setRow ( 0 , i- 6 , 0x1D );
    lc.setChar ( 0 , i- 7 , '' , false);
    lc.setChar ( 0 , i- 8 , 'and' , false);
    lc.setChar ( 0 , i- 9 , '' , false);
    lc.setRow ( 0 , i- 10 , B1001110);    
    lc.setRow ( 0 , i- 11 , B0010000);  
    lc.setChar ( 0 , i- 12 , 'a' , false);    
    lc.setChar ( 0 , i- 13 , '' , false);
    delay ( 300 );
  }
}

