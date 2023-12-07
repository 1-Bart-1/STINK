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
    Serial2.begin(115200);
}

void SerialToHttp::handleSerialData() {
    while (Serial2.available()) {
        char nextChar = Serial2.read();
        if(nextChar != '\n') {
            Serial.println("Received char: " + String(nextChar));
            jsonString.concat(nextChar);
            return;
        } else {
            Serial.println("Received JSON: " + jsonString);
            sendJsonOverHttp();
            jsonString = "";
        }
    }
}

void SerialToHttp::sendJsonOverHttp() {
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
