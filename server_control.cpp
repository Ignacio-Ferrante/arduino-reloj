#include "core_esp8266_features.h"
#include "constants.h"

void handleRoot() {
  File file = LittleFS.open("/server_page.html", "r");

  if (file) {
    server.streamFile(file, "text/html");
  } else {
    server.send(404, "text/plain", "Archivo HTML no encontrado");
  }

  file.close();
}

void getConfigs() {
  server.send(200, "application/json", getStringJsonConfigs(globalConfig, false, true));
}

void setWifi() {
  globalConfig.ssid = server.arg("ssid");
  globalConfig.password = server.arg("password");
  saveConfig();

  reconectWifi();
}

void resetWifi() {
  blink(RESET_WIFI_COLOR, 1);

  reconectWifi();
}

void setVelocity() {
  globalConfig.refreshVelocity = map(server.arg("velocity").toInt(), 1, 100, 100, 1);
  saveConfig();
  server.send(200);
}

void setUseInvertedDigits() {
  globalConfig.useInvertedDigits = server.arg("useInvertedDigits").toInt();
  saveConfig();
  server.send(200);
}

void setColor() {
  globalConfig.color = server.arg("color").toInt();
  saveConfig();
  server.send(200);
}

void setColorMode() {
  globalConfig.colorMode = server.arg("mode").toInt();
  saveConfig();
  server.send(200);
}

void setBrightness() {
  globalConfig.brightness = map(server.arg("brightness").toInt(), 1, 100, 50, 255);
  server.send(200);
}

void setAutoBrightness() {
  globalConfig.autoBrightness = server.arg("status").toInt() == 0 ? false : true;
  saveConfig();
  server.send(200);
}

void setNightTimeEnabled() {
  globalConfig.nightTimeEnabled = server.arg("status").toInt() == 0 ? false : true;
  saveConfig();
  server.send(200);
}

void setNightTimeRange() {
  for (int i = 0; i < 4; i++)
    globalConfig.nightTimeRange[i] = server.arg(String(i)).toInt();
  saveConfig();
  server.send(200);
}

void getbrightness() {
  DynamicJsonDocument jsonObject(4096);
  jsonObject["brightness"] = map(analogRead(LIGHT_SENSOR_PIN), 0, 1024, 0, 100);

  String jsonStr;
  serializeJson(jsonObject, jsonStr);

  server.send(200, "application/json", jsonStr);
}

void syncTime() {
  hours = server.arg("hour").toInt();
  minutes = server.arg("min").toInt();
  setTime(hours, minutes, 0, 1, 1, 2024);
  server.send(200);
}

void setTimerMode() {
  globalConfig.timerMode = server.arg("mode").toInt();
  saveConfig();
  stopTimer();
  server.send(200);
}

void setStartTimer() {
  startTimer();
  server.send(200);
}

void setPauseTimer() {
  pauseTimer();
  server.send(200);
}

void setStopTimer() {
  stopTimer();
  server.send(200);
}

void setCountDown() {
  globalConfig.countdownMinutes = server.arg("min").toInt();
  globalConfig.countdownSeconds = server.arg("sec").toInt();
  saveConfig();
  server.send(200);
}

void soundTimbre() {
  server.send(200, "text/plain", "Sonando");
  sound();
}

void resetDefault() {
  blink(RESET_DEFAULT_COLOR, 2);
  reconectWifi();
  resetDefaultConfig();
}

void initServer() {
  server.on("/", handleRoot);

  server.on("/config", getConfigs);
  server.on("/wifi", setWifi);
  server.on("/resetwifi", resetWifi);
  server.on("/velocity", setVelocity);
  server.on("/inverteddigits", setUseInvertedDigits);
  server.on("/color", setColor);
  server.on("/colormode", setColorMode);
  server.on("/brightness", setBrightness);
  server.on("/nighttimeenabled", setNightTimeEnabled);
  server.on("/nighttime", setNightTimeRange);
  server.on("/getbrightness", getbrightness);
  server.on("/autobrightness", setAutoBrightness);
  server.on("/settime", syncTime);
  server.on("/timermode", setTimerMode);
  server.on("/starttimer", setStartTimer);
  server.on("/pausetimer", setPauseTimer);
  server.on("/stoptimer", setStopTimer);
  server.on("/setcountdown", setCountDown);
  server.on("/timbre", soundTimbre);

  server.on("/resetdefault", resetDefault);

  server.begin();
}