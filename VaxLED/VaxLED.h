#ifndef VaxLED_H
#define VaxLED_H

#include <Adafruit_NeoPixel.h>

/**
 * @brief Klassedefinisjon for VaxLED.
 * Holder styr paa et NeoPixel-objekt og kan starte
 * LED-sekvensen eller slaa av dioden.
 */
class VaxLED
{
    public:
        VaxLED(int ledCount, int pin);
        void signal(int index, int r, int g, int b);
        void off();
    ;

    private:
        Adafruit_NeoPixel flora;
        int _pin;
        int _ledCount;
        int _default_brightness = 200;
    ;
};

#endif
