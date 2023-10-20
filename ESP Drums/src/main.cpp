#include <Arduino.h>
#include <Communication.h>
#include <Hit.h>

void sendHitCallback() {
  communication.sendHit();
}

Hit hit(sendHitCallback);

void setup() {
  communication.begin();
}

void loop() {
  
}