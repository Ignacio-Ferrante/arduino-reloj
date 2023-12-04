#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <TimeLib.h>
#include <FastLED.h>
#include <LittleFS.h>
#include <EEPROM.h>
#include <ArduinoJson.h>

#define LED_SEGMENT_QUANTITY 2
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

    int color, colorMode, brightness, lightLimit, nightLightLimit;

    int nightTimeRange[4];
    bool firstTime;
};

extern configs globalConfig;

extern int digits[10][7];
extern int invertedDigits[10][7];

void initServer();
void initializeEEPROM();
void loadConfig();
void saveConfig();

#endif