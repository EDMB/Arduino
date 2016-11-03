#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
  #else
  #include "WProgram.h"
  #endif
#include <Wire.h>
#include "wm_crypto.h"

/*Replace #include "WProgram.h" with the above code to make compatible with
latest Arduino IDE.*/