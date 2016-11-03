

/*                   Red    ---> 5v 
   Flow meter 1 ---> Black ---> GND
            (Signal) Yellow ---> digital pin 2


                     Red ---> 5v
   Flow meter 2 ---> Black ---> GND
            (Signal) Yellow ---> digital pin 3
*/

#define FLOWSENSORPIN 2
#define FLOWSENSORPIN2 3 

// count how many pulses!
volatile uint16_t pulses = 0;
volatile uint16_t pulses2 = 0;
// track the state of the pulse pin
volatile uint8_t lastflowpinstate;
volatile uint8_t lastflowpinstate2;
// you can try to keep time of how long it is between pulses
volatile uint32_t lastflowratetimer = 0;
volatile uint32_t lastflowratetimer2 = 0;
// and use that to calculate a flow rate
volatile float flowrate;
volatile float flowrate2;
// Interrupt is called once a millisecond, looks for any pulses from the sensor!
SIGNAL(TIMER0_COMPA_vect) {
  uint8_t x = digitalRead(FLOWSENSORPIN);
  
  if (x == lastflowpinstate) {
    lastflowratetimer++;
    return; // nothing changed!
  }
  
  if (x == HIGH) {
    //low to high transition!
    pulses++;
  }
  
  lastflowpinstate = x;
  flowrate = 1000.0;
  flowrate /= lastflowratetimer;  // in hertz
  lastflowratetimer = 0;
}


SIGNAL(TIMER2_COMPA_vect) {
  
  uint8_t x2 = digitalRead(FLOWSENSORPIN2);
  
  if (x2 == lastflowpinstate2) {
    lastflowratetimer2++;
    return; // nothing changed!
  }
  

  if (x2 == HIGH) {
    //low to high transition!
    pulses2++;
  }


  lastflowpinstate2 = x2;
  flowrate2 = 1000.0;
  flowrate2 /= lastflowratetimer2;  // in hertz
  lastflowratetimer2 = 0;
}


void useInterrupt(boolean v) {
  if (v) {
    // Timer0 is already used for millis() - we'll just interrupt somewhere
    // in the middle and call the "Compare A" function above
    OCR0A = 0xAF;
    TIMSK0 |= _BV(OCIE0A);
  } else {
    // do not call the interrupt function COMPA anymore
    TIMSK0 &= ~_BV(OCIE0A);
  }
}




void useInterrupt2(boolean b) {
  if (b) {
    // Timer0 is already used for millis() - we'll just interrupt somewhere
    // in the middle and call the "Compare A" function above
    OCR2A = 0xAF;
    TIMSK2 |= _BV(OCIE2A);
  } else {
    // do not call the interrupt function COMPA anymore
    TIMSK2 &= ~_BV(OCIE2A);
  }
}



void setup()
{
  Serial.begin(9600);
  
  pinMode(FLOWSENSORPIN, INPUT);
  digitalWrite(FLOWSENSORPIN, HIGH);
  lastflowpinstate = digitalRead(FLOWSENSORPIN);
  
  pinMode(FLOWSENSORPIN2, INPUT);
  digitalWrite(FLOWSENSORPIN2, HIGH);
  lastflowpinstate2 = digitalRead(FLOWSENSORPIN2);
  
  useInterrupt(true);
  useInterrupt2(true);

}


void loop() {
  

  float liters = pulses;
  liters /= 7.5;
  liters /= 60.0;

  float liters2 = pulses2;
  liters2 /= 7.5;
  liters2 /= 60.0;
 
  //Serial.println(level);
  Serial.print(liters); Serial.print(" Liters"); Serial.print("        "); Serial.print(liters2); Serial.println(" Liters");
  
  delay(100);
 
}
