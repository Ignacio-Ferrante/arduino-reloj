#include "constants.h"

unsigned long lastSync;
bool isUpdated = false;

bool shouldUpdate() {
  return !isUpdated || millis() - lastSync > 10 * 60 * 1000; //10m
}

void updateTime() {
  hours = hour();
  minutes = minute();

  if (WiFi.status() == WL_CONNECTED && shouldUpdate()) {
    lastSync = millis();
    timeClient.update();
    hours = timeClient.getHours();
    minutes = timeClient.getMinutes();
    setTime(hours, minutes, timeClient.getSeconds(), 1, 1, 2024);
    isUpdated = true;
  }
}

void forceUpdateTime() {
  isUpdated = false;
}