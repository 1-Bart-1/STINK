#include <Arduino.h>

const int speakerPin = 4;

void setup() {
    pinMode(speakerPin, OUTPUT);
}

void loop() {
    // Play a sound on the speaker
    tone(speakerPin, 1000);
    delay(1000);

    // Stop the sound
    noTone(speakerPin);
    delay(1000);
}
