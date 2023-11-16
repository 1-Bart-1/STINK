#include <Arduino.h>
#include <Communication.h>
#include "Speaker.h"
#include <Button.h>


void calculateBPM(JsonDocument* receivedDataPtr) {
  speaker.bpmCalc();
  speaker.monitorTime();
}


void onDataReceived(JsonDocument* receivedData){
  calculateBPM(receivedData);
}

void sendButtonCallback(bool song_playing) {
  communication.sendButton(song_playing);
}

void setup() {
  Serial.begin(115200);
  communication.begin(onDataReceived);
  button.begin(sendButtonCallback);
  speaker.begin();
}

void loop() {
  speaker.playMusic();
  speaker.update(200/*ms*/);
}