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
    if (abs(time[songCount] - liveTime) < ((float)this->updateTime/1000.0)){
        tone(this->auxPin, this->notes[songCount]);
        songCount++;
    }
}

void Speaker :: update(){
    Serial.printf("livetime %f \n", this->liveTime);
    Serial.printf("prevTime %i \n", this->prevTime);
    if (this->bpm != 0){
        Serial.printf("bpm %f\n", this->bpm);
        this->liveTime = (float)this->prevTime + 60.0/this->bpm;
    }

    if (this->liveTime>=0){
        playMusic();
    }
}



Speaker speaker;
