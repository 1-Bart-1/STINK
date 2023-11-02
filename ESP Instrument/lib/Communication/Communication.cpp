#include "Communication.h"

Communication::Communication() {}

void Communication::begin() {
    sendReceiveJson.begin(nullptr);
}

void Communication::sendData(){
    StaticJsonDocument<JSON_OBJECT_SIZE(1)> data;
    data["temp"] = 20;
    sendReceiveJson.send(data);
}

Communication communication;