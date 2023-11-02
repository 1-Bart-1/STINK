#ifndef Speaker_h
#define Speaker_h
#include "notes.h"


class Speaker
{
    public:
        Speaker();
        void begin();
        void timeCalc();
        void bpmCalc();
        void playMusic();
        void monitorTime();
        void update(int updateTime);

        unsigned long drumTime[6];
        float bpm;
        int auxPin;

    private:
        int songCount;
        float liveTime;
        unsigned int prevTime;
        const int notes[3] = {C4, 2, 3};
        const float type[100];
        float time[100];
};
extern Speaker speaker;
#endif


