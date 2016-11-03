/***********************************************************************************************
//
// Demo pour librairie decodeurDCF77
//
/***********************************************************************************************/

#include <Arduino.h>
#include "decodeurDCF77.h"

const uint8_t PIN_DCF77 = 3;

void setup() {
  pinMode(PIN_DCF77, INPUT);
  Serial.begin(115200);
  Serial.println("Demo decodage signal DCF77\n");
  Serial.println("Recherche pulsation...");
}

void loop() {
  static uint8_t longueur = 0;

  bool trame_decodee = decodeurDCF77.traiterSignal(digitalRead(PIN_DCF77), millis());

  if (trame_decodee) {
    Serial.print(' ');
    Serial_printDCF77();
  }

  if (longueur > decodeurDCF77.longueur_trame_en_cours()) {
    longueur = 0;
    Serial.println();
  }

  while (longueur < decodeurDCF77.longueur_trame_en_cours()) {
    Serial.print(decodeurDCF77.bit_trame(longueur++));
  }
}

void Serial_printDCF77() {
  switch (decodeurDCF77.joursem()) {
    case 0 : Serial.println("(vide)"); return;
    case 1 : Serial.print("Lundi"); break;
    case 2 : Serial.print("Mardi"); break;
    case 3 : Serial.print("Mercredi"); break;
    case 4 : Serial.print("Jeudi"); break;
    case 5 : Serial.print("Vendredi"); break;
    case 6 : Serial.print("Samedi"); break;
    case 7 : Serial.print("Dimanche"); break;
  }
  Serial.print(' ');
  Serial_print99(decodeurDCF77.jour());
  Serial.print('/');
  Serial_print99(decodeurDCF77.mois());
  Serial.print("/20");
  Serial_print99(decodeurDCF77.annee());
  Serial.print(' ');
  Serial_print99(decodeurDCF77.heure());
  Serial.print(':');
  Serial_print99(decodeurDCF77.minute());
  Serial.print(' ');
  if (decodeurDCF77.heure_ete()) {
    Serial.print("(heure d'ete)");
  } else {
    Serial.print("(heure d'hiver)");
  }
}

void Serial_print99(uint8_t nombre) {
  if (nombre < 10) Serial.print('0');
  Serial.print(nombre);
}
