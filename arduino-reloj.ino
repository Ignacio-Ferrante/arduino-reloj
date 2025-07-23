#include "constants.h"

unsigned long lastRefresh;

void setup() {
  initializeClock();
  lastRefresh = millis();
}

void loop() {
  if (millis() - lastRefresh >= globalConfig.refreshVelocity) {
    updateTime();
    globalConfig.timerMode == CLOCK ? showTime(hours, minutes) : timerManagment();
    lastRefresh = millis();
  }

  server.handleClient();
  ElegantOTA.loop();
  MDNS.update();
}