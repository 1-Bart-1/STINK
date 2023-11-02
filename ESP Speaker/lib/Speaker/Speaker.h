#ifndef Speaker_h
#define Speaker_h


class Speaker
{
    public:
        void begin();
        void bpmCalc();
        void playSound(int note, int bpm, float type);
        void playMusic();

        int drumMsg[6];
        float bpm;
        int auxPin;

    private:
        bool isPlayingSound;
        static const int notes[];
        static const float types[];
};

#endif


