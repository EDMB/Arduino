#include <VirtualWire.h>
#include <DHT.h>

#define DHTPIN 2

#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  Serial.begin(9600);
  Serial.println("setup");
  vw_set_tx_pin(12);
  vw_setup(2000);
  pinMode(13,OUTPUT);
  dht.begin();
}
void loop()
{
  int h = dht.readHumidity();
  int t = dht.readTemperature();

  String messageString = String();
  for(int i=0;i<6;i++){
    messageString.concat(analogRead(i));
    messageString.concat(",");
  }
  messageString.concat(t);
  messageString.concat(",");
  messageString.concat(h);
  messageString.concat(",");

  char msg[messageString.length()+1];
  messageString.toCharArray(msg,messageString.length()+1);
  digitalWrite(13, true);
  vw_send((uint8_t *)msg, strlen(msg));
  vw_wait_tx();
  digitalWrite(13, false);
  delay(1000);
}
