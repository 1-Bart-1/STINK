#ifndef Button_h
#define Button_h

#include "Arduino.h"
#include <Communication.h>

class Button {
    public:
        Button();
        void begin(void (*sendButtonCallback)(bool* song_playing), bool* song_playing);
        void update();
        int pin = 2;
        int ledPin = 5;
        int debounceTime = 1000;
        bool* song_playing;
        void (*sendButton)(bool* song_playing);
};

extern Button button;

extern void interruptHandler();
extern void analizeButton(void *pvParameters);

#endif

