#ifndef Speaker_h
#define Speaker_h
#include "notes.h"

#include <arduino.h>
#include <notes.h>

class Speaker
{
    public:
        Speaker();
        void begin(int updateTime);
        void timeCalc();
        void bpmCalc();
        void playMusic();
        void monitorTime();
        void update();

        unsigned long drumTime[6];
        float bpm;
        int auxPin = 4;

    private:
        int updateTime = 0;
        float liveTime = -8.0f;
        int32_t prevTime = -8;
        const int notes[4] = {NOTE_C4, NOTE_A2, NOTE_B3, 0};
        const float type[4] = {quarterNote, quarterNote, wholeNote, wholeNote};
        float time[4];
};
extern Speaker speaker;
#endif


