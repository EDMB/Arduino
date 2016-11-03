/**
 * Exemple de code pour la bibliothèque Mirf – Client d'envoi de tableau de valeurs
 */

#include <SPI.h>      // Pour la communication via le port SPI
#include <Mirf.h>     // Pour la gestion de la communication
#include <nRF24L01.h> // Pour les définitions des registres du nRF24L01
#include <MirfHardwareSpiDriver.h> // Pour la communication SPI
 
void setup() {
  Serial.begin(9600);
   
  Mirf.cePin = 9; // Broche CE sur D9
  Mirf.csnPin = 10; // Broche CSN sur D10
  Mirf.spi = &MirfHardwareSpi; // On veut utiliser le port SPI hardware
  Mirf.init(); // Initialise la bibliothéque

  Mirf.channel = 100; // Choix du cannal de communication (128 canaux disponible, de 0 à 127)
  Mirf.payload = sizeof(int) * 6; // Taille d'un message (maximum 32 octets)
  Mirf.config(); // Sauvegarde la configuration dans le module radio
  
  Mirf.configRegister(RF_SETUP, 0x26);
  
  Mirf.setTADDR((byte *) "nrf02"); // Adresse de transmission
  Mirf.setRADDR((byte *) "nrf01"); // Adresse de réception
   
  Serial.println("Go Sender"); 
}
 
void loop() {
  int valeurs[6];
  int i;
  
  i++;
  // Lit les broches analogiques
  valeurs[0] = analogRead(0);
  valeurs[1] = analogRead(1);
  valeurs[2] = analogRead(2);
  valeurs[3] = analogRead(3);
  valeurs[4] = analogRead(4);
  valeurs[5] = analogRead(5);
  valeurs[6] = analogRead(6);
  
    Serial.print("[0]=");
    Serial.println(valeurs[0]); // Affiche le message
    Serial.print("[1]=");
    Serial.println(valeurs[1]); 
    Serial.print("[2]=");
    Serial.println(valeurs[2]); 
    Serial.print("[3]=");
    Serial.println(valeurs[3]); 
    Serial.print("[4]=");
    Serial.println(valeurs[4]); 
    Serial.print("[5]=");
    Serial.println(valeurs[5]);

  
  Mirf.send((byte *) &valeurs); // On envoi le message
  while(Mirf.isSending()); // On attend la fin de l'envoi
  
  delay(500);
} 
