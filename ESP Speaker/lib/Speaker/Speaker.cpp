#include "Speaker.h"
#include <arduino.h>
#include <numeric>


Speaker :: Speaker(){}

void Speaker :: begin(int updateTime){
    this->updateTime = updateTime;
    this->timeCalc(); 
}


void Speaker :: monitorTime(){
    // when a beat from the drum happens, update live time accordingly
    this->liveTime = this->prevTime + 1.0f;
    this->prevTime += 1;
}

void Speaker :: timeCalc(){
    time[0] = 0;
    // Finds the size of the time[] array
    int timeLength = sizeof(this->time)/sizeof(this->time[0]); 
    // Inputs the timestamp in beats for each note into said array
    Serial.println(timeLength);
    for (int i = 0; i < timeLength; i++){ 
        this->time[i] = std::accumulate(this->type, this->type + i, this->time[i]);
    }
}

void Speaker :: bpmCalc(){
    static unsigned long bpmMillis = 0;
    static float current_bpm = 0;
    static unsigned long previousMillis = 0;
    static int numberOfHits = 0;

    numberOfHits++;
    if (numberOfHits <= 1){
        bpmMillis = millis();
    } else if (numberOfHits > 1) {
        unsigned long currentMillis = millis();
        float minutes = (currentMillis - previousMillis) / 60000.0; // convert milliseconds to minutes
        current_bpm = 1 / minutes;

        if (this->bpm != 0) this->bpm = (this->bpm*5 + current_bpm*1) / 6;
        else this->bpm = current_bpm;

        previousMillis = currentMillis;
    }
}


void Speaker :: playMusic(){
    // plays a new tone if the current time matches the timestamps in the time array
    static int songCount = 0;
    static int lastSongCount = 0;

    static int timeLength = sizeof(time) / sizeof(time[0]);

    if (liveTime >= 0 && songCount < timeLength) {
        if(this->liveTime >= this->time[songCount]) {
            // noTone(this->auxPin);
            tone(this->auxPin, this->notes[songCount]);
            Serial.printf("\tsongCount %i \n", songCount);
            Serial.printf("\ttime %f \n", time[songCount]);
            Serial.printf("\tnote %i \n", this->notes[songCount]);
            songCount++;
        }
    } else if (liveTime >= 0 && songCount >= timeLength) {
        noTone(this->auxPin);
    }


    // if (liveTime >= 0) {
    //     Serial.printf("songCount %i \n", songCount);
    //     for(songCount; time[songCount] < liveTime; songCount++){
    //         Serial.printf("\t\ttime %i \n", time[songCount]);
    //     };
    //     for(songCount; time[songCount + 1] > liveTime; songCount--){
    //         Serial.printf("\t\ttime %i \n", time[songCount]);
    //     };

    //     if(songCount != lastSongCount && songCount >= 0) tone(this->auxPin, this->notes[songCount]);
    //     lastSongCount = songCount;
    // }
}

void Speaker :: update(){
    static long lastTime = millis();
    long currentTime = millis();
    float deltaTime = (currentTime - lastTime) / 1000.0; // convert milliseconds to seconds
    lastTime = currentTime;

    Serial.printf("livetime %f \n", this->liveTime);
    // Serial.printf("prevTime %i \n", this->prevTime);
    if (this->bpm != 0){
        // Serial.printf("bpm %f\n", this->bpm);
        this->liveTime += deltaTime * (60.0/this->bpm);
    }

    playMusic();
}



Speaker speaker;
