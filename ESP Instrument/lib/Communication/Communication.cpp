#include "Communication.h"

Communication::Communication() {}

void Communication::begin() {
    sendReceiveJson.begin();
}

void Communication::sendData(){
    JsonObject data;
    data["temp"] = "hot";
    sendReceiveJson.send(address, data);
}

Communication communication;