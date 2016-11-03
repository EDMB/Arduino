/***********************************************************************************************
//
// Programme de test reception de signal DCF77 pour module DCF1 (www.pollin.de)
//
// Resultat sur terminal serie
//
/***********************************************************************************************/

#include <Arduino.h>
#include "decodeurDCF1.h"

const uint32_t DELAI_ACTUALISATION_ECRAN = 5000; //millisecondes

/***********************************************************************************************/
//Cablage                   Arduino          DCF1
                             // GND----------PON
const uint8_t PIN_DCF1 = 3;  // PIN----------DATA
                             // GND----------GND
                             // 3V3----------VCC

//La pin de branchement doit disposer d'une interruption (pin 2 ou 3 pour une Uno)
/***********************************************************************************************/

uint32_t ref_millis;

void setup() {
  Serial.begin(115200);
  Serial.println("Programme de test reception DCF77 pour module DCF1");
  Serial.println("avec lectures automatiques de la pin DATA via des interruptions\n");
  Serial.println("Cablage pour module DCF1 (www.pollin.de) : ");
  Serial.println("DCF1(PON)-----------(GND)Arduino");
  Serial.print("DCF1(DATA)---------(PIN");
  Serial.print(PIN_DCF1);
  Serial.println(")Arduino");
  Serial.println("DCF1(GND)-----------(GND)Arduino");
  Serial.println("DCF1(VCC)-----------(3V3)Arduino\n");
  Serial.println("L'antenne doit etre perpendiculaire a la direction de l'emetteur (Allemagne)\n");
  Serial.println("SIGNAL: FAIBLE        <-OK---BON-------PARASITES------>");

  decodeurDCF1.begin(PIN_DCF1);
  decodeurDCF1.start();

  if (!decodeurDCF1.started())
  {
    Serial.println("Probleme : la pin selectionnee n'a pas d'interruption associee !");
    while (1);
  }

  ref_millis = decodeurDCF1.millis_derniere_trame_ok();
}

void loop() {
  static uint32_t chrono_affichage = 0;

  //Affichage de la barre de reception du signal
  if (millis() - chrono_affichage >= DELAI_ACTUALISATION_ECRAN) {
    chrono_affichage += DELAI_ACTUALISATION_ECRAN;
    uint8_t niv = decodeurDCF1.qualiteReception();
    uint8_t n = 0;
    while (n++ < niv) Serial.print(">>>>>");
    while (n++ <= 11) Serial.print("     ");
    if (decodeurDCF1.millis_derniere_trame_ok() > ref_millis) {
      ref_millis = decodeurDCF1.millis_derniere_trame_ok();
      Serial_printDCF77();
    }
    else {
      Serial.print("Reception ");
      Serial_print99(decodeurDCF1.longueur_trame_en_cours());
      Serial.println("/59");
    }
  }
}

void Serial_printDCF77() {
  switch (decodeurDCF1.joursem()) {
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
  Serial_print99(decodeurDCF1.jour());
  Serial.print('/');
  Serial_print99(decodeurDCF1.mois());
  Serial.print("/20");
  Serial_print99(decodeurDCF1.annee());
  Serial.print(' ');
  Serial_print99(decodeurDCF1.heure());
  Serial.print(':');
  Serial_print99(decodeurDCF1.minute());
  Serial.print(' ');
  if (decodeurDCF1.heure_ete()) {
    Serial.println("(heure d'ete)");
  } else {
    Serial.println("(heure d'hiver)");
  }
}

void Serial_print99(uint8_t nombre) {
  if (nombre < 10) Serial.print('0');
  Serial.print(nombre);
}
