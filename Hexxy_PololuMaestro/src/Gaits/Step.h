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

#define SPEED_MOD       3

static const PhaseStep phaseSteps[STEP_PHASE_CNT + 1] =
{
    { 1000 / SPEED_MOD, { 10, 10, 0 } },
    { 1000 / SPEED_MOD, { 0, 0, -40 } },
    { 2000 / SPEED_MOD, { -10, -10, 0 } },
    { 1000 / SPEED_MOD, { 10, 10, 0 } },
};

class LegStep
{
public:
    LegStep(uint8_t startPhase = 0, int xMod = 0);
    void Init();
    void Update();
    //void Reset() { phase = 0; }
    void GetCurrentPos(int &x, int &y, int &z);
    void GetCurrentPos(int(&pos)[3]) { GetCurrentPos(pos[0], pos[1], pos[2]); };
    bool CalcSpeed();
    void CalcStepPerTick();

    //private:

    bool logging;

    int8_t phase;
    uint8_t _startPhase;
    float oldSpeedX;
    float oldSpeedY;
    int tickCnt;
    int ticksPerPhase[4];
    int _xMod;
    StepPosition valPerTick[STEP_PHASE_CNT]; // X, Y, Z per tick
};


#endif