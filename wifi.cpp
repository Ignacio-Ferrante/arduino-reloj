#include "constants.h"

void reconectWifi() {
  server.send(200, "text/plain", "Conectando al WiFi -> " + globalConfig.ssid + " : " + globalConfig.password);
  
  WiFi.begin(globalConfig.ssid, globalConfig.password);

  for (int i = 1; i < 100; i++) {
    if (WiFi.status() == WL_CONNECTED) {
      forceUpdateTime();
      break;
    } else {
      if (i % 3 != 0)
        printAllSegments(RECONECT_WIFI_COLOR, 255);
      else
        turnOffAllSegments();

      delay(300);
    }
  }
}