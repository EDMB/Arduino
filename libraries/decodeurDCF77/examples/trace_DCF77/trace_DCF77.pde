/***********************************************************************************************
//
// Programme de prise de trace de signal DCF77 pour module DCF1 (www.pollin.de)
//
// Resultat sur terminal série
// pour copier/coller dans votre traceur de courbe préféré (Microsoft Excel, Open Office Calc, etc.)
//
/***********************************************************************************************/

#include <Arduino.h>

/***********************************************************************************************/
//Cablage                   Arduino          DCF1
                             // GND----------PON
const uint8_t PIN_DCF77 = 3; // PIN----------DATA
                             // GND----------GND
                             // 3V3----------VCC
/***********************************************************************************************/

const uint32_t VITESSE_TERMINAL_SERIE = 115200;

const uint16_t NB_SECONDES_TRACE = 10; //10 = maximum pour une Uno (1250 octets de RAM pour la trace)

/***********************************************************************************************/

const uint16_t NB_BITS_TRACE = NB_SECONDES_TRACE * 1000;
const uint16_t NB_OCTETS_TRACE = (NB_BITS_TRACE + 7) / 8;

uint8_t  trace[NB_OCTETS_TRACE];

void calculerAdresse(uint16_t rang, uint16_t *rang_octet, uint8_t *rang_bit)
{
  if (rang >= NB_BITS_TRACE)
  {
    rang = NB_BITS_TRACE - 1;
  }

  *rang_octet = rang >> 3;
  *rang_bit   = rang  & 7;
}

uint8_t lireTrace(uint16_t rang)
{
  uint16_t rang_octet;
  uint8_t rang_bit;

  calculerAdresse(rang, &rang_octet, &rang_bit);

  return (trace[rang_octet] & (1 << rang_bit)) ? 1 : 0;
}

void ecrireTrace(uint16_t rang, uint8_t valeur)
{
  uint16_t rang_octet;
  uint8_t rang_bit;

  calculerAdresse(rang, &rang_octet, &rang_bit);

  if (valeur)
  {
    trace[rang_octet] |= (1 << rang_bit);
  }
  else
  {
    trace[rang_octet] &= ~(1 << rang_bit);
  }
}


void setup()
{
  Serial.begin(VITESSE_TERMINAL_SERIE);
  Serial.println("Programme de trace du signal DCF77");
  Serial.print("sur ");
  Serial.print(NB_SECONDES_TRACE);
  Serial.println(" secondes");
  Serial.println("Un echantillon par milliseconde");
  Serial.println();
  Serial.println("L'antenne doit etre perpendiculaire a la direction de l'emetteur (Allemagne)");
  Serial.println();
  pinMode(PIN_DCF77, INPUT);
}

void loop()
{
  static uint32_t ref_millis;
  static uint16_t curseur = 0;
  static bool rate;
  uint32_t chrono, delai;

  chrono = millis();
  if (curseur == 0)
  {
    ecrireTrace(curseur++, digitalRead(PIN_DCF77));
    ref_millis = chrono;
    rate = false;
  }
  else
  {
    delai = chrono - ref_millis;
    if (delai > 0)
    {
      ecrireTrace(curseur++, digitalRead(PIN_DCF77));
      rate &= (delai > 1);
      ref_millis = chrono;
    }
  }

  if (curseur == NB_BITS_TRACE)
  {
    if (rate)
    {
      Serial.println("Capture ratee");
    }
    else
    {
      Serial.println("Capture");
      for (uint16_t i=0; i<NB_BITS_TRACE; i++)
      {
        if (lireTrace(i))
        {
          Serial.println('1');
        }
        else
        {
          Serial.println('0');
        }
      }
    }
    curseur = 0;
    Serial.println();
    Serial.println("Fin de programme");
    while (1);
  }
}
