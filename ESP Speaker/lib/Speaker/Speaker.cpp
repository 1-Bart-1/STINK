#include "Speaker.h"

Speaker :: Speaker(){}


void Speaker :: begin(){
    this->processSong();
    this->timeCalc(); 
}

void Speaker :: processSong() {
    for (int i = 0; i < 32; i++) {
        for (int j = 0; j < 5; j++) {
            if (i % 2 == 0) {
                this->notes.push_back(this->song[i][j]);
            } else {
                this->types.push_back(this->song[i][j]);
            }
        }
    }
    
    Serial.printf("First three notes %i\t%i\t%i\n",notes[0],notes[1],notes[2]);
    Serial.printf("First three types %f\t%f\t%f\n",types[0],types[1],types[2]);
}

void Speaker :: monitorTime(){
    // when a beat from the drum happens, update live time accordingly
    this->liveTime = this->prevTime + 1.0f;
    this->prevTime += 1;
}

void Speaker :: timeCalc(){
    time.push_back(0.0f); // Initialize the first element of time vector
    for (int i = 1; i < types.size(); i++) {
        time.push_back(std::accumulate(types.begin(), types.begin() + i, 0.0f));
    }
    Serial.printf("First three times %f\t%f\t%f\n",time[0],time[1],time[2]);
}

void Speaker :: bpmCalc(){
    unsigned long currentBeatTime = millis();
    
    if (lastBeatTime == 0) {
        lastBeatTime = currentBeatTime;
        return;
    }

    float beatInterval = (currentBeatTime - lastBeatTime) / 1000.0;
    lastBeatTime = currentBeatTime;

    if (beatInterval <= 0) {
        return;
    }
    float currentBpm = 60.0 / beatInterval;

    if (this->bpm != 0) {
        this->bpm = (this->bpm + currentBpm*5) / 6;
    } else {
        this->bpm = currentBpm;
    }
    Serial.printf("bpm %f\n", this->bpm);
}


void Speaker :: playMusic(){
    if (liveTime >= 0 && songCount < time.size()) {
        if(this->liveTime >= this->time[songCount]) {
            tone(this->auxPin, this->notes[songCount]);
            Serial.printf("\tsongCount %i \n", songCount);
            Serial.printf("\ttime %f \n", time[songCount]);
            Serial.printf("\tnote %i \n", this->notes[songCount]);
            songCount++;
        }
    } else if (liveTime >= 0 && songCount >= time.size()) {
        noTone(this->auxPin);
    }
}

void Speaker :: liveTimeCalc(){
    // calculates the current song time based on the bpm and the minutes passed since the last beat
    float minutesPassed = (millis() - this->lastBeatTime) / 1000.0 / 60.0;
    this->liveTime = this->bpm * minutesPassed + this->prevTime;
    Serial.printf("livetime %f \n", this->liveTime);
}

void Speaker :: updateOnHit(){
    this->monitorTime();
    this->bpmCalc();
}

void Speaker :: updateOnLoop(){
    this->liveTimeCalc();
    playMusic();
}

void Speaker :: reset(){
    this->prevTime = -8;
    this->liveTime = -8.0f;
    this->lastBeatTime = 0;
    this->bpm = 0;
    this->songCount = 0;
}


Speaker speaker;
