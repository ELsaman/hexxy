#ifndef GAIT_SEQUENCER_H
#define GAIT_SEQUENCER_H


#include "Gait.h"
#include "Arduino.h"

class GaitSequencer
{
public:
    GaitSequencer & instance()
    {
        static GaitSequencer sequencer;
        return sequencer;
    }

    void SetGaitSpeed(float speed) { if (speed > 0) _gait->SetSpeed(speed); }
    void Update(uint32_t diff);

private:
    Gait * _gait;

    GaitSequencer() {}
    ~GaitSequencer() {}
};

#define sGaitSequencer GaitSequencer::instance()

#endif