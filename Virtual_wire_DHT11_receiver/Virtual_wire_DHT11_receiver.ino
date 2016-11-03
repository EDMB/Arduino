#include <VirtualWire.h>
void setup()
{
     Serial.begin(9600);
    Serial.println("setup");
    Serial.println("CLEARDATA");
    vw_setup(2000);
    vw_set_rx_pin(11);
    vw_rx_start();
    pinMode(13,OUTPUT);
}
void loop()
{
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;
    if (vw_get_message(buf, &buflen)) 
    {
int i;
digitalWrite(13, true); 
//Serial.print("Got:   ");
Serial.println("CLEARDATA");
Serial.print("DATA, ,");
for (i = 0; i < buflen; i++)
{
  
    Serial.write(buf[i]);
    Serial.print(" ");
}
Serial.println(" ");

     digitalWrite(13, false);
    }
}
