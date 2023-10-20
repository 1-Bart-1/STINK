#include "Hit.h"

Hit::Hit(void (*callback)()) {
    _callback = callback;
    _lastDebounceTime = 0;
    _lastState = LOW;
}

void Hit::begin() {
    pinMode(_pin, INPUT);
}

void Hit::update() {
    int reading = analogRead(_pin);
    int state = LOW;
    if (reading > _threshold) {
        state = HIGH;
    }
    if (state != _lastState) {
        _lastDebounceTime = millis();
    }
    if ((millis() - _lastDebounceTime) > _debounceTime) {
        if (state != _lastState) {
            _lastState = state;
            if (_lastState == HIGH) {
                _callback();
            }
        }
    }
}
