#ifndef Communication_H
#define Communication_H

#include "SendReceiveJson.h"
#include <ArduinoJson.h>

class Communication {
public:
    Communication();
    void begin(void (*callback)(JsonDocument* receivedData));
    void sendData(float average_sourness, float average_volume);
private:
    const uint8_t address[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
};

extern Communication communication;

#endif
