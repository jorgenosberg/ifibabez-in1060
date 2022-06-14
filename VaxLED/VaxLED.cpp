#include "VaxLED.h"

/**
 * @brief Oppretter et nytt VaxLED-objekt.
 * @param ledCount : antall NeoPixel i stripen, hvis man evt. seriekobler flere
 * @param pin : pinen LEDen er koblet til
 */
VaxLED::VaxLED(int ledCount, int pin) 
{
  _ledCount = ledCount;
  _pin = pin;

  // oppretter og initialiserer NeoPixel-objektet
  Adafruit_NeoPixel flora(_ledCount, _pin, NEO_GRB + NEO_KHZ800);
  flora.begin();
};

/**
 * @brief Regner ut lysstyrke som maa times med non-blocking kode
 * i hovedsketchen. Baserer seg paa en tenkt sirkel og bruker radianene
 * for aa fade ihht. en sinuskurve.
 * @param index : indeks i LED-stripen (hvis man evt. seriekobler to eller flere)
 * @param r : roed verdi (0-255)
 * @param g : groenn verdi (0-255)
 * @param b : blaa verdi (0-255)
 */
void VaxLED::signal(int index, int r, int g, int b)
{               
  int interval = 15;
  long duration = 15000;
  long startTime = millis();
  
  while (millis() - startTime < duration) {
    
    // 360 grader av en tenkt sirkel
    for (int i = 0; i < 361; i++) {                         

      // setter LED paa indeks index til oppgitt farge
      flora.setPixelColor(0, 255, 255, 255);                        

      // konverterer grad/vinkel til radianer
      float angle = radians(i);      

      // regner ut punktet vha. sinuskurven som utgjoer lysstyrken
      int brightness = (255 / 2) + (255 / 2) * sin(angle);      
      
      // sender lysstyrken til NeoPixel-objektet 
      flora.setBrightness(brightness);

      // skrur paa ny lysstyrke og evt. ny farge                 
      flora.show();

      // delay foer neste lysstyrke
      delay(interval);
    }
  }

  // skrur av LED-dioden
  off();
};

/**
 * @brief Skrur av LED-dioden. Virker litt ulogisk aa bruke show(), 
 * men clear() setter kun RGB-verdien til 0,0,0 - oppdaterer ikke alltid LED-status
 */
void VaxLED::off() 
{
  flora.clear();
  flora.show(); 
}