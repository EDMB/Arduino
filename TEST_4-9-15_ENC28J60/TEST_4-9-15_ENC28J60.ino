// This is a demo of the RBBB running as webserver with the Ether Card
// 2010-05-28 <jc@wippler.nl> http://opensource.org/licenses/mit-license.php

#include <EtherCard.h>

// ethernet interface mac address, must be unique on the LAN
static byte mymac[] = { 0x74,0x69,0x69,0x2D,0x30,0x31 };
static byte myip[] = { 192,168,1,200 };

byte Ethernet::buffer[500];
BufferFiller bfill;

void setup () {
  //CS is connected to pin 10
  if (ether.begin(sizeof Ethernet::buffer, mymac, 10) == 0)
    Serial.println(F("Failed to access Ethernet controller"));
  ether.staticSetup(myip);
}

static word homePage() {
  long t = millis() / 1000;
  word h = t / 3600;
  byte m = (t / 60) % 60;
  byte s = t % 60;
  bfill = ether.tcpOffset();
  bfill.emit_p(PSTR(
    "HTTP/1.0 200 OK\r\n"
    "Content-Type: text/html\r\n"
    "Pragma: no-cache\r\n"
    "\r\n"
    "<meta http-equiv='refresh' content='1'/>"
    "<title>RBBB server</title>" 
    "<h1>$D$D:$D$D:$D$D</h1>"),
      h/10, h%10, m/10, m%10, s/10, s%10);
  return bfill.position();
}

void loop()
{
 Client client = server.available();
 if (client) {
   // an http request ends with a blank line
   boolean current_line_is_blank = true;
   while (client.connected()) {
     if (client.available()) {
       char c = client.read();
       // if we've gotten to the end of the line (received a newline
       // character) and the line is blank, the http request has ended,
       // so we can send a reply
       if (c == '\n' && current_line_is_blank) {
         // send a standard http response header
         client.println("HTTP/1.1 200 OK");
         client.println("Content-Type: text/html");
         client.println();
         
         // output the value of each analog input pin
         for (int i = 0; i < 6; i++) {
           client.print("analog input ");
           client.print(i);
           client.print(" is ");
           client.print(analogRead(i));
           client.println("");
         }
         break;
       }
       if (c == '\n') {
         // we're starting a new line
         current_line_is_blank = true;
       } else if (c != '\r') {
         // we've gotten a character on the current line
         current_line_is_blank = false;
       }
     }
   }
   // give the web browser time to receive the data
   delay(1);
   client.stop();
 }
}
