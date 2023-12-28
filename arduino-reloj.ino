#include "constants.h"

unsigned long lastRefresh;

void setup() {
  initializeClock();
  lastRefresh = millis();
}

void loop() {
  if (millis() - lastRefresh >= globalConfig.refreshVelocity) {
    globalConfig.timerMode == CLOCK ? clockManagment() : timerManagment();
    lastRefresh = millis();
  }

  server.handleClient();
  ElegantOTA.loop();
}