/**
 * Exemple de code pour la bibliothèque VirtualWire – Serveur d'envoi de tableau de valeurs
 */

#include <VirtualWire.h>
#include <SoftwareSerial.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display


const int rxpin = 2;           // pin used to receive (not used in this version) 
const int txpin = 3;           // pin used to send to LCD
SoftwareSerial serial_lcd(rxpin, txpin); // new serial port on pins 2 and 3




void setup() {
  Serial.begin(9600);
  serial_lcd.begin(9600); //initialize the software serial port also for 9600
  lcd.begin (16,2); //  <<----- My LCD was 16x2

  lcd.init();                      // initialize the lcd 
 
  // Print a message to the LCD.
  lcd.backlight();
  lcd.print("Reader");
  
  
  // Initialisation de la bibliothèque VirtualWire
  // Vous pouvez changez les broches RX/TX/PTT avant vw_setup() si nécessaire
  vw_setup(2000);
  vw_rx_start(); // On peut maintenant recevoir des messages

  Serial.println("Go !"); 
}

int number = 0;

void loop() {
  int valeurs[6];
  byte taille_message = sizeof(valeurs);

  /* 
   La variable "taille_message" doit impérativement être remise à 
   la taille du tableau avant de pouvoir recevoir un message. 
   Le plus simple est d'utiliser une variable locale pour ne pas
   avoir à réassigner la valeur à chaque début de loop().
   */

  // On attend de recevoir un message
  vw_wait_rx();

  if (vw_get_message((byte *) &valeurs, &taille_message)) {
    // On copie le message, qu'il soit corrompu ou non

    Serial.print("[0]=");
    Serial.print(valeurs[0]); // Affiche le message
    Serial.print("-[1]=");
    Serial.print(valeurs[1]); 
    Serial.print("-[2]=");
    Serial.print(valeurs[2]); 
    Serial.print("-[3]=");
    Serial.print(valeurs[3]); 
    Serial.print("-[4]=");
    Serial.print(valeurs[4]); 
    Serial.print("-[5]=");
    Serial.println(valeurs[5]);
    
    serial_lcd.print("The number is ");  // send text to the LCD
    serial_lcd.println(number);    // print the number on the LCD
    
    number++;   // to the next number
    
    lcd.setCursor(0, 1);
    lcd.print("V=");
    lcd.setCursor(4, 1);
    lcd.print(valeurs[0]);
    lcd.setCursor(10, 1);
    lcd.print(number);
  }
}
