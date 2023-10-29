#include "Communication.h"

Communication::Communication() {}

void Communication::begin() {
    sendReceiveJson.begin();
}

void Communication::sendHit(){
    JsonObject data;
    data["time"] = millis();
    sendReceiveJson.send(address, data);
}

Communication communication;