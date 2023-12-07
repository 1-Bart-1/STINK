#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include "SendReceiveJson.h"

class Communication {
public:
    Communication();
    void begin(void (*callback)(JsonDocument* receivedData));
    void sendButton(bool song_playing);
    void sendSongInfo(JsonDocument* songInfo);
private:
    void (*_callback)();
    const uint8_t address[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
};

extern Communication communication;

#endif
