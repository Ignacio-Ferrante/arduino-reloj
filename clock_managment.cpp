#include "constants.h"

void updateTime() {
  if (WiFi.status() == WL_CONNECTED) {
    timeClient.update();
    hours = timeClient.getHours();
    minutes = timeClient.getMinutes();
    setTime(hours, minutes, 0, 1, 1, 2024);
  } else {
    hours = hour();
    minutes = minute();
  }
}