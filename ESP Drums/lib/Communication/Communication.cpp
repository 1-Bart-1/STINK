#include "Communication.h"

Communication::Communication() {}

void Communication::begin(void (*callback)(JsonDocument* receivedData)) {
    Serial.println("Communication beginning");
    sendReceiveJson.begin(callback);
    Serial.println("Communication begun");
}

void Communication::sendHit(){
    Serial.println("Sending hit");
    StaticJsonDocument<JSON_ARRAY_SIZE(1)> data;
    data["message"] = "Hit";
    serializeJson(data, Serial);
    Serial.println();
    sendReceiveJson.send(data);
}

Communication communication;

