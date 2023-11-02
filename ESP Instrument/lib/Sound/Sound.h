#ifndef SOUND_H
#define SOUND_H

#include <Arduino.h>

class Sound {
    public:
        Sound(int pin);
        float getFrequency();

    private:
        int _pin;
};

#endif
