#include <Arduino.h>
#include <Communication.h>
#include <Hit.h>

void sendHitCallback() {
  communication.sendHit();
}

void setup() {
  Serial.begin(115200);
  hit.begin(sendHitCallback);
  communication.begin();
}

void loop() {
}


