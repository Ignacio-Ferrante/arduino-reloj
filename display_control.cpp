#include "constants.h"

bool nightTime;
int brightness;

void printLed(int position) {
  if (nightTime)
    leds[position] = CHSV(1, 255, brightness);
  else
    leds[position] = CHSV(globalConfig.color, 255, brightness);
}

void updateBrightness() {
  int ligthRead = analogRead(LIGHT_SENSOR_PIN);
  int mappedBright = map(ligthRead, 0, 1024, 1, 255);

  if (nightTime)
    brightness = mappedBright;
  else {
    brightness = max(mappedBright, globalConfig.brightness);
    brightness = min(255, (brightness * 3) / 2);
  }
}

bool isNightTime() {
  return (hours < globalConfig.nightTimeRange[2] || (hours == globalConfig.nightTimeRange[2] && minutes < globalConfig.nightTimeRange[3]))
    || (hours > globalConfig.nightTimeRange[0] || (hours == globalConfig.nightTimeRange[0] && minutes >= globalConfig.nightTimeRange[1]));
}

int nextColor = globalConfig.color;

void showTime(int hour, int minutes) {
  nightTime = isNightTime();
  updateBrightness();

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

void printAllSegments(int color, int bright) {
  for (int i = 0; i < LED_COUNT; i++)
    leds[i] = CHSV(color, 255, bright);
}

void turnOffAllDigits() {
  FastLED.clear();
  FastLED.show();
}