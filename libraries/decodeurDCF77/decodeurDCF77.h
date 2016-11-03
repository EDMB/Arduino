/***************************************************************************************************
/*
/* Décodeur DCF77
/*
/* Code générique multi-plateforme, non spécifique à Arduino.
/* (2015) Bricoleau
/*
/***************************************************************************************************/
#ifndef decodeurDCF77_h
#define decodeurDCF77_h

#include <stdint.h>

class decodeurDCF77_c
{
  public :
    decodeurDCF77_c();

    bool traiterSignal(uint8_t signal_0_ou_1, uint32_t millis_signal);
    //retourne true si une trame est décodée, false sinon

    //Les donnees ci-dessous sont mises à jour par la fonction traiterSignal()
    //Utilisation en lecture seule

    //HORLOGE
    const uint32_t millis_derniere_trame_ok();
    const uint8_t  annee();
    const uint8_t  mois();
    const uint8_t  jour();
    const uint8_t  joursem(); //1 = lundi, ... 7 = dimanche
    const uint8_t  heure();
    const uint8_t  minute();
    const bool     heure_ete();

    //SIGNAL
    const uint8_t  qualiteReception(uint32_t millis_maintenant);
          //valeurs renvoyées :
          //  0    : signal inexistant
          //1 à 4  : signal trop faible, pas de décodage possible
          //  5    : signal parfait, décodage probable
          //  6    : signal correct, décodage probable
          //7 à 11 : signal parasité, décodage incertain
    const uint8_t  longueur_trame_en_cours(); //pour suivre la réception
    const uint8_t  bit_trame(uint8_t rang);   //pour suivre la réception

  private :
    uint32_t _millis_derniere_trame_ok;
    uint8_t  _annee;
    uint8_t  _mois;
    uint8_t  _jour;
    uint8_t  _joursem;
    uint8_t  _heure;
    uint8_t  _minute;
    bool     _heure_ete;

    uint32_t ref_synchro_pulsation;
    void     decalerPulsation(uint32_t millis_reference);
};

extern decodeurDCF77_c decodeurDCF77;

#endif
