/***************************************************************************************************
/*
/* Demo pour librairie tunerDCF77
/*
/*
/***************************************************************************************************/
#include <Arduino.h>
#include "tunerDCF77.h"

const uint32_t DELAI_ACTUALISATION_ECRAN = 1000; //millisecondes
const uint8_t  pin_dcf77 = 3;

void setup()
{
  Serial.begin(115200);
  pinMode(pin_dcf77, INPUT);
  Serial.println("Tuner pour signal DCF77\n");
  Serial.println("SIGNAL: FAIBLE        <-OK---BON-------PARASITES------>");
}

void loop()
{
  static uint32_t chrono_affichage = 0;
  static uint8_t signal_precedent = LOW;

  uint32_t maintenant = millis();

  //Enregistrement du signal
  uint8_t signal = digitalRead(pin_dcf77);
  if (signal != signal_precedent) {
    signal_precedent = signal;
	if (signal == LOW) {
	  tunerDCF77.enregistrerFrontDescendant(maintenant);
	}
	else {
	  tunerDCF77.enregistrerFrontMontant(maintenant);
	}
  }

  //Affichage de la barre de réception du signal
  if (maintenant - chrono_affichage >= DELAI_ACTUALISATION_ECRAN) {
    chrono_affichage += DELAI_ACTUALISATION_ECRAN;
	uint8_t niv = tunerDCF77.qualiteReception(maintenant);
	uint8_t n = 0;
	while (n++ < niv) Serial.print(">>>>>");
	while (n++ <= 11) Serial.print("     ");
	if (niv < 10) Serial.print('0');
	Serial.print(niv);
	Serial.print(" Signal ");
	switch (niv) {
	  case 0 : Serial.println("inexistant");break;
	  case 1 :
	  case 2 :
	  case 3 :
	  case 4 : Serial.println("trop faible");break;
	  case 5 : Serial.println("OK");break;
	  case 6 : Serial.println("correct");break;
	  default: Serial.println("avec parasites");
	}
  }
}
