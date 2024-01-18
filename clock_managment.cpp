#include "constants.h"

unsigned long lastSync;

bool shouldUpdate() {
  return millis() - lastSync > 10 * 60 * 1000; //10m
}

void updateTime() {
  hours = hour();
  minutes = minute();

  if (WiFi.status() == WL_CONNECTED && shouldUpdate()) {
    lastSync = millis();
    timeClient.update();
    hours = timeClient.getHours();
    minutes = timeClient.getMinutes();
    setTime(hours, minutes, 0, 1, 1, 2024);
  }
}