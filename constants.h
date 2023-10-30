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

#define Q_LED_DIGIT 2
#define LED_COUNT 60
#define LED_PIN 16  //D0
#define POTENTIOMETER_PIN 6
#define LIGHT_SENSOR_PIN A0

extern String ssid;
extern String password;

extern ESP8266WebServer server;
extern WiFiUDP ntpUDP;
extern NTPClient timeClient;
extern CRGB leds[LED_COUNT];

extern int color;
extern int brightness;
extern int lightLimit;
extern int idleLight;
extern int lowLightMin;
extern int lowLightMax;
extern int useInvertedDigits;

extern int digits[10][7];
extern int invertedDigits[10][7];

void initServer();

#endif