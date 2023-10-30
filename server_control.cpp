#include "constants.h"

void handleRoot() {
  LittleFS.begin();

  File file = LittleFS.open("/server_page.html", "r");
  
  if (file) {
    size_t fileSize = file.size();
    String html = "";

    while (file.available()) {
      html += file.readString();
    }

    file.close();
    
    // Reemplaza las variables en el archivo HTML con los valores actuales
    html.replace("{{color}}", String(color));
    html.replace("{{lightLimit}}", String(lightLimit));
    html.replace("{{idleLight}}", String(idleLight));
    html.replace("{{lowLightMin}}", String(lowLightMin));
    html.replace("{{lowLightMax}}", String(lowLightMax));
    html.replace("{{useInvertedDigits}}", String(useInvertedDigits));

    server.send(200, "text/html", html);
  } else {
    server.send(404, "text/plain", "Archivo HTML no encontrado");
  }
}

void handleSetColor() {
  color = server.arg("color").toInt();
}

void handleLightLimit() {
  lightLimit = server.arg("lightLimit").toInt();
}

void handleIdleLight() {
  idleLight = server.arg("idleLight").toInt();
}

void handleLowLightMin() {
  lowLightMin = server.arg("lowLightMin").toInt();
}

void handleLowLightMax() {
  lowLightMax = server.arg("lowLightMax").toInt();
}

void handleUseInvertedDigits() {
  useInvertedDigits = server.arg("useInvertedDigits").toInt();
}

void initServer() {
  server.on("/", handleRoot);
  server.on("/color", handleSetColor);
  server.on("/lightlimit", handleLightLimit);
  server.on("/idlelight", handleIdleLight);
  server.on("/lowlightmin", handleLowLightMin);
  server.on("/lowlightmax", handleLowLightMax);
  server.on("/inverteddigits", handleUseInvertedDigits);
  server.begin();
  Serial.println("Servidor iniciado");
}