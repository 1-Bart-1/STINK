#include "SerialToHttp.h"

SerialToHttp* SerialToHttp::_instance = nullptr;
void (*SerialToHttp::_userCallback)(JsonDocument* receivedData) = nullptr;

SerialToHttp::SerialToHttp(const char* ssid, const char* password, const char* url) {
    _ssid = ssid;
    _password = password;
    _url = url;
    _instance = this;
}

void SerialToHttp::begin() {
    WiFi.begin(_ssid, _password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");
    Serial1.begin(115200);
}

void SerialToHttp::handleSerialData() {
    if (Serial1.available()) {
        String jsonString = Serial1.readStringUntil('\n');
        sendJsonOverHttp(jsonString);
    }
}

void SerialToHttp::sendJsonOverHttp(const String& jsonString) {
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        http.begin(_url); // Specify the URL
        http.addHeader("Content-Type", "application/json");

        // Send the POST request
        int httpResponseCode = http.POST(jsonString);

        // Check the returning code
        if (httpResponseCode > 0) {
            // Get the response body
            String response = http.getString();
            Serial.println("HTTP Response code: " + String(httpResponseCode));
            Serial.println("Response: " + response);
        } else {
            Serial.println("Error on sending POST: " + String(httpResponseCode));
        }

        // Close the connection
        http.end();
    } else {
        Serial.println("WiFi not connected");
    }
}
