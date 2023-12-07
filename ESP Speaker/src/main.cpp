#include <Arduino.h>
#include <Communication.h>
#include "Speaker.h"
#include <Button.h>

#include <Speaker.h>

bool song_playing = false;
int updateTime = 50;


void onDataReceived(JsonDocument* receivedData){
  // if(receivedData->containsKey("song_playing")) {
  //   song_playing = (*receivedData)["song_playing"].as<bool>();
  // }
  if(receivedData->containsKey("message") && (*receivedData)["message"].as<String>() == "Hit" && song_playing) {
    speaker.updateOnHit();
  }
  if(receivedData->containsKey("loudness")) {
    Serial.println((*receivedData)["loudness"].as<float>());
    Serial.println("trying to send");
    communication.sendSongInfo(receivedData);
  }
}

void sendButtonCallback(bool* song_playing) {
  speaker.reset();
  communication.sendButton(*song_playing);
}

void setup() {
  Serial.begin(115200);
  communication.begin(onDataReceived);
  button.begin(sendButtonCallback, &song_playing);
  speaker.begin();
}

void loop() {
  if(song_playing){
    speaker.updateOnLoop();
    delay(updateTime);
  }
}