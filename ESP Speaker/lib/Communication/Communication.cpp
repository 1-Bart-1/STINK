#include "Communication.h"

Communication::Communication() {}

void Communication::begin(void (*callback)(JsonObject* receivedData)) {
    sendReceiveJson.begin(callback);
    Serial.println("Communication started");
}

Communication communication;