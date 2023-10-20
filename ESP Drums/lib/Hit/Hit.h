#ifndef Hit_h
#define Hit_h

#include "Arduino.h"

class Hit {
    public:
        Hit(void (*callback)());
        void begin();
        void update();
    private:
        int _pin;
        int _threshold;
        int _debounceTime;
        void (*_callback)();
        unsigned long _lastDebounceTime;
        int _lastState;
};

#endif

