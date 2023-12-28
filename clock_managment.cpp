#include "constants.h"

void clockManagment() {
  if (WiFi.status() == WL_CONNECTED) {
    timeClient.update();
    showTime(timeClient.getHours(), timeClient.getMinutes());
  }
  else {
    showTime(0, 0);
  }
}