#include "constants.h"

void saveConfig() {
  EEPROM.begin(sizeof(globalConfig));
  EEPROM.put(0, globalConfig);
  EEPROM.commit();
  EEPROM.end();
}

void loadConfig() {
  EEPROM.begin(sizeof(globalConfig));
  EEPROM.get(0, globalConfig);
  EEPROM.end();
}

void wipeEEPROM() {
  for (int i = 0; i < EEPROM.length(); i++) {
    EEPROM.write(i, 0);
  }
  EEPROM.commit();
}

bool isEEPROMEmpty() {
  bool isEmpty = true;

  for (int i = 1; i < EEPROM.length(); i++) {
    if (EEPROM.read(i) != 0 && EEPROM.read(i) != 255) {
      isEmpty = false;
      break;
    }
  }

  return isEmpty;
}

void initializeEEPROM() {
  EEPROM.begin(sizeof(globalConfig)+1);

  if (EEPROM.read(0) != 17 && isEEPROMEmpty()) {
    EEPROM.write(0, 17);
    EEPROM.put(1, globalConfig);
    EEPROM.commit();
  }
  else {
    EEPROM.get(1, globalConfig);
  }

  EEPROM.end();
}