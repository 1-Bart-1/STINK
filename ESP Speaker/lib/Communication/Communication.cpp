#include "Communication.h"

Communication::Communication() {}

void Communication::begin(void (*callback)(JsonDocument* receivedData)) {
    sendReceiveJson.begin(callback);
    Serial.println("Communication started");
}

Communication communication;