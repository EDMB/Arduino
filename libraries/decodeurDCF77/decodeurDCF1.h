/***************************************************************************************************
/*
/* Driver de récepteur DCF77, modèle DCF1 (www.polllin.de)
/* Librairie spécifique Arduino
/*
/* (2015) Bricoleau
/*
/***************************************************************************************************/
#ifndef decodeurDCF1_h
#define decodeurDCF1_h

#include <Arduino.h>

class decodeurDCF1_c
{
  public :
    void begin(uint8_t pin); //obligatoirement une pin avec interruption

    void start(); //activer le traitement de l'interruption (non inclus dans begin)
    void stop();  //desactiver le traitement de l'interruption

    //A partir de là, les donnees ci-dessous sont automatiquement mises à jour par l'interruption
    //Utilisation en lecture seule

    //HORLOGE
    const uint32_t millis_derniere_trame_ok(); //Suivre la valeur de cette zone
          //pour savoir si une nouvelle date/heure est disponible ci-dessous
    const uint8_t  annee();
    const uint8_t  mois();
    const uint8_t  jour();
    const uint8_t  joursem(); //1 = lundi, ... 7 = dimanche
    const uint8_t  heure();
    const uint8_t  minute();
    const bool     heure_ete();

    //SIGNAL
    const uint8_t  qualiteReception();
          //valeurs renvoyées :
          //  0    : signal inexistant
          //1 à 4  : signal trop faible, pas de décodage possible
          //  5    : signal parfait, décodage probable
          //  6    : signal correct, décodage probable
          //7 à 11 : signal parasité, décodage incertain
    const uint8_t  longueur_trame_en_cours(); //pour suivre la réception
    const uint8_t  bit_trame(uint8_t rang);   //pour suivre la réception

    //DIVERS
    const bool started(); //interruption activee
    const uint8_t pin();

  private :
    uint8_t _pin;
};

extern decodeurDCF1_c decodeurDCF1;

#endif
