#include "Communication.h"

Communication::Communication() {}


void Communication::sendData(float average_sourness, float average_volume){
    StaticJsonDocument<JSON_ARRAY_SIZE(2)> data;
    data["average_sourness"] = average_sourness;
    data["loudness"] = average_volume;
    sendReceiveJson.send(data);
}

Communication communication;