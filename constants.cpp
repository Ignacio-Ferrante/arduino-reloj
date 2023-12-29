#include "constants.h"

ESP8266WebServer server(80);

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", -3 * 3600);

CRGB leds[LED_COUNT];

configs globalConfig;
configs defaultConfig = {
  .ssid = "WiFi Casa 2.4",
  .password = "0102721003",
  .refreshVelocity = 100,
  .useInvertedDigits = 1,
  .color = 17,
  .colorMode = 0,
  .brightness = 100,
  .nightTimeRange = {22, 30, 7, 0},
  .timerMode = 0,
  .countdownMinutes = 5,
  .countdownSeconds = 0
};

int hours, minutes;

bool isTimerRunning;
unsigned long timerStartTime;

int segmentMap[10][7] = {
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

int invertedSegmentMap[10][7] = {
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