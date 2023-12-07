#include "SerialToHttp.h"

SerialToHttp serialToHttp("MotstandenNett", "123456798", "http://10.22.35.177:3000/api/instrument-stats/new");

void setup() {
  Serial.begin(115200);
  serialToHttp.begin();
}

void loop() {
  serialToHttp.handleSerialData();
}
