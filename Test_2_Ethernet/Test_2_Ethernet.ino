#include <EtherCard.h>
#include "DHT.h"
#include <LCD5110_Basic.h>
 
 
#define DHTPIN 8
#define DHTPIN_OUT 9
#define DHTTYPE DHT22
#define BACKLIGHT = 7; 
 
// ethernet interface mac address, must be unique on the LAN
static byte mymac[] = { 0x74,0x69,0x69,0x2D,0x30,0x31 };
 
byte Ethernet::buffer[700];
char myIpString[24];
 
extern uint8_t MediumNumbers[];
 
extern uint8_t SmallFont[];
static uint32_t timer;
 
DHT dht(DHTPIN, DHTTYPE);
DHT dht_out(DHTPIN_OUT, DHTTYPE);
LCD5110 myGLCD(6,5,4,2,3);
 
const char website[] PROGMEM = "%DOMAIN%";
 
int dstart = 0; 
int dlen = 0; 
char tbuff[12];
char cbuff[]="serial=0&temperature=00&humidity=00&oustsidetemp=00&oustsidehum=00";
 
 
// called when the client request is complete
static void my_callback (byte status, word off, word len) {
  Serial.println(">>>");
  Ethernet::buffer[off+300] = 0;
  Serial.print((const char*) Ethernet::buffer + off);
  Serial.println("...");
  memset( &tbuff, 0, sizeof(tbuff)); 
}
 
void setup () {
  Serial.begin(57600);
  Serial.println(F("\n[setup]"));
 
  if (ether.begin(sizeof Ethernet::buffer, mymac,10) == 0) 
    Serial.println(F("Failed to access Ethernet controller"));
  if (!ether.dhcpSetup())
    Serial.println(F("DHCP failed"));
 
  ether.printIp("IP:  ", ether.myip);
  ether.printIp("GW:  ", ether.gwip);  
  ether.printIp("DNS: ", ether.dnsip);  
 
  if (!ether.dnsLookup(website))
    Serial.println("DNS failed");
     
  pinMode(7,OUTPUT);
     
  sprintf(myIpString, "%d.%d.%d.%d", ether.myip[0], ether.myip[1], ether.myip[2], ether.myip[3]);  
  ether.printIp("SRV: ", ether.hisip);
  myGLCD.InitLCD();
  dht.begin();
  dht_out.begin();
   
}
 
void loop () {
  
  ether.packetLoop(ether.packetReceive());
   
  word len = ether.packetReceive();
  word pos = ether.packetLoop(len);
   
  if(pos)
  {
  char* data = (char *) Ethernet::buffer + pos;
  Serial.println("----------------");
  Serial.println("data received:");
  Serial.println(data);
  Serial.println("----------------");
  if (strncmp("GET /?on",data,8) == 0) {
  digitalWrite(7, LOW); 
  Serial.println("LED ON:");
  }
  if (strncmp("GET /?off",data,9) == 0) {
  digitalWrite(7, HIGH); 
  Serial.println("LED OFF:");
  }
  }
   
  if (millis() > timer) {
     
  float h = dht.readHumidity();
  float ho = dht_out.readHumidity();
  // Read temperature as Celsius
  float t = dht.readTemperature();
  float to = dht_out.readTemperature();
 
     myGLCD.clrScr();
  
     myGLCD.setFont(SmallFont);
     myGLCD.print("------------", CENTER, 17);
       
     myGLCD.print("Teplota",LEFT,0);
     myGLCD.print("Venkovni",LEFT,15);
     myGLCD.print("Vlhkost",LEFT,24);
     myGLCD.print("Venkovni",LEFT,34);
     myGLCD.printNumF(t, 1, RIGHT, 0);
     myGLCD.printNumF(to, 1, RIGHT, 15);
     myGLCD.printNumI(ho, RIGHT, 34);
     myGLCD.printNumI(h, RIGHT, 24);
      
  
    timer = millis() + 50000;
    Serial.println();
    Serial.print("<<< REQ ");
   
  
  dtostrf(t,2,2,tbuff); 
  dstart = 21;
  //start of replace 
  dlen = 2; 
   
  for (int i=0+dstart; i <= dstart+dlen-1; i++)
  { 
  cbuff[i] = tbuff[i-dstart];
  }
   
  dtostrf(h,2,3,tbuff);
  dstart = 33;
  dlen = 2;
   
  for (int i=0+dstart; i <= dstart+dlen-1; i++)
  { 
  cbuff[i] = tbuff[i-dstart];
  } 
   
  memset( &tbuff, 0, sizeof(tbuff)); 
 
  // Outside values
  dtostrf(to,2,2,tbuff); 
  dstart = 49;
  dlen = 2; 
   
  for (int i=0+dstart; i <= dstart+dlen-1; i++)
  { 
  cbuff[i] = tbuff[i-dstart];
  }
   
  dtostrf(ho,2,3,tbuff);
  dstart = 64;
  dlen = 2;
   
  for (int i=0+dstart; i <= dstart+dlen-1; i++)
  { 
  cbuff[i] = tbuff[i-dstart];
  } 
    Serial.println();
    Serial.print("Buffer");
    Serial.println();
    Serial.print(cbuff);
    Serial.println();
   
    ether.browseUrl(PSTR("/%WRITE_SCRIPT%.php?"),cbuff, website, my_callback);
    
}
 
myGLCD.setFont(SmallFont);
myGLCD.print(myIpString, CENTER, 46);
 
}

