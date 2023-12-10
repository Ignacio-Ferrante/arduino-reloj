#include "constants.h"

void setup() {
  initializeEEPROM();

  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, LED_COUNT);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 1000);
  FastLED.clear();
  FastLED.show();

  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP("reloj");

  if (globalConfig.ssid != "") {
    WiFi.begin(globalConfig.ssid, globalConfig.password);
  }

  ElegantOTA.begin(&server);
  timeClient.begin();
  pinMode(LIGHT_SENSOR_PIN, INPUT);

  resetCountDown();
  resetCrono();

  initServer();
}

int cont = 0;

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    if (cont % 20 < 10)
      printAllSegments(globalConfig.color, 150);
    else
      FastLED.clear();

    cont++;
    FastLED.show();
  } else {
    cont = 0;

    nightTime = isNightTime();
    updateBrightness();

    if (globalConfig.timeMode != 0) {
      manageTimer();
    } else {
      timeClient.update();
      showTime(timeClient.getHours(), timeClient.getMinutes());
    }
  }

  server.handleClient();
  ElegantOTA.loop();
  delay(globalConfig.refreshVelocity);
}

void updateBrightness() {
  int ligthRead = analogRead(LIGHT_SENSOR_PIN);
  int mappedBright = map(ligthRead, 0, 1024, 1, 255);

  if (nightTime)
    brightness = mappedBright;
  else {
    brightness = mappedBright > globalConfig.brightness ? mappedBright : globalConfig.brightness;
    brightness = min(255, (brightness * 3) / 2);
  }
}

bool isNightTime() {
  int hour = timeClient.getHours(), minutes = timeClient.getMinutes();

  return (hour < globalConfig.nightTimeRange[2] || (hour == globalConfig.nightTimeRange[2] && minutes < globalConfig.nightTimeRange[3]))
    || (hour > globalConfig.nightTimeRange[0] || (hour == globalConfig.nightTimeRange[0] && minutes >= globalConfig.nightTimeRange[1]));
}

void manageTimer() {
  if (isRunning) {
    unsigned long currentTime = millis() - startTime;
    int minutes = currentTime / 60000;
    int seconds = (currentTime / 1000) % 60;

    if (globalConfig.timeMode == 1) {
      cronoMinutes = minutes;
      cronoSeconds = seconds;
      showTime(minutes, seconds);
    } else {
      countdownMinutes = max(0, countdownMinutes - minutes);
      countdownSeconds = max(0, countdownSeconds - seconds);
      showTime(countdownMinutes, countdownSeconds);

      if(countdownMinutes == 0 && countdownSeconds == 0) {
        resetCountDown();
        isRunning = false;
      }
    }

  } else {
    if (contTimer % 20 < 10) {
      if (globalConfig.timeMode == 1)
        showTime(cronoMinutes, cronoSeconds);
      else
        showTime(countdownMinutes, countdownSeconds);
    } else
      FastLED.clear();
  }
  contTimer++;
}

void resetCountDown() {
  countdownMinutes = globalConfig.countdownMinutes;
  countdownSeconds = globalConfig.countdownSeconds;
}

void resetCrono() {
  cronoMinutes = 0;
  cronoSeconds = 0;
}