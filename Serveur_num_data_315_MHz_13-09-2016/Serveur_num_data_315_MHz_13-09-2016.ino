/**
 * Exemple de code pour la bibliothèque VirtualWire – Client d'envoi de tableau de valeurs
 */
 
#include <VirtualWire.h>

void setup() {
  Serial.begin(9600);

  // Initialisation de la bibliothèque VirtualWire
  // Vous pouvez changez les broches RX/TX/PTT avant vw_setup() si nécessaire
  vw_setup(2000);
  
  Serial.println("Go !"); 
}
 
void loop() {
  int valeurs[6];
  
  // Lit les broches analogiques
  valeurs[0] = analogRead(0);
  valeurs[1] = analogRead(1);
  valeurs[2] = analogRead(2);
  valeurs[3] = analogRead(3);
  valeurs[4] = analogRead(4);
  valeurs[5] = analogRead(5);
  
  vw_send((byte *) &valeurs, sizeof(valeurs)); // On envoie le message
  vw_wait_tx(); // On attend la fin de l'envoi
  
  delay(1000);
}
