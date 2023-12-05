#include "Speaker.h"

Speaker :: Speaker(){}


void Speaker :: begin(){
    this->processSong();
    this->locationCalc(); 
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

void Speaker :: monitorLocation(){
    // when a beat from the drum happens, update live location accordingly
    this->liveLocation = this->prevLocation + 1.0f;
    this->prevLocation += 1;
}

void Speaker :: locationCalc(){
    location.push_back(0.0f); // Initialize the first element of location vector
    for (int i = 1; i < types.size(); i++) {
        location.push_back(std::accumulate(types.begin(), types.begin() + i, 0.0f));
    }
    Serial.printf("First three locations %f\t%f\t%f\n",location[0],location[1],location[2]);
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
    if (liveLocation >= 0 && songCount < location.size()) {
        if(this->liveLocation >= this->location[songCount]) {
            tone(this->auxPin, this->notes[songCount]);
            Serial.printf("\tsongCount %i \n", songCount);
            Serial.printf("\tlocation %f \n", location[songCount]);
            Serial.printf("\tnote %i \n", this->notes[songCount]);
            songCount++;
        }
    } else if (liveLocation >= 0 && songCount >= location.size()) {
        noTone(this->auxPin);
    }
}

void Speaker :: liveLocationCalc(){
    // calculates the current song location based on the bpm and the minutes passed since the last beat
    float minutesPassed = (millis() - this->lastBeatTime) / 1000.0 / 60.0;
    this->liveLocation = this->bpm * minutesPassed + this->prevLocation;
    Serial.printf("liveLocation %f \n", this->liveLocation);
}

void Speaker :: updateOnHit(){
    this->monitorLocation();
    this->bpmCalc();
}

void Speaker :: updateOnLoop(){
    this->liveLocationCalc();
    playMusic();
}

void Speaker :: reset(){
    this->prevLocation = -8;
    this->liveLocation = -8.0f;
    this->lastBeatTime = 0;
    this->bpm = 0;
    this->songCount = 0;
}


Speaker speaker;
