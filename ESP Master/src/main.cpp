#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "MotstandenWifi";
const char* pass = "12345687";
const String url = "http://motstanden.no/api/instrument-stats/new";

void setup() {
  Serial.begin(115200);
  // Serial1 har Rx pin 9 og Tx pin 10
  Serial1.begin(115200);
  
  HTTPClient http;
  WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.println("Connecting to WiFi...");
    }
  Serial.println("Connected to WiFi");
}

void loop() {
  if (Serial1.available()) {
    StaticJsonDocument<2> recivedData;
    DeserializationError error = deserializeJson(recivedData, Serial1);

    if (error) {
      Serial.println("JSON parsing error");
    } else {
      http.addHeader("Content-Type", "application/json");
      int httpCode = http.POST(recivedData);
      if (httpCode > 0) {
        Serial.printf("[HTTP] POST... code: %d\n", httpCode);
        http.end();
      } else {
        Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }
    }
  }
}
