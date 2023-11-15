#include <Arduino.h>
#include <Communication.h>
#include <Hit.h>

void sendHitCallback() {
  communication.sendHit();
}

void communicationCallback(JsonDocument* receivedData) {
  serializeJson(*receivedData, Serial);
  Serial.println();
  if((*receivedData)["song_playing"] != NULL) {
    hit.song_playing = (*receivedData)["song_playing"].as<bool>();
  }
}

void setup() {
  Serial.begin(115200);
  hit.begin(sendHitCallback);
  communication.begin(communicationCallback);
}

void loop() {
}


