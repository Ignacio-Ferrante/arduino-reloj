#include "constants.h"

void setup() {
  initializeEEPROM();

  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, LED_COUNT);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 1000);
  FastLED.clear();
  FastLED.show();

  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP("reloj");

  if(globalConfig.ssid != "") {
    WiFi.begin(globalConfig.ssid, globalConfig.password);
  }

  timeClient.begin();
  pinMode(LIGHT_SENSOR_PIN, INPUT);

  initServer();
}

bool nightTime;
int cont = 0;

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    if (cont % 20 < 10) {
      for (int i = 0; i < LED_COUNT; i++)
        leds[i] = CHSV(globalConfig.color, 255, 150);
    } else
      FastLED.clear();

    cont++;
    FastLED.show();
  } else {
    cont = 0;
    server.handleClient();
    timeClient.update();
    nightTime = isNightTime();

    updateBrightness();
    showTime(timeClient.getHours(), timeClient.getMinutes());
  }
  delay(globalConfig.refreshVelocity);
}

int brightness;

void updateBrightness() {
  int ligthRead = analogRead(LIGHT_SENSOR_PIN);
  int porcentaje = map(ligthRead, 0, 1024, 0, 100);

  if (porcentaje > globalConfig.lightLimit)
    brightness = 255;
  else if (nightTime) {
    brightness = porcentaje >= globalConfig.nightLightLimit ? map(ligthRead, 0, 1024, globalConfig.nightLightLimit, 254) : 1;
  } else {
    int mappedBright = map(globalConfig.brightness, 1, 254, 1, 100);
    brightness = porcentaje > mappedBright ? map(porcentaje, 1, 100, 1, 254) : globalConfig.brightness;
  }
}

bool isNightTime() {
  int hour = timeClient.getHours(), minutes = timeClient.getMinutes();

  return (hour < globalConfig.nightTimeRange[2] || (hour == globalConfig.nightTimeRange[2] && minutes < globalConfig.nightTimeRange[3]))
    || (hour > globalConfig.nightTimeRange[0] || (hour == globalConfig.nightTimeRange[0] && minutes >= globalConfig.nightTimeRange[1]));
}

int nextColor = globalConfig.color;

void showTime(int hour, int minutes) {
  FastLED.clear();

  int time[4] = { hour / 10, hour % 10, minutes / 10, minutes % 10 };

  if (globalConfig.colorMode != 0 && !nightTime) {
    nextColor++;
    if (nextColor > 255)
      nextColor = 0;
    globalConfig.color = nextColor;
  }

  for (int i = 0; i < 4; i++) {
    globalConfig.useInvertedDigits ? showDigit(i, time[3 - i]) : showDigit(i, time[i]);

    if (globalConfig.colorMode == 2 && !nightTime)
      globalConfig.color = (globalConfig.color + 10) % 255;

    if (i == 1) {
      for (int i = 0; i < 2 * LED_SEGMENT_QUANTITY; i++)
        printLed(14 * LED_SEGMENT_QUANTITY + i);

      if (globalConfig.colorMode == 2 && !nightTime)
        globalConfig.color = (globalConfig.color + 10) % 255;
    }
  }

  FastLED.show();
  delay(10);
  FastLED.show(); // disminuye el problema de la interrupcion por usar wifi
}

void showDigit(int position, int value) {
  int offset = position * 7 * LED_SEGMENT_QUANTITY + ((position / 2) * 2 * LED_SEGMENT_QUANTITY);

  for (int i = 0; i < 7 * LED_SEGMENT_QUANTITY; i++) {
    int num = digits[value][i / LED_SEGMENT_QUANTITY];
    int inNum = invertedDigits[value][i / LED_SEGMENT_QUANTITY];

    if ((globalConfig.useInvertedDigits == 0 && num == 1) || (globalConfig.useInvertedDigits == 1 && inNum == 1))
      printLed(i + offset);
    else
      leds[i + offset] = CHSV(0, 0, 0);
  }
}

void printLed(int position) {
  if (brightness == 255)
    leds[position] = CRGB::Green;
  else if (nightTime)
    leds[position] = CHSV(17, 255, brightness);
  else
    leds[position] = CHSV(globalConfig.color, 255, brightness);
}