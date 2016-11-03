import os
import sys
import termios
import fcntl

        self.fd = sys.stdin.fileno()

        // Stop resetting the arduino on serial connect//

        self.newattr = termios.tcgetattr(self.fd)
        self.newattr[2] = self.newattr[2] & ~termios.HUPCL
        termios.tcsetattr(self.fd, termios.TCSANOW, self.newattr)


void setup() {
  // put your setup code here, to run once:
  int a=10;
  }

void loop() {
  // put your main code here, to run repeatedly:
  Serial.begin(9600); 
  int a;
  a=a+1;
  delay (10);
  Serial.println (a);
  }

  
  
