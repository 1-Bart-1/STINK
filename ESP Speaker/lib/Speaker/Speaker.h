#ifndef Speaker_h
#define Speaker_h
#include "notes.h"

#include <arduino.h>
#include <vector>
#include <numeric>
#include <notes.h>

class Speaker
{
    public:
        Speaker();
        void begin();
        void updateOnLoop();
        void updateOnHit();
        void reset();
    private:
        float bpm;
        int auxPin = 4;
        int songCount;
        void processSong();
        void timeCalc();
        void bpmCalc();
        void playMusic();
        void liveTimeCalc();
        void monitorTime();
        unsigned long lastBeatTime = 0;
        float liveTime = -8.0f;
        int32_t prevTime = -8;
        std::vector<std::vector<float>> song = {
            {NA4, NA4, NA4, NB4, NA4},
            {QN, EN, QN, EN, QN},
            {NAS4, NAS4, NAS4, NC4, NAS4},
            {QN, EN, QN, EN, QN},
            {NA4, NA4, NA4, NB4, NA4},
            {QN, EN, QN, EN, QN},
            {NA4, NG4, NF4, NDS4},
            {QN, QN, QN, QN},

            {ND4, NDS4, ND4, NDS4, NF4},
            {QN, QN, EN, QN, EN},
            {NF4, 0},
            {HN, HN},
            {ND4, NDS4, NF4, NG4, NGS4},
            {QN, QN, EN, QN, EN},
            {NGS4, 0},
            {HN, HN},
            {NG4, NGS4, NG4, NGS4, NAS4},
            {QN, QN, QN, EN, EN},
            {NAS4, NAS4, NAS4, NGS4, NG4},
            {EN, QN, EN, QN, EN},
            {NF4, NF4, NE4, NDS4, ND4},
            {QN, QN, EN, QN, EN},
            {ND4, NF5, NF5, NG5, NF5},
            {QN, EN, QN, EN, QN},
            {NDS5},
            {WN},
            {0, NDS5, NDS5, NF5, NDS5},
            {QN, EN, QN, EN, QN},
            {ND5},
            {WN},
            {ND5},
            {WN}
        };
        std::vector<int> notes;
        std::vector<float> types;
        std::vector<float> time;
};
extern Speaker speaker;
#endif


