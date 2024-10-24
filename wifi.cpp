#include "constants.h"

void reconectWifi() {
  server.send(200, "text/plain", "Conectando al WiFi -> " + globalConfig.ssid + " : " + globalConfig.password);
  
  WiFi.begin(globalConfig.ssid, globalConfig.password);

  int count = 0;

  for (int i = 0; i < 30; i++) {
    if (WiFi.status() == WL_CONNECTED)
      break;
    else {
      if (count % 3 != 0)
        printAllSegments(50, 255);
      else
        turnOffAllSegments();

      delay(300);
    }
  }

  forceUpdateTime();
}