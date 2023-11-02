#include "Speaker.h"
#include <arduino.h>
#include <numeric>


Speaker :: Speaker(){}

void Speaker :: begin(){
    this->timeCalc(); 
}


void Speaker :: monitorTime(){
    // when a beat from the drum happens, update live time accordingly
    this->liveTime = this->prevTime + 1;
    this->prevTime += 1;
}

void Speaker :: timeCalc(){
    time[0] = 0;
    // Finds the size of the time[] array
    int timeLength = sizeof(this->time)/sizeof(this->time[0]); 
    // Inputs the timestamp in beats for each note into said array
    for (int i; i > timeLength; i++){ 
        this->time[i] = std::accumulate(this->type, this->type + i, this->time[i]);
    }
}

void Speaker :: bpmCalc(){
    static int i = 0;
    if (i > 5){
        i = 0;
    }
    // Adds the time in ms for each drum-beat into an array
    this->drumTime[i] = millis(); 
    // Calculates the bpm using the difference in the "oldest" element in the array and the "newest" element
    if (this->drumTime[5] != 0){ 
        int valHigh = i;
        int valLow = i + 1;
        (valLow > 5) ? (valLow = 0) : (valLow = valLow);
        bpm = 12 / ((this->drumTime[valHigh] - this->drumTime[valLow]) * 1/(1000*60));
        this->bpm = bpm;
    }
    i++;
}


void Speaker :: playMusic(){
    // plays a new tone if the current time matches the timestamps in the time array
    if ((liveTime - 0.1) < time[songCount] || time[songCount] < (liveTime + 0.1)){
        tone(this->auxPin, this->notes[this->songCount]);
        songCount++;
    }
}

void Speaker :: update(int updateTime){
    // updates the current time every 200ms, based on the bpm
    static unsigned long prevMillis;
    unsigned long updateMillis = millis();

    if (updateMillis > prevMillis + updateTime){
        this->liveTime = this->prevTime + 60/this->bpm;
        prevMillis = updateMillis;
    }

}



Speaker speaker;
