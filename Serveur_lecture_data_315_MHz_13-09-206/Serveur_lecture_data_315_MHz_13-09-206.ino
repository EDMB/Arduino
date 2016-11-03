/**
 * Exemple de code pour la bibliothèque VirtualWire – Serveur d'envoi de tableau de valeurs
 */

#include <VirtualWire.h>

void setup() {
  Serial.begin(9600);

  // Initialisation de la bibliothèque VirtualWire
  // Vous pouvez changez les broches RX/TX/PTT avant vw_setup() si nécessaire
  vw_setup(2000);
  vw_rx_start(); // On peut maintenant recevoir des messages

  Serial.println("Go !"); 
}

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
  }
}
