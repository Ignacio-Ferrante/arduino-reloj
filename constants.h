#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ElegantOTA.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <TimeLib.h>
#include <FastLED.h>
#include <LittleFS.h>
#include <EEPROM.h>
#include <ArduinoJson.h>
#include "core_esp8266_features.h"

#define SEGMENT_LED_QUANTITY 2
#define DOT_LED_QUANTITY 2
#define LED_COUNT 60
#define LED_PIN 16 // D0
#define LIGHT_SENSOR_PIN A0

#define ERROR_CONFIG_COLOR 1
#define CREATE_CONFIG_COLOR 30
#define RESET_WIFI_COLOR 113
#define RECONECT_WIFI_COLOR 200
#define RESET_DEFAULT_COLOR 70

extern ESP8266WebServer server;
extern WiFiUDP ntpUDP;
extern NTPClient timeClient;
extern CRGB leds[LED_COUNT];

struct configs {
    String ssid;
    String password;

    int refreshVelocity;
    int useInvertedDigits;

    int color, colorMode, brightness;
    bool autoBrightness, nightTimeEnabled;

    int nightTimeRange[4];

    int timerMode, countdownMinutes, countdownSeconds;
};

enum ColorMode { STATIC, RAINBOW, FLOW };
enum TimerMode { CLOCK, COUNT, COUNTDOWN };

extern configs defaultConfig, globalConfig;

extern int hours, minutes;

extern int segmentMap[10][7], invertedSegmentMap[10][7];

void initializeClock();
void updateTime();
void forceUpdateTime();
void timerManagment();
bool isTimerActive();
void startTimer();
void pauseTimer();
void stopTimer();

void initServer();

void initializeFileSystem();
void loadConfig();
void saveConfig();
void resetDefaultConfig();
DynamicJsonDocument getJsonConfigs(configs config, bool showWifiData, bool transformForServer);
String getStringJsonConfigs(configs config, bool showWifiData, bool transformForServer);
void updateServerPage(String page);

void showTime(int hour, int minutes);
void showNumer(int number);
void printAllSegments(int color, int bright);
void turnOffAllSegments();
void blink(int color, int times);
void sound();
void reconectWifi();

#endif