#ifndef STEP_H
#define STEP_H

#include "Common.h"
#include "Arduino.h"

#define STEP_PHASE_CNT      3

struct StepPosition
{
    float x;
    float y;
    float z;
    float r;
};

struct PhaseStep
{
    uint16_t timer;
    Position pos;
};

#define SPEED_MOD       2

static const PhaseStep phaseSteps[STEP_PHASE_CNT + 1] = 
{
    { 1000 / SPEED_MOD, { 10, 10, 0 } },
    { 1000 / SPEED_MOD, { 0, 0, -70 } },
    { 2000 / SPEED_MOD, { -10, -10, 0 } },
    { 1000 / SPEED_MOD, { 10, 10, 0 } },
};

class LegStep
{
public:
    LegStep(uint8_t startPhase = 0);
    void Update();
    void Reset() { phase = 0; }
    void GetCurrentPos(int &x, int &y, int &z);
    bool CalcSpeed();
    void CalcStepPerTick();

//private:
    float oldSpeedX;
    float oldSpeedY;
    uint16_t tickCnt;
    uint8_t phase; 
    uint8_t ticksPerPhase[STEP_PHASE_CNT];
    StepPosition valPerTick[STEP_PHASE_CNT]; // X, Y, Z per tick
};


#endif