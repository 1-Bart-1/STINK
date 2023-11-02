#include "Communication.h"

Communication::Communication() {}

void Communication::begin(void (*callback)(JsonDocument* receivedData)) {
    sendReceiveJson.begin(callback);
    Serial.println("Communication started");
}

void Communication::sendButton(bool song_playing){
    Serial.println("Sending button info");
    StaticJsonDocument<JSON_ARRAY_SIZE(1)> data;
    data["song_playing"] = song_playing;
    serializeJson(data, Serial);
    Serial.println();
    sendReceiveJson.send(data);
}

Communication communication;