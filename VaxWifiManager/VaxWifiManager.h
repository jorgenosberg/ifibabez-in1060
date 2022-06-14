#ifndef VaxWifiManager_h
#define VaxWifiManager_h

#include <WiFi.h>
#include <time.h>
#include <HTTPClient.h>

class VaxWifiManager
{
    public:
        // konstruktoerer
        VaxWifiManager(); // default internett hvis man bruker samme hele tiden
        VaxWifiManager(const char * ssid, const char * password); // for aa koble til et annet nett

        // kobler til eller fra
        bool connectToWiFi();
        void disconnect();

        // sender requests til Google scriptet, NTP-server eller oppgitt URL
        bool sendUpdateRequest(const char* vaxType, int vaxNumber);
        String requestTime();
        String requestURL(const char* url);
    ;

    private:
        // nettverksinnstillinger
        const char * _ssid;
        const char * _password;

        // google script-innstillinger
        const char * _scriptID;
        const char * _scriptURL;

        // ntp server-innstillinger
        const char * _ntp;
        unsigned long _gmtOffset;
        unsigned int _dstOffset;
    ;
};

#endif
