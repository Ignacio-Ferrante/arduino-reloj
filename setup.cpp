#include "constants.h"

void initializeClock() {
  Serial.begin(9600);

  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, LED_COUNT);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 1000);
  FastLED.clear();
  FastLED.show();

  blink(HUE_AQUA, 1);

  initializeFileSystem();

  //Configura la IP estática
  IPAddress ip(192, 168, 1, 201);
  IPAddress gateway(192, 168, 1, 1);
  IPAddress subnet(255, 255, 255, 0);

  WiFi.mode(WIFI_AP_STA);
  WiFi.config(ip, gateway, subnet, gateway);
  WiFi.softAP("Reloj");
  WiFi.setHostname("Reloj");

  if (globalConfig.ssid != "") {
    WiFi.begin(globalConfig.ssid, globalConfig.password);
  }

  initServer();
  timeClient.begin();
  ElegantOTA.begin(&server);

  setTime(0, 0, 0, 1, 1, 2025);

  pinMode(LIGHT_SENSOR_PIN, INPUT);
  MDNS.begin("reloj");
}