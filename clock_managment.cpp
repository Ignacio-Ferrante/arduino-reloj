#include "constants.h"

void updateTime() {
  if (WiFi.status() == WL_CONNECTED) {
    timeClient.update();
    hours = timeClient.getHours();
    minutes = timeClient.getMinutes();
  } else {
    hours = hour();
    minutes = minute();
  }
}