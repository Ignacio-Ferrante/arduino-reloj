#include "constants.h"
#include "server_control.h"

void setup() {
  Serial.begin(115200);
  EEPROM.begin(512);

  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, LED_COUNT);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 1000);
  FastLED.clear();
  FastLED.show();

  WiFi.begin(ssid, password);

  int cont = 0;
  while (WiFi.status() != WL_CONNECTED) {
    if (cont % 2 == 0) {
      for (int i = 0; i < LED_COUNT; i++)
        leds[i] = CHSV(0, 255, 125);
    } else
      FastLED.clear();

    cont++;
    FastLED.show();
    delay(500);
  }
  Serial.println("  Conectado!");

  timeClient.begin();
  pinMode(LIGHT_SENSOR_PIN, INPUT);

  initServer();
}

void loop() {
  server.handleClient();
  // Obtiene la hora y los minutos
  timeClient.update();

  updateBrightness();
  showTime(timeClient.getHours(), timeClient.getMinutes());

  delay(250);
}

void updateBrightness() {
  int ligthRead = analogRead(LIGHT_SENSOR_PIN);
  int porcentaje = map(ligthRead, 0, 1024, 0, 100);

  if (porcentaje >= lightLimit)
    brightness = 255;
  else if (porcentaje >= idleLight)
    brightness = map(ligthRead, idleLight * 10, lightLimit * 10, 150, 254);
  else
    brightness = map(ligthRead, 0, idleLight * 10, lowLightMin, lowLightMax);

  Serial.println("Ligth read: " + String(ligthRead) + " - porcentaje: " + String(porcentaje) + " - brillo: " + String(brightness));
}

void showTime(int hour, int minutes) {
  Serial.println(String(hour) + " : " + String(minutes));
  FastLED.clear();

  int time[4] = { hour / 10, hour % 10, minutes / 10, minutes % 10 };

  for (int i = 0; i < 4; i++) {
    useInvertedDigits ? showDigit(i, time[3 - i]) : showDigit(i, time[i]);
  }

  for (int i = 0; i < 2 * Q_LED_DIGIT; i++) {  //colorea los puntos
    leds[14 * Q_LED_DIGIT + i] = CHSV(color, 255, brightness);
  }

  FastLED.show();
  delay(10);
  FastLED.show();  //disminuye el problema de la interrupcion por usar wifi
}

void showDigit(int position, int value) {
  int offset = position * 7 * Q_LED_DIGIT + ((position / 2) * 2 * Q_LED_DIGIT);

  for (int i = 0; i < 7 * Q_LED_DIGIT; i++) {
    int num = digits[value][i / Q_LED_DIGIT];
    int inNum = invertedDigits[value][i / Q_LED_DIGIT];
    if ((useInvertedDigits == 0 && num == 1) || (useInvertedDigits == 1 && inNum == 1)) {
      leds[i + offset] = brightness < 255
                           ? CHSV(color, 255, brightness)
                           : leds[i + offset] = CRGB::Green;
    } else {
      leds[i + offset] = CHSV(0, 0, 0);
    }
  }
}