#include "constants.h"

void initializeClock() {
  initializeEEPROM();

  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, LED_COUNT);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 1000);
  FastLED.clear();
  FastLED.show();

  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP("reloj");

  if (globalConfig.ssid != "") {
    WiFi.begin(globalConfig.ssid, globalConfig.password);
  }

  initServer();
  timeClient.begin();
  ElegantOTA.begin(&server);

  pinMode(LIGHT_SENSOR_PIN, INPUT);

  resetCrono();
}