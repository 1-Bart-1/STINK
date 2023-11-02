#include "Sound.h"

Sound::Sound(int pin) {
    _pin = pin;
    pinMode(_pin, INPUT);
}

float Sound::getFrequency() {
    // Code to calculate frequency from sound input
    // and return the calculated frequency value
    return 0.0;
}
