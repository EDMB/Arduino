#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

RH_ASK driver;

void setup()
{
    Serial.begin(9600);	  // Debugging only
    if (!driver.init())
         Serial.println("init failed");
}

void loop()
{
    int sensorValue0 = analogRead(A0); //analogRead(A0);
    
   
    const char *msg = "Hello World!";
    char *msg1 = "Hello World!";
    String stringOne = "Hello String";
    stringOne =  String(analogRead(A0), DEC);
    *msg1= stringOne;
   
    driver.send((uint8_t *)msg1, strlen(msg1));
    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
    delay(1000);
}
