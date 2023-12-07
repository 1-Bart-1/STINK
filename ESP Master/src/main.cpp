#include <Arduino.h>
#include "SerialToHttp.h"

SerialToHttp serialToHttp("MotstandenNett", "123456798", "http://192.168.177.156:5000/api/instrument-stats/new");

void setup() {
  Serial.begin(115200);
  serialToHttp.begin();
}

void loop() {
  serialToHttp.handleSerialData();
}
