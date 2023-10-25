#include <Arduino.h>
#include <Communication.h>

void calculateBPM(JsonObject* receivedDataPtr) {
  JsonObject receivedData = *receivedDataPtr;
  Serial.println("Data received: " + receivedData["hit"].as<String>());
}

void onDataReceived(JsonObject* receivedData){
  calculateBPM(receivedData);
}

void setup() {
  Serial.begin(115200);
  communication.begin(onDataReceived);
}

void loop() {
}