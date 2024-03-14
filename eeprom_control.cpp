#include "constants.h"

void saveConfig() {
  EEPROM.begin(sizeof(globalConfig));
  EEPROM.put(0, globalConfig);
  EEPROM.commit();
  EEPROM.end();
}

void wipeEEPROM() {
  EEPROM.begin(sizeof(globalConfig)*3);

  for (int i = 0; i < EEPROM.length(); i++) {
    EEPROM.write(i, 0);
  }
  EEPROM.commit();
  EEPROM.end();
}

bool isEEPROMEmpty() {
  bool isEmpty = true;

  for (int i = 0; i < EEPROM.length(); i++) {
    if (EEPROM.read(i) != 0 && EEPROM.read(i) != 255) {
      isEmpty = false;
      break;
    }
  }

  return isEmpty;
}

void initializeEEPROM() {
  EEPROM.begin(2 * sizeof(defaultConfig));

  if (isEEPROMEmpty()) {
    EEPROM.put(0, defaultConfig);
    EEPROM.commit();
    globalConfig = defaultConfig;
  } else {
    EEPROM.get(0, globalConfig);
  }

  EEPROM.end();
}