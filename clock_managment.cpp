#include "constants.h"

void clockManagment() {
  if (WiFi.status() == WL_CONNECTED) {
    showTime(0, 0);
  }
  else {
    timeClient.update();
    showTime(timeClient.getHours(), timeClient.getMinutes());
  }
}