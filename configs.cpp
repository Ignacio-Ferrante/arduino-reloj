#include "constants.h"

String configFilePath = "/config.json";

String getStringJsonConfigs(configs config, bool showWifiData, bool transformForServer) {
  String jsonStr;
  DynamicJsonDocument object = getJsonConfigs(config, showWifiData, transformForServer);
  serializeJson(object, jsonStr);
  return jsonStr;
}

DynamicJsonDocument getJsonConfigs(configs config, bool showWifiData, bool transformForServer) {
  DynamicJsonDocument jsonObject(4096);
  if (showWifiData) {
    jsonObject["ssid"] = config.ssid;
    jsonObject["password"] = config.password;
  }

  if (transformForServer) {
    jsonObject["refreshVelocity"] = map(config.refreshVelocity, 1, 100, 100, 1);
    jsonObject["brightness"] = map(config.brightness, 50, 255, 1, 100);
  } else {
    jsonObject["refreshVelocity"] = config.refreshVelocity;
    jsonObject["brightness"] = config.brightness;
  }

  jsonObject["useInvertedDigits"] = config.useInvertedDigits;
  jsonObject["color"] = config.color;
  jsonObject["colorMode"] = config.colorMode;
  jsonObject["autoBrightness"] = config.autoBrightness;
  jsonObject["nightTimeEnabled"] = config.nightTimeEnabled;
  jsonObject["nightTimeRange"][0] = config.nightTimeRange[0];
  jsonObject["nightTimeRange"][1] = config.nightTimeRange[1];
  jsonObject["nightTimeRange"][2] = config.nightTimeRange[2];
  jsonObject["nightTimeRange"][3] = config.nightTimeRange[3];
  jsonObject["timerMode"] = config.timerMode;
  jsonObject["isTimerActive"] = isTimerActive();
  jsonObject["countdownMinutes"] = config.countdownMinutes;
  jsonObject["countdownSeconds"] = config.countdownSeconds;

  // otra opcion para el nightTimeRange Crear un array para la variable nightTimeRange
  //JsonArray nightTimeRange = doc.createNestedArray("nightTimeRange");
  //for (int i = 0; i < 4; i++) {
  //  nightTimeRange.add(configs.nightTimeRange[i]);
  //}

  //jsonObject["nightTimeRange"] = nightTimeRange;

  return jsonObject;
}

void saveSpecificConfig(configs configs) {
  File file = LittleFS.open(configFilePath, "w");
  if (!file) {
    blink(ERROR_CONFIG_COLOR, 2);
    Serial.println("Error al abrir el archivo para escribir");
    return;
  }

  DynamicJsonDocument object = getJsonConfigs(configs, true, false);
  serializeJson(object, file);
  file.close();
  Serial.println("Configuración guardada en " + configFilePath);
}

void saveConfig() {
  saveSpecificConfig(globalConfig);
}

void resetDefaultConfig() {
  globalConfig = defaultConfig;
  saveSpecificConfig(defaultConfig);
}

void initializeFileSystem() {
  Serial.println("Inicializando File System");
  if (!LittleFS.begin()) {
    Serial.println("Error inicializando LittleFS");
    blink(ERROR_CONFIG_COLOR, 6);
    return;
  }

  if (!LittleFS.exists(configFilePath)) {
    blink(CREATE_CONFIG_COLOR, 1);
    Serial.println("Archivo " + configFilePath + " no encontrado. Cargando default.");
    saveSpecificConfig(defaultConfig);
    globalConfig = defaultConfig;
  } else {
    loadConfig();
  }
}

void loadConfig() {
  // Abre el archivo en modo lectura
  File file = LittleFS.open(configFilePath, "r");
  if (!file) {
    Serial.println("Error al abrir el archivo para leer");
    blink(ERROR_CONFIG_COLOR, 2);
    return;
  }

  // Carga el JSON desde el archivo
  DynamicJsonDocument doc(4096);

  if (deserializeJson(doc, file)) {
    Serial.println("Error al deserializar el JSON");
    blink(ERROR_CONFIG_COLOR, 2);
    file.close();
    return;
  }

  String jsonString;
  serializeJson(doc, jsonString);
  Serial.println("Json leido: " + jsonString);

  // Restaura los valores del JSON en el struct
  globalConfig.ssid = doc["ssid"].as<String>();
  globalConfig.password = doc["password"].as<String>();
  globalConfig.refreshVelocity = doc["refreshVelocity"];
  globalConfig.useInvertedDigits = doc["useInvertedDigits"];
  globalConfig.color = doc["color"];
  globalConfig.colorMode = doc["colorMode"];
  globalConfig.brightness = doc["brightness"];
  globalConfig.autoBrightness = doc["autoBrightness"];
  globalConfig.nightTimeEnabled = doc["nightTimeEnabled"];

  JsonArray nightTimeRange = doc["nightTimeRange"].as<JsonArray>();
  for (int i = 0; i < 4; i++) {
    globalConfig.nightTimeRange[i] = nightTimeRange[i];
  }

  globalConfig.timerMode = doc["timerMode"];
  globalConfig.countdownMinutes = doc["countdownMinutes"];
  globalConfig.countdownSeconds = doc["countdownSeconds"];

  file.close();
  Serial.println("Configuración cargada desde " + configFilePath);
  Serial.println("Json cargado: " + getStringJsonConfigs(globalConfig, true, false));
}

void updateServerPage(String newPageString) {
  File pageFile = LittleFS.open("/server_page.html", "w");
  if (pageFile) {
    pageFile.print(newPageString);
    pageFile.close();
    Serial.println("server_page guardado correctamente.");
  } else {
    Serial.println("Error al guardar server_page.");
  }
}
