#include <VaxMonitor.h>

/**
 * @brief Oppretter et nytt objekt av klassen VaxMonitor med Member Initializer List.
 * @param pin 1-3 : GPIO-pinene knappene er koblet til
 * @param led 1-3 : en referanse til et objekt av klassen VaxLED (LED-stripen som skal brukes)
 * @param buzzer : en referanse til et objekt av klassen VaxBuzzer
 */
VaxMonitor::VaxMonitor(Pushbutton& btn1, Pushbutton& btn2, Pushbutton& btn3, VaxLED& led1, VaxLED& led2, VaxLED& led3, VaxBuzzer& buzzer, VaxWifiManager& VaxWifiManager) : 
_btn1(btn1), _btn2(btn2), _btn3(btn3), _led1(led1), _led2(led2), _led3(led3), _buzzer(buzzer), _vaxWifiManager(VaxWifiManager)
{   
  // tom konstruktoer fordi alt skjer
  // i member initializer list
}

/**
 * @brief Sjekker status paa knappen. Maa kjoeres kontinuerlig i loop(). 
 * Kaller knappens tilkoblede funksjoner naar status endres.
 */
void VaxMonitor::refresh()
{
    if (_btn1.getSingleDebouncedPress()) {
      _led1.signal(0,255,255,255);
      _buzzer.playTone();
      // Her ville print-metoden som snakker med printeren ha vaert
      _vaxWifiManager.sendUpdateRequest((char*) "Pfizer (0,3 ml)", _vaxNumber);
      _vaxNumber++;
    }

    if (_btn2.getSingleDebouncedPress()) {
      _led2.signal(0,255,255,255);
      _buzzer.playTone();
      _vaxWifiManager.sendUpdateRequest((char*) "Moderna (0,25 ml)", _vaxNumber);
      _vaxNumber++;
    }

    if (_btn2.getSingleDebouncedPress()) {
      _led3.signal(0,255,255,255);
      _buzzer.playTone();
      _vaxWifiManager.sendUpdateRequest((char*) "Moderna (0,5 ml)", _vaxNumber);
      _vaxNumber++;
    }
}

/**
 * @brief Sjekker status paa knappen. Maa kjoeres kontinuerlig i loop(). 
 * Kaller knappens tilkoblede funksjoner naar status endres.
 */
void VaxMonitor::startup()
{
    _buzzer.playStartupSound();
    _vaxWifiManager.connectToWiFi();
}

/**
 * @brief Sjekker status paa knappen. Maa kjoeres kontinuerlig i loop(). 
 * Kaller knappens tilkoblede funksjoner naar status endres.
 */
void VaxMonitor::shutdown()
{
    _buzzer.playShutdownSound();
    _vaxWifiManager.disconnect();
}
