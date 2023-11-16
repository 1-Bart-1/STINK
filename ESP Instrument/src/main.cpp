#include <Arduino.h>
#include <Communication.h>
#include <Sound.h>

bool song_playing = false;

/*
1. when song=true message received:
  a. measure and get average data, using timed interrupt
2. when song=false message received:
  a. stop measuring data
  b. send data
*/

void communicationReceiveCb(JsonDocument* receivedData){
  serializeJson(*receivedData, Serial);
  Serial.println();
  if(receivedData->containsKey("song_playing")){
    bool was_playing = song_playing;
    song_playing = (*receivedData)["song_playing"].as<bool>();
    if(!song_playing && was_playing){
      communication.sendData(sound.getAverageSourness(), sound.getAverageVolume());
    }
  }
}

void setup() {
  Serial.begin(115200);
  sendReceiveJson.begin(communicationReceiveCb);
  sound.begin();
}

void loop() {
  if(song_playing){
    sound.update();
    delay(1000);
  }
}
