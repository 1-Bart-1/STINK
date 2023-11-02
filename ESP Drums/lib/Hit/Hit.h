#ifndef Hit_h
#define Hit_h

#include "Arduino.h"
#include <Communication.h>

class Hit {
    public:
        Hit();
        void begin(void (*sendHitCallback)());
        void update();
        int pin = 2;
        int threshold = 1000;
        int debounceTime = 200;
        void (*sendHit)();
};

extern Hit hit;

extern void interruptHandler();
extern void analizeHit(void *pvParameters);

#endif

