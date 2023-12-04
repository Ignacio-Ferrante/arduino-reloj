#include "constants.h"

void handleRoot() {
  LittleFS.begin();

  File file = LittleFS.open("/server_page.html", "r");

  if (file) {
    server.streamFile(file, "text/html");
  }
  else {
    server.send(404, "text/plain", "Archivo HTML no encontrado");
  }

  file.close();
}

void getConfigs() {
  DynamicJsonDocument jsonObject(JSON_OBJECT_SIZE(12));
  jsonObject["refreshVelocity"] = globalConfig.refreshVelocity;
  jsonObject["useInvertedDigits"] = globalConfig.useInvertedDigits;
  jsonObject["color"] = globalConfig.color;
  jsonObject["colorMode"] = globalConfig.colorMode;
  jsonObject["brightness"] = map(globalConfig.brightness, 1, 255, 1, 100);
  jsonObject["lightLimit"] = globalConfig.lightLimit;
  jsonObject["nightLightLimit"] = globalConfig.nightLightLimit;
  jsonObject["nightTimeRange"][0] = globalConfig.nightTimeRange[0];
  jsonObject["nightTimeRange"][1] = globalConfig.nightTimeRange[1];
  jsonObject["nightTimeRange"][2] = globalConfig.nightTimeRange[2];
  jsonObject["nightTimeRange"][3] = globalConfig.nightTimeRange[3];

  String jsonStr;
  serializeJson(jsonObject, jsonStr);

  server.send(200, "application/json", jsonStr);
}

void setWifi() {
  globalConfig.ssid = server.arg("ssid");
  globalConfig.password = server.arg("password");

  WiFi.begin(globalConfig.ssid, globalConfig.password);
  saveConfig();
}

void setVelocity() {
  globalConfig.refreshVelocity = map(server.arg("velocity").toInt(), 1, 100, 100, 1);
  saveConfig();
}

void setUseInvertedDigits() {
  globalConfig.useInvertedDigits = server.arg("useInvertedDigits").toInt();
  saveConfig();
}

void setColor() {
  globalConfig.color = server.arg("color").toInt();
  saveConfig();
}

void setColorMode() {
  globalConfig.colorMode = server.arg("mode").toInt();
  saveConfig();
}

void setBrightness() {
  globalConfig.brightness = map(server.arg("brightness").toInt(), 1, 100, 1, 254);
}

void setLightLimit() {
  globalConfig.lightLimit = server.arg("lightLimit").toInt();
  saveConfig();
}

void setNightLightLimit() {
  globalConfig.nightLightLimit = server.arg("lightLimit").toInt();
  saveConfig();
}

void setNightTimeRange() {
  for (int i = 0; i < 4; i++)
    globalConfig.nightTimeRange[i] = server.arg(String(i)).toInt();
  saveConfig();
}

void getbrightness() {
  DynamicJsonDocument jsonObject(JSON_OBJECT_SIZE(2));
  jsonObject["brightness"] = map(analogRead(LIGHT_SENSOR_PIN), 0, 1024, 0, 100);

  String jsonStr;
  serializeJson(jsonObject, jsonStr);

  server.send(200, "application/json", jsonStr);
}

void initServer() {
  server.on("/", handleRoot);
  server.on("/config", getConfigs);
  server.on("/wifi", setWifi);
  server.on("/velocity", setVelocity);
  server.on("/inverteddigits", setUseInvertedDigits);
  server.on("/color", setColor);
  server.on("/colormode", setColorMode);
  server.on("/brightness", setBrightness);
  server.on("/lightlimit", setLightLimit);
  server.on("/nightlightlimit", setNightLightLimit);
  server.on("/nighttime", setNightTimeRange);
  server.on("/getbrightness", getbrightness);
  server.begin();
}