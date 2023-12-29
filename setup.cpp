#include "constants.h"

void reboot(bool success) {
  wipeEEPROM();
}

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
  ElegantOTA.onStart(wipeEEPROM);
  ElegantOTA.onEnd(reboot);

  setTime(0, 0, 0, 1, 1, 2024);

  pinMode(LIGHT_SENSOR_PIN, INPUT);

  resetCrono();
}