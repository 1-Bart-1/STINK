#ifndef Speaker_h
#define Speaker_h

#include <arduino.h>
#include <notes.h>

class Speaker
{
    public:
        Speaker();
        void begin();
        void bpmCalc();
        void playSound(int note, int bpm, float type);
        void playMusic();

        int numberOfHits = 0;
        float bpm;
        int auxPin = 4;

    private:
        bool isPlayingSound;
        const int notes[4] = {A4, A1, A3, A5};
        const float types[4] = {quarterNote, quarterNote, quarterNote, quarterNote};
};

extern Speaker speaker;

#endif


