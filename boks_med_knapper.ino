#include <Pushbutton.h>
#include <VaxMonitor.h>

#define BUTTON1_PIN 11
#define BUTTON2_PIN 12
#define BUTTON3_PIN 13

#define LED1_PIN A1
#define LED2_PIN A2
#define LED3_PIN A3

#define BUZZER_PIN A4

Pushbutton btn1(BUTTON1_PIN);
Pushbutton btn2(BUTTON2_PIN);
Pushbutton btn3(BUTTON3_PIN);

VaxLED led1(1, LED1_PIN);
VaxLED led2(1, LED2_PIN);
VaxLED led3(1, LED3_PIN);

VaxBuzzer buzzer(BUZZER_PIN);

const char* ssid = "Oppe IAV4";
const char* pswd = "pappabetaler";

VaxWifiManager vaxWifiManager(ssid, pswd);

VaxMonitor vaxMonitor(btn1, btn2, btn3, led1, led2, led3, buzzer, vaxWifiManager);

void setup() 
{
  vaxMonitor.startup();
}

void loop() 
{
  vaxMonitor.refresh();
}
