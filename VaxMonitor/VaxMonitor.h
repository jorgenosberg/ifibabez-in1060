#ifndef VaxMonitor_h
#define VaxMonitor_h

#include <Pushbutton.h>
#include <VaxLED.h>
#include <VaxBuzzer.h>
#include <VaxWifiManager.h>

/**
 * @brief Klassedefinisjon for VaxMonitor. 
 * Holder styr paa alle objektene av Pusbutton, VaxLED-klassen, 
 * VaxBuzzeren og VaxWifiManageren. Haandterer events fra
 * knappene med riktige kall paa objekt-referansene.
 */
class VaxMonitor 
{
    public:
        VaxMonitor(Pushbutton& btn1, Pushbutton& btn2, Pushbutton& btn3, VaxLED& led1, VaxLED& led2, VaxLED& led3, VaxBuzzer& buzzer, VaxWifiManager& vaxWifiManager); // konstruktoer
        void startup();
        void shutdown();
        void refresh(); // sjekker status paa knappene
    ;

    private:        
        int _vaxNumber = 1;
        
        VaxBuzzer& _buzzer;

        VaxWifiManager& _vaxWifiManager;

        VaxLED& _led1;
        VaxLED& _led2;
        VaxLED& _led3;

        Pushbutton& _btn1;
        Pushbutton& _btn2;
        Pushbutton& _btn3;
    ;
};

#endif