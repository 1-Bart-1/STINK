#include <Arduino.h>
#include <Communication.h>
#include <Hit.h>

void sendHitCallback() {
  communication.sendHit();
}

void communicationCallback(JsonDocument* receivedData) {
  serializeJson(*receivedData, Serial);
  Serial.println();
}

void setup() {
  Serial.begin(115200);
  hit.begin(sendHitCallback);
  communication.begin(communicationCallback);
}

void loop() {
}


