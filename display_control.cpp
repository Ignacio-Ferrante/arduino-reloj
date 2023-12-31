#include "constants.h"

bool nightTime;
int brightness, baseColor, variableColor;

int getBrightness() {
  int ligthRead = analogRead(LIGHT_SENSOR_PIN);
  int mappedBright = map(ligthRead, 0, 1024, 1, 255);

  if (nightTime)
    return mappedBright;
  else {
    mappedBright = max(mappedBright, globalConfig.brightness);
    return min(255, (mappedBright * 3) / 2);
  }
}

bool isNightTime() {
  return (hours < globalConfig.nightTimeRange[2] || (hours == globalConfig.nightTimeRange[2] && minutes < globalConfig.nightTimeRange[3]))
    || (hours > globalConfig.nightTimeRange[0] || (hours == globalConfig.nightTimeRange[0] && minutes >= globalConfig.nightTimeRange[1]));
}

void updateVariableColor() {
  if (globalConfig.colorMode == FLOW)
    variableColor = (variableColor + 10) % 255;
}

void printLed(int position, int color) {
  if (nightTime)
    leds[position] = CHSV(1, 255, brightness);
  else if (globalConfig.colorMode == STATIC)
    leds[position] = CHSV(globalConfig.color, 255, brightness);
  else
    leds[position] = CHSV(color, 255, brightness);
}

int calculateDigitOffset(int position) {
  return position * 7 * SEGMENT_LED_QUANTITY + ((position / 2) * 2 * DOT_LED_QUANTITY);
}

void showDigit(int position, int digitMap[7], int color) {
  int offset = calculateDigitOffset(position);

  for (int i = 0; i < 7 * SEGMENT_LED_QUANTITY; i++) {
    if (digitMap[i / SEGMENT_LED_QUANTITY])
      printLed(i + offset, color);
    else
      leds[i + offset] = CHSV(0, 0, 0);
  }

  updateVariableColor();
}

void showDot() {
  for (int i = 0; i < 2 * DOT_LED_QUANTITY; i++)
    printLed(14 * SEGMENT_LED_QUANTITY + i, variableColor);

  updateVariableColor();
}

void showTime(int digit[4]) {
  nightTime = isNightTime();
  brightness = getBrightness();
  FastLED.clear();

  baseColor = (baseColor + 1) % 255;
  variableColor = baseColor;

  for (int i = 0; i < 4; i++) {
    globalConfig.useInvertedDigits
      ? showDigit(i, invertedSegmentMap[digit[3 - i]], variableColor)
      : showDigit(i, segmentMap[digit[i]], variableColor);

    if (i == 1)
      showDot();
  }

  FastLED.show();
  delayMicroseconds(10000);
  FastLED.show(); // disminuye el problema de la interrupcion por usar wifi
}

void showTime(int hour, int minutes) {
  int digit[4] = { hour / 10, hour % 10, minutes / 10, minutes % 10 };
  showTime(digit);
}

void showNumer(int number) {
  int digit[4];

  for (int i = 3; i > 0; i--) {
    digit[i] = number % 10;
    number /= 10;
  }

  showTime(digit);
}

void printAllSegments(int color, int bright) {
  for (int i = 0; i < LED_COUNT; i++)
    leds[i] = CHSV(color, 255, bright);
}

void turnOffAllSegments() {
  FastLED.clear();
  FastLED.show();
}