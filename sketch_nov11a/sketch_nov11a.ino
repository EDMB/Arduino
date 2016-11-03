    #include <SPI.h>         // needed for Arduino versions later than 0018
    #include <Ethernet.h>
    #include <EthernetUdp.h>         // UDP library from: bjoern@cs.stanford.edu 12/30/2008

    // Enter a MAC address and IP address for your controller below.
    // The IP address will be dependent on your local network:
    byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
    IPAddress ip(192, 168, 1, 177);
    IPAddress remote(192, 168, 1, 5);

    unsigned int localPort = 412;      // local port to listen on

    // An EthernetUDP instance to let us send and receive packets over UDP
    EthernetUDP Udp;

    void setup() {
      Serial.begin(9600);
      while (!Serial) {
        yield();
      }
      delay(2000); 
      
      Serial.setDebugOutput(true);
      Serial.print("[SETUP] Reset Info: ");
      Serial.println(ESP.getResetInfo());
      delay(1000); 
         
      // start the Ethernet and UDP:
      Ethernet.begin(mac, ip);
      IPAddress localIP = Ethernet.localIP(); 

      Serial.println(String("localIP=") + localIP.toString() + " subnetMask=" + Ethernet.subnetMask() + " subnetMask=" + Ethernet.gatewayIP());
      
      int ret = Udp.begin(localPort);
      Serial.println("begin... ret=" + String( ret )  );
    }

    void loop() {

       // Check the sockets status for references. 
      for( int i = 0 ; i < MAX_SOCK_NUM ; i++ ) {
        Serial.print(", Socket ID=" + String( i ) + " Status=" + Udp.SocketStatus( i ) );
      }
      Serial.println("");
      Serial.println("Sending...");
      int ret = 0 ; 
      
      // send a reply to the IP address and port that sent us the packet we received
      ret = Udp.beginPacket(remote, localPort) ;
      Serial.println("beginPacket... ret=" + String( ret )  );
      yield();
      
      ret = Udp.write("hello world");
      Serial.println("write... ret=" + String( ret )  );
      yield();
      
      ret = Udp.endPacket();
      Serial.println("endPacket... ret=" + String( ret )  );

      WaitABunch( 1000 ) ; 
    }


    void WaitABunch( int amount ) {
      while( amount > 0 ) {
        yield();
        delay(200);
        amount -= 200 ;     
      }  
    }
