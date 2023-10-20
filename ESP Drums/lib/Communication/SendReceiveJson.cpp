#include "SendReceiveJson.h"

SendReceiveJson* SendReceiveJson::instance = nullptr;

SendReceiveJson::SendReceiveJson() {
    
}

void SendReceiveJson::begin() {
    if (instance == nullptr) {
        instance = this;
        if (esp_now_init() != ESP_OK) {
            Serial.println("Error initializing ESP-NOW");
            return;
        }
        esp_now_register_send_cb(onDataSent);
        esp_now_register_recv_cb(onDataReceived);
    }
}

void SendReceiveJson::send(const uint8_t* address, const JsonObject& data) {
    // Serialize the JSON document to a string
    String json;
    serializeJson(data, json);

    // Send the JSON string
    esp_now_send(address, (uint8_t*)json.c_str(), json.length());
}

bool SendReceiveJson::receive(JsonObject& data) {
    if (Serial.available()) {
        // Read the JSON string from Serial
        String json = Serial.readString();

        // Parse the JSON string
        DynamicJsonDocument doc(MAX_DATA_SIZE);
        DeserializationError error = deserializeJson(doc, json);

        // Check for parsing errors
        if (error) {
            Serial.println("Error parsing JSON");
            return false;
        }

        // Copy the parsed JSON object to the output parameter
        data = doc.as<JsonObject>();

        return true;
    }
    return false;
}

void SendReceiveJson::onDataSent(const uint8_t* mac, esp_now_send_status_t status) {
    if (status == ESP_NOW_SEND_SUCCESS) {
        Serial.println("Data sent successfully");
    } else {
        Serial.println("Error sending data");
    }
}

void SendReceiveJson::onDataReceived(const uint8_t* mac, const uint8_t* data, int len) {
    // Parse the JSON string
    String json((char*)data);
    DynamicJsonDocument doc(MAX_DATA_SIZE);
    DeserializationError error = deserializeJson(doc, json);

    // Check for parsing errors
    if (error) {
        Serial.println("Error parsing JSON");
        return;
    }

    // Copy the parsed JSON object to a new JSON object
    JsonObject receivedData = doc.as<JsonObject>();

    Serial.println("Data received: " + receivedData["message"].as<String>());
}

SendReceiveJson sendReceiveJson;