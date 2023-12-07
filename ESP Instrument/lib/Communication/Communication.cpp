#include "Communication.h"

Communication::Communication() {}


void Communication::sendData(float average_sourness, float average_volume){
    static int id = 0;
    id++;
    StaticJsonDocument<JSON_ARRAY_SIZE(4)> data;
    data["id"] = id;
    data["instrument"] = "Trombone";
    data["loudness"] = average_volume;
    data["sourpercentage"] = average_sourness;
    sendReceiveJson.send(data);
}

Communication communication;