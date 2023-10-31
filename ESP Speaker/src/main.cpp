#include <Arduino.h>
#include <Communication.h>

void calculateBPM(JsonDocument* receivedDataPtr) {
  serializeJson(*receivedDataPtr, Serial);
  Serial.println();

  // String hitValue = (*receivedDataPtr)["message"].as<String>();
  // Serial.println("Data received - hit: " + hitValue);
}


void onDataReceived(JsonDocument* receivedData){
  calculateBPM(receivedData);
}

void setup() {
  Serial.begin(115200);
  communication.begin(onDataReceived);
}

void loop() {
}