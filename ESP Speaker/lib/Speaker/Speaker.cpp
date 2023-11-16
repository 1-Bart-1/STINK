#include "Speaker.h"
#include <arduino.h>


Speaker :: Speaker(){}

void Speaker :: begin(){

}

void Speaker :: bpmCalc(){
    static bool hasStartedCounting = false;
    static unsigned long bpmMillis;
    static float bpm;

    if (hasStartedCounting == false & this->drumMsg[0] > 0){
        bpmMillis = millis();
        hasStartedCounting = true;
    }
    else if (this->drumMsg[6] > 0){
        bpm = 12/( (sizeof(this->drumMsg)/sizeof(this->drumMsg[0])) *pow(10,-3)) * 60;
        hasStartedCounting = false;
        memset(this->drumMsg, 0, sizeof(this->drumMsg));
        bpmMillis = 0;
        this->bpm = bpm;
    }
}


void Speaker :: playSound(int note, int bpm, float type){
    static bool isPlayingSound = false;
    static unsigned long soundMillis = 0;
    unsigned long currentMillis = millis();

    int duration = (60/bpm) * type * 1000; // unit ms

    if (this->isPlayingSound == false){
        tone(this->auxPin, note, duration);
        this->isPlayingSound = true;
        soundMillis = millis();
    }
    else if ((this->isPlayingSound == true) && (currentMillis > (soundMillis + duration*1.3))){
        noTone(this->auxPin);
        this->isPlayingSound = false;
    }
}

void Speaker :: playMusic(){
    static int count;
    bool wasPlayingSound = this->isPlayingSound;

    if (wasPlayingSound != this->isPlayingSound && wasPlayingSound == false){
        count++;
    }

    playSound(this->notes[count], this->bpm, this->types[count]);
}

Speaker speaker;
