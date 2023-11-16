#include <Arduino.h>
#include <Communication.h>
#include "Speaker.h"
#include <Button.h>

#include <Speaker.h>

bool song_playing = false;
int updateTime = 200;


void onDataReceived(JsonDocument* receivedData){
  if(receivedData->containsKey("song_playing")) {
    song_playing = (*receivedData)["song_playing"].as<bool>();
  }
  if(receivedData->containsKey("message") && (*receivedData)["message"].as<String>() == "Hit" && song_playing) {
    speaker.bpmCalc();
    speaker.monitorTime();
  }
}

void sendButtonCallback(bool* song_playing) {
  communication.sendButton(*song_playing);
}

void setup() {
  Serial.begin(115200);
  communication.begin(onDataReceived);
  button.begin(sendButtonCallback, &song_playing);
  speaker.begin(updateTime);
}

void loop() {
  if(song_playing){
    speaker.update();
    delay(updateTime);
  }
}