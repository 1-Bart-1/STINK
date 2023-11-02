#ifndef Communication_H
#define Communication_H

#include "SendReceiveJson.h"

class Communication {
public:
    Communication();
    void begin(void (*callback)(JsonDocument* receivedData));
    void sendHit();
private:
    const uint8_t address[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
};

extern Communication communication;

#endif
