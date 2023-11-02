#include <Arduino.h>
#include <Communication.h>
#include "Speaker.h"


void calculateBPM(JsonDocument* receivedDataPtr) {
  speaker.bpmCalc();
  speaker.monitorTime();
}


void onDataReceived(JsonDocument* receivedData){
  calculateBPM(receivedData);
}

void setup() {
  Serial.begin(115200);
  communication.begin(onDataReceived);
  speaker.begin();
}

void loop() {
  speaker.playMusic();
  speaker.update(200/*ms*/);
}