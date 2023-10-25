#include "Communication.h"

Communication::Communication() {}

void Communication::begin() {
    Serial.println("Communication beginning");
    sendReceiveJson.begin(nullptr);
    Serial.println("Communication begun");
}

void Communication::sendHit(){
    Serial.println("Sending hit");
    JsonObject data;
    data["hit"] = 1;
    sendReceiveJson.send(address, data);
    Serial.println("Hit sent");
}

Communication communication;

