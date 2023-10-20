#include <Arduino.h>
#include <Communication.h>


void setup() {
  communication.begin();
}

void loop() {
  communication.sendData();
}