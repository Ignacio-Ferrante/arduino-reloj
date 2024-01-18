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

#define SEGMENT_LED_QUANTITY 2
#define DOT_LED_QUANTITY 2
#define LED_COUNT 60
#define LED_PIN 16 // D0
#define LIGHT_SENSOR_PIN A0

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
void timerManagment();
void startTimer();
void pauseTimer();
void stopTimer();

String getJsonConfigs(configs config, bool showWifiData);
void initServer();

void initializeEEPROM();
void saveConfig();
void wipeEEPROM();

void showTime(int hour, int minutes);
void showNumer(int number);
void printAllSegments(int color, int bright);
void turnOffAllSegments();

#endif