#include <Arduino.h>
#include <Communication.h>

/*
1. when song=true message received:
  a. measure and get average data
2. when song=false message received:
  a. stop measuring data
  b. send data
*/


void setup() {
  communication.begin();
}

void loop() {
  communication.sendData();
}