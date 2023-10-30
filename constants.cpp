#include "constants.h"

String ssid = "WiFi Casa 2.4";
String password = "0102721003";

ESP8266WebServer server(80);

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", -3 * 3600);

CRGB leds[LED_COUNT];

int color = 10, brightness = 250, lightLimit = 60, idleLight = 20, lowLightMin = 1, lowLightMax = 50, useInvertedDigits = 1;

int digits[10][7] = {
  { 0, 1, 1, 1, 1, 1, 1 },  // 0
  { 0, 1, 0, 0, 0, 0, 1 },  // 1
  { 1, 0, 1, 1, 0, 1, 1 },  // 2
  { 1, 1, 1, 0, 0, 1, 1 },  // 3
  { 1, 1, 0, 0, 1, 0, 1 },  // 4
  { 1, 1, 1, 0, 1, 1, 0 },  // 5
  { 1, 1, 1, 1, 1, 1, 0 },  // 6
  { 0, 1, 0, 0, 0, 1, 1 },  // 7
  { 1, 1, 1, 1, 1, 1, 1 },  // 8
  { 1, 1, 1, 0, 1, 1, 1 },  // 9
};

int invertedDigits[10][7] = {
  { 0, 1, 1, 1, 1, 1, 1 },  // 0
  { 0, 0, 0, 1, 1, 0, 0 },  // 1
  { 1, 0, 1, 1, 0, 1, 1 },  // 2
  { 1, 0, 1, 1, 1, 1, 0 },  // 3
  { 1, 1, 0, 1, 1, 0, 0 },  // 4
  { 1, 1, 1, 0, 1, 1, 0 },  // 5
  { 1, 1, 1, 0, 1, 1, 1 },  // 6
  { 0, 0, 1, 1, 1, 0, 0 },  // 7
  { 1, 1, 1, 1, 1, 1, 1 },  // 8
  { 1, 1, 1, 1, 1, 1, 0 },  // 9
};